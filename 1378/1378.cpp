#include <stdio.h>
#include <iostream> 
#include <vector>
#include <queue>
#include <list>
#include <stack>
#include <math.h>
#include <iomanip>
#include <algorithm>

#define MAXN 1001

using namespace std;

using num = long;

struct Point {
    num x;
    num y;
};

Point points[MAXN];
num dists[MAXN][MAXN];

num dist(Point p, Point q) {
    num x = p.x - q.x;
    num y = p.y - q.y;
    
    return x*x + y*y;
}


num count_isosceles_vertex(num num_points) {
    num count = 0;
    for(num i = 0; i < num_points; ++i)  {
        num aux = 0;
        for(num j = 0; j < num_points; ++j)
            dists[i][aux++] = dist(points[i], points[j]);
            
        sort(dists[i], dists[i] + aux);
        
        num last = -1L;
        num counter_for_i = 0;
        
        for(num j = 0; j < aux; ++j) {
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
    num num_points;
    while(true) {
    	cin >> num_points;
    	if (num_points == 0) 
            break;
    	
        for(num i = 0; i < num_points; ++i)
            cin >> points[i].x >> points[i].y;
        
        num count = count_isosceles_vertex(num_points);
        cout << count << endl;
    }
    
}