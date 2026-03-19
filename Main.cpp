/* Brandon Baier - Assignment 4
 * Main program
 * runs in the following phases
 * 1) prep history data structure []
 * 2) reading a command from user & adding it to history vector []
 * 3) if reading is simple, exit loop & terminate program []
 * 4) if command is _history_, print the history vector content []
 * 5) if the command is _pwd_ print the current working directory []
 * 6) if command is something else, tokenize, check for piping & redirection, then execute properly []
 * 7) if command redirects, assume last token is file name & open the file using dup2 to change standard in/out []
 * 8) if command has pipe operator, create 2 children []
 */


#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fstream>
#include <fcntl.h>
#include <cstring>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include <map>
#include <array>
using namespace std;

#include "Main.h"
#include "history.h"
// -------------------------------------------------------------- HISTORY -----------------------------------------------------


// Tokenizes the vector. Useful for later
vector <string> getTokenVector(const string &userInput) {
    vector<string> tmpVec;

    stringstream streamObj = stringstream(userInput);
    string currentToken;
    while (streamObj >> currentToken) {
        tmpVec.push_back(currentToken);
    }
    return tmpVec;
}

// if cin is back to normal, it should wait for user keyboard to enter info
// void stdInVerification() {
//     cout << "verifying cin is back to normal" << endl;
//     string tempInput;
//     cin >> tempInput;
//     cin.ignore();
//     cout << tempInput << endl;
// }

int main() {

    history h;
    string userInput;
    vector<string> history;

    int stdInputSave = dup(0);
    int stdOutputSave = dup(1);

    // import the command history from history.txt
    h.readHistory(history, stdInputSave);

    //main program loop
    while (userInput != "exit") {

        cout << endl;
        //u ser enters info
        cout << "Enter user input: ";
        getline(cin, userInput);

        // 2) adding userInput to history vector.
        h.addHistory(history, userInput);


        // Converting
        vector<string> tokenVec = getTokenVector(userInput);
        int tokenNum = tokenVec.size();
        char* userCommand[tokenNum];
        for (int i = 0; i < tokenVec.size(); i++) {
            userCommand[i] = (char *) tokenVec[i].c_str();
        }
        userCommand[-1] = NULL;
        // add user entry to the history vector before tokenization

        // 3) process command

        //


        // tokenization & printing of info
        vector <string> userVec = getTokenVector(userInput);
        for (int i = 0; i < userVec.size(); i++) {
            cout << userVec[i] << endl;
        }
    }

    //write history to the history file given historyVec & standard output save
    h.writeHistory(history, stdOutputSave);

    cout << "end of the program :3" << endl;
    return 0;
}