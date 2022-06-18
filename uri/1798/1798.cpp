#include <stdio.h>
#include <iostream> 
#include <vector>
#include <queue>
#include <list>
#include <stack>
#include <math.h>

using namespace std; 

using num = int;

struct Pipe {
    int len;
    int cost;
    Pipe(int len, int cost):
        len(len), cost(cost) {}
};


int main() {
    num num_sub_pipes, total_len_pipe;
    cin >> num_sub_pipes >> total_len_pipe;
    vector<Pipe> pipes;
    vector<num> max_profit_per_len(total_len_pipe+1, 0);

    for (int i = 0; i < num_sub_pipes; i++) {
        num len, cost;
        cin >> len >> cost;
        if (len <= total_len_pipe)
            max_profit_per_len[len] = max(max_profit_per_len[len], cost);
        pipes.push_back(Pipe(len, cost));
    }

    for (int len = 0; len <= total_len_pipe; len++) {
        num max_profit = max_profit_per_len[len];
        for (int sub = 0; sub < num_sub_pipes; sub++) {
            Pipe sub_pipe = pipes[sub];
            if (len >= sub_pipe.len) {
                num len_left = len - sub_pipe.len;
                num price_with_subpipe = max_profit_per_len[len_left] + sub_pipe.cost;
                max_profit = max(max_profit, price_with_subpipe);
            }
        }
        max_profit_per_len[len] = max_profit;
    }
    
    cout << max_profit_per_len[total_len_pipe] << endl;
    
}