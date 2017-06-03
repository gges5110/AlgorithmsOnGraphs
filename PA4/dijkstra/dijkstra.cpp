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
Constraints. 1 ≤ n ≤ 10 3 , 0 ≤ m ≤ 10 5 , u 6 = v, 1 ≤ u, v ≤ n, edge weights are non-negative integers not
exceeding 10 3 .
Output Format. Output the minimum weight of a path from u to v, or −1 if there is no path
*/

#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

int distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
  //write your code her
  return -1;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, cost, s, t);
}
