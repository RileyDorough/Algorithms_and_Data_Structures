// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// This file is an implementation of the GraphADT file.
// The standrad graph operations are taken from the textbook with modifications
// This program was compiled/ written by Chandler Whitley and James Dorough
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include "GraphADT.h"
#include <iostream>
#include <string>
#include <fstream>
#include <memory>

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Source code from the textbook pages 389-390
// Implementation for the adjacency matrix representation
//
// Please note: the mark bits for graph nodes are modified to use smart pointers!
// Specifically, the mark private data member is a smart pointer to an array of integers
//
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class Graphm : public GraphADT {
private:
	int numVertex, numEdge;		 // Store number of vertices, edges
	int **matrix;				 // Pointer to adjacency matrix
	std::unique_ptr<int[]> mark; // Smart pointer to mark array
	const int VISITED = 1;		 // constants for each of the node's mark bit
	const int UNVISITED = 0;

public:
	Graphm(int numVert) // Constructor
	{
		Init(numVert);
	}

	~Graphm() { // Destructor
		//we no longer need to delete the pointer to mark array because it is a smart pointer
		for (int i = 0; i < numVertex; i++)
			delete[] matrix[i];
		delete[] matrix;
	}

	void Init(int n) { // Initialize the graph
		int i;
		numVertex = n;
		numEdge = 0;
		//mark = new int[n]; // Initialize mark array
		mark = std::unique_ptr<int[]>(new int[n]);

		for (i = 0; i < numVertex; i++)
			mark[i] = UNVISITED; // Modified so that 0 = UNVISITED
		matrix = (int**) new int*[numVertex]; // Make matrix
		for (i = 0; i < numVertex; i++)
			matrix[i] = new int[numVertex];
		for (i = 0; i < numVertex; i++) // Initialize to 0 weights
			for (int j = 0; j < numVertex; j++)
				matrix[i][j] = 0;
	}

	int n() { return numVertex; }	// Number of vertices
	int e() { return numEdge; }		// Number of edges

	// Return first neighbor of "v"
	int first(int v) {
		for (int i = 0; i < numVertex; i++)
			if (matrix[v][i] != 0) return i;
		return numVertex; // Return n if none
	}

	// Return v’s next neighbor after w
	int next(int v, int w) {
		for (int i = w + 1; i < numVertex; i++)
			if (matrix[v][i] != 0)
				return i;
		return numVertex; // Return n if none
	}

	// Set edge (v1, v2) to "wt"
	// This function was modified to only add an edge if the weight is greater than 0
	void setEdge(int v1, int v2, int wt) {
		// Modified to use conditional statement instead of "Assert"
		if (wt < 0)
			std::cout << "\nIllegal weight value\n";
		if (matrix[v1][v2] == 0)
		{
			if (wt > 0)
			{
				numEdge++;
			}
		}
		matrix[v1][v2] = wt;
	}

	void delEdge(int v1, int v2) { // Delete edge (v1, v2)
		if (matrix[v1][v2] != 0) numEdge--;
		matrix[v1][v2] = 0;
	}

	bool isEdge(int i, int j) // Is (i, j) an edge?
	{
		return matrix[i][j] != 0;
	}

	int weight(int v1, int v2) { return matrix[v1][v2]; }
	int getMark(int v) { return mark[v]; }
	void setMark(int v, int val) { mark[v] = val; }

	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// This function was not taken from the textbook
	// This function takes as input a filename and reads in an adjacency matrix graph
	void inputGraph(std::string filename)
	{ 
		// Open up the input file
		std::ifstream graphin;
		graphin.open(filename);

		if (!graphin)
		{
			std::cout << "failed to open input file.\n";
		}
	
		// variables to keep track of data
		int col{ n() };
		int row{ n() };
		int** myArray;

		// Read in the information
		
		// First create the rows
		myArray = new int*[col];
		for (int i = 0; i < row; i++)
		{
			myArray[i] = new int[col];
		}

		for (int i = 0; i < row; i++)
		{
			// Fill up the rows for the number of columns
			for (int j = 0; j < col; j++)
			{
				int val;
				graphin >> val;
				myArray[i][j]  = val;
				setEdge(i, j, val);
			}
		}
	}
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	void printGraph()
	{
		std::cout << "Number of verticies: " << n() << std::endl;
		std::cout << "Number of edges: " << e() << std::endl;
		std::cout << "\nMatrix is: \n";
		int col{ n() };
		int row{ n() };

		for (int i = 0; i < row; i++)
		{
			// Fill up the rows for the number of columns
			for (int j = 0; j < col; j++)
			{
				std::cout << matrix[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}



	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// This function was not taken from the textbook
	// This function takes as input a filename and output an adjacency matrix graph to a file with that name
	void outputgraph(std::string filename)
	{
		std::cout << std::endl;
		std::ofstream graphOutput;
		graphOutput.open(filename);
		int col{ n() };
		int row{ n() };

		// process each element and output a new line when necessary
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				graphOutput << matrix[i][j] << " ";
				std::cout << matrix[i][j] << " "; // also display the graph on the command line
			}
			graphOutput << "\n";
			std::cout << "\n";
		}
	}
	// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
};
