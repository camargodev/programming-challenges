#include <stdio.h>
#include <iostream> 
#include <vector>
#include <queue>
#include <list>
#include <stack>
#include <math.h>

using namespace std; 
using num = int;
#define for_range(n) for (num i = 0; i < n; i++)
#define INF 0x3f3f3f3f

const num MAX_SPELLS = 1001;
const num MAX_HP = 2001;

num dp[MAX_SPELLS][MAX_HP];

struct Spell {
    num damage;
    num cost;
};

num num_spells, total_hp;

vector<Spell> spells;

num calc_min_mana(num idx, num rem_hp) {
    cout << "idx = " << idx << " e rem_hp = " << rem_hp << endl;
    if (rem_hp <= 0) {
        return 0;
    }
    
    if (idx == num_spells) 
        return INF;

    if (dp[idx][rem_hp] != -1)
        return dp[idx][rem_hp];

    Spell spell = spells[idx];
    cout << "spell = " << spell.damage << " cost = " << spell.cost << endl;
    num without_spell = calc_min_mana(idx+1, rem_hp);
    cout << "without_spell  = " << without_spell << endl;
    num with_spell = spell.cost + calc_min_mana(idx+1, rem_hp-spell.damage);
    cout << "with_spell  = " << with_spell << endl;
    dp[idx][rem_hp] = min(with_spell, without_spell);
    return dp[idx][rem_hp];
}

int main() {
    while(cin >> num_spells >> total_hp) {
        memset(dp, -1, sizeof dp);
        spells.resize(num_spells);
        for_range(num_spells) {
            cout << "aa" << endl;
            Spell spell;
            num damage, cost;
            cin >> damage >> cost;
            spell.damage = damage;
            spell.cost = cost;
            cout << "aaa spell = " << spell.damage << " cost = " << spell.cost << endl;
            spells.push_back(spell);
        }
        num min_mana = calc_min_mana(0, total_hp);
        if (min_mana != INF) cout << min_mana << endl;
        else cout << -1 << endl;
        spells.clear();
    }

}