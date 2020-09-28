#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>

using namespace std; 

using num = long long;
using keyty = pair<num, num>;
#define loop(n) for (num i=0; i<n; ++i)
#define loopi(i, n) for (num i=0; i<n; ++i)

num MAX_MINS = 3600;
num N;

map<keyty, num> cache;

struct Request {
  num start;
  num duration;
  num end;
  Request(num start, num end): 
    start(start), duration(end-start), end(end) {}
};

struct Comp {
    bool operator()(Request const& r1, Request const& r2) {
        return (r1.start > r2.start);
    }
};

using ReqPQ = priority_queue<Request, vector<Request>, Comp>;
vector<Request> requests;

num maxUsage(num minute, num index) {
    
    if (index == N) return 0; 
    if (minute == MAX_MINS) return 0;

    keyty key = make_pair(index, minute);
    if (cache.find(key) != cache.end()) return cache[key];
    
    num usage = maxUsage(minute, index+1);
    Request request = requests[index];
    if (minute <= request.start) {
        num usageWithCurr = maxUsage(request.end, index+1);
        usage = max(usage, usageWithCurr + request.duration);
    }
    cache[key] = usage;
    return usage;
}

num stoneMaxUse() {
    return maxUsage(0, 0);
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