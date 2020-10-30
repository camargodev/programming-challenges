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

int test_main() {
    segment L(point(0,0), point(0,10));
    segment R(point(5,0) , point(5,10));
    
    point pA(3,7);
    point pB(2,4);

    segment X(point(2,4), point(5,7));
    segment Y(point(3,0), point(0,2));

    cout << "from pA to R " << point_to_segment_distance(pA, R) << endl;
    cout << "from pA to X " << point_to_segment_distance(pA, X) << endl;
    cout << "from pB to L " << point_to_segment_distance(pB, L) << endl;
    cout << "from pB to Y " << point_to_segment_distance(pB, Y) << endl;

    return 0;
}

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
            point pipe_start, pipe_end;

            if (i % 2 == 0) {
                pipe_start = point(0, pipe_start_y);
            } else {
                pipe_start = point(l, pipe_start_y);
            }
            pipe_end = point(pipe_end_x, pipe_end_y);

            // cout << "Pipe " << i << " starts in (" << pipe_start.x << "," << pipe_start.y << ") and ends in (";
            // cout << pipe_end.x << "," << pipe_end.y << ")" << endl;

            pipes[i] = segment(pipe_start, pipe_end);
		}
		
        double min_dist = INF;
        for (int i = 0; i < n; i++) {
            segment pipe = pipes[i];
            segment wall = (i % 2 == 0) ? right_wall : left_wall;

            double min_dist_for_pipe = point_to_segment_distance(pipe.end, wall);
            // cout << "Distance from pipe " << (i+1) << " to wall is " << min_dist_for_pipe << endl;

            if (i < (n-1)) {
                segment next_pipe = pipes[i+1];
                double distance_to_next_pipe = point_to_segment_distance(pipe.end, next_pipe);
                //  cout << "Distance from pipe " << (i+1) << " to next is " << distance_to_next_pipe << endl;
                min_dist_for_pipe = min(min_dist_for_pipe, distance_to_next_pipe);
            }

            // cout << "Min dist for pipe " << (i+1) << " is " << min_dist_for_pipe << endl;

            min_dist = min(min_dist, min_dist_for_pipe);
        }

		cout << setprecision(2) << fixed << min_dist << endl;
		pipes.clear();
	}
}