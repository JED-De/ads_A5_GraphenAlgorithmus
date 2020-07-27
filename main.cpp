#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include <iostream>
#include "graph.h"
#include "graphNode.h"
using namespace std;

void Color(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int main() {

	/*Catch::Session().run();*/
	int eingabe = -1;
	int gesucht = -1;
	int graph = -1;
	Graph* test1 = new Graph();
	Graph* test2 = new Graph();
	Graph* test3 = new Graph();
	Graph* test = new Graph();
	Color(14);
	cout << "Working on Graphs. Please choose:" << endl;
	Color(7);
	while (eingabe != 0) {
		cout << "1) Graph einlesen\n2) Tiefensuche\n3) Breitensuche\n4) Prim\n5) Kruskal\n6) Print Graph\n0 zum beenden" << endl;
		cout << "Ihre Eingabe: ";
		cin >> eingabe;
		cout << endl;
		switch (eingabe) {
		case 1:
			cout << "Welcher Graph?: ";
			cin >> graph;
			if (graph == 1) {
				test1->init("graph1.txt");
				test = test1;
			}
			else if (graph == 2) {
				test2->init("graph2.txt");
				test = test2;
			}
			else if (graph == 3) {
				test3->init("graph3.txt");
				test = test3;
			}
			cout << "Datein wurden eingelesen." << endl << endl;
			break;
		case 2:
			cout << "Startknoten: ";
			cin >> gesucht;
			cout << "Rekursive Tiefensuche: ";
			test->depthSearchRek(gesucht);
			cout << endl << endl;
			break;
		case 3:
			cout << "Startknoten: ";
			cin >> gesucht;
			cout << "Iterative Breitensuche: ";
			test->breadthSearchIter(gesucht);
			cout << endl << endl;
			break;
		case 4:
			cout << "Startknoten: ";
			cin >> gesucht;
			cout << "Kosten durch Prim Methode: " << test->prim(gesucht);
			cout << endl << endl;
			break;
		case 5:
			cout << "Kosten durch Kruskal Methode: " << test->kruskal();
			cout << endl << endl;
			break;
		case 6:
			test->printAll();
			cout << "Alle Datein wurden erfolgreich gegeben.";
			cout << endl << endl;
			break;
		}
	}
	

	system("PAUSE");
	return 0;
}