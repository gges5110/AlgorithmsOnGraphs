// Advanced Problem: Checking Whether Any Intersection in a City
// is Reachable from Any Other
// Problem Introduction
// The police department of a city has made all streets one-way. You would like
// to check whether it is still possible to drive legally from any intersection to
// any other intersection. For this, you construct a directed graph: vertices are
// intersections, there is an edge (u, v) whenever there is a (one-way) street from
// u to v in the city. Then, it suffices to check whether all the vertices in the
// graph lie in the same strongly connected component.
// Problem Description
// Task. Compute the number of strongly connected components of a given directed graph with n vertices and
// m edges.
// Input Format. A graph is given in the standard format.
// Constraints. 1 ≤ n ≤ 10^4 , 0 ≤ m ≤ 10^4 .
// Output Format. Output the number of strongly connected components.

// Compile command:
// g++ -o scc.exe strongly_connected.cpp -std=c++11
// Execution command:
// ./scc.exe tests/input*.txt

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>

using std::vector;
using std::pair;
using std::string;
using std::ifstream;
using std::endl;
using std::cout;

void Visited(int u, vector<bool>& visited, vector<vector<int>>& adj, vector<int>& L);
void Assign(int u, int root, vector<int>& assigned_component, vector<vector<int>>& reverse_adj);
vector<vector<int>> Reverse(vector<vector<int>>& adj);
int UniqueElements(vector<int>& vec);

int number_of_strongly_connected_components(vector<vector<int>>& adj) {
  int result = 0;
  // Kosaraju's algorithm
  // A. For each vertex u of the graph, mark u as unvisited. Let L be empty.
  // bool *visited = new bool[adj.size()];
  vector<bool> visited(adj.size(), false);
  vector<int> L(adj.size());
  // B. For each vertex u of the graph do Visit(u), where Visit(u) is the recursive subroutine:
  //    If u is unvisited then:
  //      Mark u as visited.
  //      For each out-neighbour v of u, do Visit(v).
  //      Prepend u to L.
  //    Otherwise do nothing.
  for (int u = 0; u < adj.size(); ++u) {
    Visited(u, visited, adj, L);
  }
  // C. For each element u of L in order, do Assign(u,u) where Assign(u,root) is the recursive subroutine:
  //    If u has not been assigned to a component then:
  //      Assign u as belonging to the component whose root is root.
  //      For each in-neighbour v of u, do Assign(v,root).
  //    Otherwise do nothing.
  vector<int> assigned_component(adj.size(), -1);
  vector<vector<int>> reverse_adj = Reverse(adj);

  for (int u: L) {
    Assign(u, u, assigned_component, reverse_adj);
  }

  // Count unique elements in assigned_component
  result = UniqueElements(assigned_component);
  return result;
}

void Visited(int u, vector<bool>& visited, vector<vector<int>>& adj, vector<int>& L) {
  if (!visited[u]) {
    visited[u] = true;
    for (int v: adj[u]) {
      Visited(v, visited, adj, L);
    }
    L.insert(L.begin(), u);
  }
}

void Assign(int u, int root, vector<int>& assigned_component, vector<vector<int>>& reverse_adj) {
  if (assigned_component[u] == -1) {
    assigned_component[u] = root;
    for (int v: reverse_adj[u]) {
      Assign(v, root, assigned_component, reverse_adj);
    }
   }
}

vector<vector<int>> Reverse(vector<vector<int>>& adj) {
  vector<vector<int>> reverse_adj(adj.size(), vector<int>());
  for (int u = 0; u < adj.size(); ++u) {
    for (int v: adj[u]) {
      reverse_adj[v].push_back(u);
    }
  }
  return reverse_adj;
}

int UniqueElements(vector<int>& vec) {
  std::unordered_set<int> set;
  int result = 0;
  for (int u: vec) {
    if (set.count(u) == 0) {
      set.insert(u);
      result++;
    }
  }

  return result;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    cout << "Please provide a filename for testing." << endl;
  } else {
    ifstream fs;
    fs.exceptions(ifstream::failbit | ifstream::badbit);
    try {
      fs.open(argv[1]);

      // Original main
      size_t n, m;
      fs >> n >> m;
      vector<vector<int> > adj(n, vector<int>());
      for (size_t i = 0; i < m; i++) {
        int x, y;
        fs >> x >> y;
        adj[x - 1].push_back(y - 1);
      }
      cout << number_of_strongly_connected_components(adj) << endl;
    } catch (ifstream::failure& e) {
      std::cerr << "Exception opening/reading file" << endl;
    }
    fs.close();
  }
  return 0;

}
