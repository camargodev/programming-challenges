#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std; 
using ll = long long;

ll N, K;
ll numOfSequences;
vector<ll> sequence;

#define loop(n) for (int i=0; i<n; ++i)

bool end(ll N, ll K) {
    return N == 0 && K == 0;
}

void count(vector<ll> vals, ll len, ll index) {
    if (index == N) return;
    ll next = index+1;
    ll curr = sequence[index];
    count(vals, len, next); // choose not to add curr
    if (len == 0) { // add first ele to vals
        vals.push_back(curr);
        count(vals, 1, next);
    } else {
        if (vals[len-1] >= curr) { // cannot add curr, go to next
            count(vals, len, next);
            return;
        }

        // adding curr will finish the sequence
        if (len+1 == K) { numOfSequences+=1; return; } 

        vals.push_back(curr);
        count(vals, len+1, next);
    }
}

void countSequences() {
    vector<ll> init;
    count(init, 0, 0);
}

int main() {
    while(true) {
        cin >> N >> K;
        if (end(N,K)) break;
        numOfSequences = 0;
        loop(N) {
            ll num; cin >> num;
            sequence.push_back(num);
        }
        countSequences();
        cout << numOfSequences << endl;
        sequence.clear();
    }
    return 0;
}