#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using std::vector;
using std::pair;
using std::string;
using std::ifstream;
using std::endl;
using std::cout;

// Compile command: g++ -o reachability.exe reachability.cpp -std=c++11
// Problem Description:
// Task. Given an undirected graph and two distinct vertices u and v, check if there is a path between u and v
// Input Format. An undirected graph with n vertices and m edges. The next line contains two vertices u and v
// of the graph.
// Output Format. Output 1 if there is a path between u and v and 0 otherwise.

bool DFS(vector<vector<int> > &, vector<bool> &, int, int);

int reach(vector<vector<int> > &adj, int x, int y) {
  //write your code here
  vector<bool> visited(adj.size());
  bool connected = DFS(adj, visited, x, y);
  return connected ? 1 : 0;
}

bool DFS(vector<vector<int> > &adj, vector<bool> &visited, int source, int sink) {
  visited[source] = true;
  if (source == sink) {
    return true;
  } else {
    for (int s: adj[source]) {
      if (!visited[s]) {
        if (DFS(adj, visited, s, sink)) {
          return true;
        }
      }
    }
  }

  return false;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    cout << "Please provide a filename for testing." << endl;
  } else {
    ifstream fs;
    fs.exceptions(ifstream::failbit | ifstream::badbit);
    try {
      fs.open(argv[1]);

      size_t n, m;
      fs >> n >> m;
      vector<vector<int> > adj(n, vector<int>());
      for (size_t i = 0; i < m; i++) {
        int x, y;
        fs >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
      }
      int x, y;
      fs >> x >> y;
      cout << reach(adj, x - 1, y - 1) << endl;
    } catch (ifstream::failure& e) {
      std::cerr << "Exception opening/reading file" << endl;
    }
    fs.close();
  }
  return 0;
}
