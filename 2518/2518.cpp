#include <stdio.h>
#include <iostream> 
#include <vector>
#include <queue>
#include <list>
#include <stack>
#include <math.h>
#include <iomanip>

using namespace std; 
using num = double;
#define for_range(i, n) for (num i = 0; i < n; i++)
#define INF 0x3f3f3f3f


int main() {

    double N, H, C, L; // in cm
    while (cin >> N) {
        cin >> H >> C >> L;
        num angle = sqrt(H*H + C*C);
        num total_length = angle*N;
        num total_area_in_cm2 = total_length*L;
        num total_area_in_m2 = total_area_in_cm2/10000;
        cout << fixed << setprecision(4) << total_area_in_m2 << endl;
    }

    return 0;
}