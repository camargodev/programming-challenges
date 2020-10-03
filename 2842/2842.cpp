#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <string.h>

using namespace std;

const int MAXN = 1001;

string s, r;
int lens, lenr;
int dp[MAXN][MAXN];

int minstr(int i, int j) {
    if (dp[i][j] != -1) return dp[i][j];
    int res;
    if (i == lens) { 
        res = lenr - j;
    } else if (j == lenr) { 
        res = lens - i;
    } else if (s[i] == r[j]) {
        res = 1 + minstr(i+1,j+1);
    } else {
        res = 1 + min(minstr(i+1,j), minstr(i,j+1));
    }
    return dp[i][j] = res;
}

int main() {
    while(cin >> s) {
        cin >> r;
        lens = s.size(); lenr = r.size();
        memset(dp, -1, sizeof dp);
        int minsz = minstr(0, 0);
        cout << minsz << endl;
    }
    return 0;
}