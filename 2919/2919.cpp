#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <string.h>

using namespace std;
using num = int;
using nums = vector<int>;
#define loop(i, n) for (num i = 0; i < n; i++)

const num MAXN = 500001;

num size_vals;
num vals[MAXN];

num max_seq(num idx, num sz, num lastidx) {
    if (idx == size_vals) return sz;

    num res = max_seq(idx+1, sz, lastidx);
    if (vals[idx] > vals[lastidx]) {
        num tmp = max_seq(idx+1, sz+1, idx);
        res = max(res, tmp);
    }
    return res;
}

num max_seq_size() {
    return max_seq(0, 0, -1);
}

int main() {
    while(cin >> size_vals) {
        memset(vals, 0, sizeof vals);
        loop(i, size_vals) cin >> vals[i];
        cout << max_seq_size() << endl;
    }
    return 0;
}