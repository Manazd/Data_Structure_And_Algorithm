#include <bits/stdc++.h>

#define INFINITE INT_MAX
using namespace std;

typedef pair<int, int> iPair;


class Graph {
    int V;
    list<pair<int, int> > * adj;

public:
    Graph(int V);
    void add_edge(int u, int v, int w);
    int shortest_path(int source, int destination);
};
Graph::Graph(int V) {
    this->V = V;
    adj = new list<iPair>[V];
}
void Graph::add_edge(int u, int v, int w) {
    adj[u].emplace_back(v, w);
}
int Graph::shortest_path(int source, int destination) {
    priority_queue<iPair, vector<iPair>, greater<>> pq;
    int dis[V];
    for (int i = 0; i < V; i++)
        dis[i] = INFINITE;
    pq.push(make_pair(0, source));
    dis[source] = 0;
    while (!pq.empty()) {
        int u = pq.top().second;
        if (u == destination) return dis[destination];
        pq.pop();
        list<pair<int, int>>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i) {
            int v = (*i).first;
            int weight = (*i).second;
            if (dis[v] > dis[u] + weight) {
                dis[v] = dis[u] + weight;
                pq.push(make_pair(dis[v], v));
            }
        }
    }
    return dis[destination];
}


int main() {
    int cities, roads;
    int person1, person2;
    cin >> cities;
    Graph g(cities);
    cin >> roads;
    cin >> person1;
    cin >> person2;
    for (int i = 0; i < roads; i++) {
        int v1, v2;
        cin >> v1;
        cin >> v2;
        g.add_edge(v1 - 1, v2 - 1, 0);
        g.add_edge(v2 - 1, v1 - 1,  1);
    }
    cout<<g.shortest_path(person1 - 1, person2 - 1);
    return 0;
}
