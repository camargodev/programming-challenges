#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std; 
using ll = long long;

#define MAXN 10000
#define MAXP 10000
int prices[MAXN]; // vetor com os valores dos itens
int weights[MAXN]; // vetor com os pesos dos itens
int n; // quantidade de itens
int cache[MAXN + 1][MAXP + 1]; // tabela dinâmica, inicializada com valores negativos

ll N, K;
vector<ll> S;

int sequences(int item, int weightLeft) {
// se esse chamado recursivo já havia sido feito, então retornar o valor na tabela
    if (cache[item][weightLeft] > 0)
        return cache[item][weightLeft];

    if (item == n) {
        cache[item][weightLeft] = 0;
        return 0;
    }

    int bestComb = mochila(item + 1, weightLeft);
    if (weights[item] <= weightLeft) {
        int temp = prices[item] + mochila(item + 1, weightLeft - weights[item]);=
        bestComb = max(bestComb, temp);
    }
    cache[item][weightLeft] = bestComb;
    return bestComb;
}

ll countSequences() {
    vector<ll> init;
    return sequences(init, 0, 0);
}

void readVal() {
    ll num; cin >> num;
    S.push_back(num);
}

int main() {
    while(true) {
        cin >> N >> K;
        if (end(N,K)) break;

        loop(N) { readVal(); }

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