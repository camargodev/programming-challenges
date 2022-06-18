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
    // vector<bool>* adj;

    public:
        Graph(int numNodes) {
            this->numNodes = numNodes;
            this->edges = new vector<Edge>[numNodes];
            // this->adj = new vector<bool>[numNodes];
            // for (int i = 0; i < numNodes; i++)
            //     for (int j = 0; j < numNodes; j++)
            //         adj[i].push_back(false);
        }
        void addEdge(int from, Edge edge) {
            edges[from].push_back(edge);
            // cout << "Add " << from << " -> " << edge.to << ": " << edge.cost << endl;
            // adj[from].push_back(edge.to);
            // adj[from][edge.to] = true;
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
                    // if (adj[from][edge.to] && adj[edge.to][from]) {
                    //     // cout << adj[from][edge.to] << " && " << adj[edge.to][from] << endl;
                    //     cost = 0;
                    // }
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


int main() {
    int rows, cols;
    cin >> cols >> rows;
    Graph graph(cols*rows);
    int source, goal;
    char maze[cols][rows];
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            char c; cin >> c;
            maze[i][j] = c;
        }
    }
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            int from = i*rows + j;
            char c = maze[i][j];
            // cout << from << ": " << c << endl;

            if (c =='H') source = from;
            if (c == 'E') goal = from;
            if (c == '#') continue;
            if (i > 0 && maze[i-1][j] != '#') {
                int to = (i-1)*rows + j;
                int cost = 0;
                if (maze[i-1][j] != '.' && maze[i-1][j] != 'H' && maze[i-1][j] != 'E')
                    cost = maze[i-1][j] - '0';
                graph.addEdge(from, Edge(to, cost));
            }
            if (i < (cols-1) && maze[i+1][j] != '#') {
                int to = (i+1)*rows + j;
                int cost = 0;
                if (maze[i+1][j] != '.' && maze[i+1][j] != 'H' && maze[i+1][j] != 'E')
                    cost = maze[i+1][j] - '0';
                graph.addEdge(from, Edge(to, cost));
            }
            if (j > 0 && maze[i][j-1] != '#') {
                int to = (i)*rows + (j-1);
                int cost = 0;
                if (maze[i][j-1] != '.' && maze[i][j-1] != 'H' && maze[i][j-1] != 'E')
                    cost = maze[i][j-1] - '0';
                graph.addEdge(from, Edge(to, cost));
            }
            if (j < (rows-1) && maze[i][j+1] != '#') {
                int to = (i)*rows + (j+1);
                int cost = 0;
                if (maze[i][j+1] != '.' && maze[i][j+1] != 'H' && maze[i][j+1] != 'E')
                    cost = maze[i][j+1] - '0';
                graph.addEdge(from, Edge(to, cost));
            }
        }
    }

    // cout << "From " << source << " to " << goal << endl;
    int* dist = graph.dijkstra(source);
    if (dist[goal] == INF)
        cout << "ARTSKJID" << endl;
    else
        cout << dist[goal] << endl;
            
    // cout << "H: " << source << " - E: " << goal << endl;
    return 0;
}