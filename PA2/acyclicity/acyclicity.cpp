// Problem: Checking Consistency of CS Curriculum
// Problem Introduction
// A Computer Science curriculum specifies the prerequisites for each course as a list of courses that should be
// taken before taking this course. You would like to perform a consistency check of the curriculum, that is,
// to check that there are no cyclic dependencies. For this, you construct the following directed graph: vertices
// correspond to courses, there is a directed edge (u, v) is the course u should be taken before the course v.
// Then, it is enough to check whether the resulting graph contains a cycle.
// Problem Description
// Task. Check whether a given directed graph with n vertices and m edges contains a cycle.

// Compile command:
// g++ -o acyclicity.exe acyclicity.cpp -std=c++11
// Execution command:
// ./acyclicity.exe tests/input*.txt

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

bool DFS(vector<vector<int> > &, vector<int> &, int);

bool acyclic(vector<vector<int> > &adj) {
  // 0: white, 1:gray, -1:black
  vector<int> color(adj.size());

  for (int i = 0; i < adj.size(); ++i) {
    if (!color[i]) {
      if(DFS(adj, color, i)) {
        return true;
      }
    }
  }

  return false;
}

bool DFS(vector<vector<int> > &adj, vector<int> &color, int u) {
  color[u] = 1;
  for (int v: adj[u]) {
    if (!color[v]) {
      if(DFS(adj, color, v)) {
        return true;
      }
    } else if (color[v] == 1) {
      return true;
    }
  }
  color[u] = -1;
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
      }
      if (acyclic(adj)) {
        cout << "The graph is acyclic." << endl;
      } else {
        cout << "The graph is cyclic." << endl;
      }

    } catch (ifstream::failure& e) {
      std::cerr << "Exception opening/reading file" << endl;
    }
    fs.close();
  }
  return 0;
}
