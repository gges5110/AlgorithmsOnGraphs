/*
Problem Description
Task. Given an directed graph with possibly negative edge weights and with n vertices and m edges as well
as its vertex s, compute the length of shortest paths from s to all other vertices of the graph.
Input Format. A graph is given in the standard format.
Constraints. 1 ≤ n ≤ 10^3 , 0 ≤ m ≤ 10^4 , 1 ≤ s ≤ n, edge weights are integers of absolute value at most
10^9 .
Output Format. For all vertices i from 1 to n output the following on a separate line:
• “*”, if there is no path from s to u;
• “-”, if there is a path from s to u, but there is no shortest path from s to u (that is, the distance
from s to u is −∞);
• the length of a shortest path otherwise.

Compile command:
g++ -o shortest_paths.exe shortest_paths.cpp -std=c++11
Execution command:
./shortest_paths.exe tests/input*.txt
*/

#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::ifstream;
using std::pair;
using std::priority_queue;

void shortest_paths(const vector<vector<int>> &adj, const vector<vector<int>> &cost, int s, vector<long long> &distance, vector<int> &reachable, vector<int> &shortest) {
  //write your code here
  reachable[s] = 1;
  distance[s] = 0;
  queue<int> q;
  int n = adj.size();

  // Do n iterations of Bellman–Ford
  for (int i = 0; i < n; ++i) {
    for (int u = 0; u < n; ++u) {
      for (int j = 0; j < adj[u].size(); ++j) {
        int v = adj[u][j], alt = distance[u] + cost[u][j];
        if (distance[u] != std::numeric_limits<long long>::max() && distance[v] > alt) {
          distance[v] = alt;
          reachable[v] = 1;
          if (i == n - 1) {
            // save all nodes relaxed on n-th iteration
            q.push(v);
          }
        }
      }
    }
  }

  vector<bool> visited(n, false);
  // Do breadth-first search with queue Q and find all nodes reachable from A
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    visited[u] = true;
    // All those reachable nodes and only those can have infinite arbitrage
    shortest[u] = 0;

    for (int v: adj[u]) {
      if (visited[v] == false) {
        q.push(v);
      }
    }
  }

  shortest[s] = 1;
  distance[s] = 0;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Please provide a valid filename for testing." << std::endl;
  } else {
    ifstream fs;
    fs.exceptions(ifstream::failbit | ifstream::badbit);
    try {
      fs.open(argv[1]);

      // Original main
      int n, m, s;
      fs >> n >> m;
      vector<vector<int> > adj(n, vector<int>());
      vector<vector<int> > cost(n, vector<int>());
      for (int i = 0; i < m; i++) {
        int x, y, w;
        fs >> x >> y >> w;
        adj[x - 1].push_back(y - 1);
        cost[x - 1].push_back(w);
      }
      fs >> s;
      s--;
      vector<long long> distance(n, std::numeric_limits<long long>::max());
      vector<int> reachable(n, 0);
      vector<int> shortest(n, 1);
      shortest_paths(adj, cost, s, distance, reachable, shortest);
      for (int i = 0; i < n; i++) {
        if (!reachable[i]) {
          std::cout << "*\n";
        } else if (!shortest[i]) {
          std::cout << "-\n";
        } else {
          std::cout << distance[i] << "\n";
        }
      }
    } catch (ifstream::failure& e) {
      std::cerr << "Exception opening/reading file" << std::endl;
    }
    fs.close();
  }
  return 0;
}
