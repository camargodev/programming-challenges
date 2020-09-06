#include <iostream> 
#include <list> 
#include <stack>
#include <vector>
#define NIL -1 
using namespace std; 

using Node = int;

class Graph {
    int numOfNodes;
    // bool *visited;
    // bool *isInStack;
    // Node low;
    // stack<Node> *nodeStack;
    // vector<Node> *sccs;
    vector<Node> *edges;
    int id = 0;
    int numOfSccs = 0;
    vector<vector<Node>> bridges;

    void buildBrigesHelper(Node node, bool visited[], Node ids[], Node low[], Node parent[])  {
    
        // Mark the current node as visited 
        visited[node] = true; 
    
        // Initialize discovery time and low value 
        ids[node] = id;
        low[node] = id; 
        id += 1;
    
        for (int i = 0; i < edges[node].size(); i++) {
            Node to = edges[node][i];
            if (!visited[to])  { 
                parent[to] = node; 
                buildBrigesHelper(to, visited, ids, low, parent); 
                low[node]  = min(low[node], low[to]); 

                if (low[to] > ids[node]) {
                    vector<Node> bridgeParts;
                    bridgeParts.push_back(node);
                    bridgeParts.push_back(to);
                    bridges.push_back(bridgeParts);
                }
            } else if (to != parent[node]) 
                low[node]  = min(low[node], ids[to]); 
        } 
    } 

    void buildSccsHelper(Node node, int ids[], Node low[], 
                            stack<Node> *nodeStack, bool isInStack[]) {
        // cout << "Visiting " << node << endl;
        nodeStack->push(node);
        
        isInStack[node] = true;
        low[node] = id;
        ids[node] = id;
        id++;

        for (int i = 0; i < edges[node].size(); i++) {
            Node to = edges[node][i];
            // cout << to << " is a child of " << node << endl;
            if (ids[to] == -1)
                buildSccsHelper(to, ids, low, nodeStack, isInStack);
            if (isInStack[to]) {
                low[node] = min(low[node], low[to]);
                // cout << "Since " << to << " is on the stack, ";
                // cout << "I set low of " << node << " to " << low[node] << endl; 
            }
        }

        if (low[node] == ids[node]) {
            while(!nodeStack->empty()) {
                Node stackTop = nodeStack->top();
                nodeStack->pop();
                isInStack[stackTop] = false;
                low[stackTop] = ids[node];
                if (stackTop == node)
                    break;
            }
            numOfSccs += 1;
        }
    }
    public:
        Graph(int numOfNodes) {
            this->numOfNodes = numOfNodes;
            // visited = new list<bool>[numOfNodes];
            // isInStack = new list<bool>[numOfNodes];
            // nodeStack = new stack<Node>[numOfNodes];
            // low = new list<Node>[numOfNodes];
            // sccs = new vector<Node>[numOfNodes];
            edges = new vector<Node>[numOfNodes];
            // for (int i = 0; i < numOfNodes; i++) {
            //     visited[i] = false;
            //     isInStack[i] = false;
            // }
        }
        void addDirectionalEdge(Node from, Node to) {
            edges[from].push_back(to);
            // cout << "Edge from " << from << " to " << to << endl;
        }
        void addBidirectionalEdge(Node from, Node to) {
            edges[from].push_back(to);
            edges[to].push_back(from);
            // cout << "Edge from " << from << " to " << to << endl;
            // cout << "Edge from " << to << " to " << from << endl;
        }
        Node* buildSccs() {
            // bool *visited = new bool[this->numOfNodes]; 
            Node *ids = new Node[this->numOfNodes];
            Node *low = new Node[this->numOfNodes]; 
            stack<Node> *nodeStack = new stack<Node>();
            bool *isInStack = new bool[numOfNodes]; 

            this->id = 0;
            this->numOfSccs = 0;

            for (int i = 0; i < numOfNodes; i++) {
                ids[i] = -1;
                isInStack[i] = false;
            }

            for (int i = 0; i < numOfNodes; i++) {
                if (ids[i] == -1) {
                    buildSccsHelper(i, ids, low, nodeStack, isInStack);
                }
            }
            return low;
        }
        int getNumOfSccs() {
            return this->numOfSccs;
        }
        vector<vector<Node>> buildBridges()  { 
            // Mark all the vertices as not visited 
            bool *visited = new bool[this->numOfNodes]; 
            Node *ids = new int[this->numOfNodes]; 
            Node *low = new int[this->numOfNodes]; 
            Node *parent = new int[this->numOfNodes]; 
        
            for (int i = 0; i < this->numOfNodes; i++)  { 
                parent[i] = NIL; 
                visited[i] = false; 
            } 

            this->id = 0;
        
            for (int i = 0; i < this->numOfNodes; i++) 
                if (!visited[i]) 
                    buildBrigesHelper(i, visited, ids, low, parent); 
            
            return bridges;
        } 
};

int main() 
{ 
    int numOfNodes, numOfEdges;
    int x = 0;
    while(cin >> numOfNodes >> numOfEdges) {
        // cout << "Test case " << ++x << endl;
        Graph directedGraph(numOfNodes);
        Graph undirectedGraph(numOfNodes);

        for (int i = 0; i < numOfEdges; i++) {
            int from, to, direction;
            
            cin >> from >> to >> direction;
            from = from - 1; to = to - 1;

            if (i == 0) continue;

            if (direction == 1) directedGraph.addDirectionalEdge(from, to);
            else directedGraph.addBidirectionalEdge(to, from);

            undirectedGraph.addBidirectionalEdge(to, from);
        }
        
	    undirectedGraph.buildSccs();
        if (undirectedGraph.getNumOfSccs() > 1) {
            cout << "*" << endl;
            continue;
        }

	    Node* sccs = directedGraph.buildSccs();
        if (directedGraph.getNumOfSccs() == 1) {
            cout << "-" << endl;
            continue;
        }

        // for (int i = 0; i < numOfNodes; i++)
        //     cout << sccs[i] << " ";
        // cout << endl;

        vector<vector<Node>> bridges = undirectedGraph.buildBridges();
        bool foundCrossBridge = false;
        for (int i = 0; i < bridges.size(); i++) {
            Node bridgeFrom = bridges[i][0];
            Node bridgeTo = bridges[i][1];
            if (sccs[bridgeFrom] != sccs[bridgeTo] && !foundCrossBridge) {
                cout << "2" << endl;
                foundCrossBridge = true;
            }
            // cout << "Bridge from " << bridgeFrom << " to " << bridgeTo << endl;
        }
        if (!foundCrossBridge)
            cout << "1" << endl;
        // directionalGraph.printSccs();
        

    }
    return 0;
}