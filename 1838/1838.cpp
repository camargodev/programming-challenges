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
// num cache[1001][3601];

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
    if (cache.find(key) != cache.end()) 
        return cache[key];
    // if (cache[index][minute] != -1) return cache[index][minute];
   
    // loop(tabs) cout << " ";
    // cout << ">>> Req: " << reqidx << " starts at " << req.start << " - mins left: " << minsleft << endl;
    // if (currmin < req.start) { 
    //     // loop(tabs) cout << " ";
    //     // cout << "> At minute " << currmin << " but req starts at " << req.start << endl;
    //     minsidle += req.start - currmin;
    //     // loop(tabs) cout << " ";
    //     // cout << "> Idle for " << minsidle << " min " << endl;
    //     currmin = req.start;
    // } 


    // else if (req.start < currmin) {
        // loop(tabs) cout << " ";
        // cout << "> Cannot use req, because start already passed at " << currmin << endl;
        // return minsleft;
    // }
    // loop(tabs) cout << " ";
    // cout << "> Not gonna use curr; going to " << reqidx+1 << endl;
    Request request = requests[index];
    num usage = maxUsage(minute, index+1);
    if (minute <= request.start) {
        // loop(tabs) cout << " ";
        // cout << "> Able to use curr with duration " << req.duration << endl; 
        // minsleft -= req.duration;
        // loop(tabs) cout << " ";
        // cout << "> Available for " << minsleft << " now " << endl;
        // currmin += req.duration;

        num usageWithCurr = maxUsage(request.end, index+1);
        // reswithcurr += 
        // num minimunidlewithcurr = minidle(currmin+req.duration, reqidx+1, 
        //     minsleft-req.duration, minsidle, tabs+1);
        usage = max(usage, usageWithCurr + request.duration);
    }
    // loop(tabs) cout << " ";
    // cout << "> I'm req " << reqidx << " returning " << minimunidle << endl;
    cache[key] = usage;
    return usage;
}

num stoneMaxUse() {
    // cout << "requests = [ ";
    // loopi(i, N) { cout << "( " << requests[i].start << " - " << requests[i].duration << " ) "; }
    // cout << "]" << endl;
    return maxUsage(0, 0);
    // num idle = minidle(1, 0, TOTAL_MINS, 0, 0);
    // // return idle;
    // return TOTAL_MINS - idle;
}

int main() {
    cin >> N;
    ReqPQ heap;
    loop(N) { 
        num start, duration;
        cin >> start >> duration;
        heap.push(Request(start, duration));
    }
    // memset(cache, -1, sizeof cache);
    while(heap.size() > 0) {
        Request r = heap.top(); 
        requests.push_back(r);
        heap.pop();
    }
    num maxuse = stoneMaxUse();
    cout << maxuse << endl;
    requests.clear();
}