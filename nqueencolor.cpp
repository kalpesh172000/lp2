#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

bool isSafe(int v, const vector<vector<int>>& graph, const vector<int>& color, int c) {
    for (int u = 0; u < graph.size(); ++u) {
        if (graph[v][u] && c == color[u])
            return false;
    }
    return true;
}

bool graphColoringUtil(int v, const vector<vector<int>>& graph, vector<int>& color) {
    if (v == graph.size())
        return true;

    for (int c = 1; ; ++c) {//-----------------------middle values not given starts from 1
        if (isSafe(v, graph, color, c)) {
            color[v] = c;
            if (graphColoringUtil(v + 1, graph, color))
                return true;
            color[v] = 0;
        }
    }
    return false;
}

// Check if it is possible to color the graph
bool graphColoring(const vector<vector<int>>& graph) {
    vector<int> color(graph.size(), 0); // Initialize color array
    if (!graphColoringUtil(0, graph, color)) { // If coloring is not possible
        cout << "Solution does not exist" << endl;
        return false;
    }
    
    cout << "Solution exists:" << endl;
    
    int maxColor = *max_element(color.begin(), color.end()); // Find the maximum color used *max_element()
    vector<int> colorCount(maxColor + 1, 0); // Initialize color count array
    
    // Count the number of vertices with each color
    for (int v = 0; v < graph.size(); ++v) {
        cout << "Vertex " << v << " -> Color " << color[v] << endl;
        colorCount[color[v]]++; // Increment color count for each vertex
    }
    
    int minColor = 0;
    for (int count : colorCount) {
        if (count > 0) {
            minColor++;
        }
    }
    
    cout << "Minimum number of colors needed: " << minColor << endl;
    
    return true;
}

int main() {
    ifstream inputFile("color.txt");

    int n;
    inputFile >> n;

    vector<vector<int>> graph(n, vector<int>(n, 0));
    int i,j;
    while(inputFile>>i>>j)
    {
        graph[i][j] = 1;
        graph[j][i] = 1;
    }

    inputFile.close();

    graphColoring(graph);

    return 0;
}
