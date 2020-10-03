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

const num MAXN = 2002;
num maints[MAXN], prices[MAXN];
num dp[MAXN][MAXN];

num max_year, curr_age, max_age, new_price;
const num start_age = 1;

num min_cost(num year, num age) {
    if (dp[year][age] >= 0) return dp[year][age];

    if (year == max_year) return dp[year][age] = 0;
    num res = min_cost(year+1, start_age) + (new_price - prices[age-1] + maints[0]);

    if (age < max_age) {
        num temp = min_cost(year+1, age+1) +  maints[age];
        res = min(res, temp);
    }
    return dp[year][age] = res;
}

void print_res(num res) {
    cout << res << endl;
}

int main() {
    num start_year = 0;
    while (cin >> max_year) {
        memset(dp, -1, sizeof dp);
        cin >> curr_age >> max_age >> new_price;
        loop(i, max_age) cin >> maints[i];
        loop(i, max_age) cin >> prices[i];
        num res = min_cost(start_year, curr_age);
        print_res(res);
    }
    return 0;
}