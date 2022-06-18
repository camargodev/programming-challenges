#include <stdio.h>
#include <iostream> 
#include <vector>
#include <queue>
#include <list>
#include <stack>
#include <math.h>

using namespace std; 
using num = int;
#define for_range(i, n) for (num i = 0; i < n; i++)
#define INF 0x3f3f3f3f

const num MAX_SPELLS = 1001;
const num MAX_HP = 2001;

num dp[MAX_SPELLS][MAX_HP];

struct Spell {
    num damage;
    num cost;
};

num num_spells, total_hp;

vector<num> costs;
vector<num> damages;

num calc_min_mana(num idx, num rem_hp) {
    if (rem_hp <= 0) {
        return 0;
    }
    
    if (idx == num_spells) 
        return INF;

    if (dp[idx][rem_hp] != -1)
        return dp[idx][rem_hp];

    num without_spell = calc_min_mana(idx+1, rem_hp);
    num with_spell = costs[idx] + calc_min_mana(idx+1, rem_hp-damages[idx]);\
    dp[idx][rem_hp] = min(with_spell, without_spell);
    return dp[idx][rem_hp];
}

int main() {
    while(cin >> num_spells >> total_hp) {
        memset(dp, -1, sizeof dp);
        damages.resize(num_spells);
        costs.resize(num_spells);
        for_range(i, num_spells) {
            cin >> damages[i] >> costs[i];
        }
        num min_mana = calc_min_mana(0, total_hp);
        if (min_mana != INF) cout << min_mana << endl;
        else cout << -1 << endl;
        damages.clear();
        costs.clear();
    }

}