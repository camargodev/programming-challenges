#include <stdio.h>
#include <iostream> 
#include <vector>
#include <queue>
#include <list>
#include <stack>
#include <math.h>
#include <iomanip>
#include <algorithm>

#define MAX 1010

using namespace std;

using num = long long int;

struct Point { num x; num y; };

Point points[MAX];
num dist[MAX][MAX];

num srq_dist(int i, int j) {
    num dx = points[i].x - points[j].x;
    num dy = points[i].y - points[j].y;
    return dx*dx + dy*dy;
}

int main() {
    int num_points, i, j;
    while(true) {
    	cin >> num_points;

    	if (num_points == 0) break;
    	
        for(i = 0; i < num_points; i++)
            cin >> points[i].x >> points[i].y;
        
        int total_count = 0;
        for(i = 0; i < num_points; i++)  {
            int count_for_i = 0;
            num last = -1L;

            for(j = 0; j < num_points; j++) 
                dist[i][j] = srq_dist(i, j);
                
            sort(dist[i], dist[i] + j);

            for(j = 0; j < num_points; j++)  {
                if (dist[i][j] != last)  {
                    total_count += (count_for_i * (count_for_i - 1)) / 2;
                    count_for_i = 0;
                }
                last = dist[i][j];
                count_for_i++;
            }
            total_count += (count_for_i * (count_for_i - 1)) / 2;
        }

        cout << total_count << endl;
    }
    return 0;
    
}