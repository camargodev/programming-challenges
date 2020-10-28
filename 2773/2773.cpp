#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <iomanip>
#include <math.h>

using namespace std; 

struct Point {
    int x;
    int y;
};

Point house, school;
Point left_down, right_up, left_up, right_down;
int speed;

double dist(Point a, Point b) {
    int x = a.x - b.x;
	int y = a.y - b.y;
	return sqrt(x*x + y*y);     
}

int main() {
    while (cin >> house.x  >> house.y
            >> school.x    >> school.y >> speed
            >> left_down.x >> left_down.y
            >> right_up.x  >> right_up.y) {

        left_up.x = left_down.x;
        left_up.y = right_up.y;

        right_down.x = right_up.x;
        right_down.y = left_down.y;

        double distance_down = dist(house, left_down) 
            + dist(left_down, right_down) 
            + dist(right_down, school);

        double distance_up = dist(house, left_up) 
            + dist(left_up, right_up) 
            + dist(right_up, school);

        double min_dist = min(distance_down, distance_up);
        double time = min_dist/((double) speed);
        cout << fixed << setprecision(1) << time << endl;
    }
    return 0;
}