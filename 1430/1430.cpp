#include <iostream>
using namespace std;

float getChordDuration(char chord) {
    if(chord == 'W') {
        return (float) 1;
    } else if(chord == 'H') {
        return (float) 1/2;
    } else if(chord == 'Q') {
        return (float) 1/4;
    } else if(chord == 'E') {
        return (float) 1/8;
    } else if(chord == 'S') {
        return (float) 1/16;
    } else if(chord == 'T') {
        return (float) 1/32;
    } else if(chord == 'X') {
        return (float) 1/64;
    } else {
        return (float) 0;
    } 
}

bool isCompassValid(string compass) {
    float compassSum = 0;
    //cout << compass << endl;
    for(char& chord : compass) {
        float chordDuration = getChordDuration(chord);
        compassSum += chordDuration;
        //cout << chord << " : " << chordDuration << endl;

    }
    //cout << compassSum << endl;
    return compassSum == 1;
}

int getNumberOfValidCompasses(string composition) {
    string currentCompass = "";
    int numberOfValidCompasses = 0;
    for(char& chord : composition) {
        if (chord == '/') {
            if(currentCompass != "" && isCompassValid(currentCompass)) {
                numberOfValidCompasses += 1;
            }
            currentCompass = "";
        } else {
            currentCompass += chord;
        }
    }
    return numberOfValidCompasses;
}

int main() {

    string composition;
    cin >> composition;
    while(composition != "*") {
        int numberOfValidCompasses = getNumberOfValidCompasses(composition);
        cout << numberOfValidCompasses << endl;
        cin >> composition;
    }

}