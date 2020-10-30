#include <stdio.h>
#include <iostream> 
#include <vector>
#include <queue>
#include <list>
#include <stack>
#include <math.h>
#include <iomanip>
#include <algorithm>

#define MAXN 1010

using namespace std;

struct Point {
    int x;
    int y;
};

Point points[MAXN];
long dists[MAXN][MAXN];

long dist(Point p, Point q) {
    int x = p.x - q.x;
    int y = p.y - q.y;
    
    return x*x + y*y;
}


int count_isosceles_vertex(int num_points) {
    int count = 0;
    for(int i = 0; i < num_points; ++i)  {
        int aux_counter = 0;
        for(int j = 0; j < num_points; ++j)
            dists[i][aux_counter++] = dist(points[i], points[j]);
            
        sort(dists[i], dists[i]+aux_counter);
        
        long last = -1L;
        int counter_for_i = 0;
        
        for(int j = 0; j < aux_counter; ++j) {
            if (dists[i][j] != last) {
                count += (counter_for_i * (counter_for_i-1)) / 2;
                counter_for_i = 0;
            }
            last = dists[i][j];
            counter_for_i++;
        }
        count += (counter_for_i * (counter_for_i-1)) / 2;
    }
    return count;
}

int main() {
    int num_points;
    while(true) {
    	cin >> num_points;
    	if (num_points == 0) 
            break;
    	
        for(int i = 0; i < num_points; ++i)
            cin >> points[i].x >> points[i].y;
        
        int count = count_isosceles_vertex(num_points);
        cout << count << endl;
    }
    
}