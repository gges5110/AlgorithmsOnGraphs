#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using std::vector;
using std::pair;
using std::string;
using std::ifstream;
using std::endl;
using std::cout;

// g++ -o toposort.exe toposort.cpp -std=c++11

bool dfs(vector<vector<int> > &adj, vector<int> &color, int u) {
  color[u] = 1;
  for (int v: adj[u]) {
    if (!color[v]) {
      if(dfs(adj, color, v)) {
        return true;
      }
    } else if (color[v] == 1) {
      return true;
    }
  }
  color[u] = -1;
  return false;
}

bool acyclic(vector<vector<int> > &adj) {
  // 0: white, 1:gray, -1:black
  vector<int> color(adj.size());

  for (int i = 0; i < adj.size(); ++i) {
    if (!color[i]) {
      if(dfs(adj, color, i)) {
        return true;
      }
    }
  }

  return false;
}

void DFS(vector<vector<int> > &adj, vector<int> &color, vector<int> &order, int u) {
  color[u] = 1;
  for (int v: adj[u]) {
    if (!color[v]) {
      DFS(adj, color, order, v);
    }
  }
  color[u] = -1;
  order.push_back(u);
}

vector<int> toposort(vector<vector<int> > adj) {
  vector<int> color(adj.size(), 0);
  vector<int> order;
  DFS(adj, color, order, 0);
  std::reverse(order.begin(), order.end());
  return order;
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

      if(!acyclic(adj)) {
        vector<int> order = toposort(adj);

        for (size_t i = 0; i < order.size(); i++) {
          std::cout << order[i] + 1 << " ";
        }
        cout << endl;
      } else {
        cout << "The graph is not acyclic." << endl;
      }

    } catch (ifstream::failure& e) {
      std::cerr << "Exception opening/reading file" << endl;
    }
    fs.close();
  }
  return 0;
}
