#include <iostream>
using namespace std;

string fixPhrase(string wrongPhrase) {
    string fixedPhrase = "";
    bool appendOnBegin = false;
    string strToAppendOnBegin = "";
    for(char& letter : wrongPhrase) {
        if(letter == '[') {
            appendOnBegin = true;
            fixedPhrase = strToAppendOnBegin + fixedPhrase;
            strToAppendOnBegin = "";
            continue;
        } else if (letter == ']') {
            appendOnBegin = false;
            fixedPhrase = strToAppendOnBegin + fixedPhrase;
            strToAppendOnBegin = "";
            continue;
        }
        if (appendOnBegin) {
            strToAppendOnBegin += letter;
        } else {
            fixedPhrase += letter;
        }
    }
    if (strToAppendOnBegin != "" && appendOnBegin)
            fixedPhrase = strToAppendOnBegin + fixedPhrase;
    return fixedPhrase;
}

int main() {

    string phrase;
    char input[100000];
    while (scanf("%100000s", input) != EOF) {
        phrase = input;
        string fixedPhrase = fixPhrase(phrase);
        cout << fixedPhrase << endl;
    }

}