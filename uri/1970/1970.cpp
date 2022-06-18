#include <stdio.h>
#include <iostream> 
#include <vector>
#include <queue>
#include <list>
#include <stack>
#include <math.h>
#include <string.h>

using namespace std;

using num = int;
#define loop(n) for (num i = 0; i < n; i++)
#define loopi(i, n) for (num i = 0; i < n; i++)

const num MAX_SONGS = 101, MAX_TAPES = 4, MAX_LEN = 51;

num num_songs, num_tapes;
vector<num> songs;
num dp[MAX_SONGS][MAX_LEN][MAX_LEN][MAX_LEN];

num max_usage(num curr_song, num c1, num c2, num c3) {

    if (curr_song == num_songs) return 0;

    num val = dp[curr_song][c1][c2][c3];
    if (val != -1) return val;
    
    num song_len = songs[curr_song];
    num next = curr_song + 1;

    num result = max_usage(next, c1, c2, c3);

    num used_tape = -1;

    if (c1 >= song_len) {
        num tape_1 = max_usage(next, c1-song_len, c2, c3);
        result = max(result, song_len + tape_1);
    }
    if (c2 >= song_len) {
        num tape_2 = max_usage(next, c1, c2-song_len, c3);
        result = max(result, song_len + tape_2);
    }
    if (c3 >= song_len) {
        num tape_3 = max_usage(next, c1, c2, c3-song_len);
        result = max(result, song_len + tape_3);
    }

    return dp[curr_song][c1][c2][c3] = result;
}

int main() {
    while(cin >> num_songs >> num_tapes) {
        memset(dp, -1, sizeof dp);
        songs.resize(num_songs);
        vector<num> capacities(num_tapes, -1);
        loopi(i, num_songs) {
            cin >> songs[i];
        }
        loopi(i, num_tapes) {
            cin >> capacities[i];
        }
        num u = max_usage(0, capacities[0], capacities[1], capacities[2]);
        cout << u << endl;
        songs.clear();
        capacities.clear();
    }
    return 0;
}