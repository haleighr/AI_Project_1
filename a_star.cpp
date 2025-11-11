#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <cmath>
#include <limits>
#include <stack>
#include <string>
#include <algorithm>
using namespace std;

// Function to read adjacency matrix from a file
vector<vector<int>> readAdjacencyMatrix(const string& filename, int nodeCount) {
    vector<vector<int>> adjacencyMatrix(nodeCount, vector<int>(nodeCount, 0));
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "Error: could not open " << filename << endl;
        exit(1);
    }

    vector<int> numbers;
    string token;

    while (inputFile >> token) {
        try {
            int value = stoi(token);
            numbers.push_back(value);
        } catch (...) {
            // ignore non-numeric tokens
        }
    }

    inputFile.close();

    if (numbers.size() < nodeCount * nodeCount) {
        cerr << "Error: not enough numbers found in file." << endl;
        exit(1);
    }

    int index = 0;
    for (int i = 0; i < nodeCount; ++i) {
        for (int j = 0; j < nodeCount; ++j) {
            adjacencyMatrix[i][j] = numbers[index++];
        }
    }

    return adjacencyMatrix;
}

// Heuristic function (NEED TO FINISH)
double heuristic(int currentNode, int goalNode) {
    return 0.0; // placeholder heuristic (acts like Dijkstra)
}

// A* Function
void aStar(const vector<vector<int>>& adjacencyMatrix, int startNode, int goalNode) {
    int totalNodes = adjacencyMatrix.size();
    vector<double> costFromStart(totalNodes, numeric_limits<double>::infinity());
    vector<double> estimatedTotalCost(totalNodes, numeric_limits<double>::infinity());
    vector<int> previousNode(totalNodes, -1);
    vector<bool> nodeClosed(totalNodes, false);

    costFromStart[startNode] = 0;
    estimatedTotalCost[startNode] = heuristic(startNode, goalNode);

    using Node = pair<double, int>;
    priority_queue<Node, vector<Node>, greater<Node>> openSet;
    openSet.emplace(estimatedTotalCost[startNode], startNode);

    while (!openSet.empty()) {
        int currentNode = openSet.top().second;
        openSet.pop();

        if (nodeClosed[currentNode]) continue;
        nodeClosed[currentNode] = true;

        if (currentNode == goalNode) {
            stack<int> path;
            for (int node = goalNode; node != -1; node = previousNode[node])
                path.push(node);

            cout << "Path: ";
            while (!path.empty()) {
                cout << path.top();
                path.pop();
                if (!path.empty()) cout << " -> ";
            }
            cout << "\nCost: " << costFromStart[goalNode] << endl;
            return;
        }

        for (int neighborNode = 0; neighborNode < totalNodes; ++neighborNode) {
            if (adjacencyMatrix[currentNode][neighborNode] == 0 || nodeClosed[neighborNode]) continue;

            double tentativeCost = costFromStart[currentNode] + adjacencyMatrix[currentNode][neighborNode];
            if (tentativeCost < costFromStart[neighborNode]) {
                previousNode[neighborNode] = currentNode;
                costFromStart[neighborNode] = tentativeCost;
                estimatedTotalCost[neighborNode] = tentativeCost + heuristic(neighborNode, goalNode);
                openSet.emplace(estimatedTotalCost[neighborNode], neighborNode);
            }
        }
    }

    cout << "No path found from " << startNode << " to " << goalNode << endl;
}

int main() {
    string filename = "adjacency.txt";
    int nodeCount = 20;
    vector<vector<int>> adjacencyMatrix = readAdjacencyMatrix(filename, nodeCount);

    int startNode, goalNode;
    cout << "Enter start node (0-" << nodeCount - 1 << "): ";
    cin >> startNode;
    cout << "Enter goal node (0-" << nodeCount - 1 << "): ";
    cin >> goalNode;

    aStar(adjacencyMatrix, startNode, goalNode);
    return 0;
}
