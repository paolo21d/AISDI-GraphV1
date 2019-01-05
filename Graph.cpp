#include "Graph.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <stack>
#include <fstream>

using namespace std;

Graph::Graph() {
	vertex = 0;
	edge = 0;
	adjList = nullptr;
}

Graph::Graph(const unsigned &v, const unsigned &e, const vector<pair<unsigned, unsigned>>& edges) {
	vertex = v;
	edge = e;
	adjList = new vector<unsigned>[vertex];
	unsigned v1, v2;
	for (unsigned i = 0; i < edge; ++i) {
		v1 = edges[i].first;
		v2 = edges[i].second;
		adjList[v1].push_back(v2);
		adjList[v2].push_back(v1);
	}
	for (unsigned i = 0; i < vertex; ++i) { //posortowanie list s¹siedztwa
		sort(adjList[i].begin(), adjList[i].end());
	}
}


Graph::~Graph() {
	if (adjList != nullptr)
		delete[] adjList;
}

void Graph::inputGraph() {
	cin >> vertex >> edge;
	adjList = new vector<unsigned>[vertex]; //zaalokowanie pamiêci na listê s¹siedztwa
	unsigned v1, v2;
	for (unsigned i = 0; i < edge; ++i) { //wczytanie krawedzi do list sasiedztwa
		cin >> v1 >> v2;
		adjList[v1].push_back(v2);
		adjList[v2].push_back(v1);
	}

	for (unsigned i = 0; i < vertex; ++i) { //posortowanie list s¹siedztwa
		sort(adjList[i].begin(), adjList[i].end());
	}
}

bool Graph::inputGraphFromFile(string src) {
	fstream file;
	file.open(src, ios::in);
	if (!file.good())
		return false;

	file >> vertex;
	adjList = new vector<unsigned>[vertex]; //zaalokowanie pamiêci na listê s¹siedztwa
	unsigned v1, v2;
	while (file.good()) {
		file >> v1 >> v2;
		if (file.fail()) break; //sprawdzenie czy to juz byl koniec danych
		++edge;
		adjList[v1].push_back(v2);
		adjList[v2].push_back(v1);
	}

	for (unsigned i = 0; i < vertex; ++i) { //posortowanie list s¹siedztwa
		sort(adjList[i].begin(), adjList[i].end());
	}

	file.close();
	return true;
}

bool Graph::checkConnectivity() {
	vector<bool>visited;
	unsigned v, u, vc = 0;
	for (int i = 0; i < vertex; ++i) visited.push_back(false);
	stack<unsigned> s;

	if (vertex == 0) return true; //graf pusty traktujemy jako spojny

	s.push(0);
	visited[0] = true;
	while (!s.empty()) {
		v = s.top();
		s.pop();
		++vc;
		for (int i = 0; i < adjList[v].size(); ++i) {
			u = adjList[v][i];
			if (!visited[u]) {
				visited[u] = true;
				s.push(u);
			}
		}
	}

	if (vc == vertex) return true;
	else return false;
}

void Graph::getBridges() {
}

void Graph::printGraph() {
	cout << "Vertex: " << vertex << "\tEdge: " << edge << endl;
	for (int i = 0; i < vertex; ++i) {
		cout << "V " << i << ":\t";
		for (int x = 0; x < adjList[i].size(); ++x)
			cout << adjList[i][x] << " ";
		cout << endl;
	}
}
