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
Point field_left_down, field_right_up;
Point field_left_up, field_right_down;
int speed;

float dist(Point a, Point b) {
    int x = a.x - b.x;
	int y = a.y - b.y;
	float distance;

	distance = pow(x, 2) + pow(y, 2);
	distance = sqrt(distance);                  

	return distance;
}

int main() {
    cout << fixed << setprecision(1);
    while (cin >> house.x >> house.y) {
        cin >> school.x >> school.y;
        
        cin >> speed;

        cin >> field_left_down.x >> field_left_down.y;
        cin >> field_right_up.x >> field_right_up.y;

        field_left_up.x = field_left_down.x;
        field_left_up.y = field_right_up.y;

        field_right_down.x = field_right_up.x;
        field_right_down.y = field_left_down.y;

        float distance_down = dist(house, field_left_down) 
            + dist(field_left_down, field_right_down) 
            + dist(field_right_down, school);

        float distance_up = dist(house, field_left_up) 
            + dist(field_left_up, field_right_up) 
            + dist(field_right_up, school);

        float min_dist = min(distance_down, distance_up);
        float time = min_dist/((float) speed);
        cout << time << endl;
    }
    return 0;
}