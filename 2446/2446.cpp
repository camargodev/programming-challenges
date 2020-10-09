#include <stdio.h>
#include <iostream> 
#include <vector>
#include <queue>
#include <list>
#include <map>
#include <math.h>
#include <string.h>

using namespace std;

using num = int;

const num MAX_COINS = 1001, MAX_PRICE = 100001;

#define loopi(i, n) for (num i = 0; i < n; i++)

num total_price, num_coins;
vector<num> coins;

num dp[MAX_COINS][MAX_PRICE];

const num FALSE = 0, TRUE = 1, NONE = 2;

bool pay(num coin, num sum) { 
    if (sum > total_price) return false;
    if (sum == total_price) return true;
    if (coin == num_coins) return false;

    if (dp[coin][sum] != NONE)
        return dp[coin][sum];

    bool can_pay = pay(coin+1, sum) || pay(coin+1, sum+coins[coin]);
    dp[coin][sum] = can_pay ? TRUE : FALSE;
    return can_pay;
}

int main() {
    cin >> total_price >> num_coins;

    memset(dp, NONE, sizeof dp);
    coins.resize(num_coins);
    loopi(i, num_coins) cin >> coins[i];

    cout << (pay(0, 0) ? "S" : "N") << endl;
    coins.clear();
}