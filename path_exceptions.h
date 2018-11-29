#ifndef PATH_EXCEPTIONS_H
#define PATH_EXCEPTIONS_H

#include <string>
using namespace std; 

// Vynimkova trieda pre situaciu, ked neexistuje
// cesta z vrcholu 'vertexName1' do vrcholu 'vertexName2'.
class NoPathException {
private:
	string description;
public:
	NoPathException(string vertexName1, string vertexName2) {
		description += "\nThere is no path from \'" + vertexName1 + "\' to \'" + vertexName2 + "\'.\n";
	}
	string getDescription() { return this->description; }
};

// Vynimkova trieda pre situaciu, ked je cesta prazdna.
class PathEmptyException {
private:
	string description;
public:
	PathEmptyException() {
		description += "\nPath is empty.\n";
	}
	string getDescription() { return this->description; }
};

// Vynimkova trieda pre situaciu, ked vrchol 'vertexName' 
// nema v ceste predchodcu.
class NoPredecessorInPathException {
private:
	string description;
public:
	NoPredecessorInPathException(string vertexName) {
		description += "\nThere is no predecessor for vertex \'" + vertexName + "\' in a given path.\n";
	}
	string getDescription() { return this->description; }
};

#endif // PATH_EXCEPTIONS_H

