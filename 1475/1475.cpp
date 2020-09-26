#include <iostream>
#include <vector>

using namespace std; 

vector<int> positions;

// bool hasHole(int pos) {
//     return find(positions.begin(), positions.end(), pos) != positions.end();
// }

int minVal(int L, int P1, int P2, int pos, vector<bool> covered) {
    if (pos == L-1) { 
        // cout << "End: " << pos << endl;
        return 0;
    }

    if (covered[pos]) { 
        // cout << "Covered: " << pos << " > going to " << pos+1 << endl;
        return minVal(L, P1, P2, pos+1, covered);
    }

    vector<bool> coveredP1 = covered;
    for (int i = pos; i < pos + P1 + 1; i++)
        coveredP1[i] = true;
    int valWithP1 = P1 + minVal(L, P1, P2, pos+1, coveredP1);

    vector<bool> coveredP2 = covered;
    for (int i = pos; i < pos + P2 + 1; i++)
        coveredP2[i] = true;
    int valWithP2 = P2 + minVal(L, P1, P2, pos+1, coveredP2);

    return min(valWithP1, valWithP2);
}

int calculateMinVal(int L, int P1, int P2, vector<bool> covered) {
    return minVal(L, P1, P2, 0, covered);
}

int main() {
    int holes;
    while (cin >> holes) {
        int totalLength, patch1, patch2;
        cin >> totalLength >> patch1 >> patch2;
        vector<bool> covered(totalLength, true);
        for (int i = 0; i < holes; i++) {
            int pos; cin >> pos;
            // cout << "Hole at " << pos-1 << endl;
            // positions.push_back(pos);
            covered[pos-1] = false;
        }
        int minVal = calculateMinVal(totalLength, patch1, patch2, covered);
        cout << minVal << endl;
    }
}
