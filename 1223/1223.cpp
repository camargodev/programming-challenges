#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <stack>
#include <math.h>
#include <iomanip>

#define EPS 0.000000001
#define INF 2000000000.000000

using namespace std;

struct point {
    int x, y;
    point() {x = y = 0.0;}
    point(int x, int y) : x(x), y(y) {}
    bool operator == (const point &other) const {
		return x == other.x && y == other.y;
    }
};

using vetor = point;

struct segment {
	point start;
	point end;
	segment() {start = point(); end = point();}
	segment(point start, point end) : start(start), end(end) {}
};

vector<segment> pipes;

double point_to_point_distance(point p1, point p2) {
    double x = p1.x - p2.x;
    double y = p1.y - p2.y;
    return sqrt(x*x + y*y);
}

double point_to_segment_distance(point point, segment segment)  { 
  
    vetor segment_vector; // AB
    segment_vector.x = segment.start.x - segment.end.x;
    segment_vector.y = segment.start.y - segment.end.y;
  
    vetor point_to_start_vector; // BE
    point_to_start_vector.x = point.x - segment.start.x;
    point_to_start_vector.y = point.y - segment.start.y;

    vetor point_to_end_vector; // AE
    point_to_end_vector.x = point.x - segment.end.x;
    point_to_end_vector.y = point.y - segment.end.y;
  
    double dot_product_start, dot_product_end; 
    dot_product_start = (segment_vector.x * point_to_start_vector.x + segment_vector.y * point_to_start_vector.y); // AB_BE
    dot_product_end   = (segment_vector.x * point_to_end_vector.x   + segment_vector.y * point_to_end_vector.y); // AB_AE
  
    double distance = 0; 
  
    if (dot_product_start > 0) {
        distance = point_to_point_distance(segment.start, point);
    } else if (dot_product_end < 0) { 
        distance = point_to_point_distance(segment.end, point);
    }  else { 
        double x1 = segment_vector.x; 
        double y1 = segment_vector.y; 
        double x2 = point_to_end_vector.x; 
        double y2 = point_to_end_vector.y; 
        double mod = sqrt(x1*x1 + y1*y1); 
        distance = abs(x1*y2 - y1*x2) / mod; 
    } 
    return distance; 
} 

// 3
// 6 10
// 9 3 8
// 6 2 5
// 4 3 1

int main() {
    int n, l, h;
	while (cin >> n) {

        pipes.resize(n);

		cin >> l >> h;

        segment left_wall = segment(point(0,0), point(0,h));
        segment right_wall = segment(point(l,0), point(l,h));
        segment floor = segment(point(0,0), point(l,0));

		for (int i = 0; i < n; i++) {
            int pipe_start_y, pipe_end_x, pipe_end_y;
			cin >> pipe_start_y >> pipe_end_x >> pipe_end_y;
            int pipe_start_x = 0;
            if (i % 2 != 0) pipe_end_x = l;

            point pipe_start = point(pipe_start_x, pipe_start_y);
            point pipe_end = point(pipe_end_x, pipe_end_y);

            pipes[i] = segment(pipe_start, pipe_end);
		}
		
        double min_dist = INF;
        for (int i = 0; i < n; i++) {
            segment pipe = pipes[i];
            point pipe_point = (i % 2 == 0) ? pipe.end  : pipe.start;
            segment wall     = (i % 2 == 0) ? left_wall : right_wall;

            double min_dist_for_pipe = point_to_segment_distance(pipe_point, wall);
            // cout << "Distance from pipe " << (i+1) << " to wall is " << min_dist_for_pipe << endl;

            if (i < (n-1)) {
                segment next_pipe = pipes[i+1];
                double distance_to_next_pipe = point_to_segment_distance(pipe_point, next_pipe);
                //  cout << "Distance from pipe " << (i+1) << " to next is " << distance_to_next_pipe << endl;
                min_dist_for_pipe = min(min_dist_for_pipe, distance_to_next_pipe);
            }

            // double min_dist_for_pipe = min(distance_to_wall, distance_to_next_pipe);
            // cout << "Min dist for pipe " << (i+1) << " is " << min_dist_for_pipe << endl;

            min_dist = min(min_dist, min_dist_for_pipe);
        }

		cout << setprecision(2) << fixed << min_dist << endl;
		pipes.clear();
	}
}