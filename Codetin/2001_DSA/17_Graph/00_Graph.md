# 1. Introduction

- A **graph** is a data structure used to represent relationships between objects. It consists of a set of **vertices (nodes)** and **edges (connections)** between those vertices.
- A graph is mathematically represented as:
- `G = (V, E)`
- **walk** - a sequnce of vertices that we get from a vetrex to another vertex.
- **path** - special walk that has no repeated vertex in a walk.

**Cyclic Grapth** : if there exists a walk that starts and ends on the same vertex.  
**Acyclic Graph** : If there are no cycles. 
**Weighted Graph** : Where each edge has a 

Where:

- **V** = set of vertices  
- **E** = set of edges connecting the vertices  

Graphs are widely used in applications such as **social networks, road maps, network routing, and recommendation systems**.



# 2. Directed Graphs

- A **directed graph (digraph)** is a graph where each edge has a **direction**.
- An edge is represented as:
- u → v. This means the edge goes **from vertex u to vertex v**, but not necessarily the other way around.

## 2.1 Degrees in Directed Graphs

In directed graphs, each vertex has two types of degrees:

1. **In-degree (deg⁻(v))**  
Number of edges **coming into** a vertex.

2. **Out-degree (deg⁺(v))**  
Number of edges **going out of** a vertex.

**Properties**

- Sum of all **in-degrees = number of edges**
- Sum of all **out-degrees = number of edges**

```
Sum deg⁻(v) = Sum deg⁺(v) = |E|
```


## 2.2 Maximum Number of Edges in Directed Graph

For a directed graph with **n vertices**:
```
Max edges = n(n − 1)
```

Reason:  
Each pair of vertices can have **two directed edges**:

- u → v  
- v → u

# 3. Undirected Graphs

- An **undirected graph** is a graph where edges **do not have direction**.
- An edge between two vertices **u and v** is written as:

(u, v) = (v, u)

This means the connection works **both ways**.



## 3.1 Degree in Undirected Graphs

- The **degree of a vertex** is the number of edges connected to that vertex.
- Notation: deg(v)
- Example:  
If vertex **A** connects to **B, C, and D**  
deg(A) = 3

**Property**
The sum of the degrees of all vertices equals **twice the number of edges**.  
```
Sum deg(v) = 2|E|  
```
This is known as the **Handshaking Lemma**.  



## 3.2 Maximum Number of Edges in Undirected Graph

For an undirected graph with **n vertices**:

```
Max edges = n(n − 1) / 2
```

Reason:  
Each pair of vertices can have **only one edge** between them.