#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

class graph
{
    vector<vector<int>> adj;
    void addEdge(int u,int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void addGraphFromFile()
    {
        ifstream file("graph.txt");
        int n;
        file>>n;
        adj.resize(n);
        int u,v;
        while(file>>u>>v)
        {
            addEdge(u,v);
        }
    }

    void displayGraph()
    {
        for(int i=0;i<adj.size();i++)
        {
            cout<<i<<" -> ";
            for(int j = 0;j<adj[i].size();j++)
            {
                cout<<adj[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    void dfs(int v)
    {
        vector<bool> visited(adj.size(),false);
        dfsUtil(v,visited);
    }

    void dfsUtil(int v,vector<bool> &visited)
    {
        visited[v] = true;
        cout<<v<<" ";
        for(int i=0;i<adj[v].size();i++)
        {
            if(!visited[adj[v][i]])
            {
                dfsUtil(adj[v][i],visited);
            }
        }
    }

    void bfs(int v)
    {
        vector<bool> visited(adj.size(),false);
        visited[v]= true;
        vector<int> queue;
        queue.push_back(v);
        int size=adj.size();
        int j=1;
        while(j<=size)
        {
            v=queue[0];
            cout<<v<<" ";
            queue.erase(queue.begin());
            for(int i=0;i<adj[v].size();i++)
            {
                if(!visited[adj[v][i]])
                {
                    queue.push_back(adj[v][i]);
                    visited[adj[v][i]]=true;
                }
            }
            j++;
        }
    }
    public:
    void menu()
    {
        int ch,v;
        while (true)
        {
            cout<<"\n\nMENU\n";
            cout<<"1. Add Graph from file\n";
            cout<<"2. Display Graph\n";
            cout<<"3. Dfs of Graph\n";
            cout<<"4. Bfs of Graph\n";
            cout<<"5. Exit\n";
            cout<<"Enter your choice: ";
            cin>>ch;
            switch(ch)
            {
                case 1:
                    addGraphFromFile();
                    break;
                case 2:
                    displayGraph();
                    break;
                case 3:
                    cout<<"Enter starting point: ";
                    cin>>v;
                    dfs(v);
                    break;
                case 4:
                    cout<<"Enter starting point: ";
                    cin>>v;
                    bfs(v);
                    break;
                case 5:
                    return;
                default:
                    cout<<"Invalid choice\n";
            }
        }
        
    }
};

int main()
{
    graph g;
    g.menu();
    return 0;
}
