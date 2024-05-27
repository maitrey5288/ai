#include <iostream>
#include <set>

using namespace std;

// Structure to represent the state of water in jugs
struct State {
    int jugA, jugB;

    State(int a, int b) : jugA(a), jugB(b) {}

    // Overloading the == operator for set comparison
    bool operator==(const State& other) const {
        return jugA == other.jugA && jugB == other.jugB;
    }
};

// Function to perform Depth-First Search for the water jug problem with a depth limit
bool depthLimitedSearch(State currentState, int jugCapacityA, int jugCapacityB, int targetVolume, int depthLimit, set<State>& visited) {
    if (currentState.jugA == targetVolume || currentState.jugB == targetVolume) {
        cout << "Target volume " << targetVolume << " reached!" << endl;
        return true;
    }

    if (depthLimit <= 0) {
        return false;
    }

    if (visited.find(currentState) != visited.end()) {
        return false;
    }

    visited.insert(currentState);

    // Generate all possible next states and recursively explore
    // Fill jug A
    if (depthLimitedSearch(State(jugCapacityA, currentState.jugB), jugCapacityA, jugCapacityB, targetVolume, depthLimit - 1, visited))
        return true;
    // Fill jug B
    if (depthLimitedSearch(State(currentState.jugA, jugCapacityB), jugCapacityA, jugCapacityB, targetVolume, depthLimit - 1, visited))
        return true;
    // Empty jug A
    if (depthLimitedSearch(State(0, currentState.jugB), jugCapacityA, jugCapacityB, targetVolume, depthLimit - 1, visited))
        return true;
    // Empty jug B
    if (depthLimitedSearch(State(currentState.jugA, 0), jugCapacityA, jugCapacityB, targetVolume, depthLimit - 1, visited))
        return true;
    // Pour from A to B
    int pourAmount = min(currentState.jugA, jugCapacityB - currentState.jugB);
    if (depthLimitedSearch(State(currentState.jugA - pourAmount, currentState.jugB + pourAmount), jugCapacityA, jugCapacityB, targetVolume, depthLimit - 1, visited))
        return true;
    // Pour from B to A
    pourAmount = min(jugCapacityA - currentState.jugA, currentState.jugB);
    if (depthLimitedSearch(State(currentState.jugA + pourAmount, currentState.jugB - pourAmount), jugCapacityA, jugCapacityB, targetVolume, depthLimit - 1, visited))
        return true;

    return false;
}

// Function to perform Iterative Deepening Depth-First Search
bool IDDFS(int jugCapacityA, int jugCapacityB, int targetVolume) {
    int depthLimit = 0;
    set<State> visited;

    while (true) {
        if (depthLimitedSearch(State(0, 0), jugCapacityA, jugCapacityB, targetVolume, depthLimit, visited)) {
            return true;
        }
        depthLimit++;
        visited.clear();
    }

    return false;
}

int main() {
    // Define jug capacities and target volume
    int jugCapacityA = 4; // Capacity of jug A
    int jugCapacityB = 3; // Capacity of jug B
    int targetVolume = 2; // Target volume of water

    // Perform Iterative Deepening Depth-First Search
    IDDFS(jugCapacityA, jugCapacityB, targetVolume);

    return 0;
}