#include <stdio.h>
#include <iostream> 
#include <math.h>
using namespace std;
using num = long long;

//  (val * x) % mod  ≡ 1
// exemplo:
//  para val = 2 and mod = 7
//      (2 * x) % 7 = 1
//       x = 11, porque 22%7 = 1
int inv(int val, int mod) {

    int start_mod = mod; 
    int aux = 0;
    int res = 1; 
  
    if (mod == 1) return 0; 
  
    while (val > 1) { 
        int quotient = val / mod; 
        int temp_mod = mod; 
        mod = val % mod;
        val = temp_mod; 
        temp_mod = aux; 
        aux = res - quotient * aux; 
        res = temp_mod; 
    } 

    if (res < 0) res += start_mod; 
  
    return res; 
} 

num get_num_of_oranges(num div[], num rest[], num prod) { 
  
    num result = 0; 
    for (num i = 0; i < 3; i++) { 
        num pp = prod / div[i]; 
        result += rest[i] * inv(pp, div[i]) * pp; 
    } 
  
    return result % prod; 
} 

bool all_rests_zero(num rest[]) {
    if (rest[0] > 0) return false;
    if (rest[1] > 0) return false;
    if (rest[2] > 0) return false;
    return true;
}

int main() {
    num div[3];
    num rest[3];
    num case_index = 0;
    while(cin >> rest[0] >> div[0]) {
        // cout << "case " << case_index << endl;
        cin >> rest[1] >> div[1];
        cin >> rest[2] >> div[2];
        case_index += 1;
        num prod = div[0]*div[1]*div[2];
        bool are_all_rests_zero = all_rests_zero(rest);
        num res = are_all_rests_zero ? prod : get_num_of_oranges(div, rest, prod);
        cout << "Caso #" << case_index << ": " << res << " laranja(s)" << endl;
    }
}