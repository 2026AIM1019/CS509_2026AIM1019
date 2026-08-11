# Assignment 01 — Graph Algorithms Test Runner

This project implements:

- Bellman-Ford
- Floyd-Warshall
- CSR (Compressed Sparse Row) graph representation
- Automatic output generation and reference-file comparison
- Execution-time measurement
- Bellman-Ford/Floyd-Warshall cross-check for 10- and 100-vertex graphs

The implementation reuses the existing `Graph`, `CSRGraph`, `graph_io`, `csr`,
`output`, `compare`, `timer`, and `runner` framework wherever possible.

---

## 1. Graph Representations

### Graph

`Graph` is the adjacency-list representation used while reading weighted
adjacency-list files:

```text
adj[u]      = neighbours of u
weights[u]  = corresponding edge weights
```

### CSRGraph

`CSRGraph` stores the same directed weighted graph compactly:

```text
row_ptr
col_idx
weights
```

For vertex `u`, its outgoing edges are:

```text
for (i = row_ptr[u]; i < row_ptr[u + 1]; ++i)
```

This is particularly appropriate for Bellman-Ford because it needs to scan
all edges repeatedly.

### MatrixGraph

Floyd-Warshall is different: its dynamic-programming recurrence needs direct
access to `dist[i][j]` for every pair of vertices. Therefore it reads the
required `V x V` adjacency matrix into `MatrixGraph`.

The matrix can subsequently be converted to the existing `Graph`/`CSRGraph`
representation for Bellman-Ford cross-checking.

---

# 2. Bellman-Ford

Bellman-Ford computes shortest distances from one source to every reachable
vertex and supports negative edge weights.

For every pass, every directed edge `(u, v, w)` is relaxed:

```text
if dist[u] + w < dist[v]:
    dist[v] = dist[u] + w
```

At most `V-1` passes are required because a simple shortest path contains at
most `V-1` edges.

An additional pass checks for a possible relaxation.

If an edge can still be relaxed and its starting vertex is reachable from the
source, a negative-weight cycle reachable from the source exists.

### Important clarification about negative cycles

The statement:

> "No shortest path is defined for the affected vertices."

means that the existence of a reachable negative cycle does **not** necessarily
make every vertex's distance undefined.

Only vertices whose shortest paths can exploit the reachable negative cycle
have no finite shortest distance. Because the assignment explicitly asks to
report a negative cycle and omit the distance table, this implementation does
exactly that.

### Complexity

```text
Time:   O(VE)
Space:  O(V + E)
```

The implementation uses CSR, so the edge scan is:

```cpp
for (int u = 0; u < csr.V; ++u)
    for (int i = csr.row_ptr[u];
         i < csr.row_ptr[u + 1];
         ++i)
```

---

# 3. Floyd-Warshall

Floyd-Warshall computes shortest paths between every pair of vertices.

The central recurrence is:

```text
dist[i][j] =
    min(dist[i][j],
        dist[i][k] + dist[k][j])
```

for every intermediate vertex `k`.

It is a dynamic-programming algorithm. After processing `k`, paths are allowed
to use vertices `0 ... k` as intermediate vertices.

Negative edge weights are allowed.

A negative-weight cycle is detected when, after the algorithm finishes:

```text
dist[i][i] < 0
```

for any vertex `i`.

### Negative-cycle clarification

A negative diagonal entry proves that a negative-weight cycle exists in the
graph. It does not mean every pairwise distance is undefined; distances
affected by that cycle are the problematic ones.

The assignment requires the program to print:

```text
Negative cycle: true
```

and omit the matrix whenever any negative cycle is detected. The implementation
follows that requirement.

### Complexity

```text
Time:   O(V^3)
Space:  O(V^2)
```

---

# 4. Input Formats

## 4.1 Bellman-Ford

Bellman-Ford uses the existing weighted adjacency-list format:

```text
V E
u0 degree neighbor1 weight1 neighbor2 weight2 ...
u1 degree neighbor1 weight1 ...
...
u(V-1) degree ...
SOURCE s
```

Example:

```text
5 10
0 2 1 6 3 7
1 3 2 5 3 8 4 -4
2 1 1 -2
3 2 2 -3 4 9
4 2 0 2 2 7
SOURCE 0
```

This is stored as:

```text
Graph
   |
   v
CSRGraph
   |
   v
Bellman-Ford
```

## 4.2 Floyd-Warshall

Floyd-Warshall uses the assignment's matrix format:

```text
V
row 0
row 1
...
row V-1
```

Example:

```text
5
0 3 8 INF -4
INF 0 INF 1 7
INF 4 0 INF INF
2 INF -5 0 INF
INF INF INF 6 0
```

`INF` means there is no direct edge.

The diagonal must contain zero:

```text
dist[i][i] = 0
```

---

# 5. Output Formats

## Bellman-Ford

Normal result:

```text
Algorithm: Bellman-Ford
Source: 0
Vertex Distance
0 0
1 2
2 4
3 7
4 -2
Negative cycle: none
```

