#include <stdio.h>
#include <iostream> 
#include <vector>
#include <queue>
#include <list>

using namespace std; 
#define INF 0x3f3f3f3f

int bfs(int src, int numPeople, int* ages, vector<int>* bosses) {
    int minAge = INF;
    queue<int> people;
    bool visited[numPeople];
    for (int i = 0; i < numPeople; i++) visited[i] = false;
    
    people.push(src);
    visited[src] = true;
    
    while(people.size() > 0) {
        int person = people.front();
        people.pop();
        // int age = ages[person];
        // // cout << "Popped " << person << ": age " << age << endl;
        // minAge = min(minAge, age);
        for (int i = 0; i < bosses[person].size(); i++) {
            int boss = bosses[person][i];
            if (visited[boss]) continue;

            int age = ages[boss];
            minAge = min(minAge, age);
            people.push(boss);
            visited[boss] = true;
        }
    }
    return minAge;
}

void print(int n, int* ages) {
    cout << "[ ";
    for (int i = 0; i < n; i ++) cout << ages[i] << " ";
    cout << "]" << endl;
}

int main() {
    int numPeople, numRelations, numInstructions;
    while (cin >> numPeople >> numRelations >> numInstructions) {
        int* ages = new int[numPeople];
        vector<int>* bosses = new vector<int>[numPeople];
        // int* positions = new int[numPeople];
        for (int i = 0; i < numPeople; i++) {
            int age; cin >> age;
            ages[i] = age;
            // positions[i] = i;
        }
        // print(numPeople, ages);
        for (int i = 0; i < numRelations; i++) {
            int from, to;
            cin >> from >> to;
            from--; to--;
            bosses[to].push_back(from);
            // cout << to << " -> " << from << endl; 
        }
        for (int i = 0; i < numInstructions; i++) {
            char inst; cin >> inst;
            if (inst == 'T') {
                int person1, person2;
                cin >> person1 >> person2;
                person1--; person2--;

                for (int p = 0 ; p < numPeople; p++) {					
                    for (int b = 0; b < bosses[p].size(); b++) {
                        if (bosses[p][b] == person2) bosses[p][b] = person1;
                        else if (bosses[p][b] == person1) bosses[p][b] = person2;
                    }
                }

                vector<int> bossesp1 = bosses[person1];
                bosses[person1] = bosses[person2];
                bosses[person2] = bossesp1;

            } else if (inst == 'P') {
                int person;
                cin >> person;
                person--;
                int minAge = bfs(person, numPeople, ages, bosses);
                if (minAge == INF) cout << "*" << endl;
                else cout << minAge << endl;
            }
        }
    }
}