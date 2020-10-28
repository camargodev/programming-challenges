#include <stdio.h>
#include <iostream> 
#include <math.h>

using namespace std;
using num = unsigned long long;
const num MOD = 1000007;

int main() {
    num val;
    while (true) {
        cin >> val;
        if (val == 0) break;
        num a = 11*pow(val,2)/12;
        num b = pow(val,4)/12;
        num res = (a+b) % MOD;
        cout << res << endl;
    }
}