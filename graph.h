#pragma once
#include "Header.h"

class Graph {
public:
	Graph();
	Graph(int n);
	void setVertices(int n);
	void addEdge(int v, int w);
	void sinkNodes();
	void inDegree();
	void outDegree();
	void sourceNodes();
	void IsolatedNodes();
	void printBridgeEdges();
	void printArticulationNodes();
	void pathLengthDistribution();
	void findWeaklyConnectedComponents();
	void findStronglyConnectedComponents();
	void graphTransopse(Graph& g);
	void DFS(int s, bool* vis);
	void printGraph();
	void setFileEncoding(int* encoding);
private:
	int V;
	bool file;
	int* encoding;
	LinkedList* adj;
	int* in_Degree = NULL;
	int* out_Degree = NULL;
	void fillOrder(int s, bool* vis, Stack& stack);
	void printEdgesHelper(int node, int parent, int* vis, int* tin, int* low, int& timer, int& counter);
	void printArticulationHelper(int node, int parent, int* vis, int* tin, int* low, int& timer, int* isArticulation);
};

