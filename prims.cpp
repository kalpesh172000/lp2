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

    //generate the funtion that returns the minimum spanning tree by using prim's algorithm in the form of the vector<pair<pair<string,string>,int>>
    vector<pair<pair<string,string>,int>> getmst(string start)
    {
        if(!nodes.count(start))
        {
            cout<<"given source didn't found"<<endl;
            return {{}};
        }

        vector<pair<pair<string,string>,int>> mst;
        
        // Create a priority queue to store edges with their weights
        priority_queue<pair<int, pair<string,string>>, vector<pair<int, pair<string,string>>>, greater<pair<int, pair<string,string>>>> pq;
        
        
        // Create a set to keep track of visited nodes
        unordered_map<string,bool> visited;
        
        // Mark the starting node as visited
        visited[start] = true;
        
        // Add all the neighbors of the starting node to the priority queue
        for(auto neighbor : nodes[start]->neighbors)
        {
            pq.push({neighbor.second, {start, neighbor.first}});
        }
        
        // Continue until all nodes are visited or the priority queue is empty
        while(!pq.empty() && visited.size() < nodes.size()) //---------------------visited.size < nodes.size
        {
            // Get the edge with the minimum weight
            pair<int, pair<string,string>> edge = pq.top();
            pq.pop();
            
            string start = edge.second.first;
            string end = edge.second.second;
            int weight = edge.first;
            
            if(visited[end])
                continue;

            // Add the edge to the minimum spanning tree
            mst.push_back({{start, end}, weight});
            
            visited[end] = true;
            
            // Add the neighbors of the newly visited nodes to the priority queue
            for(auto neighbor : nodes[end]->neighbors)
            {
                if(visited.find(neighbor.first) == visited.end())
                {
                    pq.push({neighbor.second, {end, neighbor.first}});
                }
            }
        }
        
        return mst;
    }



    public:
    void menu()
    {
        int ch;
        string start;
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
                        vector<pair<pair<string,string>,int>> mst= getmst(start);
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