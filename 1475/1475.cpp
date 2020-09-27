#include <iostream>
#include <vector>
#include <map>

using namespace std; 

// map<pair<ull, vector<bool>>, ull> minValues;
using ull = int;
map<ull, ull> minValues;
ull L, P1, P2;
vector<ull> nexts;

// bool hasHole(ull pos) {
//     return find(positions.begin(), positions.end(), pos) != positions.end();
// }

ull minVal(ull pos, vector<bool> covered) {
    
    // pair<ull, vector<bool>> pairIndex = make_pair(pos, covered);
    ull index = pos;

    if (minValues.find(index) != minValues.end()) {
        // cout << "Put " << minValues[index] << " for " << pos << endl;
        return minValues[index];
    }

    if (pos >= L-1) { 
        // cout << "End: " << pos << endl;
        return 0;
    }

    if (covered[pos]) { 
        int next = nexts[pos];
        // cout << "Skipping " << pos << " > going to " << next << endl;
        return minVal(next, covered);
    }

    // cout << "AT: " << pos << endl;

    // cout << "Covered: [ ";
    // for (ull i = 0; i < L; i++) cout << covered[i] << " ";
    // cout << "]" << endl;

    vector<bool> coveredP1 = covered;
    ull nextWithP1 = pos+P1+1;
    for (ull i = pos; i < nextWithP1; i++)
        coveredP1[i] = true;
    // cout << "AT: " << pos << ": Sum " << P1 << " > going to " << nextWithP1 << endl;
    ull valWithP1 = P1 + minVal(nextWithP1, coveredP1);

    vector<bool> coveredP2 = covered;
    ull nextWithP2 = pos+P2+1;
    for (ull i = pos; i < nextWithP2; i++)
        coveredP2[i] = true;
    // cout << "AT: " << pos << ": Sum " << P2 << " > going to " << nextWithP2 << endl;
    ull valWithP2 = P2 + minVal(nextWithP2, coveredP2);

    // return min(valWithP1, valWithP2);
    ull bestVal;
    if (valWithP1 <= valWithP2) {
        // pairIndex = make_pair(pos, coveredP1);
        bestVal = valWithP1;
    } else {
        // pairIndex = make_pair(pos, coveredP2);
        bestVal = valWithP2;
    }

    minValues[index] = bestVal;
    // cout << "Caching " << bestVal << " for " << pos << endl;
    return bestVal;
}

// ull calculateMinVal(vector<bool> covered) {
//     return minVal(L, P1, P2, 0, covered);
// }

// ull minValI(ull start, vector<bool> covered) {

// }

void printTables(vector<bool> covered, vector<ull> nexts) {
    cout << "covered = [ ";
    for (int i = 0; i < covered.size(); i++) cout << covered[i] << " ";
    cout << "]" << endl;
    cout << "nexts = [ ";
    for (int i = 0; i < nexts.size(); i++) cout << nexts[i] << " ";
    cout << "]" << endl;
}

int main() {
    ull holes;
    while (cin >> holes) {
        // ull totalLength, patch1, patch2;
        cin >> L >> P1 >> P2;
        // cout << holes << " " << L << " " << P1 << " " << P2 << endl;
        vector<bool> covered(L, true);
        for(int i=0;i<L;i++) nexts.push_back(0);
        // bool isFirst = true; ull first;
        for (ull i = 0; i < holes; i++) {
            ull pos; cin >> pos;
            // cout << "Hole at " << pos-1 << endl;
            // positions.push_back(pos);
            covered[pos-1] = false;
            // if (isFirst) { first = pos-1; isFirst = false; }
        }
        int currentNext = L-1;
        // cout << "1" << endl;
        for (ull j = L; j > 0; j--) {
            // cout << "j: " << j-1 << endl;
            if (covered[j-1] == false) currentNext = j-1;
            // cout << "3" << endl;
            nexts[j-1] = currentNext;
        }
        // printTables(covered,nexts);
        ull res = minVal(0, covered);
        cout << res << endl;
        minValues.clear();
        nexts.clear();
    }
}