Negative-cycle result:

```text
Algorithm: Bellman-Ford
Source: 0
Negative cycle: true
```

The distance table is omitted when a reachable negative cycle exists.

## Floyd-Warshall

Normal result:

```text
Algorithm: Floyd-Warshall
Distance matrix:
0 1 -3 2 -4
3 0 -4 1 -1
7 4 0 5 3
2 -1 -5 0 -2
8 5 1 6 0
Negative cycle: none
```

Negative-cycle result:

```text
Algorithm: Floyd-Warshall
Negative cycle: true
```

---

# 6. Bellman-Ford/Floyd-Warshall Cross-Check

For graphs with 10 and 100 vertices, the assignment requires both algorithms
to agree.

For every Floyd-Warshall input having:

```text
V = 10
```

or

```text
V = 100
```

the runner:

1. Executes Floyd-Warshall once.
2. Converts the matrix into the existing `Graph` representation.
3. Converts that graph to the existing `CSRGraph` representation.
4. Runs Bellman-Ford from every vertex:

```text
source = 0
source = 1
...
source = V-1
```

5. Compares each Bellman-Ford distance vector with the corresponding Floyd-
   Warshall matrix row.

Therefore:

```text
BellmanFord(source = i)[j]
        ==
FloydWarshall[i][j]
```

for every `i, j`.

The console reports:

```text
BF cross-check: PASS
```

or:

```text
BF cross-check: FAIL
```

For negative-cycle test cases, the cross-check is skipped because the
assignment does not define a finite all-pairs shortest-distance matrix in that
case.

The supplied project includes 10- and 100-vertex Floyd-Warshall tests, and both
cross-checks pass.

---

# 7. Source Files Added/Changed

### Added

```text
src/bellman_ford.h
src/bellman_ford.cpp

src/floyd_warshall.h
src/floyd_warshall.cpp
```

### Modified

```text
src/graph.h
src/graph_io.h
src/graph_io.cpp
src/output.h
src/output.cpp
src/runner.h
src/runner.cpp
driver/main.cpp
Makefile
README.md
```

### Existing components reused

```text
src/graph.h
src/csr.h
src/csr.cpp
src/graph_io.*
src/timer.h
src/output.*
src/compare.*
src/runner.*
```

---

# 8. Test Directory Structure

```text
tests/
├── bellman_ford/
│   ├── test_01.txt
│   ├── test_02.txt
│   └── test_03.txt
└── floyd_warshall/
    ├── test_01.txt
    ├── test_02.txt
    ├── test_10.txt
    └── test_100.txt

outputs/
├── bellman_ford/
│   ├── test_01.txt
│   ├── test_02.txt
│   └── test_03.txt
└── floyd_warshall/
    ├── test_01.txt
    ├── test_02.txt
    ├── test_10.txt
    └── test_100.txt

generated/
├── bellman_ford/
└── floyd_warshall/
```

`generated/` is created automatically.

---

# 9. Supplied Bellman-Ford Tests

### test_01.txt

The example from the assignment is included.

Expected shortest distances from source `0`:

```text
0 -> 0
1 -> 2
2 -> 4
3 -> 7
4 -> -2
```

There is no negative cycle.

### test_02.txt

Contains a negative cycle:

```text
1 -> 2 -> 1
```

with total weight:

```text
-2 + -2 = -4
```

The program therefore reports:

```text
Negative cycle: true
```

### test_03.txt

Tests unreachable vertices and negative edges in a disconnected component.

The negative edge does not affect source `0` because its component is
unreachable from source `0`.

---

# 10. Supplied Floyd-Warshall Tests

### test_01.txt

The assignment's 5-vertex example.

### test_02.txt

Contains a negative cycle.

### test_10.txt

10-vertex positive-weight graph.

The runner performs the required all-sources Bellman-Ford cross-check.

### test_100.txt

100-vertex positive-weight graph.

The runner again performs Bellman-Ford from all 100 sources and compares the
results against Floyd-Warshall.

---

# 11. Build

Run from the `assignment_01` directory:

```bash
make
```

or:

```bash
make rebuild
```

The executable is:

```text
./graph_runner
```

---

# 12. Run

```bash
./graph_runner
```

Menu:

```text
Graph Algorithms Test Runner

1. Breadth First Search (BFS)
2. Depth First Search (DFS)
3. Single Source Shortest Path (SSSP - Dijkstra)
4. Bellman-Ford
5. Floyd-Warshall
0. Exit
```

Select:

```text
4
```

for Bellman-Ford.

Select:

```text
5
```

for Floyd-Warshall.

---

# 13. Verification

The automatic runner generates output and compares it against the reference
file:

```text
expected:
outputs/<algorithm>/test_XX.txt

generated:
generated/<algorithm>/test_XX.txt
```

A test passes only when the generated output exactly matches the reference
output.

For example:

```bash
diff generated/bellman_ford/test_01.txt \
     outputs/bellman_ford/test_01.txt
```

An empty `diff` means the files are identical.

---
