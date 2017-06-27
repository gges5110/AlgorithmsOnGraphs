/*
Computing the Minimum Cost of a Flight
Problem Introduction
Now, you are interested in minimizing not the number of segments, but the total cost of a flight. For this
you construct a weighted graph: the weight of an edge from one city to another one is the cost of the
corresponding flight.
Problem Description
Task. Given an directed graph with positive edge weights and with n vertices and m edges as well as two
vertices u and v, compute the weight of a shortest path between u and v (that is, the minimum total
weight of a path from u to v).
Input Format. A graph is given in the standard format. The next line contains two vertices u and v.
Constraints. 1 ≤ n ≤ 10^3 , 0 ≤ m ≤ 10^5 , u ! = v, 1 ≤ u, v ≤ n, edge weights are non-negative integers not
exceeding 10^3.
Output Format. Output the minimum weight of a path from u to v, or −1 if there is no path

Compile command:
g++ -o dijkstra.exe dijkstra.cpp -std=c++11
Execution command:
./dijkstra.exe tests/input*.txt
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <limits.h>

using std::vector;
using std::ifstream;

int extractMin(const vector<int> &dist, const vector<bool> &visited) {
  int min = INT_MAX, min_index = -1;
  for (int i = 0; i < dist.size(); ++i) {
    if (!visited[i] && min > dist[i]) {
      min = dist[i];
      min_index = i;
    }
  }

  return min_index;
}

bool allVisited(const vector<bool> &visited) {
  for (bool b: visited) {
    if (!b) {
      return false;
    }
  }
  return true;
}

int distance(const vector<vector<int>> &adj, const vector<vector<int>> &cost, int s, int t) {
  // write your code here
  int n = adj.size();
  vector<int> dist(n, INT_MAX); //, prev(n, -1); We don't need the path.
  vector<bool> visited(n, false);
  dist[s] = 0;

  while (!allVisited(visited)) {
    int u = extractMin(dist, visited);
    visited[u] = true;

    if (u == t) {
      break;
    } else {
      for (int j = 0; j < adj[u].size(); ++j) {
        int v = adj[u][j];
        // std::cout << "cost[" << u << "][" << v << "] = " << cost[u][j] << std::endl;
        int alt = dist[u] + cost[u][j];
        if (alt < dist[v]) {
          dist[v] = alt;
        }
      }
    }
  }

  return dist[t] == INT_MAX ? -1 : dist[t];
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
      int s, t;
      fs >> s >> t;
      s--, t--;
      std::cout << distance(adj, cost, s, t) << std::endl;
    } catch (ifstream::failure& e) {
      std::cerr << "Exception opening/reading file" << std::endl;
    }
    fs.close();
  }
  return 0;
}
