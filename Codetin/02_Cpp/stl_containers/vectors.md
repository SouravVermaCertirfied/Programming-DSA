### C++: `vector<int> adj` vs `vector<int> adj[N]`

* `vector<int> adj;`
  → Declares **one vector of integers**.

* `vector<int> adj[N];`
  → Declares an **array of N vectors**.
  Each element `adj[i]` is its **own `vector<int>`**.

Example:

```cpp
vector<int> adj[3];

adj[0].push_back(1);
adj[0].push_back(2);
adj[1].push_back(3);
```

Memory structure:

```
adj[0] → {1,2}
adj[1] → {3}
adj[2] → {}
```

✔ This is why `vector<int> adj[V]` works for **graph adjacency lists**:

```
vertex → list of neighbors
adj[i] → vector<int> (neighbors of vertex i)
```

Quick rule:

```
vector<int> adj;      // one vector
vector<int> adj[N];   // N vectors (array of vectors)
```
