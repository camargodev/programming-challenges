#include<iostream>
#include <queue>

using namespace std;
using ull = long;
using Node = long;

struct Edge {
  Node from;
  Node to;
  ull cost;
  Edge(Node from, Node to, float cost): from(from),
                                        to(to),
                                        cost(cost)  {}
};


struct EdgeComparator {
    bool operator()(Edge const& e1, Edge const& e2) {
        return (e1.cost > e2.cost);
    }
};

class Graph {
    priority_queue<Edge, vector<Edge>, EdgeComparator> graph;
    ull *nodeClustersRoots;
    ull *nodeClustersSizes;
    long numberOfClusters;
    void updateClusterRoots(ull cluster, ull root) {
        while (cluster != root) {
            int newCluster = this->nodeClustersRoots[cluster];
            this->nodeClustersRoots[cluster] = root;
            cluster = newCluster;
        }
    }
    void printRoots() {
        cout << "[ ";
        for (int i = 0; i < 7; i++) {
            cout << this->nodeClustersRoots[i] << " ";
        }
        cout << "]" << endl;
    }
    ull getClusterRootNode(ull cluster) {
        long clusterRoot = cluster;
        while (clusterRoot != this->nodeClustersRoots[clusterRoot])
            clusterRoot = this->nodeClustersRoots[clusterRoot];

        this->updateClusterRoots(cluster, clusterRoot);
        return clusterRoot;
    }
    bool areEdgeNodesAlreadyLinked(Edge edge) {
        ull from = getClusterRootNode(edge.from);
        ull to = getClusterRootNode(edge.to);
        //cout << "from: " << from << " to: " << to << endl;
        return from == to;
    }
    void joinClusters(ull cluster1, ull cluster2) {
        long rootCluster1 = getClusterRootNode(cluster1);
        long rootCluster2 = getClusterRootNode(cluster2);
        if (rootCluster1 == rootCluster2)
            return;
        this->nodeClustersRoots[rootCluster1] = rootCluster2;
        this->nodeClustersSizes[rootCluster2] += this->nodeClustersSizes[rootCluster1];
    }
  public:
    Graph() { }
    void initGraph(int numOfNodes) {
        numberOfClusters = numOfNodes;
        nodeClustersRoots = new ull[numOfNodes];
        nodeClustersSizes = new ull[numOfNodes];
        for (int i = 0; i < numOfNodes; i++) {
            this->nodeClustersRoots[i] = i;
            this->nodeClustersSizes[i] = 1;
        }
    }
    void addEdge(Edge edge) {
        // cout << "Added edge " << edge.from << " -> " << edge.to << ": " << edge.cost << endl;
        graph.push(edge);
    }
    Edge getNextEdge() {
        Edge edge = graph.top();
        // cout << "Next: " << edge.from << " -> " << edge.to << ": " << edge.cost << endl;
        graph.pop();
        return edge;
    }
    float getMstSum() {
        float mstSum = 0;
        while(numberOfClusters > 1 && graph.size() > 0) {
            Edge edge = getNextEdge();
            // printRoots();
            if (!areEdgeNodesAlreadyLinked(edge)) {
                mstSum += edge.cost;
                // cout <<  "Counted: " << edge.cost << endl;
                numberOfClusters--;
                joinClusters(edge.from, edge.to);
            }
        }
        return mstSum;
    }
};


int main()
{
    long numOfNodes, numOfEdges;

    while (true) {

        cin >> numOfNodes >> numOfEdges;
        if (numOfNodes == 0 && numOfEdges == 0) break;

        Graph* graph = new Graph();
        graph->initGraph(numOfNodes);

        for (int i = 0; i < numOfEdges; i++) {
            ull node1, node2, cost;
            cin >> node1 >> node2 >> cost;
            graph->addEdge(Edge(node1, node2, cost));
            // graph->addEdge(Edge(node2, node1, cost));
        }
        float mstSum = graph->getMstSum();
        cout << mstSum << endl;

    }
}
