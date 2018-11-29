#ifndef GRAPH_EXCEPTIONS_H
#define GRAPH_EXCEPTIONS_H

#include <string>
using namespace std;

// Vynimkova trieda pre situaciu, ked vrchol
// 'vertexName' v grafe neexistuje.
class VertexMissingException {
private:
	string description;
public:
	VertexMissingException(string vertexName) {
		description += "\nVertex \'" + vertexName + "\' is missing.\n";
	}
	string getDescription() { return this->description; }
};

// Vynimkova trieda pre situaciu, ked vrchol
// 'vertexName' uz v grafe existuje.
class VertexDuplicateException {
private:
	string description;
public:
	VertexDuplicateException(string vertexName) {
		description += "\nVertex \'" + vertexName + "\' is a duplicate.\n";
	}
	string getDescription() { return this->description; }
};

// Vynimkova trieda pre situaciu, ked hrana
// z vrcholu 'vertexName1' do 'vertexName2'
// v grafe neexistuje.
class EdgeMissingException {
private:
	string description;
public:
	EdgeMissingException(string vertexName1, string vertexName2) {
		description += "\nEdge from \'" + vertexName1 + "\' to \'" + vertexName2 + "\' is missing.\n";
	}
	string getDescription() { return this->description; }
};

// Vynimkova trieda pre situaciu, ked hrana
// z vrcholu 'vertexName1' do 'vertexName2'
// uz v grafe existuje.
class EdgeDuplicateException {
private:
	string description;
public:
	EdgeDuplicateException(string vertexName1, string vertexName2) {
		description += "\nEdge from \'" + vertexName1 + "\' to \'" + vertexName2 + "\' is a duplicate.\n";
	}
	string getDescription() { return this->description; }
};

#endif // GRAPH_EXCEPTIONS_H
