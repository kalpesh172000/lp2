#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

struct treenode
{
    int val;
    vector<treenode*> node;

    treenode(int x):val(x){} 
};

class tree
{
    treenode* root;

};

