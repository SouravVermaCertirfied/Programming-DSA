Following two are the most commonly used representations of a graph:

- Adjacency Matrix.  
- Adjacency List. 

## Adjacency Matrix

- **Adjacency Matrix:** 2D array of size **V × V** (V = number of vertices).
- Represented as **adj[i][j]**.
- **adj[i][j] = 1** → edge from **i to j**.
- **Undirected graphs:** matrix is always**symmetric**.
- **Weighted graphs:** **adj[i][j] = w** → edge with **weight w**.

### Adjacency Matrix – Pros & Cons

**Pros**
- Easy to **implement and understand**.
- **Edge removal:** `O(1)`.
- **Edge existence check (u → v):** `O(1)`.

**Cons**
- **Space complexity:** `O(V²)`.
- Inefficient for **sparse graphs** (still uses `V²` space).
- **Adding a vertex:** `O(V²)`.

<details><summary> Code here</summary>

```cpp
#include<iostream>
#include<vector>
using namespace std;

#define V 5

void addEdge(vector<vector<int>> &adj, int i, int j){
	adj[i][j] = 1;
	adj[j][i] = 1;
	return;
}
 
void printGraph(vector<vector<int>> &adj){ // ☢️ 2D array declare
	int size = adj.size();
	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++){
			cout<<adj[i][j];
		}
		cout<<endl;
	}
}

int main()
{
	vector<vector<int>> adj(V, vector<int>(V, 0)); //☢️ notice the 2 d vector declare
    addEdge(adj, 0, 1);
    addEdge(adj, 0, 4);
    addEdge(adj, 1, 2);
    addEdge(adj, 1, 3);
    addEdge(adj, 1, 4);
    addEdge(adj, 2, 3);
    addEdge(adj, 3, 4);
    printGraph(adj);
    return 0;
}
```
</details>

## Adjacency List

- Graph represented using an **array of lists**.
- **Array size = number of vertices (V)**.
- Each index **i** stores a list of **vertices adjacent to vertex i**.
- Represented as **array[i] → list of neighbors of i**.
- Can also represent **weighted graphs**.
- **Weights stored as pairs:** `(vertex, weight)`.

<details><summary> CPP code here - Using STL List </summary>

```cpp
#include <bits/stdc++.h>
using namespace std;

// Add an undirected edge between u and v
void addEdge(vector<vector<int>>& adj, int u, int v) {
    if(u < 0 || v < 0 || u >= adj.size() || v >= adj.size()) return; // bounds check
    adj[u].push_back(v);
    adj[v].push_back(u);
}

// Print the adjacency list
void printGraph(const vector<vector<int>>& adj) {
    for(int i = 0; i < adj.size(); i++) {
        cout << i << ": ";
        for(int v : adj[i]) cout << v << " ";
        cout << "\n";
    }
}

int main() {
    int V = 5;
    vector<vector<int>> adj(V);

    addEdge(adj, 2, 3);
    addEdge(adj, 1, 4);
    addEdge(adj, 0, 2);

    printGraph(adj);
}
```

</details>

<details><summary> C Code here</summary>

```cpp
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *next;
} Node;

typedef struct {
    int vertices;
    Node **adj;
} Graph;

/* safe allocation helper */
static void *xmalloc(size_t size) {
    void *ptr = malloc(size);
    if (!ptr) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

/* create graph */
Graph *graph_create(int vertices) {
    Graph *g = xmalloc(sizeof(Graph));
    g->vertices = vertices;
    g->adj = calloc(vertices, sizeof(Node*));
    if (!g->adj) {
        perror("calloc");
        exit(EXIT_FAILURE);
    }
    return g;
}

/* create node */
Node *node_create(int val) {
    Node *n = xmalloc(sizeof(Node));
    n->val = val;
    n->next = NULL;
    return n;
}

/* insert edge (O(1)) */
void graph_insert(Graph *g, int u, int v) {
    Node *n = node_create(v);
    n->next = g->adj[u];
    g->adj[u] = n;
}

/* add undirected edge */
void graph_add_edge(Graph *g, int u, int v) {

    if (!g) return;
    if (u < 0 || v < 0 || u >= g->vertices || v >= g->vertices)  return;
    graph_insert(g, u, v);
    graph_insert(g, v, u);
}

/* print graph */
void graph_print(Graph *g) {

    if (!g) return;
    for (int i = 0; i < g->vertices; i++) {
        printf("%d:", i);
        Node *cur = g->adj[i];
        while (cur) {
            printf(" %d", cur->val);
            cur = cur->next;
        }
        printf("\n");
    }
}

/* free graph */
void graph_destroy(Graph *g) {
    if (!g) return;
    for (int i = 0; i < g->vertices; i++) {
        Node *cur = g->adj[i];
        while (cur) {
            Node *tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }
    free(g->adj);
    free(g);
}

int main() {

    Graph *g = graph_create(5);
    graph_add_edge(g, 2, 3);
    graph_add_edge(g, 1, 4);
    graph_add_edge(g, 0, 2);
    graph_print(g);
    graph_destroy(g);
    return 0;
}

```

</details>