#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std; 

using ull = int;
map<ull, ull> minValues;
ull L, P1, P2;

bool isCached(ull index) {
    return minValues.find(index) != minValues.end();
}

bool hasHoleInPosition(vector<ull> holes, ull pos) {
    return find(holes.begin(), holes.end(), pos) != holes.end();
}

vector<ull> removeHolesPatched(vector<ull> holes, ull patchEnd) {
    vector<ull> holesLeft = holes;
    while (holesLeft.size()>0 && holesLeft[0] < patchEnd)
        holesLeft.erase(holesLeft.begin());
    return holesLeft;
}

ull minVal(ull pos, vector<ull> holesLeft) {

    if (isCached(pos)) return minValues[pos];

    if (pos >= L-1) return 0; // got the end

    if (hasHoleInPosition(holesLeft, pos) == false) { 
        if (holesLeft.size() == 0) return 0; // no holes left
        return minVal(holesLeft[0], holesLeft); // go to next hole
    }

    ull posAfterPatch, valWithP1, valWithP2;
    vector<ull> holesLeftAfterPatch;

    posAfterPatch = pos+P1+1;
    holesLeftAfterPatch = removeHolesPatched(holesLeft, posAfterPatch);
    valWithP1 = P1 + minVal(posAfterPatch, holesLeftAfterPatch);

    posAfterPatch = pos+P2+1;
    holesLeftAfterPatch = removeHolesPatched(holesLeft, posAfterPatch);
    valWithP2 = P2 + minVal(posAfterPatch, holesLeftAfterPatch);

    minValues[pos] = min(valWithP1, valWithP2);
    return minValues[pos];
}

int main() {
    ull holes;
    while (cin >> holes) {
        cin >> L >> P1 >> P2;
        vector<ull> holesLeft;
        for (ull i = 0; i < holes; i++) {
            ull pos; cin >> pos;
            holesLeft.push_back(pos-1);
        }
        ull res = minVal(0, holesLeft);
        cout << res << endl;
        minValues.clear();
    }
}
