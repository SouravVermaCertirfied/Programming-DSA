/*
the idea to read the graph, 
start with  node, put it in the queue,
for its adjecent nodes, put it in the queue as well,
keep popping the queue until it is empty

maintain a visited array that keeps track of the nodes that are already visited, 
so that you do not have to visit them again

*/

#include<iostream>
#include<boolean>
#include<vector>
using namespace std;

#define V 5

void graph_bfs(vector<vector<int>> &adj){
    vector<bool> visited;
    return;
}

void addEdge(vector<vector<int>> &adj, int i, int j){
    adj[i].push_back(j);
    adj[j].push_back(i);
}



int main(){
    vector<vector<int>> adj(V);
    addEdge(adj, 1, 2);
    addEdge(adj, 1, 3);
    addEdge(adj, 2, 4);
    addEdge(adj, 2, 5);
    addEdge(adj, 3, 5);
    addEdge(adj, 4, 5);
    addEdge(adj, 4, 6);
    addEdge(adj, 5, 6);
    return 0;
}