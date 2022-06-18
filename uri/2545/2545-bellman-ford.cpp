#include <stdio.h>
#include <iostream> 
#include <vector>
#include <queue>
#include <list>

using namespace std; 
#define INF 0x3f3f3f3f

struct Edge { 
	int from, to, cost;
    Edge(int from, int to, int cost) :
        from(from), to(to), cost(cost) {} 
}; 

struct SimpleEdge {
    int to, cost;
    SimpleEdge(int to, int cost) : to(to), cost(cost) {}
};

struct Graph { 
	int numNodes, numEdges = 0; 
	vector<Edge> edges; 
    vector<SimpleEdge>* edgesFrom;
}; 

struct Graph* createGraph(int numNodes) { 
	struct Graph* graph = new Graph; 
    graph->edgesFrom = new vector<SimpleEdge>[numNodes];
	graph->numNodes = numNodes; 
	return graph; 
} 

void printMaxDist(int dist[], int goal) { 
    int maxDist = dist[goal];
    if (maxDist == INF) cout << "-1" << endl;
    else cout << maxDist * (-1) << endl;
} 

void addEdge(Graph* graph, Edge edge) {
    graph->edges.push_back(edge);
    graph->numEdges += 1;
    graph->edgesFrom[edge.from].push_back(SimpleEdge(edge.to, edge.cost));
}

void bellmanFord(struct Graph* graph, int src, int goal) { 
	int numNodes = graph->numNodes; 
	int numEdges = graph->numEdges; 
	int distances[numNodes]; 
	for (int i = 0; i < numNodes; i++) distances[i] = INF; 
	distances[src] = 0; 

    queue<int> vertices;
    vertices.push(src);
    while (vertices.size() > 0) {
        int vertice = vertices.front();
        vertices.pop();
        vector<SimpleEdge> edgesFrom = graph->edgesFrom[vertice];
        for (int ef = 0; ef < edgesFrom.size(); ef++) {
            SimpleEdge simpleEdge = edgesFrom[ef];
			if (distances[vertice] != INF 
                && distances[vertice] + simpleEdge.cost < distances[simpleEdge.to]) {
				distances[simpleEdge.to] = distances[vertice] + simpleEdge.cost; 
                vertices.push(simpleEdge.to);
            }
        }
    }
    // bool isChanging = true;
    // while(isChanging) {
	// for (int n = 1; n <= numNodes-1; n++) { 
    //     bool isChanging = false;
	// 	for (int e = 0; e < numEdges; e++) { 
    //         Edge edge = graph->edges[e];
	// 		if (distances[edge.from] != INF 
    //             && distances[edge.from] + edge.cost < distances[edge.to]) {
	// 			distances[edge.to] = distances[edge.from] + edge.cost; 
    //             isChanging = true;
    //         }
	// 	} 
    //     if (!isChanging) break;
	// } 

	for (int e = 0; e < numEdges; e++) { 
        Edge edge = graph->edges[e];
		if (distances[edge.from] != INF 
            && distances[edge.from] + edge.cost < distances[edge.to]) { 
			cout << "-1" << endl;
			return;
		} 
	} 

	printMaxDist(distances, goal); 
	return; 
} 

int main() {

    int numFiles;
    while (cin >> numFiles) {
        int source = numFiles; // nodo N
        int goal = numFiles + 1; // nodo N+1
        bool isPrereq[numFiles];
        
        struct Graph* graph = createGraph(numFiles+2);
        
        for (int f = 0; f < numFiles; f++) 
            isPrereq[f] = false;
        
        for (int file = 0; file < numFiles; file++) {
            int numPreReq;
            cin >> numPreReq;
            if (numPreReq == 0)
                addEdge(graph, Edge(source, file, 0));
            for (int i = 0; i < numPreReq; i++) {
                int preReq; cin >> preReq;
                addEdge(graph, Edge(--preReq, file, -1));
                isPrereq[preReq] = true;
            }
        }
        for (int file = 0; file < numFiles; file++) {
            if(!isPrereq[file]) {
                addEdge(graph, Edge(file, goal, -1));
            }
        }

        bellmanFord(graph, source, goal);
    }
    return 0;
}