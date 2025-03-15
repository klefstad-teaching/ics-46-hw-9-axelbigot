#include "dijkstras.h"

struct Node {
	int vertex;
	int weight;

	Node(int _vertex, int _weight)
	: vertex(_vertex), weight(_weight) { }

	bool operator>(const Node& other) const {
		return weight > other.weight;
	}
};


vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
	int n = G.numVertices;

	vector<int> distance(n, INF);
	previous.resize(n, -1);
	vector<bool> seen(n, false);

	priority_queue<Node, vector<Node>, greater<Node>> pq;

	distance[source] = 0;
	pq.push(Node(source, 0));

	while (!pq.empty()) {
		Node curr = pq.top();
		pq.pop();
		int u = curr.vertex;

		if (seen[u]) continue;
		seen[u] = true;

		for (Edge e : G[u]) {
			int v = e.dst;
			int weight = e.weight;

			if (!seen[v] && (distance[u] + weight < distance[v])) {
				distance[v] = distance[u] + weight;
				previous[v] = u;

				pq.push(Node(v, distance[v]));
			}
		}
	}

	return distance;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
	vector<int> path;

	if (distances[destination] == INF) return path;

	for (int v = destination; v != -1; v = previous[v])
		path.push_back(v);
	
	reverse(path.begin(), path.end());
	return path;
}

void print_path(const vector<int>& v, int total) {
	cout << total;
	for (int i : v) cout << i << " ";
}
