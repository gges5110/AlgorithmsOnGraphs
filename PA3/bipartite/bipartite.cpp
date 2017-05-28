/*
Problem: Checking whether a Graph is Bipartite
Problem Introduction
An undirected graph is called bipartite if its vertices can be split into two parts such that each edge of the
graph joins to vertices from different parts. Bipartite graphs arise naturally in applications where a graph
is used to model connections between objects of two different types (say, boys and girls; or students and
dormitories).
An alternative definition is the following: a graph is bipartite if its vertices can be colored with two colors
(say, black and white) such that the endpoints of each edge have different colors.
Problem Description
Task. Given an undirected graph with n vertices and m edges, check whether it is bipartite.
Input Format. A graph is given in the standard format.
Constraints. 1 ≤ n ≤ 10^5 , 0 ≤ m ≤ 10^5 .
Output Format. Output 1 if the graph is bipartite and 0 otherwise.

Compile command:
g++ -o bipartite.exe bipartite.cpp -std=c++11
Execution command:
./bipartite.exe tests/input*.txt
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::string;
using std::ifstream;
using std::endl;
using std::cout;

bool BFS(int u, vector<int>& color, const vector<vector<int>>& adj);
bool colorCompare(const vector<int>& color, int u, int v);
int oppositeColor(const vector<int>& color, int u);

int bipartite(const vector<vector<int>> &adj) {
  // write your code here
  int n = adj.size();
	vector<int> color(n, -1);
	for (int u = 0; u < n; ++u) {
		// Do BFS on each node that's not colored.
		if (color[u] == -1) {
		  color[u] = 1;
			if (BFS(u, color, adj)) {
				// Return 0 is the graph is not bipartite.
				return 0;
			}
		}
	}
  return 1;
}


bool BFS(int u, vector<int>& color, const vector<vector<int>>& adj) {
	queue<int> q;
	q.push(u);

	while (!q.empty()) {
		u = q.front();
		q.pop();
		for (int v: adj[u]) {
		  if (color[v] == -1) {
				color[v] = oppositeColor(color, u);
				q.push(v);
			} else {
		  	if (colorCompare(color, u, v)) {
			  	return true;
				}
			}
		}
	}
	return false;
}

bool colorCompare(const vector<int>& color, int u, int v) {
	// Return true if the color collide with each other.
	if (color[u] == -1 || color[v] == -1) {
		return false;
	}
	return color[u] == color[v];
}

int oppositeColor(const vector<int>& color, int u) {
	return color[u] == 1 ? 2 : 1;
}


int main(int argc, char *argv[]) {
  if (argc != 2) {
    cout << "Please provide a valid filename for testing." << endl;
  } else {
    ifstream fs;
    fs.exceptions(ifstream::failbit | ifstream::badbit);
    try {
      fs.open(argv[1]);

      // Original main
  	  int n, m;
  	  fs >> n >> m;
  	  vector<vector<int> > adj(n, vector<int>());
  	  for (int i = 0; i < m; i++) {
  	    int x, y;
  	    fs >> x >> y;
  	    adj[x - 1].push_back(y - 1);
  	    adj[y - 1].push_back(x - 1);
  	  }
  	  std::cout << bipartite(adj) << endl;
    } catch (ifstream::failure& e) {
      std::cerr << "Exception opening/reading file" << endl;
    }
    fs.close();
  }
  return 0;

}

