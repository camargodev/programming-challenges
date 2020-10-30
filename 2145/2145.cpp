#include <stdio.h>
#include <iostream> 
#include <vector>
#include <queue>
#include <list>
#include <stack>
#include <math.h>
#include <iomanip>

using namespace std; 
using num = int;
using Relation = int;
#define for_range(i, n) for (num i = 0; i < n; i++)
#define INF 0x3f3f3f3f

const Relation FRIENDZONE = 0, ALMOST = 1, LOVERS = 2, NONE = 3;

struct Relationship {
    num A;
    num B;
    Relation relation;
};

num get_sum_of_divisors(num N) {
    num half = N/2;
    num sum = 1;
    for (int i = 2; i < half+1; i++) 
        if (N % i == 0) sum += i;
    return sum;
}

Relationship build_relationship(num N, num M) {
    Relationship relationship;
    num sum_n = get_sum_of_divisors(N);
    num sum_m = get_sum_of_divisors(M);

    bool m_divides_by_sum_of_n = M % sum_n == 0;
    bool n_divides_by_sum_of_m = N % sum_m == 0;

    // cout << "N = " << N << " - sum = " << sum_n << " - divides = " << n_divides_by_sum_of_m << endl;
    // cout << "M = " << M << " - sum = " << sum_m << " - divides = " << m_divides_by_sum_of_n << endl;

    if (m_divides_by_sum_of_n && n_divides_by_sum_of_m) {
        relationship.relation = LOVERS;
        return relationship;
    }

    if (sum_m == sum_n) {
        relationship.relation = ALMOST;
        return relationship;
    }

    if (m_divides_by_sum_of_n) {
        relationship.A = N;
        relationship.B = M;
        relationship.relation = FRIENDZONE;
        return relationship;
    }

    if (n_divides_by_sum_of_m) {
        relationship.A = M;
        relationship.B = N;
        relationship.relation = FRIENDZONE;
        return relationship;
    }

    relationship.relation = NONE;
    return relationship;
}

void print_relationship(Relationship relationship) {
    if (relationship.relation == NONE) {
        cout << "No connection" << endl;
    } else if (relationship.relation == ALMOST) {
        cout << "Almost lovers!" << endl;
    } else if (relationship.relation == LOVERS) {
        cout << "Friends and lovers <3" << endl;
    } else {
        cout << relationship.A << " friendzoned " << relationship.B << endl;
    }
}

int main() {

    num N, M;
    while(true) {
        cin >> N >> M;
        if (N == 0 && M == 0) break;
        Relationship relationship = build_relationship(N, M);
        print_relationship(relationship);
    }


    return 0;
}