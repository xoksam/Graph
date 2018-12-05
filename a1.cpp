#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <list>
#include <initializer_list>
#include <utility>
#include <tuple>
#include <stack>
#include <queue>
#include <map>
#include <algorithm>

// hlavickove subory s definiciami vynimkovych tried
#include "graph_exceptions.h"
#include "path_exceptions.h"

// hlavickovy subor s definiciou triedy 'Path', ktora
// reprezentuje cestu v grafe
#include "path.h"

using namespace std;


// Tema: Graf
// Typ grafu: orientovany, hranovo-ohodnoteny, zakazane viacnasobne 
// hrany a duplicitne vrcholy.
// Styl implementacie: zoznam susedov (z angl. adjacency list)

// Vyhody:
//		* pridavanie/odstranovanie vrcholov je efektivne
//		* rychle zistenie vsetkych susedov vrcholu
//		* setri pamat, zabera priestor O(|V|+|E|), matica susednosti zabera
//		* rychly vypocet vystupneho stupna vrcholu
// Nevyhody:
//		* neefektivne operacie ako pridanie/odstranenie hrany
//		* neefektivne zistenie, ci medzi 2 vrcholmi existuje hrana


class GraphAsAdjacencyList {
	struct Vertex; // forward deklaracia struktury 'Vertex'

	// struktura reprezentujuca vystupnu hranu v grafe
	struct EdgeTo {
		Vertex * endVertex; // koncovy vrchol hrany
		int length; // dlzka hrany
		EdgeTo(Vertex * endVertex, int length) :
			endVertex(endVertex), length(length)
		{};
		bool operator ==(const EdgeTo& other) {
			return (this->endVertex == other.endVertex && this->length == other.length);
		}
	};

	// struktura reprezentujuca vrchol grafu, v ktorej je uvedeny
	// jeho nazov a zoznam vystupnych hran
	struct Vertex {
		string name; // nazov vrcholu
		list<EdgeTo> edges; // zoznam vystupnych hran
		Vertex(string name) :
			name(name)
		{};
		bool operator ==(const Vertex& other) {
			return (this->name == other.name);
		}
	};

	list<Vertex> vertices; // zoznam vsetkych vrcholov grafu

	// TODO 0.1
	// Funkcia vrati referenciu na vrchol
	// s menom 'vertexName'. Ak sa dany vrchol 
	// v grafe nenajde, vyhodi sa vynimka typu
	// 'VertexMissingException'.
	//
	// Vyhadzuje vynimky:
	//		* VertexMissingException
	//
	Vertex& getVertex(string vertexName) {
		//for(auto v : vertices) {
		//	if(v.name == vertexName) return v;
		//}
		list<Vertex>::iterator it = find_if(vertices.begin(), vertices.end(), [&vertexName](Vertex &v) {
			return v.name == vertexName;
		});
		if(it != vertices.end()) return *it;

		throw VertexMissingException(vertexName);
	}

	// TODO 0.2
	// Funkcia vrati referenciu na vystupnu hranu
	// z vrcholu 'vertexName1' do vrcholu 'vertexName2'.
	// Ak sa v grafe 'vertexName1' alebo 'vertexName2' 
	// nenachadza, vyhodi sa vynimka typu 'VertexMissingException'. 
	// Ak uvedene vrcholy nie su spojene hranou, vyhodi sa 
	// vynimka typu 'EdgeMissingException'.
	//
	// Vyhadzuje vynimky:
	//		* VertexMissingException
	//		* EdgeMissingException
	EdgeTo& getEdge(string vertexName1, string vertexName2) {
		Vertex &start = getVertex(vertexName1);
		Vertex &end = getVertex(vertexName2);
		
		for(EdgeTo &e : start.edges) {
			if(e.endVertex == &end) return e;
		}
		throw EdgeMissingException(vertexName1, vertexName2);
	}

public:
	// default konstruktor
	GraphAsAdjacencyList() {

	}
	// TODO 1
	// Funkcia vrati true/false, podla toho,
	// ci vrchol 'vertexName' v grafe existuje/neexistuje.
	//
	// Vyhadzuje vynimky: ziadne
	//
	bool containsVertex(string vertexName) {
		try {
			Vertex &v = getVertex(vertexName);
			return true;
		}
		catch(VertexMissingException &e) {
			return false;
		}
	}

