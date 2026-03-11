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
void openHistoryFile() {

}

// gets the contents from the history.txt, assignment 3 part 1 works for this
void readHistory (int& stdin, vector<string>& history) {
    // open the file in read only
    int fd = open("history.txt", O_CREAT | O_RDWR);
    if (fd < 0) {
        cout << "Error opening history.txt" << endl;
        exit(1);
    }
    // changing input to the file
    dup2(fd, 0);

    // iterate over everything in the history.txt & add it to history vector

    string line;
    // trying to get it to
    while (getline(cin, line)) {
        history.push_back(line);
    }
    cout << "was able to make it out :3" << endl;

    // reverting back to standard input
    dup2(stdin, 0);
    // might need fflush, see dup2 example to fix
    //fflush(fd); //??
    // close the file

    close(fd);
}

// exports the current history vector to history txt, assignment 3 part 2 works with this
void writeHistory (vector<string>& history) {
    // open the file in a mode that erases everything &

    // open the
    //write()
    // close the file
}

// Tokenizes the vector. Useful for later
vector <string> getTokenVector(string userLine) {
    vector<string> tmpVec;

    stringstream streamObj = stringstream(userLine);
    string currentToken;
    while (streamObj >> currentToken) {
        tmpVec.push_back(currentToken);
    }
    return tmpVec;
}


int main() {

    string userInput;
    vector<string> history;
    int stdin = dup(0);
    int stdout = dup(1);

    // import the command history from history.txt
    readHistory(stdin, history);
    cout << "hopefully input is back to normal after this :3" << endl;
    //fflush(stdin);

    // main program loop
    while (userInput != "exit") {
        //u ser enters info
        cout << "Enter user input: ";
        getline(cin, userInput);

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

    //export the command history to history.txt
    //writeHistory();

    cout << "end of the program :3" << endl;
    return 0;
}