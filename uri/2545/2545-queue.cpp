#include <stdio.h>
#include <iostream> 
#include <vector>
#include <queue>
#include <list>

using namespace std; 

struct Node {
    int id, cost;
    Node(int id, int cost) : id(id), cost(cost) {}
};

int main() {

    int numFiles;
    while (cin >> numFiles) {
        // int source = numFiles; // nodo N
        // int goal = numFiles + 1; // nodo N+1
        bool isPrereq[numFiles];
        vector<int>* preReqs = new vector<int>[numFiles];
        
        // struct Graph* graph = createGraph(numFiles+2);
        
        for (int f = 0; f < numFiles; f++) 
            isPrereq[f] = false;
        
        for (int file = 0; file < numFiles; file++) {
            int numPreReq; cin >> numPreReq;
            // if (numPreReq == 0)
            //     addEdge(graph, Edge(source, file, 0));
            for (int i = 0; i < numPreReq; i++) {
                int preReq; cin >> preReq;
                preReqs[file].push_back(--preReq);
                // addEdge(graph, Edge(--preReq, file, -1));
                isPrereq[preReq] = true;
            }
        }

        queue<Node> Q;

        for (int file = 0; file < numFiles; file++) {
            if(!isPrereq[file]) {
                Q.push(Node(file, 1));
            }
        }

        int maxVal = 0;
        while (Q.size() > 0) {
            Node node = Q.front();
            Q.pop();
            maxVal = max(maxVal, node.cost);
            vector<int> reqs = preReqs[node.id];
            for (int i = 0; i < reqs.size(); i++)
                Q.push(Node(reqs[i], node.cost+1));
        }
        if (maxVal == 0) cout << "-1" << endl;
        else cout << maxVal << endl;

        // bellmanFord(graph, source, goal);
    }
    return 0;
}