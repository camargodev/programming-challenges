#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <iomanip>
#include <math.h>

using namespace std; 

using num = long long;

// -10 -10 30 30
// 5
// 1 10 6
// 5 5 8
// 2 0 4
// -3 -3 30
// -2 5 3

struct BasePlanet {
    num x;
    num y;
};
struct Planet {
    int x;
    int y;
    num population;
    Planet(num x, num y, num population):
        x(x), y(y), population(population) {}
};
struct Line {
    num a, b, c;
};
struct Result {
    double distance;
    num num_left  = 0, population_left  = 0;
    num num_right = 0, population_right = 0;
    num num_line  = 0;
};

BasePlanet source, destiny;
vector<Planet> planets;

Line calculate_line() {
    Line line;

    num x1 = source.x,  y1 = source.y;
    num x2 = destiny.x, y2 = destiny.y;

    line.a = y1-y2;
    line.b = x2-x1;
    line.c = (x1-x2)*y1 + (y2-y1)*x1;

    return line;
}

double distance() {
    double x = source.x - destiny.x;
	double y = source.y - destiny.y;
	double dist;

	dist = pow(x, 2) + pow(y, 2);
	dist = sqrt(dist);                  

	return dist;
}

Result compute() {
    Result result;
    Line line = calculate_line();
    for (int i = 0; i < planets.size(); i++) {
        Planet planet = planets[i];
        num val = line.a*planet.x + line.b*planet.y + line.c;
        if (val == 0) {
            result.num_line += 1;
        } else if (val > 0) {
            result.num_left += 1;
            result.population_left += planet.population;
        } else {
            result.num_right += 1;
            result.population_right += planet.population;
        }
    }
    result.distance = distance();
    return result;
}

void print_result(Result result) {
    cout << "Relatorio Vogon #35987-2" << endl;

    cout << fixed << setprecision(2);
    cout << "Distancia entre referencias: " << result.distance << " anos-luz" << endl;

    cout << "Setor Oeste:" << endl;
    cout << "- " << result.num_left << " planeta(s)" << endl;
    cout << "- " << result.population_left << " bilhao(oes) de habitante(s)" << endl;

    cout << "Setor Leste:" << endl;
    cout << "- " << result.num_right << " planeta(s)" << endl;
    cout << "- " << result.population_right << " bilhao(oes) de habitante(s)" << endl;

    cout << "Casualidades: " << result.num_line << " planeta(s)" << endl;
}

int main() {

    cin >> source.x >> source.y;
    cin >> destiny.x >> destiny.y;
    
    num num_points;
    cin >> num_points;
    
    for (int i = 0; i < num_points; i++) {
        num x, y, pop;
        cin >> x >> y >> pop;
        Planet planet(x, y, pop);
        planets.push_back(planet);
    }
    Result res = compute();
    print_result(res);
    return 0;
}