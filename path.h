#ifndef PATH_H
#define PATH_H

#include <algorithm>
#include <string>
#include <list>
using namespace std;

// vynimky
#include "graph_exceptions.h"
#include "path_exceptions.h"

// Trieda 'Path' reprezentuje cestu v grafe,
// ktora je tvorena postupnostou hran.
class Path {
	// Struktura 'Edge' predstavuje jednu hranu v ceste
	struct Edge { // jeden usek cesty
		string endVertexName; // cielovy vrchol
		int length; // dlzka hrany k cielovemu vrcholu
		Edge(string endVertexName, int length) :
			endVertexName(endVertexName),
			length(length)
		{}
	};
	string startVertexName; // startovaci vrchol
	list<Edge> edges; // vsetky hrany cesty okrem startovacieho vrcholu
public:
	// Default konstruktor
	Path() {}

	// Konstruktor s parametrom
	Path(string startVertexName):
		startVertexName(startVertexName)
	{}
	// Funkcia, ktora prida do cesty na zaciatok novu hranu
	void addEdgeToFront(string endVertexName, int length) {
		this->edges.push_front({ endVertexName,length});
	}
	// Funkcia, ktora odstrani poslednu hranu z cesty
	void removeLastEdge() {
		if (!this->edges.empty()) {
			this->edges.pop_back();
		}
	}
	// Funkcia, ktora odstrani poslednu hranu z cesty
	void removeFirstEdge() {
		if (!this->edges.empty()) {
			this->edges.pop_front();
		}
	}
	// Funkcia, ktora vrati meno koncoveho vrcholu v poslednej hrane cesty. 
	string getLastVertexName() {
		if (!this->edges.empty()) {
			return this->edges.back().endVertexName;
		}
		throw PathEmptyException();
	}

	// Funkcia, ktora vrati, ci je cesta prazdna.
	bool isEmpty() {
		return this->edges.empty();
	}

	// Funkcia, ktora vrati textovu reprezentaciu cesty.
	string toString() {
		string str;
		str += this->startVertexName;
		for (const Edge& e : this->edges) {
			str += " ---> " + e.endVertexName + "(" + to_string(e.length) + ")";
		}
		return str;
	}
};

#endif // PATH_H
