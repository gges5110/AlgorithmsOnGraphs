/*
Problem: Detecting Anomalies in Currency Exchange RatesProblem Description
Task. Given an directed graph with possibly negative edge weights and with n vertices and m edges, check
whether it contains a cycle of negative weight.
Input Format. A graph is given in the standard format.
Constraints. 1 ≤ n ≤ 10^3 , 0 ≤ m ≤ 10^4 , edge weights are integers of absolute value at most 10^3.
Output Format. Output 1 if the graph contains a cycle of negative weight and 0 otherwise.

Compile command:
g++ -o negative_cycle.exe negative_cycle.cpp -std=c++11
Execution command:
./negative_cycle.exe tests/input*.txt
*/


#include <iostream>
#include <fstream>
#include <vector>
#include <limits.h>

using std::vector;
using std::ifstream;

// https://stackoverflow.com/questions/16898416/fastest-algorithm-to-detect-if-there-is-negative-cycle-in-a-graph

int negative_cycle(const vector<vector<int>> &adj, const vector<vector<int>> &cost) {
  // write your code here
  int n = adj.size();
  vector<int> dist(n, INT_MAX);
  dist[0] = 0;

  for (int u = 1; u < n; ++u) {
    for (int j = 0; j < adj[u].size(); ++j) {
      int v = adj[u][j], alt = dist[u] + cost[u][j];
      if (alt < dist[v]) {
        dist[v] = alt;
      }
    }
  }

  for (int u = 0; u < n; ++u) {
    for (int j = 0; j < adj[u].size(); ++j) {
      int v = adj[u][j];
      if (dist[u] + cost[u][j] < dist[v]) {
        return 1;
      }
    }
  }

  return 0;
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
      int n, m;
      fs >> n >> m;
      vector<vector<int> > adj(n, vector<int>());
      vector<vector<int> > cost(n, vector<int>());
      for (int i = 0; i < m; i++) {
        int x, y, w;
        fs >> x >> y >> w;
        adj[x - 1].push_back(y - 1);
        cost[x - 1].push_back(w);
      }
      std::cout << negative_cycle(adj, cost) << std::endl;
    } catch (ifstream::failure& e) {
      std::cerr << "Exception opening/reading file" << std::endl;
    }
    fs.close();
  }
  return 0;
}
