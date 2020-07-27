#include <iostream>
#include <fstream>
#include "graph.h"
#include "graphNode.h"
#include <string>
#include <sstream>
#include <list>
#include <queue>
using namespace std;

Graph::Graph() {
	_anzKnoten = 0;
	_ger = false;
	_gew = true;
}
Graph::~Graph() {
	for (int i = 0; i < _anzKnoten; i++) {
		delete _nodes[i];
	}
}
bool Graph::init(string filename) {
	ifstream file;
	file.open(filename, std::ios_base::in);
	if (!file) {
		std::cout << "Cannot open file." << std::endl;
		return false;
	}
	else {
		string line;
		getline(file, line);
		istringstream iss(line);
		iss >> _anzKnoten; //Erste Zeile Auslesen
		 //Alle Knoten anlegen
		for (int i = 0; i < _anzKnoten; i++) {
			GraphNode* v = new GraphNode(i);
			_nodes.push_back(v);
		}
		//Alle Kanten anlegen
		while (std::getline(file, line)) {
			istringstream iss(line);
			int u, v, gew;
			iss >> u >> v >> gew;
			edge e1{ u, v, gew };
			_nodes[u]->addEdge(e1);
			edge e2{ v, u, gew };
			_nodes[v]->addEdge(e2);
		}
		return true;
	}
	return false;
}
bool Graph::printAll() {
	for (int i = 0; i < _anzKnoten; i++) {
		GraphNode* v = _nodes[i];
		cout << v->getKey();
		for (int j = 0; j < v->getNumberOfEdges(); j++) {
			edge e = v->getEdge(j);
			cout << "  -> " << e.destination << " [" << e.gewicht << "]";
		}
		cout << endl;
	}
	return true;
}

bool Graph::depthSearchRek(int startKey) {
	setAllUnvisited();
	startDepthSearchRek(_nodes[startKey]);
	return checkVisited();
}

void Graph::startDepthSearchRek(GraphNode* node) {
	if (node->getVisited()) {
		return;
	}
	node->setVisited(true);
	cout << node->getKey() << " ";
	for (int i = 0; i < node->getNumberOfEdges(); i++) {
		startDepthSearchRek(_nodes[node->getEdge(i).destination]);
	}
}


bool Graph::breadthSearchIter(int startKey) {
	setAllUnvisited();
	list<int> queue;
	_nodes[startKey]->setVisited(true);
	queue.push_back(startKey);
	while (!queue.empty()) {
		int v = queue.front();
		queue.pop_front();
		_nodes[v]->setVisited(true);
		cout << _nodes[v]->getKey() << " ";
		for (int i = 0; i < _nodes[v]->getNumberOfEdges(); i++) {
			int w = _nodes[v]->getEdge(i).destination;
			if (!_nodes[w]->getVisited()) {
				_nodes[w]->setVisited(true);
				queue.push_back(w);
			}
		}
	}
	return checkVisited();
}

double Graph::prim(int startKey) {

	setAllUnvisited();
	auto cmp = [](edge a, edge b) { return a.gewicht > b.gewicht; };
	std::priority_queue<edge, std::vector<edge>, decltype(cmp)> queue(cmp);

	int mst = 0;

	// visit(queue, startKey);
	_nodes[startKey]->setVisited(true);
	for (int j = 0; j < _nodes[startKey]->getNumberOfEdges(); j++) {
		int other = _nodes[startKey]->getEdge(j).destination;
		if (!_nodes[other]->getVisited())
			queue.push(_nodes[startKey]->getEdge(j));
	}


	while (!queue.empty()) {
		edge e = queue.top();
		queue.pop();
		int v = e.source;
		int w = e.destination;
		if (_nodes[v]->getVisited() && _nodes[w]->getVisited())
			continue;
		mst += e.gewicht;
		if (!_nodes[v]->getVisited()) {
			_nodes[v]->setVisited(true);
			for (int j = 0; j < _nodes[v]->getNumberOfEdges(); j++) {
				int other = _nodes[v]->getEdge(j).destination;
				if (!_nodes[other]->getVisited())
					queue.push(_nodes[v]->getEdge(j));
			}
		}
		if (!_nodes[w]->getVisited()) {
			_nodes[w]->setVisited(true);
			for (int j = 0; j < _nodes[w]->getNumberOfEdges(); j++) {
				int other = _nodes[w]->getEdge(j).destination;
				if (!_nodes[other]->getVisited())
					queue.push(_nodes[w]->getEdge(j));
			}
		}
	}

	return mst;
}

double Graph::kruskal() {

	double mst = 0;

	auto cmp = [](edge a, edge b) { return a.gewicht > b.gewicht; };
	std::priority_queue<edge, std::vector<edge>, decltype(cmp)> queue(cmp);

	for (int i = 0; i < _nodes.size(); i++) {
		_nodes[i]->setComponent(i);
		for (int j = 0; j < _nodes[i]->getNumberOfEdges(); j++) {
			if (i < _nodes[i]->getEdge(j).destination)
				queue.push(_nodes[i]->getEdge(j));
		}
	}

	while (!queue.empty()) {
		edge e = queue.top();
		queue.pop();
		int u = e.source;
		int v = e.destination;
		if (_nodes[u]->getComponent() != _nodes[v]->getComponent()) {
			mst += e.gewicht;
			int c = _nodes[v]->getComponent();
			for (int i = 0; i < _nodes.size(); i++) {
				if (_nodes[i]->getComponent() == c)
					_nodes[i]->setComponent(_nodes[u]->getComponent());
			}
		}
	}

	return mst;
}

int Graph::getAnzKnoten() {
	return _anzKnoten;
}

GraphNode* Graph::GetNodeByKey(int key) {
	return _nodes.at(key);
}

void Graph::setAllUnvisited() {
	for (int i = 0; i < _anzKnoten; i++) {
		_nodes[i]->setVisited(false);
	}
}

bool Graph::checkVisited() {
	for (int i = 0; i < _anzKnoten; i++) {
		if (!_nodes[i]->getVisited())
			return false;
	}
	return true;
}


bool Graph::testChildComponent(GraphNode* node) {
	return true;
}
