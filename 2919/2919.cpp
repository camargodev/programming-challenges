#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <string.h>

using namespace std;
using num = long long;
#define loop(i, n) for (num i = 0; i < n; i++)

const num MAXN = 500001;

num size_vals;
num vals[MAXN];
num dp[MAXN];

num max_seq_size() {
    dp[0] = -MAXN;
    num len = 0;

    loop(i, size_vals) {
        num low = 0, high = len;
        while (low <= high) {
            num mid = (low + high)/2;
            if (dp[mid] < vals[i]) 
                low = mid+1;
            else 
                high = mid-1;
        }
        dp[low] = vals[i];
        if (len < low) len = low;
    }

    return len;
}

int main() {
    while(cin >> size_vals) {
        memset(vals, 0, sizeof vals);
        memset(dp, MAXN, sizeof dp);
        loop(i, size_vals) cin >> vals[i];
        cout << max_seq_size() << endl;
    }
    return 0;
}