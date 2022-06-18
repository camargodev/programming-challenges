#include <stdio.h>
#include <iostream> 
#include <vector>
#include <queue>
#include <list>
#include <stack>
#include <math.h>

using namespace std; 
using num = int;

const num MAXN = 10001;
vector<bool> is_square_sum(MAXN, false);

void process_square_sums() {
    for (num i = 0; i < MAXN; i++) {
        for (num j = 0; j < MAXN; j++) {
            num product_of_squares = i*i + j*j;
            if (product_of_squares < MAXN)
                is_square_sum[product_of_squares] = true;
        }
    }
}

void print_result(num val) {
    if (val >= 0 && is_square_sum[val])
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
}

int main() {
    num val;
    process_square_sums();
    while(cin >> val) {
        print_result(val);
    }
    return 0;
}