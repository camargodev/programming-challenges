#include <stdio.h>
#include <iostream> 
#include <vector>
#include <queue>
#include <list>
#include <stack>
#include <math.h>

using namespace std; 

using num = int;
using haste = stack<num>;
#define loop(n) for (num i = 0; i < n; i++)
#define loopi(i, n) for (num i = 0; i < n; i++)

vector<haste> hastes;

bool is_perfect_square(float val) {
    float sqrt_val = sqrt(val);
    return floor(sqrt_val) == sqrt_val;
}

bool add_ball(num ball_number) {
    loopi(i, hastes.size()) {
        if (hastes[i].size() == 0) {
            hastes[i].push(ball_number);
            return true;
        }
        num haste_top = hastes[i].top();
        if (is_perfect_square(ball_number + haste_top)) {
            hastes[i].push(ball_number);
            return true;
        }
    }
    return false;
}

num max_added_balls(num num_hastes) {
    num added_balls = 0;
    num ball_number = 1;
    bool able_to_add_ball = true;

    while (able_to_add_ball) {
        able_to_add_ball = add_ball(ball_number);
        ball_number += 1;
        added_balls += 1;
    }

    return added_balls-1;
}

int main() {
    num test_cases;
    cin >> test_cases;
    loop(test_cases) {
        num num_hastes;
        cin >> num_hastes;
        hastes.resize(num_hastes);
        num maxBalls = max_added_balls(num_hastes);
        cout << maxBalls << endl;
        hastes.clear();
    }
    return 0;
}