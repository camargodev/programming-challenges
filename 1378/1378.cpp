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

double dist(Point p, Point q) {
    double x = p.x - q.x;
    double y = p.y - q.y;
    
    return x*x + y*y;
}

bool is_isosceles(int i, int j, int k) {
    double dist_i_j = dist(points[i], points[j]);
    double dist_i_k = dist(points[i], points[k]);
    double dist_j_k = dist(points[j], points[k]);
    if (dist_i_j == dist_i_k && dist_i_k == dist_j_k) return false;
    if (dist_i_j == dist_i_k) return true;
    if (dist_j_k == dist_i_k) return true;
    if (dist_i_j == dist_j_k) return true;
    return false;
}

int count_isosceles_vertex(int num_points) {
    int count = 0;  
    for (int i = 0; i < num_points; i++) 
        for (int j = 0; j < i; j++) 
            for (int k = 0; k < j; k++) 
                if (is_isosceles(i,j,k))
                    count += 1;
          
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