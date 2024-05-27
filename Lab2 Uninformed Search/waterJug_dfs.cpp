#include <iostream>
#include <stack>
#include <set>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>

using namespace std;

// Function to generate the next states from the current state
vector<pair<int, int>> generateNextStates(pair<int, int> state, int capacity_jug1, int capacity_jug2) {
    vector<pair<int, int>> next_states;

    // Fill Jug 1
    next_states.push_back(make_pair(capacity_jug1, state.second));

    // Fill Jug 2
    next_states.push_back(make_pair(state.first, capacity_jug2));

    // Empty Jug 1
    next_states.push_back(make_pair(0, state.second));

    // Empty Jug 2
    next_states.push_back(make_pair(state.first, 0));

    // Pour water from Jug 1 to Jug 2
    int pour_amount = min(state.first, capacity_jug2 - state.second);
    next_states.push_back(make_pair(state.first - pour_amount, state.second + pour_amount));

    // Pour water from Jug 2 to Jug 1
    pour_amount = min(state.second, capacity_jug1 - state.first);
    next_states.push_back(make_pair(state.first + pour_amount, state.second - pour_amount));

    return next_states;
}

// Function to solve the Water Jug Problem using DFS and track the path
pair<int, int> solveWaterJugProblem(int capacity_jug1, int capacity_jug2, int desired_quantity, map<pair<int, int>, pair<int, int>>& parent) {
    stack<pair<int, int>> stack;
    set<pair<int, int>> visited;

    // Initial state: both jugs empty
    stack.push(make_pair(0, 0));
    visited.insert(make_pair(0, 0));
    parent[make_pair(0, 0)] = make_pair(-1, -1); // Using (-1, -1) to indicate the initial state has no parent

    while (!stack.empty()) {
        pair<int, int> current_state = stack.top();
        stack.pop();

        // Check if we have reached the desired quantity
        if (current_state.first == desired_quantity || current_state.second == desired_quantity) {
            return current_state;
        }

        // Generate the next states and process them
        vector<pair<int, int>> next_states = generateNextStates(current_state, capacity_jug1, capacity_jug2);
        for (const auto& state : next_states) {
            if (visited.find(state) == visited.end()) {
                stack.push(state);
                visited.insert(state);
                parent[state] = current_state; // Track the parent of the state
            }
        }
    }

    return make_pair(-1, -1); // No solution found
}

// Function to print the path from the initial state to the solution state
void printPath(pair<int, int> state, map<pair<int, int>, pair<int, int>>& parent) {
    vector<pair<int, int>> path;

    while (state != make_pair(-1, -1)) {
        path.push_back(state);
        state = parent[state];
    }

    reverse(path.begin(), path.end());

    for (const auto& step : path) {
        cout << "(" << step.first << ", " << step.second << ")" << endl;
    }
}

int main() {
    int capacity_jug1 = 4;
    int capacity_jug2 = 3;
    int desired_quantity = 2;

    map<pair<int, int>, pair<int, int>> parent;

    pair<int, int> result = solveWaterJugProblem(capacity_jug1, capacity_jug2, desired_quantity, parent);

    if (result.first == -1 && result.second == -1) {
        cout << "No solution found" << endl;
    } else {
        cout << "Solution found: (" << result.first << ", " << result.second << ")" << endl;
        cout << "Path from initial state to solution state:" << endl;
        printPath(result, parent);
    }

    return 0;
}
