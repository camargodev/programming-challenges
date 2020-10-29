#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <stack>
#include <math.h>

using namespace std; 

struct Point { 
	int x, y; 
}; 

Point start_point; 

int COLINEAR = 0, CLOCKWISE = 1, COUNTER_CLOCKWISE = 2;
int MIN_HULL_SIZE = 3;

Point nextToTop(stack<Point> &S) { 
	Point p = S.top(); 
	S.pop(); 
	Point res = S.top(); 
	S.push(p); 
	return res; 
} 

void swap_points(Point &p1, Point &p2) { 
	Point temp = p1; 
	p1 = p2; 
	p2 = temp; 
} 

int square_distance(Point p1, Point p2)  { 
    int dist_x = p1.x - p2.x;
    int dist_y = p1.y - p2.y;
    return pow(dist_x,2) + pow(dist_y,2);
} 

int orientation(Point p, Point q, Point r)  { 
	int val = (q.y - p.y) * (r.x - q.x) -  (q.x - p.x) * (r.y - q.y); 
	if (val == 0) return COLINEAR;
    else if (val > 0) return CLOCKWISE;
    return COUNTER_CLOCKWISE;
} 

int compare(const void *vp1, const void *vp2) { 
    Point *p1 = (Point *)vp1; 
    Point *p2 = (Point *)vp2; 

    int o = orientation(start_point, *p1, *p2); 
    if (o == COLINEAR) 
        return (square_distance(start_point, *p2) >= square_distance(start_point, *p1))? -1 : 1; 

    return (o == COUNTER_CLOCKWISE) ? -1: 1; 
} 

void sort_points(Point* points, int n) {
    start_point = points[0]; 
    qsort(&points[1], n-1, sizeof(Point), compare); 
}

int get_bottom_most_point_index(Point points[], int n) {
    int ymin = points[0].y, min = 0; 
    for (int i = 1; i < n; i++) { 
        int y = points[i].y; 
        if ((y < ymin) || (ymin == y && points[i].x < points[min].x)) 
            ymin = points[i].y, min = i; 
    } 
    return min;
}

stack<Point> build_start_stack(Point points[]) {
    stack<Point> point_stack; 
    point_stack.push(points[0]); 
    point_stack.push(points[1]); 
    point_stack.push(points[2]); 
    return point_stack;
}

stack<Point> convex_hull(Point points[], int n) { 
    
    int bottom_most_point = get_bottom_most_point_index(points, n);
    swap_points(points[0], points[bottom_most_point]); 
    sort_points(points, n);

    int mod_len = 1;
    for (int i = 1; i < n; i++) { 
        while (i < n-1 && orientation(start_point, points[i], points[i+1]) == COLINEAR) 
            i++; 
        points[mod_len] = points[i]; 
        mod_len++;
    } 

    stack<Point> point_stack;
    
    if (mod_len < MIN_HULL_SIZE) return point_stack; 

    point_stack = build_start_stack(points);

    for (int i = MIN_HULL_SIZE; i < mod_len; i++) { 
        while (orientation(nextToTop(point_stack), point_stack.top(), points[i]) != COUNTER_CLOCKWISE) 
            point_stack.pop(); 
        point_stack.push(points[i]); 
    } 
    return point_stack;
} 

int count_onion_layers(Point points[], int n) {
    stack<Point> point_stack = convex_hull(points, n);

    while (!point_stack.empty())  { 
        Point point = point_stack.top(); 
        cout << "(" << point.x << ", " << point.y <<")" << endl; 
        point_stack.pop(); 
    } 
    return 0;
}

int main() { 
    int n;
    while (true) {
        cin >> n;
        if (n == 0) break;

        Point points[n];
        for (int i = 0; i < n; i++) {
            cin >> points[i].x >> points[i].y;
        }
        int onion_layers = count_onion_layers(points, n); 
        if (onion_layers % 2 == 0) cout << "NO" << endl;
        else cout << "YES" << endl;
    }
    return 0; 
} 
