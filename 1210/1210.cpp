#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

using num = int;
using nums = vector<int>;
using key = pair<num, num>;
#define loop(i, n) for (num i=0; i<n; ++i)
struct result {
  num cost = 0;
  nums changes;
  result(num cost, nums changes): 
    cost(cost), changes(changes) {}
};
// using cache = map<key, result>; 

const num MAXN = 2002;
num maints[MAXN], prices[MAXN];
// num dpcost[MAXN][MAXN];
// nums dpchanges[MAXN][MAXN];


num max_year, curr_age, max_age, new_price;
const num start_age = 1;

// map<key, result> dp;

// nums updated_changes(nums changes, num year) {
//     changes.push_back(year+1);
//     return changes;
// }

// result build_res(nums ch) {
//     result res;
//     res.cost = 0;
//     res.changes = ch;
//     return res;
// }

num min_cost(num year, num age) {
    // const key idx = make_pair(year, age);

    // if (dpcost[year][age] >= 0) 
    //     return result(dpcost[year][age], dpchanges[year][age]);

    if (year == max_year) return 0;
    // if (year == max_year) {
    //     res
    //     res.changes = changes;
        // result res = build_res(changes);
        // dp[idx] = res;
        // return dp[idx];
        // return res;
    // } else {
    // if (year < max_year) {

    num res = min_cost(year+1, start_age) + (new_price - prices[age-1] + maints[0]);

    if (age < max_age) {
        num temp = min_cost(year+1, age+1) +  maints[age];
        res = min(res, temp);
    }
    // }

    // dpcost[year][age] = res.cost;
    // dpchanges[year][age] = res.changes;
    return res;
}

void print_res(num res) {
    cout << res << endl;
    // if (res.changes.size() == 0) {
    //     cout << 0 << endl;
    // } else {
    //     loop(i, res.changes.size())
    //         cout << res.changes[i] << " ";
    //     cout << endl;
    // }
}

int main() {
    num start_year = 0;
    while (cin >> max_year) {
        // nums changes;
        // memset(dpcost, -1, sizeof dpcost);
        // memset(dpchanges, 0, sizeof dpchanges);
        cin >> curr_age >> max_age >> new_price;
        loop(i, max_age) cin >> maints[i];
        loop(i, max_age) cin >> prices[i];
        num res = min_cost(start_year, curr_age);
        print_res(res);
        // dp.clear();
    }
    return 0;
}