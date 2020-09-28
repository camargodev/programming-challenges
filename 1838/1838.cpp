#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>

using namespace std; 

using num = long long;
#define loop(n) for (num i=0; i<n; ++i)
#define loopi(i, n) for (num i=0; i<n; ++i)

#define INF 1000

num TOTAL_MINS = 3600;
num N;

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

num minidle(num currmin, num reqidx, num minsleft, num minsidle, int tabs) {
    if (currmin > TOTAL_MINS || reqidx == N) { 
        // loop(tabs) cout << " ";
        // cout << "> currmin = " << currmin << " and reqidx = " << reqidx << endl; 
        // loop(tabs) cout << " ";
        // cout << ">>>>> back with " << minsleft << " mins left" << endl; 
        return minsleft; 
    }

    Request req = requests[reqidx];
    // loop(tabs) cout << " ";
    // cout << ">>> Req: " << reqidx << " starts at " << req.start << " - mins left: " << minsleft << endl;
    if (currmin < req.start) { 
        // loop(tabs) cout << " ";
        // cout << "> At minute " << currmin << " but req starts at " << req.start << endl;
        minsidle += req.start - currmin;
        // loop(tabs) cout << " ";
        // cout << "> Idle for " << minsidle << " min " << endl;
        currmin = req.start;
    } 
    // else if (req.start < currmin) {
        // loop(tabs) cout << " ";
        // cout << "> Cannot use req, because start already passed at " << currmin << endl;
        // return minsleft;
    // }
    // loop(tabs) cout << " ";
    // cout << "> Not gonna use curr; going to " << reqidx+1 << endl;
    num minimunidle = minidle(currmin, reqidx+1, minsleft, minsidle, tabs+1);
    if (minsleft >= req.duration && req.start >= currmin) {
        // loop(tabs) cout << " ";
        // cout << "> Able to use curr with duration " << req.duration << endl; 
        minsleft -= req.duration;
        // loop(tabs) cout << " ";
        // cout << "> Available for " << minsleft << " now " << endl;
        currmin += req.duration;
        num minimunidlewithcurr = minidle(currmin, reqidx+1, minsleft, minsidle, tabs+1);
        minimunidle = min(minimunidle, minimunidlewithcurr);
    }
    // loop(tabs) cout << " ";
    // cout << "> I'm req " << reqidx << " returning " << minimunidle << endl;
    return minimunidle;

}

num stoneMaxUse() {
    // cout << "requests = [ ";
    // loopi(i, N) { cout << "( " << requests[i].start << " - " << requests[i].duration << " ) "; }
    // cout << "]" << endl;
    num idle = minidle(1, 0, TOTAL_MINS, 0, 0);
    // return idle;
    return TOTAL_MINS - idle;
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