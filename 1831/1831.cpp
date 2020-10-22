#include <stdio.h>
#include <iostream> 
#include <math.h>
using namespace std;
using num = long long;

int main() {
    num div[3];
    num rest[3];
    num case_index = 0;
    while(cin >> rest[0] >> div[0]) {
        // cout << "case " << case_index << endl;
        cin >> rest[1] >> div[1];
        cin >> rest[2] >> div[2];
        case_index += 1;
        bool found = false;
        num curr = 0;
        while(!found) {
            found = true;
            curr += 1;
            // cout << "curr " << curr << endl;
            for (num i = 0; i < 3; i++) {
                if (curr % div[i] != rest[i]) {
                    found = false;
                    break;
                } 
            }
        }
        cout << "Caso #" << case_index << ": " << curr << " laranja(s)" << endl;
    }
}