	// TODO 2
	// Funkcia vrati true/false, podla toho,
	// ci hrana z 'vertexName1' do 'vertexName2' existuje/neexistuje.
	//
	// Vyhadzuje vynimky: ziadne
	//
	bool containsEdge(string vertexName1, string vertexName2) {
		try {
			EdgeTo &e = getEdge(vertexName1, vertexName2);
			return true;
		}
		catch(VertexMissingException &ex) {
			return false;
		}
		catch(EdgeMissingException &ee) {
			return false;
		}
	}

	// TODO 3
	// Funkcia prida vrchol 'vertexName' do grafu.
	// Ak sa vrchol v grafe uz nachadza, tak vyhodi 
	// vynimku typu 'VertexDuplicateException'.
	//
	// Vyhadzuje vynimky:
	//		* VertexDuplicateException
	//
	void addVertex(string vertexName) {
		if(containsVertex(vertexName)) {
			throw VertexDuplicateException(vertexName);
		}
		this->vertices.push_back(Vertex(vertexName));
	}

	// TODO 4
	// Funkcia prida hranu z vrcholu 'vertexName1' do 
	// 'vertexName2' s dlzkou 'length'.
	// Ak sa vrchol 'vertexName1' alebo 'vertexName2' v 
	// grafe nenachadza, vyhodi sa vynimka 'VertexMissingException'.
	// Ak sa taka hrana v grafe uz nachadza, vyhodi sa vynimka 
	// 'EdgeDuplicateException'.
	//
	// Vyhadzuje vynimky:
	//		* VertexMissingException
	//		* EdgeDuplicateException
	void addEdge(string vertexName1, string vertexName2, int length) {
		Vertex &start = getVertex(vertexName1);
		Vertex &end = getVertex(vertexName2);

		if(containsEdge(vertexName1, vertexName2)) {
			throw EdgeDuplicateException(vertexName1, vertexName2);
		}
		start.edges.push_back(EdgeTo(&end, length));
	}

	// TODO 5
	// Funkcia, ktora vrati textovu reprezentaciu grafu.
	// Textova reprezentacia bude obsahovat vsetky vrcholy
	// grafu a ich zoznam vystupnych hran s uvedenim cieloveho
	// vrcholu hrany a jej dlzky.
	//
	// Vyhadzuje vynimky: ziadne
	//
	string toString() {
		string str;
		for(Vertex &v : this->vertices) {
			str += v.name + ": ";
			for(EdgeTo &e : v.edges) {
				str += e.endVertex->name + "(" + to_string(e.length) + "), ";
			}
			str += "\n";
		}
		return str;
	}

	// TODO 6
	// Funkcia odstrani vrchol 'vertexName' z grafu.
	// Funkcia odstrani aj prislusne hrany.
	// Ak sa vrchol v grafe nenachadza, tak vyhodi 
	// vynimku typu 'VertexMissingException'.
	//
	// Vyhadzuje vynimky:
	//		* VertexMissingException
	//
	void removeVertex(string vertexName) {
		Vertex &vert = getVertex(vertexName);

		for(Vertex &v : vertices) {
			for(auto it = v.edges.begin(); it != v.edges.end(); ) {
				if((*it).endVertex->name == vertexName) {
					it = v.edges.erase(it); // Vracia novy platny iterator
					//removeEdge(v.name, vertexName);
					continue;
				}
				it++;
			}
		}
		vertices.remove(vert);
	}

	// TODO 7
	// Funkcia odstrani hranu z 'vertexName1' do 'vertexName2'.
	// Ak sa vrchol 'vertexName1' alebo 'vertexName2' v grafe 
	// nenachadza, tak vyhodi vynimku typu 'VertexMissingException'.
	// Ak sa hrana z 'vertexName1' do 'vertexName2' v grafe 
	// nenachadza, tak vyhodi vynimku typu 'EdgeMissingException'.
	//
	// Vyhadzuje vynimky:
	//		* VertexMissingException
	//		* EdgeMissingException
	//
	void removeEdge(string vertexName1, string vertexName2) {
		Vertex &v1 = getVertex(vertexName1);
		Vertex &v2 = getVertex(vertexName2);

		EdgeTo &e = getEdge(v1.name, v2.name);
		v1.edges.remove(e);
	}

