
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

// Define the cities and their connections
map<string, map<string, int>> graph = {
    {"A", {{"B", 2}, {"C", 4}}},
    {"B", {{"A", 2}, {"D", 3}, {"E", 1}}},
    {"C", {{"A", 4}, {"F", 5}}},
    {"D", {{"B", 3}, {"G", 7}}},
    {"E", {{"B", 1}, {"G", 2}}},
    {"F", {{"C", 5}, {"G", 1}}},
    {"G", {{"D", 7}, {"E", 2}, {"F", 1}}}
};

// Heuristic function (estimated distance to goal "G")
map<string, int> heuristic = {
    {"A", 6}, {"B", 4}, {"C", 3}, {"D", 4}, {"E", 2}, {"F", 1}, {"G", 0}
};

// Best First Search function
vector<string> bestFirstSearch(const string &start, const string &goal) {

    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> frontier; 
    map<string, string> cameFrom;

    frontier.push({heuristic[start], start});
    cameFrom[start] = "";

    while (!frontier.empty()) {
        string current = frontier.top().second;
        frontier.pop();

        if (current == goal) {
            vector<string> path;
            while (current != "") {
                path.push_back(current);
                current = cameFrom[current];
            }
            reverse(path.begin(), path.end());
            return path;
        }

        for (const auto &neighbor : graph[current]) {
            string next = neighbor.first;

            if (cameFrom.find(next) == cameFrom.end()) {
                cameFrom[next] = current;
                int priority = heuristic[next];
                frontier.push({priority, next});
            }
        }
    }

    return {}; // no path found
}

int main() {
    string start = "A";
    string goal = "G";

    vector<string> path = bestFirstSearch(start, goal);

    if (!path.empty()) {
        cout << "Shortest path from " << start << " to " << goal << ":\n";
        for (const string &city : path) {
            cout << city << " -> ";
        }
        cout << "Goal reached.\n";
    } else {
        cout << "No path found from " << start << " to " << goal << ".\n";
    }

    return 0;
}

