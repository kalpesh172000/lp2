#include<iostream>
#include<unordered_map>
#include<string>
#include<fstream>
#include<vector>
#include<utility>
#include<queue>


using namespace std;

struct node 
{
    string name;
    vector<pair<string,int>> neighbors;
    node(string name) : name(name) {}
};

class krushkals 
{
    unordered_map<string,node*> nodes;
    
    void getMap()
    {
        ifstream city("citiesGraph.txt");
        string start;
        string end;
        int weight;
        while(city>>start>>end>>weight)
        {
            if(!nodes[start])
                nodes[start] = new node(start);
            if(!nodes[end])
                nodes[end] = new node(end);
            nodes[start]->neighbors.push_back({end,weight});
            nodes[end]->neighbors.push_back({start,weight});
        }
        city.close();
    }


    void displayCity()
    {
        for(auto city : nodes)
        {
            cout<<city.first<<" -> ";
            for(auto neighbor : city.second->neighbors)
            {
                cout<<neighbor.first<<" ";
            }
            cout<<endl;
        }
        
        // unordered_map<string,node*>::iterator it = nodes.begin();
        // while(it != nodes.end())
        // {
        //     cout<<it->first<<endl<<endl;
        //     it++;
        // }
    }

    vector<pair<pair<string,string>,int>> getmst()
    {
        vector<pair<pair<string,string>,int>> mst;
        
        // Create a priority queue to store edges with their weights
        priority_queue<pair<int, pair<string,string>>, vector<pair<int, pair<string,string>>>, greater<pair<int, pair<string,string>>>> pq;
        
        // Create a disjoint set to keep track of connected components
        unordered_map<string, string> parent;
        unordered_map<string, int> rank;
        
        // Initialize the parent and rank for each node
        for(auto node : nodes)
        {
            parent[node.first] = node.first;
            rank[node.first] = 0;
        }
        
        // Add all the edges to the priority queue
        for(auto node : nodes)
        {
            string u = node.first;
            for(auto neighbor : node.second->neighbors)
            {
                string v = neighbor.first;
                int weight = neighbor.second;
                pq.push({weight, {u, v}});
            }
        }
        
        // Continue until all nodes are visited or the priority queue is empty
        while(!pq.empty() && mst.size() < nodes.size() - 1) //---------------mst.size< nodes.size - 1 
        {
            // Get the edge with the minimum weight
            pair<int, pair<string,string>> edge = pq.top();
            pq.pop();
            
            string u = edge.second.first;
            string v = edge.second.second;
            int weight = edge.first;
            
            // Find the parent of u and v
            string parentU = findParent(u, parent);
            string parentV = findParent(v, parent);
            
            // Check if adding the edge creates a cycle
            if(parentU != parentV)
            {
                // Add the edge to the minimum spanning tree
                mst.push_back({{u, v}, weight});
                
                // Union the sets of u and v
                unionSets(parentU, parentV, rank, parent);
            }
        }
        
        return mst;
    }
    
    string findParent(string node, unordered_map<string, string>& parent)
    {
        if(parent[node] != node)
        {
            parent[node] = findParent(parent[node], parent);
        }
        return parent[node];
    }
    
    void unionSets(string u, string v, unordered_map<string, int>& rank, unordered_map<string, string>& parent)
    {
        if(rank[u] > rank[v])
        {
            parent[v] = u;
        }
        else if(rank[u] < rank[v])
        {
            parent[u] = v;
        }
        else
        {
            parent[u] = v;
            rank[v]++;
        }
    }



    public:
    void menu()
    {
        int ch;
        while(true)
        {
            cout<<"\nMENU\n";
            cout<<"1. Build Graph\n";
            cout<<"2. Display Graph\n";
            cout<<"3. Find MST\n";
            cout<<"4. Exit\n";
            cout<<"Enter your choice: ";
            cin>> ch;
            switch(ch)
            {
                case 1:
                    getMap();
                    break;
                case 2:
                    displayCity();
                    break;
                case 3:
                    {
                        vector<pair<pair<string,string>,int>> mst= getmst();
                        for(auto edge : mst)
                        {
                            cout<<edge.first.first << " - "<< edge.first.second << " : " << edge.second<<endl;
                        }
                        break;
                    }
                case 4:
                    return;
                default:
                    cout<<"enter the correct option\n";
                    break;
            }
        }
    }
};

int main()
{
    krushkals a;
    a.menu();
    return 0;
}