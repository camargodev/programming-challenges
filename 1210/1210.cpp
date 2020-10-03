#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;
#define loop(n) for (num i=0; i<n; ++i)
#define loopi(i, n) for (num i=0; i<n; ++i)
using num = int;
using nums = vector<num>;

struct result {
  num cost;
  nums changes;
  result(num cost, nums changes): 
    cost(cost), changes(changes) {}
};

num MAX_YEAR, MAX_AGE, NEW_COST;
nums maints, sales;

nums changesUpdated(nums changes, num val) {
    changes.push_back(val);
    return changes;
}

num minCost(num year, num age) {
    if (year == MAX_YEAR) return 0;

    if (age == MAX_AGE) {
        return minCost(year+1, 1) + (NEW_COST - sales[age-1]) + maints[0];
    }

    num change = minCost(year+1, 1) + (NEW_COST - sales[age-1]) + maints[0];
    num maint  = minCost(year+1, age+1) + maints[age];

    return min(change, maint);

    // num res = minCost(year+1, 1) + (NEW_COST - soldCosts[age-1]) + maintCosts[0];

    // if (age < MAX_AGE) {
    //     num temp = minCost(year+1, age+1) + maintCosts[age];
    //     if (temp < res) res = temp;
    // }
    // return res;
}

num minimumCost(num age) {
    nums empty;
    return minCost(0, age);
}

int main() {
    num age, cost;
    while(cin >> MAX_YEAR) {
        cin >> age >> MAX_AGE >> NEW_COST;
        loop(MAX_AGE) {  
            cin >> cost;
            maints.push_back(cost);
        }
        loop(MAX_AGE) {  
            cin >> cost;
            sales.push_back(cost);
        }
        // p();
        num res = minimumCost(age);
        cout << res << endl;
        // loopi(i, res.changes.size()) { cout << res.changes[i] << " "; }
        // cout << endl;
    }

    return 0;
}