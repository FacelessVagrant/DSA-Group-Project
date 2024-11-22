#include <iostream>
#include <vector>
#include <queue>
#include <utility> 

using namespace std;

#define INF 1000000 // large constant to represent "infinity"

class Graph {
	int V; // number of vertices
	vector<pair<int, int>>* adj; //adjacency list (vertex, weight)

public:

	Graph(int V) {
		this->V = V;
		adj = new vector<pair<int, int>>[V];
	}

	void addEdge(int u, int v, int w) {
		adj[u].push_back(make_pair(v, w)); //add edge u -> v with weight w
		adj[v].push_back(make_pair(u, w));
	}

	// function to implement Prim's Algorithm
	void primMST() {
		// priority queue to store (value, vertex)
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

		// arrays to store the MST state
		vector<int> value(V, INF); // store the minimum weight
		vector<int> parent(V, -1);    // store the parent
		vector<bool> inMST(V, false); // track whether a vertex 

		// start from vertex 0
		value[0] = 0;
		pq.push(make_pair(0, 0)); //push the first vertex

		while (!pq.empty()) {
			int u = pq.top().second; // get the vertex with the smallest value
			pq.pop();

			if (inMST[u]) continue; // skip if already in the MST

			inMST[u] = true;

			// search all neighbors of vertex `u`
			for (auto neighbor : adj[u]) {
				int v = neighbor.first;  // neighbor vertex
				int weight = neighbor.second; // weight of the edge (u, v)

				// ff v is not in the MST and weight is smaller than the current value
				if (!inMST[v] && weight < value[v]) {
					value[v] = weight;
					pq.push(make_pair(value[v], v)); // push updated value to the priority queue
					parent[v] = u; // update the parent of vertex `v`
				}
			}
		}

		// print the edges in the MST
		cout << "Edges in MST:\n";
		bool mstExists = false;
		for (int i = 1; i < V; ++i) { // start from 1 (vertex 0 has no parent)
			if (parent[i] != -1) { 
				mstExists = true;
				cout << parent[i] << " - " << i << endl;
			}
		}

		if (!mstExists) {
			cout << "No MST could be formed. Check the input graph.\n";
		}
	}
};

int main() {
	int V = 8; // nmber of vertices
	Graph g(V); 
    g.addEdge(0, 1, 5);
    g.addEdge(0, 4, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 7, 2);
    g.addEdge(3, 6, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 3);

	g.primMST();

	return 0;
}
