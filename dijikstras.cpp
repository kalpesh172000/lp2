#include<iostream>
#include<unordered_map>
#include<string>
#include<fstream>
#include<vector>
#include<utility>
#include<queue>
#include<algorithm>
#include<limits.h>


using namespace std;

struct node 
{
    string name;
    vector<pair<string,int>> neighbors;
    node(string name) : name(name) {}
};

class prims 
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

    vector<pair<pair<string, string>, int>> dijkstras(string start, string end) 
    {
        
        if(!nodes.count(start) || !nodes.count(end)) {
            cout << "Invalid start or end node" << endl;
            return {};
        }

        // Create a priority queue to store the nodes to be visited
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;//-----------see the pair<int,string> here

        // Create a map to store the distance of each node from the start node
        unordered_map<string, int> distance;

        // Create a map to store the previous node in the shortest path
        unordered_map<string, string> previous;

        // Initialize the distance of all nodes to infinity except the start node
        for (auto node : nodes) {
            if (node.first == start) {
                distance[node.first] = 0;
            } else {
                distance[node.first] = INT_MAX;
            }
        }

        // Add the start node to the priority queue
        pq.push({0, start});

        // Dijkstra's algorithm
        while (!pq.empty()) 
        {
            string current = pq.top().second;
            pq.pop();

            // Check if the current node has already been visited
            if (distance[current] == INT_MAX) {
                continue;
            }

            // Check if the current node is the destination
            if (current == end) {
                break;
            }

            // Visit each neighbor of the current node
            for (auto neighbor : nodes[current]->neighbors) {
                string next = neighbor.first;
                int weight = neighbor.second;

                // Calculate the new distance to the neighbor
                int newDistance = distance[current] + weight;

                // Update the distance and previous node if the new distance is shorter
                if (newDistance < distance[next]) {
                    distance[next] = newDistance;
                    previous[next] = current; //---------------keep eye on this 
                    pq.push({newDistance, next});
                }
            }
        }

        // Reconstruct the shortest path
        vector<pair<pair<string, string>, int>> path;
        string current = end;
        while (current != start) {
            string previousNode = previous[current];
            int weight = 0;
            for (auto neighbor : nodes[previousNode]->neighbors) {
                if (neighbor.first == current) {
                    weight = neighbor.second;
                    break;
                }
            }
            path.push_back({{previousNode, current}, weight});
            current = previousNode;
        }
        reverse(path.begin(), path.end());

        return path;
    }


    public:
    void menu()
    {
        int ch;
        string start,end;
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
                        cout<<"enter the start node : ";
                        cin>>start;
                        cout<<"enter the destionation : ";
                        cin>>end;
                        vector<pair<pair<string,string>,int>> mst= dijkstras(start,end);
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
    prims a;
    a.menu();
    return 0;
}