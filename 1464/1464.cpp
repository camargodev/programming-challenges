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
    
    int bottom_most_point = get_bottom_most_point_index(points, n);
    swap_points(points[0], points[bottom_most_point]); 
    start_point = points[0]; 
    qsort(&points[1], n-1, sizeof(Point), compare); 

    int mod_len = 1;
    for (int i = 1; i < n; i++) { 
        while (i < n-1 && orientation(start_point, points[i], points[i+1]) == COLINEAR) 
            i++; 
        points[mod_len] = points[i]; 
        mod_len++;
    } 

    vector<Point> hull;
    
    if (mod_len < MIN_HULL_SIZE) return hull; // empty

    hull = build_start_hull(points);

    for (int i = MIN_HULL_SIZE; i < mod_len; i++) { 
        while (orientation(hull[hull.size()-2], hull[hull.size()-1], points[i]) != COUNTER_CLOCKWISE) 
            hull.pop_back(); 
        hull.push_back(points[i]); 
    } 
    return hull;
} 

void print_points(vector<Point> points) {
    if (points.size() == 0 ){
        cout << "No points " << endl;
        return;
    }
    for (int i = 0; i < points.size(); i++)
        cout << "(" << points[i].x << ", " << points[i].y <<")" << endl; 
}

void print_hull(vector<Point> hull) {
    if (hull.size() == 0 ){
        cout << "Empty Hull " << endl;
        return;
    }
    for (int i = hull.size() - 1; i >= 0; i--)
        cout << "(" << hull[i].x << ", " << hull[i].y <<")" << endl; 
}

struct find_point : std::unary_function<Point, bool> {
    Point other_point;
    find_point(Point other_point):other_point(other_point) { }
    bool operator()(Point const& point) const {
        return point.x == other_point.x && point.y == other_point.y;
    }
};

vector<Point> remove_hull_from_points(vector<Point> points, vector<Point> hull) {
    points.erase(
        remove_if(begin(points), end(points), [&](auto point) {
            return find_if(begin(hull), end(hull), find_point(point)) != end(hull); 
        }), end(points));
    return points;
}

int count_onion_layers(vector<Point> points) {
    int num_of_hulls = 0;
    bool can_make_a_hull = true;
    while (can_make_a_hull) {
        vector<Point> hull = convex_hull(points, points.size());
        num_of_hulls += 1;
        print_hull(hull);
        cout << endl;
        if (hull.size() > 0) {
            points = remove_hull_from_points(points, hull);
            if (points.size() == 0) 
                can_make_a_hull = false;
        } else {
            can_make_a_hull = false;
        }
    }
    cout << num_of_hulls << endl;
    return num_of_hulls;
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
        int onion_layers = count_onion_layers(points); 
        if (onion_layers % 2 == 0) cout << "Do not take this onion to the lab!" << endl;
        else cout << "Take this onion to the lab!" << endl;
    }
    return 0; 
} 
