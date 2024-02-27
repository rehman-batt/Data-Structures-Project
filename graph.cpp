#include "graph.h"

Graph::Graph()
{
	V = 0;
	adj = NULL;
	file = false;
}

Graph::Graph(int n) {
	V = n;
	adj = new LinkedList[V];
	file = false;
}

void Graph::setFileEncoding(int* encoding) {
	this->encoding = encoding;
	file = true;
}

void Graph::setVertices(int n) {
	V = n;
	adj = new LinkedList[V];
}
//Graph::~Graph() {
//	delete[] adj;
//}

void Graph::addEdge(int v, int w) {
	adj[v].insertAtHead(w);
}

void Graph::printGraph() {
	for (int i = 0; i < V; i++) {
		if (file == false)
		{
			cout << i << " -> ";
		}
		else
		{
			cout << encoding[i] << " -> ";
		}
		Node* temp = adj[i].get_head();
		while (temp != NULL)
		{
			if (file == false)
			{
				cout << temp->get_data() << " -> ";
			}
			else
			{
				cout << encoding[temp->get_data()] << " -> ";
			}
			temp = temp->get_next();
		}
		cout << endl;
	}
}


void Graph::sinkNodes()
{
	int count = 0;
	for (int i = 0; i < V; i++) {
		Node* temp = adj[i].get_head();
		if (temp == NULL)
		{
			count++;
		}
	}

	cout << "No of Sink Nodes: " << count;
}

void Graph::sourceNodes()
{
	int count = 0;
	for (int i = 0; i < V; i++)
	{
		if (in_Degree[i] == 0)
		{
			count++;
		}
	}

	cout << "No of Source Nodes: " << count;
}

void Graph::inDegree()
{
	in_Degree = new int[V];
	for (int i = 0; i < V; i++) {
		in_Degree[i] = 0;
	}
	for (int i = 0; i < V; i++) {
		Node* temp = adj[i].get_head();
		while (temp != NULL)
		{
			in_Degree[temp->get_data()]++;
			temp = temp->get_next();
		}
	}
	for (int i = 0; i < V; i++) {
		if (file== false)
		{
			cout << i << " -> " << in_Degree[i] << endl;
		}
		else
		{
			cout << encoding[i] << " -> " << in_Degree[i] << endl;
		}
	}
}



void Graph::outDegree()
{
	out_Degree = new int[V];
	for (int i = 0; i < V; i++) {
		out_Degree[i] = 0;
	}
	for (int i = 0; i < V; i++) {
		Node* temp = adj[i].get_head();
		while (temp != NULL)
		{
			out_Degree[i]++;
			temp = temp->get_next();
		}
	}
	for (int i = 0; i < V; i++) {
		if (file == false)
		{
			cout << i << " -> " << out_Degree[i] << endl;
		}
		else
		{
			cout << encoding[i] << " -> " << out_Degree[i] << endl;
		}
	}
}


void Graph::IsolatedNodes()
{
	int count = 0;
	for (int i = 0; i < V; i++)
	{
		if (in_Degree[i] == 0 && out_Degree[i] == 0)
		{
			count++;
		}
		
	}

	cout << "No of Isolated Nodes: " << count;
}

void Graph::printEdgesHelper(int node, int parent, int* vis, int* tin, int* low, int& timer, int& counter) {
	vis[node] = 1;
	tin[node] = low[node] = timer++;
	
	Node* temp = adj[node].get_head();
	while (temp != NULL)
	{
		int it = temp->get_data();

		if (it == parent)
		{
			continue;
		}

		if (!vis[it]) {
			printEdgesHelper(it, node, vis, tin, low, timer, counter);
			low[node] = (low[node] < low[it]) ? low[node] : low[it];
			if (low[it] > tin[node]) {
				counter++;
			}
		}
		else {
			low[node] = (low[node] < tin[it]) ? low[node] : tin[it];
		}

		temp = temp->get_next();
	}
}

	
void Graph::printBridgeEdges()
{
	int count = 0;
	
	int* tin = new int[V];
	for (int i = 0; i < V; i++)
	{
		tin[i] = -1;
	}
		
	int* low = new int[V];
	
	for (int i = 0; i < V; i++)
	{
		low[i] = -1;
	}
	
	int* vis = new int[V];

	for (int i = 0; i < V; i++)
	{
		vis[i] = 0;
	}
	
	int timer = 0;
	
	for (int i = 0; i < V; i++) {
		if (!vis[i]) {
			printEdgesHelper(i, -1, vis, tin, low, timer, count);
		}
	}

	cout << "The no. of Bridge Edges are: " << count << endl;

	delete[] vis;
	delete[] low;
	delete[] tin;
}



void Graph::printArticulationHelper(int node, int parent, int* vis, int* tin, int* low, int& timer, int* isArticulation)
{
	vis[node] = 1;
	tin[node] = low[node] = timer++;
	int child = 0;

	Node* temp = adj[node].get_head();
	while (temp != NULL)
	{
		int it = temp->get_data();

		if (it == parent)
		{
			continue;
		}

		if (!vis[it]) {
			printArticulationHelper(it, node, vis, tin, low, timer, isArticulation);
			
			low[node] = (low[node] < low[it]) ? low[node] : low[it];
			child++;
			if (low[it] >= tin[node] && parent != -1) {
				isArticulation[node] = 1;
			}
		}
		else {
			low[node] = (low[node] < tin[it]) ? low[node] : tin[it];
		}
		temp = temp->get_next();
	}

	if (parent == -1 && child > 1) {
		isArticulation[node] = 1;
	}
	
}




