#include <limits.h> 
#include <string.h> 
#include <iostream> 
#include <queue> 
using namespace std; 

typedef vector<int> Row;
typedef vector<Row> Matrix;

Matrix buildDefaultGraph(int numOfNodes) {
    Matrix graph;
    for (int i = 0; i < numOfNodes; i++) {
        Row row(numOfNodes);
        for (int j = 0; j < numOfNodes; j++) {
            row[j] = 0;
        }
        graph.push_back(row);
    }
    return graph;
}

Matrix copyGraph(int numOfNodes, Matrix original) {
    Matrix graph;
    for (int i = 0; i < numOfNodes; i++) {
        Row row(numOfNodes);
        for (int j = 0; j < numOfNodes; j++) {
            row[j] = original[i][j];
        }
        graph.push_back(row);
    }
    return graph;
}

class Graph {

    int numOfNodes, S, T;

    bool bfs(Matrix residualGraph, int parent[]) { 
        bool visited[numOfNodes]; 
        memset(visited, 0, sizeof(visited)); 
    
        queue<int> nodes; 
        nodes.push(S); 
        visited[S] = true; 
        parent[S] = -1; 

        while (!nodes.empty()) { 
            int from = nodes.front(); 
            nodes.pop(); 
    
            for (int to = 0; to < numOfNodes; to++) {
                if (!visited[to] && residualGraph[from][to] > 0)  { 
                    nodes.push(to); 
                    parent[to] = from; 
                    visited[to] = true; 
                } 
            } 
        } 
        return visited[T]; 
    } 

    public:

    Graph(int numOfNodes, int S, int T) {
        this->numOfNodes = numOfNodes;
        this->S = S;
        this->T = T;
    }
    
    int fordFulkerson(Matrix graph) { 
        int u, v; 
    
        Matrix residualGraph = copyGraph(numOfNodes, graph); 
    
        int parent[numOfNodes];
    
        int maxFlow = 0;  
        while (bfs(residualGraph, parent)) { 
            int pathFlow = INT_MAX; 
            for (int node = T; node != S; node = parent[node])  { 
                int parentNode = parent[node]; 
                pathFlow = min(pathFlow, residualGraph[parentNode][node]); 
            } 
            for (int node = T; node != S; node = parent[node]) { 
                int parentNode = parent[node];
                residualGraph[parentNode][node] -= pathFlow; 
                residualGraph[node][parentNode] += pathFlow; 
            } 
            maxFlow += pathFlow; 
        } 
    
        return maxFlow; 
} 

    
};

int getIndex(string size) {
    // XXL, XL, L, M, S ou XS
    int index;
    if (size == "XXL") index = 0;
    if (size == "XL")  index = 1;
    if (size == "L")   index = 2;
    if (size == "M")  index = 3;
    if (size == "S")   index = 4;
    if (size == "XS")  index = 5;
    return index + 1;
}

int S = 0;
int NUM_SIZES = 6;

int main()  { 
    int numTests;
    cin >> numTests;
    for (int t = 0; t < numTests; t++) {
        int numShirts, numPeople;
        cin >> numShirts >> numPeople;

        int numOfNodes = 1 + NUM_SIZES + numPeople + 1;
        int T = numOfNodes-1;
        int numOfShirtsPerSize = numShirts/NUM_SIZES;
        
        Matrix adj = buildDefaultGraph(numOfNodes);
        for (int c = 0; c < NUM_SIZES; c++)
            adj[S][c+1] = numOfShirtsPerSize;

        for (int i = 0; i < numPeople; i++) {
            string shirtSize1, shirtSize2;
            cin >> shirtSize1 >> shirtSize2;
            int shirtIndex1, shirtIndex2;
            int personIndex = i + NUM_SIZES + 1;
            shirtIndex1 = getIndex(shirtSize1);
            shirtIndex2 = getIndex(shirtSize2);
            adj[shirtIndex1][personIndex] = 1;
            adj[shirtIndex2][personIndex] = 1;
            adj[personIndex][T] = 1;
        }

        Graph graph(numOfNodes, S, T);

        int maxFlow = graph.fordFulkerson(adj);
        if (maxFlow == numPeople) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
} 