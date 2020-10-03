#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <string.h>

using namespace std;

using num = int;
using nums = vector<int>;
using key = pair<num, num>;
#define loop(i, n) for (num i = 0; i < n; i++)

const num MAXN = 2002;
num maints[MAXN], prices[MAXN];
num dp[MAXN][MAXN];

num max_year, curr_age, max_age, new_price;
const num start_age = 1;

num next(num curr) { return curr+1; }

num change_price(num age) {
    return new_price - prices[age-1] + maints[0];
}

num maint_price(num age) {
    return maints[age];
}

num min_cost(num year, num age) {
    if (dp[year][age] != -1) 
        return dp[year][age];

    if (year == max_year) 
        return dp[year][age] = 0;

    num res = min_cost(next(year), start_age) + change_price(age);

    if (age < max_age) {
        num temp = min_cost(next(year), next(age)) + maint_price(age);
        res = min(res, temp);
    }

    return dp[year][age] = res;
}

nums track_changes() {
    nums changes;
    num age = curr_age;
    
    loop(year, max_year) {
        if (age == max_age) {
            changes.push_back(next(year));
            age = start_age;
            continue;
        } 
        int change = dp[next(year)][start_age] + change_price(age);
        int maint = dp[next(year)][next(age)] + maint_price(age);
        age = next(age);
        if (change <= maint) {
            changes.push_back(next(year));
            age = start_age;
        } 
    }
    return changes;
}

void print_res(num res, nums changes) {
    cout << res << endl;
    if (changes.size() == 0) {
        cout << 0 << endl;
        return;
    } 
    loop(i, changes.size()) {
        if (i > 0) cout << " ";
        cout << changes[i];
    }
    cout << endl;
}

int main() {
    num start_year = 0;
    while (cin >> max_year) {
        memset(dp, -1, sizeof dp);
        cin >> curr_age >> max_age >> new_price;
        loop(i, max_age) cin >> maints[i];
        loop(i, max_age) cin >> prices[i];
        num res = min_cost(start_year, curr_age);
        nums changes = track_changes();
        print_res(res, changes);
    }
    return 0;
}