#include <stdio.h>
#include <iostream> 
#include <vector>
#include <queue>
#include <list>

using namespace std; 
#define INF 0x3f3f3f3f

int maxVal = 0;

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

void updateMaxVal(vector<int> path) {
    int pathSize = path.size()-2;
    maxVal = max(maxVal, pathSize);
}

void print(vector<int> path, int source, int goal) {
    cout << "[ ";
    for (int i = 0; i < path.size(); i++) {
        if (path[i] == source) cout << "S";
        else if (path[i] == goal) cout << "T";
        else cout << path[i]+1;
        cout << " ";
    }
    cout << "]" << endl;
}

bool visitedNodeInPath(vector<int> path, int node) {
    for (int i = 0; i < path.size(); i++) 
        if (path[i] == node) return true; 
    return false;
}

void bfs(struct Graph* graph, int src, int goal) {
    maxVal = 0;
    queue<vector<int>> paths;
    vector<int> firstPath;
    firstPath.push_back(src);
    paths.push(firstPath);
    while(paths.size() > 0) {
        vector<int> path = paths.front();
        paths.pop();
        int lastNode = path[path.size()-1];
        if (lastNode == goal) {
            updateMaxVal(path);
        }
        for (int i = 0; i < graph->edgesFrom[lastNode].size(); i++) {
            SimpleEdge edge = graph->edgesFrom[lastNode][i];
            if (!visitedNodeInPath(path, edge.to)) {
                // print(path, src, goal);
                vector<int> newPath = path;
                newPath.push_back(edge.to);
                paths.push(newPath);
            } else {
                maxVal = 0;
                return;
            }
        }

    }
}

int main() {

    int numFiles;
    while (cin >> numFiles) {
        int source = numFiles; // nodo N
        int goal = numFiles + 1; // nodo N+1
        bool isPrereq[numFiles];
        bool invalidPreReq = false;
        
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
                if (preReq == file) {
                    cout << "-1" << endl;
                    invalidPreReq = true;
                }
                isPrereq[preReq] = true;
            }
        }
        if (invalidPreReq) continue;
        for (int file = 0; file < numFiles; file++) {
            if(!isPrereq[file]) {
                addEdge(graph, Edge(file, goal, -1));
            }
        }

        bfs(graph, source, goal);
        if (maxVal == 0) cout << "-1" << endl;
        else cout << maxVal << endl;
    }
    return 0;
}