void Graph::printArticulationNodes()
{
	int count = 0;

	int* tin = new int[V];

	for (int i = 0; i < V; i++)
	{
		tin[i] = -1;
	}

	int* low = new int[V];

	for (int i = 0; i < V; i++)
	{
		low[i] = -1;
	}

	int* vis = new int[V];

	for (int i = 0; i < V; i++)
	{
		vis[i] = 0;
	}

	int* isArticulation = new int[V];

	for (int i = 0; i < V; i++)
	{
		isArticulation[i] = 0;
	}

	int timer = 0;

	for (int i = 0; i < V; i++) {
		if (!vis[i]) {
			printArticulationHelper(i, -1, vis, tin, low, timer, isArticulation);
		}
	}

	for (int i = 0; i < V; i++) {
		if (isArticulation[i] == 1)
		{
			count++;
		}
	}

	cout << "The no. of Articulation Nodes are: " << count << endl;

	delete[] vis;
	delete[] low;
	delete[] tin;
	delete[] isArticulation;
}

void Graph::pathLengthDistribution()
{
	int* dist = new int[V];
	int diameter = INT_MIN;

	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++)
		{
			dist[j] = INT_MAX;
		}

		Queue q;

		dist[i] = 0;

		q.enQueue(i);

		while (q.isEmpty() == false)
		{
			int node = q.showFront();
			q.deQueue();

			Node* temp = adj[node].get_head();
			while (temp != NULL)
			{
				int it = temp->get_data();
				if (dist[node] + 1 < dist[it]) {
					dist[it] = dist[node] + 1;
					q.enQueue(it);
				}
				temp = temp->get_next();
			}
		}
		
		if (file == false)
		{
			cout << "Source Node: " << i << endl;
		}
		else
		{
			cout << "Source Node: " << encoding[i] << endl;
		}

		for (int k = 0; k < V; k++)
		{
			if ((dist[k] != INT_MAX) && (dist[k] > diameter))
			{
				diameter = dist[k];
			}
			if (dist[k] != INT_MAX)
			{
				if (file == false)
				{
					cout << k << ": " << dist[k] << "\t";
				}
				else
				{
					cout << encoding[k] << ": " << dist[k] << "\t";
				}
			}
			else
			{
				if (file==false)
				{
					cout << k << ": " << "inf" << "\t";
				}
				else
				{
					cout << encoding[k] << ": " << "inf" << "\t";
				}
				
			}
		}
		cout << endl << endl;
	}
	
	cout << "Diameter of Graph: " << diameter;
	cout << endl << endl;

	delete[] dist;
}


void Graph::findWeaklyConnectedComponents()
{
	int max = INT_MIN;
	bool* vis = new bool[V];
	for (int i = 0; i < V; i++)
	{
		vis[i] = false;
	}

	Stack stack;

	for (int q = 0; q < V; q++)
	{
		if (!vis[q])
		{
			stack.push(q);


			LinkedList component;

			while (!stack.isEmpty())
			{
				int v = stack.peek();
				stack.pop();

				if (!vis[v])
				{
					vis[v] = true;


					component.insertAtHead(v);

					Node* temp = adj[v].get_head();
					while (temp != NULL)
					{
						int w = temp->get_data();
						if (!vis[w]) {
							stack.push(w);
						}
						temp = temp->get_next();
					}
				}
			}

			int count = 0;
			cout << "WCC: ";
			Node* comp = component.get_head();

			

			while (comp != NULL)
			{
				count++;
				if (file == false)
				{
					cout << comp->get_data() << " ";
				}
				else
				{
					cout << encoding[comp->get_data()] << " ";
				}
				comp = comp->get_next();
			}
			

			cout << endl;
			cout << "Size of WCC: " << count << endl;

			if (count > max)
			{
				max = count;
			}
		}
	}

	cout << "The size of the largest WCC: " << max << endl;

	delete[] vis;
}

void Graph::fillOrder(int s, bool* vis, Stack& stack) 
{	
	vis[s] = true;

	Node* temp = adj[s].get_head();

	while (temp != NULL)
	{
		if (!vis[temp->get_data()])
		{
			fillOrder(temp->get_data(), vis, stack);
		}
		temp = temp->get_next();
	}

	stack.push(s);
}

void Graph::graphTransopse(Graph& g) {


	for (int s = 0; s < V; s++) {

		Node* temp = adj[s].get_head();
		
		while (temp != NULL)
		{
			g.addEdge(temp->get_data(), s);
			temp = temp->get_next();
		}
	}


}

int scc = 0;

void Graph::DFS(int s, bool* vis) {
	vis[s] = true;
	if (file == false)
	{
		cout << s << " ";
	}
	else
	{
		cout << encoding[s] << " ";
	}
	scc++;
	Node* temp = adj[s].get_head();
	
	while (temp != NULL)
	{
		if (!vis[temp->get_data()])
		{
			DFS(temp->get_data(), vis);
		}
		temp = temp->get_next();
	}
}

void Graph::findStronglyConnectedComponents()
{
	int max = INT_MIN;
	Stack stack;

	bool* vis = new bool[V];

	for (int i = 0; i < V; i++)
	{
		vis[i] = false;
	}

	for (int i = 0; i < V; i++)
	{
		if (vis[i] == false)
		{
			fillOrder(i, vis, stack);
		}
	}

	Graph tempGraph(V);
	
	graphTransopse(tempGraph);

	for (int i = 0; i < V; i++)
	{
		vis[i] = false;
	}

	while (!stack.isEmpty())
	{
		int s = stack.peek();
		stack.pop();
		
		if (vis[s] == false)
		{
			scc = 0;
			cout << "SCC: ";
			tempGraph.DFS(s, vis);
			cout << endl << "Size of SCC: " << scc << endl << endl;
			if (max < scc)
			{
				max = scc;
			}
		}
	}

	cout << endl << "The size of max SCC: " << max << endl << endl;
	
	delete[] vis;
}