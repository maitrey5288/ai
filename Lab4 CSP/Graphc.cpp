#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

bool isSafe(int node, vector<int>& color, vector<vector<int>>& graph, int col) {
    for (int neighbor : graph[node]) {
        if (color[neighbor] == col) {
            return false;
        }
    }
    return true;
}

bool solve(int node, vector<int>& color, int m, int N, vector<vector<int>>& graph) {
    if (node == N) { //base case-if every node is colored I reach the N
        return true;
    }

    for (int col = 1; col <= m; col++) {
        if (isSafe(node, color, graph, col)) {
            color[node] = col;
            if (solve(node + 1, color, m, N, graph)) return true; //no need to check other possible solutions
            color[node] = 0; // remove the previously given color, backtrack
        }
    }
    return false; //no solution
}

bool graphColoring(vector<vector<int>>& graph, int m, int N) {
    vector<int> color(N, 0);
    if (solve(0, color, m, N, graph)) {
        // Print colors assigned to each vertex
        cout << "Vertex Colors:\n";
        for (int i = 0; i < N; ++i) {
            cout << "Vertex " << i + 1 << ": Color " << color[i] << endl;
        }
        return true;
    }
    return false;
}

int main() {
    int N, m, edges;
    cout << "Enter the number of nodes: ";
    cin >> N;
    cout << "Enter the number of colors: ";
    cin >> m;
    cout << "Enter the number of edges: ";
    cin >> edges;

    vector<vector<int>> graph;
    graph.resize(N);

    cout << "Enter the edges:\n";
    for (int i = 0; i < edges; i++) {
        int node1, node2;
        cout << "\nEnter edge vertices of edge " << i + 1 << " :";
        cin >> node1 >> node2;
        node1--;
        node2--;
        graph[node1].push_back(node2);
        graph[node2].push_back(node1);
    }

    cout << (graphColoring(graph, m, N) ? "Yes" : "No") << endl;

    return 0;
}