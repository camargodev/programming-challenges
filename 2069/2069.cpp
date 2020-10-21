#include <stdio.h>
#include <iostream> 
#include <math.h>
using namespace std;
using num = long long;

const num MAXN = 100000LL;

int main() {
    num a, b;
    cin >> a >> b;
    num res = 1;
    for (num i = 2; i < MAXN; i++) {
        num exp_a = 0, exp_b = 0;
        while (a % i == 0) { exp_a += 1; a /= i; }
        while (b % i == 0) { exp_b += 1; b /= i; }
        num exp = min(exp_a, exp_b);
        exp = (exp + (exp % 2))/2;
        res *= pow(i, exp);
    }
    if (a == b) res *= a;
    cout << res << endl;
}