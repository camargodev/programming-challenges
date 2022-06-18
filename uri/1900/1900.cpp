#include <stdio.h>
#include <iostream> 
#include <vector>
#include <queue>
#include <list>
#include <map>
#include <math.h>
#include <string.h>

using namespace std;

using num = long long;

int main() {
    map<num, num> total_for_val;
    num len; cin >> len;
    num total = 0, sum = 0, curr;
    total_for_val[0] = 1;
    for(int i = 0; i < len; i++){
        cin >> curr;
        sum += curr; // soma até então
        total += total_for_val[sum]; 
        total_for_val[sum]++;
    }
    cout << total << endl;
    return 0;
}
