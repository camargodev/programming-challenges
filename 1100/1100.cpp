#include <stdio.h>
#include <iostream> 
#include <vector>
#include <queue>
#include <list>
#include <deque>

using namespace std; 

#define MAXN 100100
#define INF 0x3f3f3f3f

struct Tile {
    int id;
    int x;
    int y;
    int moves = 0;
    bool visited = false;
    Tile() {}
    Tile(int x, int y):
        x(x), y(y) {}
};

class GraphBuilder {
    bool visited[8][8];

    int getLetterIndex(char c) {
        if (c == 'a') return 0;
        if (c == 'b') return 1;
        if (c == 'c') return 2;
        if (c == 'd') return 3;
        if (c == 'e') return 4;
        if (c == 'f') return 5;
        if (c == 'g') return 6;
        if (c == 'h') return 7;
        return -1;
    }
    
    bool isValid(int x, int y) {
        if (x < 0 || y < 0)   return false;
        if (x >= 8 || y >= 8) return false;
        return true;
    }

    vector<Tile> getNexts(Tile tile) {
        vector<Tile> adj;
        int x = tile.x; int y = tile.y;
        if (isValid(x-2,y-1)) adj.push_back(Tile(x-2,y-1));
        if (isValid(x-2,y+1)) adj.push_back(Tile(x-2,y+1));
        if (isValid(x+2,y-1)) adj.push_back(Tile(x+2,y-1));
        if (isValid(x+2,y+1)) adj.push_back(Tile(x+2,y+1));
        if (isValid(x-1,y-2)) adj.push_back(Tile(x-1,y-2));
        if (isValid(x-1,y+2)) adj.push_back(Tile(x-1,y+2));
        if (isValid(x+1,y-2)) adj.push_back(Tile(x+1,y-2));
        if (isValid(x+1,y+2)) adj.push_back(Tile(x+1,y+2));
        return adj;
    }

    public:
        GraphBuilder() {
            for (int i = 0; i < 8; i++)
                for (int j = 0; j < 8; j++)
                    visited[i][j] = false;
        }

        int build(string source, string destiny) {

            int srcx = (getLetterIndex(source.at(0)));
            int srcy = (source.at(1) - '0') - 1;

            int destx = (getLetterIndex(destiny.at(0)));
            int desty = (destiny.at(1) - '0') - 1;

            queue<Tile> tiles;

            Tile sourceTile(srcx, srcy);
            visited[srcx][srcy] = true;
            tiles.push(sourceTile);
            
            while (tiles.size() > 0) {

                Tile tile = tiles.front();
                tiles.pop();
                
                if (tile.x == destx && tile.y == desty) {
                    return tile.moves;
                }
                
                vector<Tile> nexts = getNexts(tile);

                for (int i = 0; i < nexts.size(); i++) {
                    Tile next = nexts.at(i);
                    if (visited[next.x][next.y]) 
                        continue;
                    visited[next.x][next.y] = true;
                    next.moves = tile.moves + 1;
                    tiles.push(next);
                }
            }
        }
};

int main() {
    string from, to;
    while(cin >> from >> to) {
        GraphBuilder builder;
        int dist = builder.build(from, to);
        cout << "To get from " << from;
        cout << " to " << to;
        cout << " takes " << dist;
        cout << " knight moves." << endl;
    }
    return 0;
}