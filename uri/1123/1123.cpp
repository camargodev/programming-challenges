#include <stdio.h>
#include <iostream> 
#include <vector>
#include <queue>
#include <list>

using namespace std; 

#define MAXN 100100
#define INF 0x3f3f3f3f

struct Edge {
    int to;
    int cost;
    Edge(int to, int cost):
        to(to), cost(cost) {}
};

struct Node {
    int index;
    int cost;
    Node(int index, int cost):
        index(index), cost(cost) {}
};

struct HeapComparator {
    bool operator()(Node const& e1, Node const& e2) {
        return (e1.cost > e2.cost);
    }
};

using NodePQ = priority_queue<Node, vector<Node>, HeapComparator>;

class Graph {

    vector<Edge>* edges;
    int numNodes;

    public:
        Graph(int numNodes) {
            this->numNodes = numNodes;
            this->edges = new vector<Edge>[numNodes];
        }
        void addEdge(int from, Edge edge) {
            edges[from].push_back(edge);
        }
        int* dijkstra(int source) {
            NodePQ heap;
            bool* visited = new bool[numNodes];
            int* dist = new int[numNodes];
            
            for(int i = 0; i < numNodes; i++) { 
                visited[i] = false;
                dist[i] = INF;
            }

            dist[source] = 0;
            heap.push(Node(source, 0));
            
            while(heap.size() > 0) {
                Node node = heap.top();
                heap.pop();
                visited[node.index] = true;
                for (int i = 0; i < edges[node.index].size(); i++) {
                    Edge edge = edges[node.index][i];
                    if (visited[edge.to]) continue;
                    int newDist = dist[node.index] + edge.cost;
                    if (newDist < dist[edge.to]) {
                        dist[edge.to] = newDist;
                        heap.push(Node(edge.to, newDist));
                    }
                }
            }
            return dist;
        }
};

bool endOfInput(int n, int m, int d, int s) {
    return (n==0) && (m==0) && (d==0) && (s==0);
}

int main() {
    while(true) {
        int numNodes, numEdges, destiny, source;
        cin >> numNodes >> numEdges >> destiny >> source;
        
        if (endOfInput(numNodes, numEdges, destiny, source)) {
            break;
        }
        destiny = destiny - 1;
       
        Graph graph(numNodes);
        for(int i = 0; i < numEdges; i++) {
            int from, to, cost;
            cin >> from >> to >> cost;
            if (from >= destiny || to == from+1)
                graph.addEdge(from, Edge(to, cost));
            if (to >= destiny || from == to+1)
                graph.addEdge(to, Edge(from, cost));
        }

        int* dist = graph.dijkstra(source);
        cout << dist[destiny] << endl;
    }
    return 0;
}