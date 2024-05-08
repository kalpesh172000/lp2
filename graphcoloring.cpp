#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool isSafe(int v, vector<vector<int>>& graph, vector<int>& color, int c) {
    for(int i = 0; i < graph.size(); i++) {
        if(graph[v][i] && c == color[i]) {
            return false;
        }
    }

    return true;
}

bool graphColorUtil(vector<vector<int>>& graph, vector<int>& color, int m, int v) {
    if(v == graph.size()) {
        return true;
    }

    for(int c = 1; c <= m; c++) {
        if(isSafe(v, graph, color, c)) {
            color[v] = c;
            if(graphColorUtil(graph, color, m, v+1)) {
                return true;
            }

            color[v] = 0;
        }
    }

    return false;
}

int main () {
    vector<vector<int>> graph = {   {0,1,0,1},
                                    {1,0,1,1},
                                    {0,1,0,0},
                                    {1,1,0,0}
    };

    int m,V;

    cout<<"Enter number of colors: ";
    cin>>m;
    
    V = 4;

    vector<int> color(V, 0);

    if(graphColorUtil(graph, color, m, 0)) {
        cout<<"Can be colored!"<<endl;
        cout<<"Colors needed: "<<*max_element(color.begin(), color.end())<<endl;
        cout<<"Vertex \t Color"<<endl;
        for(int i = 0; i < V; i++) {
            cout<<i<<"\t"<<color[i]<<endl;
        }
    }
    else{
        cout<<"Cannot be colored!";
    }
}