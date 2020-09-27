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

#define loop(n) for (ll i=0; i<n; ++i)

bool end(ll N, ll K) {
    return N == 0 && K == 0;
}
 

ll count(vector<ll> vals, ll len, ll index) {
    if (index == N) { cout << "  FIM. Voltando" << endl;  return 0; }

    cout << "Estou em " << index << " com len " << len << endl;
    pll cacheIndex = make_pair(index, len);
    if (cache.find(cacheIndex) != cache.end()) { 
        if (sequence[index] <= vals[len-1]) {
            cout << "Achei cache para " << index << ", mas não posso usar: ";
            cout << sequence[index] << " <= " << vals[len-1] << endl;
        } else {
            cout << "Retornando da cache o valor " << cache[cacheIndex] << " pra " << index 
                << " com len " << len << endl;
            return cache[cacheIndex]; 
        }
    } else {
        cout << " Nada em cache para pos " << index << " len " << len << endl;
    }

    ll next = index+1;
    ll curr = sequence[index];

    vector<ll> valswithcurr = vals;
    valswithcurr.push_back(curr);

    cout << "Chamando recursao: " << endl;
    ll seqsWithoutCurr = count(vals, len, next); // qdo escolhe nao colocar curr na seq
    if (len == 0) {// pode add qualquer valor
        if (index > N-K) {
            cout << "Nao consigo mais achar K valores. Voltando de pos " << index << endl;
            return 0;
        }
        cout << "Pos " << index << " com len 0, adicionei " << curr << endl;
        // cache[cacheIndex] = seqsWithoutCurr + count(valswithcurr, 1, next);
        cout << " Sem curr " << curr << " tenho " << seqsWithoutCurr << " seqs" << endl;
        cout << "Chamando recursao: " << endl;
        ll seqsWithCurr = count(valswithcurr, 1, next);
        cout << " Com curr " << curr << " tenho " << seqsWithCurr << " seqs" << endl;
        return seqsWithoutCurr + seqsWithCurr;
        // return cache[cacheIndex];
    }

    if (vals[len-1] >= curr) { // se curr > ultimo, entao nao pode add curr
        cout << "Ultimo val " << vals[len-1] << ", nao poss add " << curr << endl;
        cout << " Retornando " << seqsWithoutCurr << endl;
        // cache[cacheIndex] = seqsWithoutCurr;
        // return cache[cacheIndex];
        return seqsWithoutCurr;
    }

    if (len+1 == K) {// se com curr, chega a K, entao +1 no num de seqs
        cache[cacheIndex] = seqsWithoutCurr + 1;
        cout << "Completei K com " << curr << endl;
        cout << " > [ "; 
        loop(K-1) cout << vals[i] << " ";
        cout << curr << " ]" << endl;
        cout << "Coloquei " << cache[cacheIndex] << " para pos " << index << " com len " << len << endl;
        return cache[cacheIndex];
    }

    cout << "Nao caiu em nenhum if: " << endl;
    cout << " Sem curr " << curr << " tenho " << seqsWithoutCurr << " seqs" << endl;
    // cout << "Processing both with and without curr" << endl;
    // cout << "Add " << curr << " > going to " << next << endl;
    // return seqsWithoutCurr + count(valswithcurr, len+1, next);
    // cache[cacheIndex] = seqsWithoutCurr + count(valswithcurr, len+1, next);
    // return cache[cacheIndex];
    ll seqsWithCurr = count(valswithcurr, len+1, next);
    cout << " Com curr " << curr << " tenho " << seqsWithCurr << " seqs" << endl;
    cache[cacheIndex] =  seqsWithoutCurr + seqsWithCurr;
    return cache[cacheIndex];
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