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
char* userCommand[4];

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

/* this function should be able to run anything that requires a linux command to be run.
 * 0) determine the desired input & output channel desired for commands to run through this.
 *          * Assume there will only be one instance of redirection or piping in one command line, handling additional is extra credit
 *          ** Assume that there is always a space between any redirection / piping operations
 * 1) pipes are created to communicate with the child process
 * 2) process is forked to create an environment for the command to be run
 * 3) parent process waits for child process to run, child process runs the command and writes information to the parent
 * 4) info is output through the correct channel based on piping & redirecting info given
 */

// creates the char* array used for


// creating a function that
void pipingInstance(vector<string>& tokenVec) {
    // parse through the tokenized vector to determine piping or redirection
    int fd_toChild[2]; // creation of child pipe
    int fd_toParent[2]; // creation of parent pipe

    // creating piping to child -> parent
    if(pipe(fd_toChild) == -1){
        perror("ERROR:Child to Parent Pipe creation failed");
        exit(2);
    }
    // creating piping to parent -> child
    if(pipe(fd_toParent) == -1){
        perror("ERROR: Parent to Child Pipe creation failed");
        exit(3);
    }

    // creating the userCommand char* to be utilized in child process execvp function
    int tokenNum = tokenVec.size();


    for (int i = 0; i <=tokenVec.size(); i++) {
        userCommand[i] = (char*) tokenVec[i].c_str();
    }
    userCommand[-1] = NULL;

    cout << "ready for piping instance" << endl;

    pid_t child_pid = fork();

    if(child_pid < 0){ // fork failed
        perror("ERROR: Fork failed");
    }

    // -------------------------------- CHILD PROCESS --------------------------------
    if(child_pid == 0){
        // closing unneeded pipe ends
        close(fd_toChild[1]);
        close(fd_toParent[0]);

        // running the linux command. done within the if statement to check if it's run
        if (execvp(userCommand[0], userCommand) < 0) {
            cout << "ERROR: couldn't change the execution image for the child process :3" << endl;
        }

        cout << "This message should never run :3" << endl;

        // choose what input to redirect to here
        close(fd_toParent[1]);

    }
    // ------------------------------- PARENT PROCESS --------------------------------
    else{
        // closing unnecessary pipe ends
        close(fd_toChild[0]);
        close(fd_toParent[1]);

        // sending the child process the user command
        write(fd_toChild[1], tokenVec[0].c_str(), tokenVec[0].size()+1);

        //closing the child pipe
        close(fd_toChild[1]);

        // everything before is fine/needs to run before the parent
        wait(0);

        // output what the child process spits out
        close(fd_toParent[0]);


    }

}



/* Main contains the main loop of the program, responsible for handling logic involving
 *
 */
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

        // 1) printing current directory
        if (userInput == "pwd") {
            cout << "printing current directory :3" << endl;
            cout << getcwd(NULL, 0) << endl;
        }



        // Converting
        vector<string> tokenVec = getTokenVector(userInput);
        int tokenNum = tokenVec.size();
        char* userCommand[tokenNum];
        for (int i = 0; i < tokenVec.size(); i++) {
            userCommand[i] = (char *) tokenVec[i].c_str();
        }
        userCommand[-1] = NULL;

        // 3) process command

        // command entry scrutinized for certain scenarios via string comparison & counting
        /* 1) Exit is called
         * 2) "Enter" is pressed with no other commands
         * 3) simple one word command
         * 4) command with piping or redirection
         */
        bool simple = false;

        cout << "output token vec info" << endl;
        for (int i = 0; i < tokenVec.size(); i++) {

            cout << "value " << i << ": " << tokenVec[i] << endl;
        }

        pipingInstance(tokenVec);
    }

    //write history to the history file given historyVec & standard output save
    h.writeHistory(history, stdOutputSave);

    cout << "end of the program :3" << endl;
    return 0;
}
