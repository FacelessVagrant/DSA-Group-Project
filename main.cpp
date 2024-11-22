#include <iostream>
#include <vector>
#include <queue>
#include <utility> 

using namespace std;

#define INF 1000000 // A large constant to represent "infinity"

class Graph {
	int V; // Number of vertices
	vector<pair<int, int>>* adj; // Adjacency list (vertex, weight)

public:
	// Constructor
	Graph(int V) {
		this->V = V;
		adj = new vector<pair<int, int>>[V];
	}

	// Function to add an edge
	void addEdge(int u, int v, int w) {
		adj[u].push_back(make_pair(v, w)); // Add edge u -> v with weight w
		adj[v].push_back(make_pair(u, w)); // Undirected: also add v -> u
	}

	// Function to implement Prim's Algorithm
	void primMST() {
		// Priority queue to store (value, vertex)
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

		// Arrays to store the MST state
		vector<int> value(V, INF); // Store the minimum weight to add each vertex
		vector<int> parent(V, -1);    // Store the parent of each vertex in the MST
		vector<bool> inMST(V, false); // Track whether a vertex is included in the MST

		// Start from vertex 0
		value[0] = 0;
		pq.push(make_pair(0, 0)); // Push the first vertex with weight 0

		while (!pq.empty()) {
			int u = pq.top().second; // Get the vertex with the smallest value
			pq.pop();

			if (inMST[u]) continue; // Skip if already in the MST

			inMST[u] = true; // Mark as included in the MST

			// Check all neighbors of vertex `u`
			for (auto neighbor : adj[u]) {
				int v = neighbor.first;  // Neighbor vertex
				int weight = neighbor.second; // Weight of the edge (u, v)

				// If v is not in the MST and weight is smaller than the current value
				if (!inMST[v] && weight < value[v]) {
					value[v] = weight;
					pq.push(make_pair(value[v], v)); // Push updated value to the priority queue
					parent[v] = u; // Update the parent of vertex `v`
				}
			}
		}

		// Print the edges in the MST
		cout << "Edges in MST:\n";
		bool mstExists = false;
		for (int i = 1; i < V; ++i) { // Start from 1 (vertex 0 has no parent)
			if (parent[i] != -1) { // Ensure parent exists
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
	int V = 8; // Number of vertices (adjust to match your input graph)
	Graph g(V);

	// Add edges to the graph (as per your example)
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

	// Run Prim's algorithm and print the MST
	g.primMST();

	return 0;
}

//How we can implement BFS/DFS algorithms
//Analyse the time complexity of the algorithms in terms of big Oh

