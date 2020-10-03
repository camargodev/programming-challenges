#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <string.h>

using namespace std;

const int MAXN = 1001;

string s, r;
int dp[MAXN][MAXN];

int minstr(int i, int j) {
    if (dp[i][j] != -1) return dp[i][j];
    if (i == s.size()) return dp[i][j] = i-j;
    if (j == r.size()) return dp[i][j] = j-i;
    if (s[i] == r[j])
        return dp[i][j] = 1 + minstr(i+1,j+1);
    return dp[i][j] = 1 + min(minstr(i+1,j), minstr(i,j+1));
}

int main() {
    while(cin >> s) {
        cin >> r;
        memset(dp, -1, sizeof dp);
        int minsz = minstr(0, 0);
        cout << minsz << endl;
    }
    return 0;
}