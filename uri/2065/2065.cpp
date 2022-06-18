#include <stdio.h>
#include <iostream> 
#include <vector>
#include <queue>

using namespace std; 

struct Worker {
    int id;
    int time;
    int freeTime = 1;
    Worker(int id, int time) : id(id), time(time) {}
};

struct Costumer {
    int id;
    int numOfProducts;
    Costumer(int id, int n) : id(id), numOfProducts(n) {}
};

struct AvailWorkerComparator {
    bool operator()(Worker const& w1, Worker const& w2) {
        return (w1.id > w2.id);
    }
};

struct FreeWorkerComparator {
    bool operator()(Worker const& w1, Worker const& w2) {
        return (w1.freeTime > w2.freeTime);
    }
};

using AvailableWorkers = priority_queue<Worker, vector<Worker>, AvailWorkerComparator>;
using WorkersFreeTime = priority_queue<Worker, vector<Worker>, FreeWorkerComparator>;

// void updateAvailableWorkers(WorkerPQ* availableWorkers, )

int main() {

    int numWorkers, numCustomers, time, custProducts;
    cin >> numWorkers >> numCustomers;

    vector<Costumer> costumersLeft;
    AvailableWorkers availableWorkers;
    WorkersFreeTime workersFreeTime;

    for (int i = 0; i < numWorkers; i++) {
        cin >> time;
        Worker worker(i, time);
        workersFreeTime.push(worker);
    }

    for (int i = 0; i < numCustomers; i++) {
        cin >> custProducts;
        Costumer costumer(i, custProducts);
        costumersLeft.push_back(costumer);
    }

    int now = 1;

    int lastTime = 0;

    while(costumersLeft.size() > 0) {
        // cout << "\nNow: " << now << endl;
        while (workersFreeTime.size() > 0 && workersFreeTime.top().freeTime <= now) {
            Worker w = workersFreeTime.top();
            // cout << "Worker " << w.id << " is available with free time " << w.freeTime << endl;;
            availableWorkers.push(w);
            workersFreeTime.pop();
        }
        // cout << "I currently have " << availableWorkers.size() << " available workers" << endl;
        if (availableWorkers.size() == 0) {
            now = workersFreeTime.top().freeTime;
        } else {
            Worker availableWorker = availableWorkers.top();
            Costumer costumer = costumersLeft[0];

            // cout << "The used worker is " << availableWorker.id << endl;
            // cout << "Customer is " << costumer.id << endl;
            // cout << "Now " << now << ": " << "cost: " << costumer.numOfProducts;
            // cout << " worker: " << availableWorker.time << endl;

            availableWorker.freeTime = now + (costumer.numOfProducts*availableWorker.time);
            workersFreeTime.push(availableWorker);

            costumersLeft.erase(costumersLeft.begin());
            availableWorkers.pop();

            lastTime = max(lastTime, availableWorker.freeTime-1);

            // now += 1;
        }

        // Costumer costumer(custProducts);
        // costumers.push_back(costumer);
    }

    cout << lastTime << endl;

    return 0;


}