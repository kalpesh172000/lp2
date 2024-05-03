#include<iostream>
#include<unordered_map>
#include<list>
#include<string>
#include<fstream>
#include<vector>
#include<utility>
#include<queue>
#include<algorithm>


using namespace std;

struct node 
{
    string name;
    vector<pair<string,int>> neighbors;
    node(string name) : name(name) {}
};

class astar
{
    unordered_map<string,node*> nodes;
    unordered_map<string,int> heuristics;


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

    void getHeuristics()
    {
        ifstream file("heuristics.txt");
        string start;
        int weight;
        while(file>>start>>weight)
        {
            heuristics[start] = weight;
        }
        file.close();
    }

    int calculateHCost(string next)
    {
        return heuristics[next];
    }

    pair<vector<string>,int> findPath(string start, string end)
    {
        if(!nodes.count(start) || !nodes.count(end))
        {
            cout<<"given source didn't found"<<endl;
            return {{},-1};
        }

        priority_queue< pair<int,string>,vector<pair<int,string>>, greater<pair<int, string>>> openSet;
        unordered_map<string,int> gCost;
        unordered_map<string,string> comeFrom;

        openSet.push({0,start});
        gCost[start] = 0;

        while(!openSet.empty())
        {
            string current = openSet.top().second;
            cout<<current<<" "<<openSet.top().first<<endl;
            openSet.pop();

            if(current == end)
            {
                vector<string> path;
                int totalCost = gCost[current];
                while(current != start)
                {
                    path.push_back(current);
                    current = comeFrom[current];
                }
                path.push_back(start);
                reverse(path.begin(),path.end());
                return {path,totalCost};
            }

            for(auto neighbor : nodes[current]->neighbors)
            {
                string next = neighbor.first;
                int newCost = gCost[current] + neighbor.second;
                //check if it is already visited or or if new cost is less than previous cost
                if(!gCost.count(next) || newCost < gCost[next])
                {
                    gCost[next] = newCost;
                    int hCost = calculateHCost(next);
                    int fCost = newCost + hCost;
                    
                    openSet.push({fCost,next});
                    comeFrom[next] = current;
                }

            }
        }
        cout<<"no path found from the Start node to the goal node\n";
        return {{},-2};
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
    public:
    void menu()
    {
        int ch;
        while(true)
        {
            cout<<"\nMENU\n";
            cout<<"1. Build Graph\n";
            cout<<"2. Display Graph\n";
            cout<<"3. Find Path\n";
            cout<<"4. Exit\n";
            cout<<"Enter your choice: ";
            cin>> ch;
            switch(ch)
            {
                case 1:
                    getMap();
                    getHeuristics();
                    break;
                case 2:
                    displayCity();
                    break;
                case 3:
                    {
                        string s1;
                        cout<<"Enter the Starting city: ";
                        cin>>s1;
                        string destination = "Bucharest";
                        auto result = findPath(s1,destination);
                        for(auto city : result.first)
                        {
                            cout<<city<<" -> ";
                        }
                        cout<<result.second<<endl;
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
    astar a;
    a.menu();
    return 0;
}