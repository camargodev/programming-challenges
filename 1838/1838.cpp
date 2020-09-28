#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>

using namespace std; 

using num = long long;
#define loop(n) for (num i=0; i<n; ++i)
#define loopi(i, n) for (num i=0; i<n; ++i)


num TOTAL_MINS = 3600;
num N;

struct Request {
  num start;
  num duration;
  num end;
  Request(num start, num duration): 
    start(start), duration(duration), end(start+duration) {}
};

struct Comp {
    bool operator()(Request const& r1, Request const& r2) {
        return (r1.start > r2.start);
    }
};

using ReqPQ = priority_queue<Request, vector<Request>, Comp>;
vector<Request> requests;

num maxUse(num index, num minsleft, num minsidle) {
    if (index == N) return 0;
    cout << "at index " << index << endl;
    Request curr = requests[index];
    num maxusage = maxUse(index+1, minleft, minsidle);
    if (minleft >= curr.duration) {
        cout << " can add curr with duration " << curr.duration << endl;
        num temp = curr.duration + maxUse(index+1, minleft-curr.duration);
        cout << "  max with curr = " << temp << endl;
        cout << "  max without curr = " << maxusage << endl;
        maxusage = max(maxusage, temp);
    }
    return maxusage;
}

num stoneMaxUse() {
    cout << "requests = [ ";
    loopi(i, N) { cout << requests[i].start << " "; }
    cout << "]" << endl;
    return maxUse(0, TOTAL_MINS, TOTAL_MINS);
}


int main() {
    cin >> N;
    ReqPQ heap;
    loop(N) { 
        num start, duration;
        cin >> start >> duration;
        heap.push(Request(start, duration));
    }
    while(heap.size() > 0) {
        Request r = heap.top(); 
        requests.push_back(r);
        heap.pop();
    }
    num maxuse = stoneMaxUse();
    cout << maxuse << endl;
    requests.clear();
}