	// TODO 8
	// Funkcia vrati vektor nazvov susednych vrcholov
	// vrcholu 'vertexName'. Susedny vrchol je taky, 
	// s ktorym je vrchol 'vertexName' spojeny vystupnou 
	// hranou. Ak sa vrchol 'vertexName' v grafe nenachadza,
	// vyhodi sa vynimka typu 'VertexMissingException'.
	//
	// Vyhadzuje vynimky:
	//		* VertexMissingException
	//
	vector<string> neighbors(string vertexName) {
		Vertex v = getVertex(vertexName);
		vector<string> res;
		for(EdgeTo &e : v.edges) { // Prebehnem vsetky hrany incidujuce s vrcholom 'v'
			res.push_back(e.endVertex->name); // Do resultu pushnem nazov vrchola do ktoreho smeruje hrana s 'v'
		}
		return res;
	}

	// TODO 9
	// Funkcia, ktora vrati vektor nazvov vsetkych vrcholov v grafe.
	//
	// Vyhadzuje vynimky: ziadne
	//
	vector<string> getVertexNames() {
		vector<string> res;
		for(Vertex &v : this->vertices) 
			res.push_back(v.name);
		return res;
	}


	// TODO 10
	// Funkcia vrati vstupny stupen vrcholu 'vertexName'.
	// Vstupny stupen vrcholu hovori kolko hran do neho vstupuje. 
	// Ak sa vrchol 'vertexName' v grafe nenachadza,
	// vyhodi sa vynimka typu 'VertexMissingException'.
	//
	// Vyhadzuje vynimky:
	//		* VertexMissingException
	//
	int inDegree(string vertexName) {
		Vertex &v = getVertex(vertexName);
		int degree = 0;
		for(Vertex &ve : vertices) {
			for(EdgeTo &e : ve.edges) {
				if(e.endVertex == &v) degree++;
			}
		}

		return degree;
	}

	// TODO 11
	// Funkcia vrati vystupny stupen vrcholu 'vertexName'.
	// Vystupny stupen vrcholu hovori kolko hran z neho vystupuje. 
	// Ak sa vrchol 'vertexName' v grafe nenachadza,
	// vyhodi sa vynimka typu 'VertexMissingException'.
	//
	// Vyhadzuje vynimky:
	//		* VertexMissingException
	//
	int outDegree(string vertexName) {
		Vertex v = getVertex(vertexName);
		return v.edges.size();
	}

	// TODO 12
	// Funkcia vrati postupnost navstivenych vrcholov pocas
	// prechodu grafom do hlbky z vrcholu 'startVertexName'. 
	// Ak sa vrchol 'startVertexName' v grafe nenachadza, 
	// vyhodi sa vynimka typu 'VertexMissingException'.
	//
	// Vyhadzuje vynimky:
	//		* VertexMissingException
	//
	list<string> dfs(string startVertexName) {
		Vertex *start = &getVertex(startVertexName);
		stack<Vertex*> stack;
		list<string> res;

		map<Vertex*, bool> visitedNodes; // Musi to byt iba refernica na classu ... Inak to NEJDE 
										// Preto su vsade * :D
		for(Vertex &v : vertices) visitedNodes[&v] = false; // Na zaciatku su vsetky oznacene ako nenavstivene

		stack.push(start); 
		// Klasika z Diskretnej Matematiky :D
		while(!stack.empty()) {
			Vertex *v = stack.top(); // Ulozim si prvy vrchol v stacku
			stack.pop();
			if(!visitedNodes[v]) { // Ak som este nenavstivil 'v'
				visitedNodes[v] = true; // Tak ho navstivim :D
				res.push_back(v->name); // A do vlozim ho do vysledku

				for(EdgeTo e : v->edges) { 
					if(!visitedNodes[e.endVertex]) stack.push(e.endVertex);
				}
			}
		}

		return res;
	}

