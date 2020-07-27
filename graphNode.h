#pragma once
#include <iostream>
#include <vector>
using namespace std;

struct edge {
	int source;
	int destination;
	int gewicht;
};

class GraphNode {
private:
	int _key;
	vector<edge> _edges;
	bool _visited;
	int _component;

public:
	GraphNode();
	GraphNode(int key);
	int getKey();
	void setKey(int value);
	bool getVisited();
	void setVisited(bool value);
	void addEdge(edge value);
	edge getEdge(int value){
		return _edges[value];
	};
	int getNumberOfEdges();
	int getComponent();
	void setComponent(int value);
};