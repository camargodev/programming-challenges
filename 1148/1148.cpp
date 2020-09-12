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
    vector<bool>* adj;

    public:
        Graph(int numNodes) {
            this->numNodes = numNodes;
            this->edges = new vector<Edge>[numNodes];
            this->adj = new vector<bool>[numNodes];
            for (int i = 0; i < numNodes; i++)
                for (int j = 0; j < numNodes; j++)
                    adj[i].push_back(false);
        }
        void addEdge(int from, Edge edge) {
            edges[from].push_back(edge);
            // adj[from].push_back(edge.to);
            adj[from][edge.to] = true;
            // cout << "Setei true de " << from << " -> " << edge.to << endl;
        }
        int* dijkstra(int source) {
            NodePQ heap;
            bool* visited = new bool[numNodes];
            // bool* sameCountry = new bool[numNodes];
            int* dist = new int[numNodes];
            
            for(int i = 0; i < numNodes; i++) { 
                visited[i] = false;
                // sameCountry[i] = false;
                dist[i] = INF;
            }

            // for (int i = 0; i < edges[source].size(); i++) {
            //     Edge edge = edges[source][i];
            //     sameCountry[edge.to] = true;
            // }

            dist[source] = 0;
            heap.push(Node(source, 0));
            
            while(heap.size() > 0) {
                Node node = heap.top();
                heap.pop();
                visited[node.index] = true;
                int from = node.index;
                for (int i = 0; i < edges[from].size(); i++) {
                    Edge edge = edges[node.index][i];
                    if (visited[edge.to]) continue;
                    int cost = edge.cost;
                    // cout << from << " -> " << edge.to << endl;
                    if (adj[from][edge.to] && adj[edge.to][from]) {
                        // cout << adj[from][edge.to] << " && " << adj[edge.to][from] << endl;
                        cost = 0;
                    }
                    int newDist = dist[node.index] + cost;
                    if (newDist < dist[edge.to]) {
                        dist[edge.to] = newDist;
                        heap.push(Node(edge.to, newDist));
                    }
                }
            }
            return dist;
        }
};

bool endOfInput(int n, int m) {
    return (n==0) && (m==0);
}

int main() {
    // cout << "1 " << endl;
    while(true) {
        int numNodes, numEdges, queries, destiny, source;
        cin >> numNodes >> numEdges;
        
        if (endOfInput(numNodes, numEdges)) {
            break;
        }
       
        Graph graph(numNodes);
        for(int i = 0; i < numEdges; i++) {
            int from, to, cost;
            cin >> from >> to >> cost;
            from--; to--;
            graph.addEdge(from, Edge(to, cost));
        }

        cin >> queries;

        for (int q = 0; q < queries; q++) {
            cin >> source >> destiny;
            source--; destiny--;
            int* dist = graph.dijkstra(source);
            if (dist[destiny] == INF)
                cout << "Nao e possivel entregar a carta" << endl;
            else
                cout << dist[destiny] << endl;
        } 
        cout << endl;

    }
    return 0;
}