#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <stack>
#include <math.h>
#include <iomanip>

using namespace std; 

struct Point { 
	int x, y; 

	bool operator ==(Point other) {
		return x == other.x && y == other.y;
	}
}; 

Point start_point; 

int COLINEAR = 0, CLOCKWISE = 1, COUNTER_CLOCKWISE = 2;
int MIN_HULL_SIZE = 3;

void swap_points(Point &p1, Point &p2) { 
	Point temp = p1; 
	p1 = p2; 
	p2 = temp; 
} 

void print_points(vector<Point> points) {
    cout << "POINTS: " << endl;
    if (points.size() == 0 ){
        cout << "No points " << endl;
        return;
    }
    for (int i = 0; i < points.size(); i++)
        cout << "(" << points[i].x << ", " << points[i].y <<")" << endl; 
    cout << endl;
}

void print_hull(vector<Point> hull) {
    cout << "HULL: " << endl;
    if (hull.size() == 0 ){
        cout << "Empty Hull " << endl;
        return;
    }
    for (int i = hull.size() - 1; i >= 0; i--)
        cout << "(" << hull[i].x << ", " << hull[i].y <<")" << endl;
    cout << endl;
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

int get_bottom_most_point_index(vector<Point> points, int n) {
    int ymin = points[0].y, min = 0; 
    for (int i = 1; i < n; i++) { 
        int y = points[i].y; 
        if ((y < ymin) || (ymin == y && points[i].x < points[min].x)) 
            ymin = points[i].y, min = i; 
    } 
    return min;
}

vector<Point> build_start_hull(vector<Point> points) {
    vector<Point> start_hull; 
    start_hull.push_back(points[0]); 
    start_hull.push_back(points[1]); 
    start_hull.push_back(points[2]); 
    return start_hull;
}

vector<Point> convex_hull(vector<Point> points, int n) { 

    // print_points(points);
    
    int bottom_most_point = get_bottom_most_point_index(points, n);
    swap_points(points[0], points[bottom_most_point]); 
    start_point = points[0]; 
    qsort(&points[1], n-1, sizeof(Point), compare); 

    // int mod_len = 1;
    bool is_line = true;
    for (int i = 1; i < n-1; i++) {
        if (orientation(start_point, points[i], points[i+1]) != COLINEAR)
            is_line = false;
    } 

    vector<Point> hull;
    
    if (n < MIN_HULL_SIZE || is_line) return hull; // empty

    hull = build_start_hull(points);

    for (int i = MIN_HULL_SIZE; i < n; i++) { 
        while (orientation(hull[hull.size()-2], hull[hull.size()-1], points[i]) == CLOCKWISE)
            hull.pop_back(); 
        hull.push_back(points[i]); 
    } 
    return hull;
} 


vector<Point> remove_hull_from_points(vector<Point> points, vector<Point> hull) {
    points.erase(
        remove_if(begin(points), end(points), [&](auto point) {
            return find(begin(hull), end(hull), point) != end(hull); 
        }), end(points));
    return points;
}

double count_tape_size(vector<Point> points) {
    double tape_size = 0;
    vector<Point> hull = convex_hull(points, points.size());
    // print_hull(hull);
    int last = hull.size()-1;
    for (int i = 0; i < last; i++) {
        double dist = sqrt(square_distance(hull[i], hull[i+1]));
        // cout << "Distance between " << "(" << hull[i].x << ", " << hull[i].y <<")";
        // cout << " and " << "(" << hull[i+1].x << ", " << hull[i+1].y <<")";
        // cout << " is " << dist << endl;
        tape_size += dist;
    }
    double dist = sqrt(square_distance(hull[last], hull[0]));
    // cout << "Distance between last " << "(" << hull[last].x << ", " << hull[last].y <<")";
    // cout << " and first " << "(" << hull[0].x << ", " << hull[0].y <<")";
    // cout << " is " << dist << endl;
    tape_size += dist;
    return tape_size;
}

int main() { 
    int n;
    while (true) {
        cin >> n;
        if (n == 0) break;
 
        vector<Point> points;
        for (int i = 0; i < n; i++) {
            Point point;
            cin >> point.x >> point.y;
            points.push_back(point);
        }
        double tape_size = count_tape_size(points); 
        cout << "Tera que comprar uma fita de tamanho " << fixed << setprecision(2) << tape_size << "." << endl;
    }
    return 0; 
} 
