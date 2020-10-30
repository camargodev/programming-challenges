#include <stdio.h>
#include <iostream> 
#include <vector>
#include <queue>
#include <list>
#include <stack>
#include <math.h>
#include <iomanip>
#include <algorithm>

#define MAX 1010

using namespace std;

int X[MAX], Y[MAX];
long T[MAX][MAX];

long sqr(long v) { return v*v; }

int main() {
    int num_points;
    while(true) {
    	cin >> num_points;
    	if (num_points == 0) 
            break;
    	
        for(int i = 0; i < num_points; ++i)
            cin >> X[i] >> Y[i];
        
        int sum = 0;
        for(int i = 0; i < num_points; ++i)  {
        	int aux = 0;
            for(int j = 0; j < num_points; ++j)
                T[i][aux++] = sqr(X[i] - X[j]) + sqr(Y[i] - Y[j]);
                
            sort(T[i], T[i] + aux);
            long last = -1L;
            int cnt = 0;
            
            for(int j = 0; j < aux; ++j)  {
                if (T[i][j] != last)  {
                    sum += (cnt * (cnt - 1)) / 2;
                    cnt = 0;
                }
                last = T[i][j];
                cnt++;
            }
            sum += (cnt * (cnt - 1)) / 2;
        }

        cout << sum << endl;
    }
    return 0;
    
}