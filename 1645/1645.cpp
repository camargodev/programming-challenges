#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std; 
using ll = long long;
using pll = pair<ll, ll>;

ll N, K;
// ll numOfSequences;
vector<ll> sequence;
map<pll, ll> cache;
vector<vector<ll>> seqsbynum;

#define loop(n) for (ll i=0; i<n; ++i)

bool end(ll N, ll K) {
    return N == 0 && K == 0;
}
 

ll count(vector<ll> vals, ll len, ll index) {
    if (index == N) return 0; 
    if (len == 0 && index > (N-K)) return 0;

    ll next = index+1;
    ll curr = sequence[index];

    vector<ll> valswithcurr = vals;
    valswithcurr.push_back(curr);

    ll seqsWithoutCurr = count(vals, len, next);

    if (len == 0) { // pode add qualquer valor
        ll seqsWithCurr = count(valswithcurr, len+1, next);
        return seqsWithoutCurr + seqsWithCurr;
    }

    if (vals[len-1] >= curr) { // se curr > ultimo, entao nao pode add curr
        return seqsWithoutCurr;
    }

    if ((len+1) == K) { // se com curr, chega a K, entao +1 no num de seqs
        cache[cacheIndex] = seqsWithoutCurr + 1;
        return cache[cacheIndex];
    }

    ll seqsWithCurr = count(valswithcurr, len+1, next);
    return seqsWithoutCurr + seqsWithCurr;
}

ll countSequences() {
    vector<ll> init;
    return count(init, 0, 0);
}

int main() {
    while(true) {
        cin >> N >> K;
        if (end(N,K)) break;
        loop(N) {
            ll num; cin >> num;
            sequence.push_back(num);
        }
        if (K == 1) {
            cout << N << endl;
        } else {
            ll numOfSequences = countSequences();
            cout << numOfSequences << endl;
        }
        sequence.clear();
        cache.clear();
    }
    return 0;
}