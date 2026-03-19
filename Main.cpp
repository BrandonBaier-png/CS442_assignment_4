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

// -------------------------------------------------------------- HISTORY -----------------------------------------------------

// gets the contents from the history.txt, assignment 3 part 1 works for this
void readHistory (vector<string>& history, int inputSave) {
    // open the file in read only
    string file_name = "history.txt";
    int fd = open((char*)file_name.c_str(), O_CREAT | O_RDWR, 0666);
    if (fd < 0) {
        cout << "Error opening history.txt" << endl;
        exit(1);
    }

    // changing input to the file
    dup2(fd, 0);

    /* iterate over everything in the history.txt & add it to history vector
     * vector takes in info as fifo order
    */
    string line;
    while (getline(cin, line)) {
        history.push_back(line);
    }

    // so turns out, the stdin input errors out whenever the input is changed, needs to be cleared of errors whenever input is changed
    cin.clear();
    clearerr(stdin);
    close(fd);
    dup2(inputSave, 0);

}

// adds any input command into the history vector, while applying a numbering
void addHistory(vector<string>& history, string& userInput) {
    // determine the number of commands already sitting in the history vector
    int commNum = history.size() + 1;
    string commAndNum = to_string(commNum) + ": " + userInput;
    /* add the <# of command>, <user given command> info to the beginning of the vector, so
     * when printed out in a for loop, it will follow fifo standards
    */
    history.insert(history.begin(), userInput);

}


// exports the current history vector to history txt, assignment 3 part 2 works with this
void writeHistory (vector<string>& history, int outputSave) {


    cout << "temp history dump :3 :" << endl;

    for (int i = 0; i < history.size(); i++) {
        cout << history[i] << endl;
    }

    // Open the file in write & a mode that clears everything within the file
    string file_name = "history.txt";
    // Need to trunicate the file, writing only
    int fd = open((char*)file_name.c_str(), O_TRUNC | O_WRONLY, 0666); // the final no's might not be correct on this one
    if (fd < 0) {
        cout << "Error opening history.txt" << endl;
        exit(1);
    }
    // change the stdout to the opened file
    dup2(fd ,1);

    // output everything in the history vector into the file, with a new line placed between each entry
    for (int i = 0; i < history.size(); i++) {
        cout << history[i] << endl;
    }

    // close the file, clear out the buffer, redirect the input back to standard output
    fflush(stdout);
    cout.clear();
    clearerr(stdout);
    close(fd);
    dup2(outputSave, 1);
}

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

    string userInput;
    vector<string> history;


    int stdInputSave = dup(0);
    int stdOutputSave = dup(1);

    // import the command history from history.txt
    readHistory(history, stdInputSave);


    for (int i = 0; i < history.size(); i++) {}

    //stdInVerification();

    // commented out cause it causes an infinite loop :(

    //main program loop
    while (userInput != "exit") {


        cout << endl;
        //u ser enters info
        cout << "Enter user input: ";
        getline(cin, userInput);
        addHistory(history, userInput);
        // adding userInput to history vector.
        // should be handdled in fifo order, with most recent command at the top of history

        // Converting
        vector<string> tokenVec = getTokenVector(userInput);
        int tokenNum = tokenVec.size();
        char* userCommand[tokenNum];
        for (int i = 0; i < tokenVec.size(); i++) {
            userCommand[i] = (char *) tokenVec[i].c_str();
        }
        userCommand[-1] = NULL;
        // add user entry to the history vector before tokenization



        // tokenization & printing of info
        vector <string> userVec = getTokenVector(userInput);
        for (int i = 0; i < userVec.size(); i++) {
            cout << userVec[i] << endl;
        }
    }

    //write history to the history file given historyVec & standard output save
    writeHistory(history, stdOutputSave);

    cout << "end of the program :3" << endl;
    return 0;
}