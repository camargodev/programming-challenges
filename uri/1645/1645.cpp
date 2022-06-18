#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std; 
using ll = long long;
using pll = pair<ll, ll>;
using chkey = pair<ll, pll>;

ll N, K;
// ll numOfSequences;
vector<ll> sequence;
map<chkey, ll> cache;
vector<vector<ll>> seqsbynum;

#define loop(n) for (ll i=0; i<n; ++i)

bool end(ll N, ll K) {
    return N == 0 && K == 0;
}

chkey makekey(ll last, ll curr, ll len) {
    return make_pair(last, make_pair(curr, len));
}
 

ll count(ll lastindex, ll currindex, ll len) {
    chkey key = makekey(lastindex, currindex, len);

    if (cache.find(key) != cache.end()) return cache[key];
    if (currindex >= N) return 0;

    ll nextindex = currindex + 1;
    ll seqsWithoutCurr = count(lastindex, nextindex, len); // qdo nao adiciona currval

    if (len == 0)// pode add qualquer valor, entao considera com e sem currval
        cache[key] = seqsWithoutCurr + count(currindex, nextindex, len+1);
    else if (sequence[lastindex] >= sequence[currindex]) // nao pode adicionar curr
        cache[key] = seqsWithoutCurr; 
    else if ((len+1) == K)// adicionando curr, chega a K, entao +1 no num de seqs
        cache[key] = seqsWithoutCurr + 1;
    else // cai aqui qdo len>0, pode add curr e nao chegou em K
        cache[key] = seqsWithoutCurr + count(currindex, nextindex, len+1);
    
    return cache[key];
}

ll countSequences() {
    return count(-1, 0, 0);
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