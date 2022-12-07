// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// This is the main driver for creating minimum cost spanning trees of adjacency matrix graphs
// This program was written collaborativly by Chandler Whitley and James Dorough
// The textbook was used as a source for this project
// The Prim and minVertex algorithms were taken from the book with modifications

#include <iostream>
#include "Graphm.h"
using namespace std;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const int VISITED = 1;
const int UNVISITED = 0;


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Finds minium vertex in a graph that has not been visited 
int minVertex(Graphm* G, int* D);

// Prim's MST algorithm
Graphm * Prim(Graphm* G, int* D, int s);


int main()
{
	cout << "Lab 5 - Riley Dorough" << endl << endl;

	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Graphm * OriginalGraph1 = new Graphm(6);
	OriginalGraph1->inputGraph("inputGraph.txt");
	OriginalGraph1->printGraph();
	
	cout << endl << "Begin MST 1 starting at vertex 0  \n\n";
	int * D1 = new int[OriginalGraph1->n()];
	for (int i = 0; i < OriginalGraph1->n(); i++)
	{
		D1[i] = 9999;
	}
	D1[0] = 0;
	Graphm * MSTVertex0 = Prim(OriginalGraph1, D1, 0);
	MSTVertex0->outputgraph("MSTGraphVertex_0.txt");
	

	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Graphm * OriginalGraph2 = new Graphm(6);
	OriginalGraph2->inputGraph("inputGraph.txt");

	cout << endl << "Begin MST 2 starting at vertex 4 \n\n";
	int * D2 = new int[OriginalGraph2->n()];
	for (int i = 0; i < OriginalGraph2->n(); i++)
	{
		D2[i] = 9999;
	}
	D2[4] = 0;
	Graphm * MSTVertex4 = Prim(OriginalGraph2, D2, 4);
	MSTVertex4->outputgraph("MSTGraphVertex_4.txt");
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Graphm * OriginalGraph3 = new Graphm(6);
	OriginalGraph3->inputGraph("inputGraph.txt");

	cout << endl << "Begin MST 3 starting at vertex 2 \n\n";
	int * D3 = new int[OriginalGraph3->n()];
	for (int i = 0; i < OriginalGraph3->n(); i++)
	{
		D3[i] = 9999;
	}
	D3[2] = 0;
	Graphm * MSTVertex2 = Prim(OriginalGraph3, D3, 2);
	MSTVertex2->outputgraph("MSTGraphVertex_2.txt");
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	system("pause");
	return 0;
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Prim's MST algorithm
Graphm * Prim(Graphm* G, int* D, int s)
{
	Graphm * someMSTGraph = new Graphm(G->n());
	int * V = new int[G->n()]; // Store closest vertex
	int i, w;
	for (i = 0; i < G->n(); i++) { // Process the vertices
		int v = minVertex(G, D);
		G->setMark(v, VISITED);

		if (v != s)
		{
			std::cout << "Add edge " << V[v] << " to " << v << "; weight: " << D[v] << std::endl;
			someMSTGraph->setEdge(v, V[v], D[v]); //AddEdgetoMST(V[v], v); // Add edge to MST . . .  V[v] is current, need to pass in previous as well
			someMSTGraph->setEdge(V[v], v, D[v]);
		}
		if (D[v] == 9999) return G; // Unreachable vertices
		for (w = G->first(v); w < G->n(); w = G->next(v, w))
			if (D[w] > G->weight(v, w)) {
				D[w] = G->weight(v, w); // Update distance
				V[w] = v; // Where it came from
			}
	}

	return someMSTGraph;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// MinVertex function taen from the textbook
int minVertex(Graphm* G, int* D) { // Find min cost vertex
	int i, v = -1;
	// Initialize v to some unvisited vertex
	for (i = 0; i < G->n(); i++)
		if (G->getMark(i) == UNVISITED) { v = i; break; }
	for (int i = 0; i < G->n(); i++) // Now find smallest D value
		if ((G->getMark(i) == UNVISITED) && (D[i] < D[v]))
		{
			v = i;
		}
	return v;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++