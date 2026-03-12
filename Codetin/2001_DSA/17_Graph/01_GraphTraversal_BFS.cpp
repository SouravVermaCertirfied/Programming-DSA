/* Approch of BFS
1. Maintain a queue, insert the starting node
2. Mark the starting node as visited
3. While queue is not empty:
    - Dequeue a node
    - Process/print the node
    - Enqueue all unvisited adjacent nodes
    - Mark them as visited
*/

#include<iostream>
#include<queue>
#include<vector>
using namespace std;

void bfs(int start, vector<vector<int>>& adj, vector<bool>& visited) {
     queue<int> q;
     q.push(start);
     visited[start] = true;
     
     while(!q.empty()) {
          int node = q.front();
          q.pop();
          cout << node << " ";
          
          for(int neighbor : adj[node]) {
                if(!visited[neighbor]) {
                     q.push(neighbor);
                     visited[neighbor] = true;
                }
          }
     }
}

int main() {
     int vertices = 5;
     vector<vector<int>> adj(vertices);
     vector<bool> visited(vertices, false);
     
     // Add edges (undirected graph)
     adj[0] = {1, 2};
     adj[1] = {0, 3};
     adj[2] = {0, 4};
     adj[3] = {1};
     adj[4] = {2};
     
     cout << "BFS Traversal: ";
     bfs(0, adj, visited);
     
     return 0;
}


