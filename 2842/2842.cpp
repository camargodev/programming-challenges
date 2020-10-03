#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <string.h>

using namespace std;

const int MAXN = 1001;
const int MAXS = 2*MAXN+1;

string s, r;
int lens, lenr;
int dp[MAXN][MAXN];

int minstr(int i, int j, string t) {
    if (dp[i][j] != -1) return dp[i][j];
    int res;
    if (i == lens) { 
        res = lenr - j;
    } else if (j == lenr) { 
        res = lens - i;
    } else if (s[i] == r[j]) {
        res = 1 + minstr(i+1,j+1,(t+s[i]));
    } else {
        res = 1 + min(minstr(i+1,j,(t+s[i])), minstr(i,j+1,(t+r[j])));
    }
    return dp[i][j] = res;
}

int main() {
    while(cin >> s) {
        cin >> r;
        lens = s.size(); lenr = r.size();
        memset(dp, -1, sizeof dp);
        string t = "";
        int minsz = minstr(0, 0, t);
        cout << minsz << endl;
    }
    return 0;
}