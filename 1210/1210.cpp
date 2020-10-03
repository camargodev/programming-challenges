#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

using num = int;
using nums = vector<int>;
// using key = pair<num, num>;
#define loop(i, n) for (num i=0; i<n; ++i)
struct result {
  num cost;
  nums changes;
  result(num cost, nums changes): 
    cost(cost), changes(changes) {}
};
// using cache = map<key, result>; 

const num MAXN = 2002;
num maints[MAXN], prices[MAXN];

num max_year, curr_age, max_age, new_price;
const num start_age = 1;

// map<key, result> dp;

nums updated_changes(nums changes, num year) {
    changes.push_back(year+1);
    return changes;
}

// result build_res(nums ch) {
//     result res;
//     res.cost = 0;
//     res.changes = ch;
//     return res;
// }

result min_cost(num year, num age, nums changes) {
    // const key idx = make_pair(year, age);

    // if (dp.find(idx) != dp.end()) 
    //     return dp[idx];
    
    if (year == max_year) {
        return result(0, changes);
        // result res = build_res(changes);
        // dp[idx] = res;
        // return dp[idx];
        // return res;
    }
    num next_year = year+1;

    result res = min_cost(next_year, start_age, updated_changes(changes, year));
    res.cost += (new_price - prices[age-1] + maints[0]);

    if (age < max_age) {
        result temp = min_cost(next_year, age+1, changes);
        temp.cost += maints[age];
        if (temp.cost < res.cost) res = temp;
    }

    // dp[idx] = res;
    return res;
}

void print_res(result res) {
    cout << res.cost << endl;
    if (res.changes.size() == 0) {
        cout << 0 << endl;
    } else {
        loop(i, res.changes.size())
            cout << res.changes[i] << " ";
        cout << endl;
    }
}

int main() {
    num start_year = 0;
    while (cin >> max_year) {
        nums changes;
        cin >> curr_age >> max_age >> new_price;
        loop(i, max_age) cin >> maints[i];
        loop(i, max_age) cin >> prices[i];
        result res = min_cost(start_year, curr_age, changes);
        print_res(res);
        // dp.clear();
    }
    return 0;
}