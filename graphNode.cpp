#include <iostream>
#include "graphNode.h"
using namespace std;
GraphNode::GraphNode() {
	_key = 0;
	_visited = false;
};
GraphNode::GraphNode(int key) {
	_key = key;
	_visited = false;

};
int GraphNode::getKey() {
	return _key;
};
void GraphNode::setKey(int value) {
	_key = value;
};

bool GraphNode::getVisited() {
	return _visited;
};
void GraphNode::setVisited(bool value) {
	_visited = value;
};

void GraphNode::addEdge(edge value) {
	_edges.push_back(value);
};

int GraphNode::getNumberOfEdges() {
	return _edges.size();
};

int GraphNode::getComponent() {
	return _component;
};

void GraphNode::setComponent(int value) {
	_component = value;
};