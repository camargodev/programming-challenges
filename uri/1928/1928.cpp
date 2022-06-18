#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;
using ull = int;

const ull MAX_NUM_OF_CARDS = 50000;

class Node { 
    public:
        ull id;
        ull depth;
        Node* parent;
        vector<Node*> children;
        bool visited = false;
        ull numOfVisitedChildren = 0;
        ull numOfVisits = 0;
        bool cameBackToParent = false;
        Node(ull id, ull depth, Node* parent) { 
            this->id = id; 
            this->depth = depth; 
            this->parent = parent;
            // cout << " Received parent " << this->parent->id << endl;
        }
        Node(ull id, ull depth) {
            this->id = id; 
            this->depth = depth; 
            this->parent = NULL;
        }
        Node() {
            this->id = 0;
            this->depth = 0;
            this->parent = NULL;
        }
        void printMe() {
            cout << "Im " << id;
            if (parent != NULL)
                cout << " (parent: " << parent->id << ")";
            cout << " with depth " << depth;
            cout << ". I have " << children.size() << " kids" << endl;
            for (int i = 0; i < children.size(); i++)
                children[i]->printMe();
        }
};

class Tree {
    private:
       ull numOfNodes;
       vector<ull> edges[MAX_NUM_OF_CARDS];
       Node* nodes[MAX_NUM_OF_CARDS];
    void fillNode(Node *node) {
        // cout << "Building for node " << node->id << endl;
        for (ull i = 0; i < edges[node->id].size(); i++) {
            ull childId = edges[node->id][i];
            // cout << "Child id = " << childId << endl;
            if (node->parent != NULL && node->parent->id == childId)
                continue;
            
            Node* child = new Node(childId, (node->depth+1), node);
            fillNode(child);
            node->children.push_back(child);
        }
        nodes[node->id] = node;
        // cout << "Added node " << node->id << endl;
    }

    public:
        Tree(ull numOfNodes) { 
            this->numOfNodes = numOfNodes; 
        }
        void addEdge(ull from, ull to) {
            //cout << "Adding edge " << from << " <-> " << to << endl;
            edges[from].push_back(to);
            edges[to].push_back(from);
        }
        Node* getRoot() {
            Node* root = new Node;
            fillNode(root);
            return root;
        }
        Node* getNode(ull id) {
            return nodes[id];
        }
};

class LCA {
    public:
        ull getLcaNodeDepth(ull id1, ull id2) {
            ull index1 = indexes[id1];
            ull index2 = indexes[id2];
            // cout << "Im looking for " << id1 << " and " << id2 << endl;
            ull minIndex = min(index1, index2);
            ull maxIndex = max(index1, index2);
            // cout << "I'll look from " << minIndex << " to " << maxIndex << endl;
            ull minDepth = MAX_NUM_OF_CARDS;
            for (int i = minIndex; i <= maxIndex; i++) {
                // cout << "Looking for " << i << endl;
                minDepth = min(minDepth, depths.at(i));
            }
            // cout << "The min depth I found is " << minDepth << endl;
            return minDepth;
        }
        void buildLcaTables(Node* root, int x) {
            if (root == NULL) {
                // cout << "I should end here" << endl;
                returnedToRoot = true;
                return;
            } 
            if (returnedToRoot)
                return;
            indexes[root->id] = depths.size();
            nodes.push_back(root->id);
            depths.push_back(root->depth);
            root->numOfVisits++;
            // cout << endl;
            // cout << x << ": Node id " << root->id << " with depth " << root->depth << endl;
            if (!root->visited) {
                // cout << "I'm visiting " << root->id << endl;
                root->visited = true;
                for (int i = 0; i < root->children.size(); i++) {
                    // cout << "Visiting child " << root->children.at(i)->id << " of " << root->id << endl;
                    root->numOfVisitedChildren++;
                    buildLcaTables(root->children.at(i), x+1);
                }
            }
            if (root->numOfVisitedChildren != root->children.size()) {
                // cout << root-> id << " not ready to come back" << endl;
                return;
            }
            if (root->cameBackToParent) {
                // cout << "This node already came back to parent" << endl;
                return;
            }
            // cout << "For " << root->id << " the num of visits is " << root->numOfVisits;
            // cout << " (max is " << root->children.size()+1 << ")" << endl;
            if (root->numOfVisits > (root->children.size()+1)) {
                // cout << root-> id << " already visited " << (root->children.size()+1) << " times" << endl;
                return;
            }
            // cout << "I am " << root->id << " going back to parent " << endl;
            root->cameBackToParent = true;
            buildLcaTables(root->parent,x-1);
        }

        void printLcaTables(ull num) {
            if ((2*num-1) != nodes.size())
                cout << "ERROR!!!" << endl;
            cout << "Nodes: ";
            for (int i = 0; i < nodes.size(); i++) {
                cout << " " << nodes.at(i);
            }
            cout << endl;
            cout << "Depths:";
            for (int i = 0; i < depths.size(); i++) {
                cout << " " << depths.at(i);
            }
            cout << endl;
            cout << "Indexes:";
            for (int i = 0; i < num; i++) {
                cout << " " << indexes[i];
            }
            cout << endl;
        }
    private:
        // Node* lcaNode;
        vector<ull> nodes;
        vector<ull> depths;
        ull indexes[MAX_NUM_OF_CARDS];
        bool returnedToRoot = false;
};

int main()
{
    ull numOfCards;
    cin >> numOfCards;

    Tree tree(numOfCards);
    LCA lca;

    vector<vector<ull>> parPositions(numOfCards/2);
    for (ull i = 0; i < numOfCards; i++) {
        ull val;
        cin >> val;
        parPositions[val-1].push_back(i);
    }

    for (ull i = 0; i < numOfCards-1; i++) {
        ull from, to;
        cin >> from >> to;
        tree.addEdge(from-1, to-1);
    }

    Node* root = tree.getRoot();
    // root->printMe();
    // cout << "Checkpoint 1" << endl;
    lca.buildLcaTables(root, 0);
    // cout << "Checkpoint 2" << endl;
    // lca.printLcaTables(numOfCards);
    // cout << "Done"<< endl;
    ull totalDistance = 0;
    for (ull i = 0; i < (numOfCards/2); i++) {
        ull card1 = parPositions[i][0]; 
        ull card2 = parPositions[i][1]; 
        // cout << "card1 = " << card1 << endl;
        // cout << "card2 = " << card2 << endl;
        ull lcaDepth = lca.getLcaNodeDepth(card1, card2);
        Node* node1 = tree.getNode(card1);
        Node* node2 = tree.getNode(card2);
        // Node* lcaNode = lca.getLCA(root, card1, card2);
        // cout << "node1 = " << node1->id << " ("<<node1->depth << ")" << endl;
        // cout << "node2 = " << node2->id << " ("<<node2->depth << ")" << endl;
        // cout << " lcadepth = " << lcaDepth;
        ull distance = abs(node1->depth - lcaDepth) + abs(node2->depth - lcaDepth);
        // cout << " dist = " << distance << endl;
        totalDistance += distance;
        // cout << "For " << card1 << " and " << card2 << ", LCA is: " << lcaNode->id << endl;
    }

    cout << totalDistance << endl;
    return 0;
}
