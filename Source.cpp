#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <algorithm>
#include "Graph.h"

using namespace std;

bool readFromFile(string &src, unsigned &vertex, unsigned &edge, vector<pair<unsigned, unsigned>> &edges) {
	edges.clear();
	fstream file;
	file.open(src, ios::in);
	if (!file.good())
		return false;

	file >> vertex;
	unsigned v1, v2;
	pair<unsigned, unsigned> p;
	while (file.good()) {
		file >> v1 >> v2;
		if (file.fail()) break; //sprawdzenie czy to juz byl koniec danych
		p = make_pair(min(v1, v2), max(v1, v2));
		edges.push_back(p);
	}
	edge = edges.size();
	file.close();
	return true;
}
int main() {
	unsigned v=0, e=0;
	unsigned delV1, delV2, putV1, putV2;
	vector<pair<unsigned, unsigned>> edges; //vector trzymajacy pary wierzcholkow, czyli poszczegolne krawedzi
	string src = "graf1.txt";

	if (!readFromFile(src, v, e, edges)) //wczytanie z pliku grafu
		return -1;
	cout << "Graf oryginalny:" << endl;
	Graph g(v, e, edges);
	g.printGraph();
	cout << "//////////////////////" << endl;

	for (unsigned i = 0; i < edges.size(); ++i) { //usuwanie kolejnych krawedzi wraz z ich wierzcholkami
		vector<pair<unsigned, unsigned>> tempEdges;
		unsigned tempE=0, tempV=v-2;
		delV1 = edges[i].first; //usuwany wierzcholek 1
		delV2 = edges[i].second; //usuwany wierzcholek 2
		for (unsigned x = 0; x < edges.size(); ++x) {
			putV1 = edges[x].first;
			putV2 = edges[x].second;
			if (x == i || putV1 == delV1 || putV1 == delV2 || putV2 == delV1 || putV2 == delV2) continue; //nie dodajemy takiej krawedzi
			
			if (putV1 > delV2) {
				putV1 -= 2;
			}
			else if (putV1 > delV1) {
				putV1 -= 1;
			}
			if (putV2 > delV2) {
				putV2 -= 2;
			}
			else if (putV2 > delV1) {
				putV2 -= 1;
			}
			++tempE;
			tempEdges.push_back(make_pair(putV1, putV2));
		}
		Graph tempGraph(tempV, tempE, tempEdges);
		cout << "Graf " << i <<" Usunieto: "<<delV1<<" "<<delV2<< endl;
		tempGraph.printGraph();
		if (!tempGraph.checkConnectivity()) {
			cout << "**********Most rozlegly: " << delV1 << " " << delV2 << endl;
		}
	}
	system("pause");
	return 0;
}