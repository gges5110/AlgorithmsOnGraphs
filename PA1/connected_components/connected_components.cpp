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

void DFS(vector<vector<int> > &, vector<bool> &, int);

int number_of_components(vector<vector<int> > &adj) {
  int res = 0;
  //write your code here
  vector<bool> visited(adj.size());

  for (int i = 0; i < adj.size(); ++i) {
    if (!visited[i]) {
      res++;
      DFS(adj, visited, i);
    }
  }

  return res;
}

void DFS(vector<vector<int> > &adj, vector<bool> &visited, int source) {
  visited[source] = true;
  for (int s: adj[source]) {
    if (!visited[s]) {
      DFS(adj, visited, s);
    }
  }
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
      cout << number_of_components(adj) << endl;
    } catch (ifstream::failure& e) {
      std::cerr << "Exception opening/reading file" << endl;
    }
    fs.close();
  }
  return 0;
}
