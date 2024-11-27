#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>

using namespace std;

class GraphConnectivity 
{
private:
    vector<int> parent, size;
    int connectedComponents;

public:
    GraphConnectivity(int nodes) 
    {
        parent.resize(nodes + 1);
        size.resize(nodes + 1, 1);
        iota(parent.begin(), parent.end(), 0);
        connectedComponents = nodes;
    }

    int findRoot(int node) 
    {
        if (parent[node] != node) 
        {
            parent[node] = findRoot(parent[node]);
        }
        return parent[node];
    }

    void mergeSets(int a, int b) 
    {
        int rootA = findRoot(a);
        int rootB = findRoot(b);
        if (rootA != rootB) {
            if (size[rootA] < size[rootB]) 
            {
                swap(rootA, rootB);
            }
            parent[rootB] = rootA;
            size[rootA] += size[rootB];
            connectedComponents--;
        }
    }

    int getConnectedComponents() const 
    {
        return connectedComponents;
    }
};

int main() {
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    int cities, roads, earthquakes;
    inputFile >> cities >> roads >> earthquakes;

    vector<pair<int, int>> connections(roads + 1);
    for (int i = 1; i <= roads; i++) {
        inputFile >> connections[i].first >> connections[i].second;
    }

    vector<int> destroyedRoads(earthquakes);
    vector<bool> isRoadDestroyed(roads + 1, false);

    for (int i = 0; i < earthquakes; i++) 
    {
        inputFile >> destroyedRoads[i];
        isRoadDestroyed[destroyedRoads[i]] = true;
    }

    GraphConnectivity graph(cities);

    for (int i = 1; i <= roads; i++) 
    {
        if (!isRoadDestroyed[i]) {
            graph.mergeSets(connections[i].first, connections[i].second);
        }
    }

    vector<int> results(earthquakes);

    for (int i = earthquakes - 1; i >= 0; i--) 
    {
        results[i] = (graph.getConnectedComponents() == 1) ? 1 : 0;

        int roadIndex = destroyedRoads[i];
        graph.mergeSets(connections[roadIndex].first, connections[roadIndex].second);
    }

    for (int result : results) 
    {
        outputFile << result;
    }

    return 0;
}
