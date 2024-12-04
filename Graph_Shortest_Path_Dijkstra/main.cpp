#include <bits/stdc++.h>

#define INFINITE INT_MAX

using namespace std;

typedef pair<int, int> myPair;
typedef struct road Struct;


class Graph{

    int vrt;
    list<pair<int, int> > * adj;

public:
    explicit Graph(int vertex);
    void addingEdge(int z, int y, int x);
    Struct dijkstra(int source, int dest);

};

struct road{

    list<int> road;
    int dist{};

};


Graph::Graph(int vertex) {
    this -> vrt = vertex;
    adj = new list<myPair>[vertex];
}

void Graph::addingEdge(int z, int y, int x) {
    adj[y].emplace_back(z, x);
    adj[z].emplace_back(y, x);
}

Struct Graph::dijkstra(int source, int dest) {
    int dist[vrt], prn[vrt];
    priority_queue<myPair, vector<myPair>, greater<>> priorityQueue;

    for (int i = 0; i < vrt; i++)
        dist[i] = INFINITE;
    priorityQueue.push(make_pair(0, source));
    dist[source] = 0;

    for (int j = 0; j < vrt; j++)
        prn[j] = -1;
    prn[source] = source;

    while (!priorityQueue.empty()) {
        int t = priorityQueue.top().second;
        if (t == dest) {
            Struct str;
            int i = dest;
            str.dist = dist[dest];

            while (prn[i] != i) {
                if (i == (100000 + prn[i]))
                    str.road.push_front(0);
                else if (i >= 100000)
                    str.road.push_front(i - 100000 + 1);
                else
                    str.road.push_front(i + 1);
                i = prn[i];
            }
            str.road.push_front(source + 1);
            return str;
        }
        priorityQueue.pop();

        list<pair<int, int>>::iterator iter;

        for (iter = adj[t].begin(); iter != adj[t].end(); ++iter) {
            int edgeWeight = (*iter).second;
            int vertex = (*iter).first;

            if (dist[vertex] > dist[t] + edgeWeight) {
                dist[vertex] = dist[t] + edgeWeight;
                prn[vertex] = t;
                priorityQueue.push(make_pair(dist[vertex], vertex));
            }
        }
    }

    Struct str;
    int index = dest;
    str.dist = dist[dest];

    while (prn[index] != index) {
        if (index >= 100000)
            str.road.push_front(index - 100000 + 1);
        else if (index == (prn[index] + 100000))
            str.road.push_front(0);
        else
            str.road.push_front(index + 1);
        index = prn[index];
    }

    str.road.push_front(source + 1);
    return str;
}

int main() {
    Graph myGraph(200000);
    int edges, vertices;
    int  shirin, farhad;

    cin >> vertices;
    cin >> edges;
    cin >> farhad;
    cin >> shirin;

    int grf[vertices];
    for (int i = 0; i < vertices; i++) {
        cin >> grf[i];
        if (grf[i] != (-1))
            myGraph.addingEdge(i, i + 100000, grf[i]);
    }

    for (int i = 0; i < edges; i++) {
        int x, z, y;
        cin >> z;
        cin >> y;
        cin >> x;
        y--;
        z--;
        myGraph.addingEdge(z, y, x);
        myGraph.addingEdge(z + 100000, y + 100000, x);
    }

    vector<Struct> path;
    Struct point = myGraph.dijkstra((farhad - 1), (shirin + 100000 - 1));
    cout<< point.dist<< endl;

    for (const auto &item: point.road)
        cout<< item <<" ";

    return 0;
}
