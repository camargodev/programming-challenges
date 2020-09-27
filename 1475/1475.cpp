#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std; 

// map<pair<ull, vector<bool>>, ull> minValues;
using ull = int;
map<ull, ull> minValues;
ull L, P1, P2;
// vector<ull> nexts;

// bool hasHole(ull pos) {
//     return find(positions.begin(), positions.end(), pos) != positions.end();
// }

ull minVal(ull pos, vector<ull> holesLeft) {
    
    // pair<ull, vector<bool>> pairIndex = make_pair(pos, covered);
    ull index = pos;

    // cout << "HERE 1" << endl;
    if (minValues.find(index) != minValues.end()) {
        // cout << "Put " << minValues[index] << " for " << pos << endl;
        return minValues[index];
    }

    // cout << "HERE 2" << endl;
    if (pos >= L-1) { 
        // cout << "End: " << pos << endl;
        return 0;
    }
    // cout << "HERE 3 " << index  << endl;
// find(v.begin(), v.end(), key) != v.end()
    if (find(holesLeft.begin(), holesLeft.end(), index) == holesLeft.end()) { 
        // int next = pos+1;
        // while (covered[next] && next<L) next+=1;
        if (holesLeft.size() == 0) {
            // cout << "No hole left. Going Back. " << endl;
            return 0;
        }
        int next = holesLeft[0];
        // int next = nexts[pos];
        // cout << "Skipping " << pos << " > going to " << next << endl;
        return minVal(next, holesLeft);
    }

    // cout << "AT: " << pos << endl;

    // cout << "Covered: [ ";
    // for (ull i = 0; i < L; i++) cout << covered[i] << " ";
    // cout << "]" << endl;

    // cout << "HERE 4" << endl;
    vector<ull> holesLeftWithP1 = holesLeft;
    ull nextWithP1 = pos+P1+1;
    while (holesLeftWithP1.size()>0 && holesLeftWithP1[0] < nextWithP1)
        holesLeftWithP1.erase(holesLeftWithP1.begin());
    // for (ull i = pos; i < nextWithP1; i++)
    //     coveredP1[i] = true;
    // cout << "AT: " << pos << ": Sum " << P1 << " > going to " << nextWithP1 << endl;
    ull valWithP1 = P1 + minVal(nextWithP1, holesLeftWithP1);

    // vector<bool> coveredP2 = covered;
    // ull nextWithP2 = pos+P2+1;
    // for (ull i = pos; i < nextWithP2; i++)
    //     coveredP2[i] = true;
    vector<ull> holesLeftWithP2 = holesLeft;
    ull nextWithP2 = pos+P2+1;
    // cout << "AT: " << pos << ": Sum " << P2 << " > going to " << nextWithP2 << endl;
    while (holesLeftWithP2.size()>0 && holesLeftWithP2[0] < nextWithP2)
        holesLeftWithP2.erase(holesLeftWithP2.begin());
    ull valWithP2 = P2 + minVal(nextWithP2, holesLeftWithP2);

    // return min(valWithP1, valWithP2);
    // ull bestVal;
    // if (valWithP1 <= valWithP2) {
    //     // pairIndex = make_pair(pos, coveredP1);
    //     bestVal = valWithP1;
    // } else {
    //     // pairIndex = make_pair(pos, coveredP2);
    //     bestVal = valWithP2;
    // }

    minValues[index] = min(valWithP1, valWithP2);
    // cout << "Caching " << minValues[index] << " for " << pos << endl;
    return minValues[index];
}

// ull calculateMinVal(vector<bool> covered) {
//     return minVal(L, P1, P2, 0, covered);
// }

// ull minValI(ull start, vector<bool> covered) {

// }

// void printTables(vector<bool> covered, vector<ull> nexts) {
//     cout << "covered = [ ";
//     for (int i = 0; i < covered.size(); i++) cout << covered[i] << " ";
//     cout << "]" << endl;
//     cout << "nexts = [ ";
//     for (int i = 0; i < nexts.size(); i++) cout << nexts[i] << " ";
//     cout << "]" << endl;
// }

int main() {
    ull holes;
    while (cin >> holes) {
        // ull totalLength, patch1, patch2;
        cin >> L >> P1 >> P2;
        // cout << holes << " " << L << " " << P1 << " " << P2 << endl;
        // vector<bool> covered(L, true);
        vector<ull> holesLeft;
        // for(int i=0;i<L;i++) nexts.push_back(0);
        // bool isFirst = true; ull first;
        for (ull i = 0; i < holes; i++) {
            ull pos; cin >> pos;
            // cout << "Hole at " << pos-1 << endl;
            // positions.push_back(pos);
            // covered[pos-1] = false;
            holesLeft.push_back(pos-1);
            // if (isFirst) { first = pos-1; isFirst = false; }
        }
        // int currentNext = L-1;
        // // cout << "1" << endl;
        // for (ull j = L; j > 0; j--) {
        //     // cout << "j: " << j-1 << endl;
        //     if (covered[j-1] == false) currentNext = j-1;
        //     // cout << "3" << endl;
        //     nexts[j-1] = currentNext;
        // }
        // printTables(covered,nexts);
        ull res = minVal(0, holesLeft);
        cout << res << endl;
        minValues.clear();
        // nexts.clear();
    }
}