	// TODO 13
	// Funkcia najde a vrati cestu ('Path') z vrcholu 
	//	'startVertexName' do vrcholu 'endVertexName' 
	// pomocou prehladavania grafu do hlbky (Depth First Search). 
	// Ak sa vrchol 'startVertexName' alebo 'endVertexName' 
	// v grafe nenachadza, vyhodi sa vynimka typu 'VertexMissingException'. 
	// Ak graf neobsahuje cestu z 'startVertexName' do 'endVertexName',
	// vyhodi sa vynimka typu 'NoPathException'.
	//
	// Vyhadzuje vynimky:
	//		* VertexMissingException
	//		* NoPathException
	//
	Path dfs_Path(string startVertexName, string endVertexName) {
		return Path();
	}

	// TODO 14
	// Funkcia vrati postupnost navstivenych vrcholov pocas
	// prechodu grafom do sirky z vrcholu 'startVertexName'. 
	// Ak sa vrchol 'startVertexName' v grafe nenachadza, 
	// vyhodi sa vynimka typu 'VertexMissingException'.
	//
	// Vyhadzuje vynimky:
	//		* VertexMissingException
	//
	list<string> bfs(string startVertexName) {
		Vertex *start = &getVertex(startVertexName);
		queue<Vertex*> q;
		list<string> res;

		map<Vertex*, bool> visitedNodes;

		for(Vertex &v : vertices) visitedNodes[&v] = false;
		
		visitedNodes[start] = true;

		res.push_back(start->name);
		q.push(start);

		while(!q.empty()) {
			Vertex *v = q.front();
			q.pop();

			for(EdgeTo &e : v->edges) {
				if(!visitedNodes[e.endVertex]) {
					visitedNodes[e.endVertex] = true;
					res.push_back(e.endVertex->name);
					q.push(e.endVertex);
				}
			}

		}

		return res;
	}

	// TODO 15
	// Funkcia najde a vrati cestu ('Path') z vrcholu 
	//	'startVertexName' do vrcholu 'endVertexName' 
	// pomocou prehladavania grafu do sirky (Breadth First Search). 
	// Ak sa vrchol 'startVertexName' alebo 'endVertexName' 
	// v grafe nenachadza, vyhodi sa vynimka typu 'VertexMissingException'. 
	// Ak graf neobsahuje cestu z 'startVertexName' do 'endVertexName',
	// vyhodi sa vynimka typu 'NoPathException'.
	//
	// Vyhadzuje vynimky:
	//		* VertexMissingException
	//		* NoPathException
	//
	Path bfs_Path(string startVertexName, string endVertexName) {
		return Path();
	}


	// TODO 16
	// Funkcia najde najkratsiu cestu z 'startVertexName' do 'endVertexName'.
	// Ak 'startVertexName' alebo 'endVertexName' neexistuju, vyhodi sa vynimka
	// typu 'VertexMissingException'. Ak neexistuje medzi nimi cesta, vyhodi sa
	// 'NoPathException'.
	Path dijkstra(string startVertexName, string endVertexName) {
		return Path();
	}


	// EXTRA uloha
	// Konstruktor, ktory vytvori graf z dodaneho 
	// inicializacneho zoznamu. 
	//
	// Format jedneho prvku inicializacneho zoznamu:
	// {nazov zdrojoveho vrcholu, zoznam vystupnych hran }
	//
	// Priklad inicializacneho zoznamu pre graf z webstranky cvicenia:
	// 
	//	{ "A",	{ {"C", 9}, {"D", 10}, {"F", 14}, {"H", 1}, {"I", 3} } }, 
	//	{ "B",	{ {"A", 7} } },
	//  { "C",	{ {"D", 8} } },
	//	{ "D",	{ {"A", 2} } },
	//	{ "E",	{ } },
	//	{ "F",	{ } },
	//	{ "G",	{ {"A", 2}, {"F", 4} } },
	//	{ "H",	{ {"D", 5}, {"G", 3} } },
	//	{ "I",	{ {"C", 1} } }
	//
	// Poznamka: vrcholy uvedene v zozname vystupnych hran budu rovno pridane do grafu.
	//
	// Vyhadzuje vynimky: ziadne
	//
	GraphAsAdjacencyList(initializer_list<pair<string, list<pair<string, int>>>> init_list) {
		
	}
};

