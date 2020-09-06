#include<iostream>
#include <queue>

using namespace std;
using ull = unsigned long long;

struct Process {
  ull startTime;
  ull duration;
  bool isnil;
  Process(ull startTime, ull duration, bool isnil = false) : startTime(startTime),
                                                             duration(duration),
                                                             isnil(isnil)  {}
};

struct DurationComparison {
    bool operator()(Process const& p1, Process const& p2) {
        // true = p1 antes de p2
        /* cout << "now" << now << endl;
        if (p1.startTime > now && p2.startTime > now)
            return (p1.duration > p2.duration);
        if (p1.startTime <= now && p2.startTime <= now)
            return (p1.duration > p2.duration);
        if (p1.startTime > now)
            return false;
        return true; */
        return (p1.duration > p2.duration);
    }
};

struct ClockComparison {
    bool operator()(Process const& p1, Process const& p2) {
        // true = p1 antes de p2
        /* cout << "now" << now << endl;
        if (p1.startTime > now && p2.startTime > now)
            return (p1.duration > p2.duration);
        if (p1.startTime <= now && p2.startTime <= now)
            return (p1.duration > p2.duration);
        if (p1.startTime > now)
            return false;
        return true; */
        return (p1.startTime > p2.startTime);
    }
};

void addWaitingProcess(priority_queue<Process, vector<Process>, ClockComparison> * scheduler,
                Process proc) {
  scheduler->push(proc);
}


void addReadyProcess(priority_queue<Process, vector<Process>, DurationComparison> * scheduler,
                Process proc) {
  scheduler->push(proc);
}

Process getProcess(priority_queue<Process, vector<Process>, DurationComparison> * scheduler) {
  if (scheduler->size() == 0) { return Process(0, 0, true); }
  Process bestFit = scheduler->top();
  scheduler->pop();
  return bestFit;
}

int main() {
  ull numProcesses;
  while (scanf("%llu", &numProcesses) != EOF) {
    ull now = 1;
    ull totalWaited = 0;
    ull numProcessesExecuted = 0;
    priority_queue<Process, vector<Process>, DurationComparison> availableProcs;
    priority_queue<Process, vector<Process>, ClockComparison> procsBuffer;
    for (unsigned int i = 0; i < numProcesses; i++) {
        ull startTime, duration;
        scanf("%llu %llu", &startTime, &duration);
        addWaitingProcess(&procsBuffer, Process(startTime, duration));
    }
    while (numProcessesExecuted < numProcesses) {
        /*cout << procsBuffer.size() << endl;
        cout << procsBuffer.top().startTime << endl;*/
        while (procsBuffer.size() > 0 && procsBuffer.top().startTime <= now) {
            addReadyProcess(&availableProcs, procsBuffer.top());
            procsBuffer.pop();
        }
        Process process = getProcess(&availableProcs);
        if (process.isnil) {
            now = procsBuffer.top().startTime;
            continue;
        }
       /* cout << process.startTime << endl;
        cout << process.duration << endl; */
        if (now < process.startTime)
            now = process.startTime;
        totalWaited += (now - process.startTime);
        now += process.duration;
        numProcessesExecuted += 1;
    }

    cout << totalWaited << endl;

  }
}