int main() {
	GraphAsAdjacencyList g;
	vector<string> graphVertices = {"A", "B", "C", "D", "E", "F", "G", "H", "I"};
	// TODO: riadne otestujte operacie v grafe a spravne odchytavajte vynimky
	try {
		for(string &v : graphVertices) 
			g.addVertex(v);
		
		vector<tuple<string, string, int>> graphEdges = {
			make_tuple("A", "C", 9), make_tuple("A", "D", 10), make_tuple("A", "F", 14), make_tuple("A", "H", 1), make_tuple("A", "I", 3),
			make_tuple("B", "A", 7), 
			make_tuple("C", "D", 8), 
			make_tuple("D", "A", 2),
			make_tuple("G", "A", 2), make_tuple("G", "F", 4),
			make_tuple("H", "D", 5), make_tuple("H", "G", 3),
			make_tuple("I", "C", 1)};


		for(auto t : graphEdges) {
			g.addEdge(get<0>(t), get<1>(t), get<2>(t));
		}
	
		cout << g.toString() << endl;
	/*	g.removeEdge("B", "A");
		cout << g.toString() << endl;

		g.removeEdge("X", "E");
	*/
		//g.removeVertex("A");
		cout << g.toString() << endl;
		
		for(auto s : g.getVertexNames()) {
			cout << s << " ";
		}

	}
	catch(VertexDuplicateException &ve) {
		cout << ve.getDescription() << endl;
	} 
	catch(EdgeDuplicateException &ee) {
		cout << ee.getDescription() << endl;
	}
	catch(EdgeMissingException &em) {
		cout << em.getDescription() << endl;
	}
	catch(VertexMissingException &ve) {
		cout << ve.getDescription() << endl;
	}

	// TODO 8 - neighbors
	cout << endl << "TODO 8" << endl;
	cout << "Neighbors of A: ";
	vector<string> A_neighbors = g.neighbors("A");
	for(string& n : A_neighbors) { cout << n << " "; }
	cout << endl << "Neighbors of D: ";
	vector<string> D_neighbors = g.neighbors("D");
	for(string& n : D_neighbors) { cout << n << " "; }
	//cout << endl << "Neighbors of P: ";
	//vector<string> P_neighbors = g.neighbors("P"); // odkomentujte, co sa stane?
	//for (string& n : P_neighbors) { cout << n << " "; }

	// TODO 9 - getVertexNames
	cout << endl << endl << "TODO 9" << endl;
	cout << "All vertices in the graph: ";
	vector<string> all_vertex_names = g.getVertexNames();
	for(string& v : all_vertex_names) { cout << v << " "; }

	// TODO 10 - inDegree
	cout << endl << endl << "TODO 10" << endl;
	cout << "In-degree:" << endl;
	for(const string& n : all_vertex_names) { cout << n << ": " << g.inDegree(n) << endl; }

	// TODO 11 - outDegree
	cout << endl << "TODO 11" << endl;
	cout << "Out-degree:" << endl;
	for(const string& n : all_vertex_names) { cout << n << ": " << g.outDegree(n) << endl; }

	// TODO 12 - dfs

	cout << endl << "TODO 12" << endl;
	list<string> visited_sequence;
	cout << "DFS(A): ";
	visited_sequence = g.dfs("A");
	for(string s : visited_sequence) { cout << s << " "; }
	cout << endl << "DFS(B): ";
	visited_sequence = g.dfs("B");
	for(string s : visited_sequence) { cout << s << " "; }
	cout << endl << "DFS(F): ";
	visited_sequence = g.dfs("F");
	for(string s : visited_sequence) { cout << s << " "; }
	cout << endl;

	// TODO 14 - bfs
	cout << endl << "TODO 14" << endl;
	list<string> visited_sequence2;
	cout << "BFS(A): ";
	visited_sequence2 = g.bfs("A");
	for(string s : visited_sequence2) { cout << s << " "; }
	cout << endl << "BFS(H): ";
	visited_sequence2 = g.bfs("H");
	for(string s : visited_sequence2) { cout << s << " "; }
	cout << endl << "BFS(F): ";
	visited_sequence2 = g.bfs("F");
	for(string s : visited_sequence2) { cout << s << " "; }
	cout << endl;

	system("pause");
	return 0;
}