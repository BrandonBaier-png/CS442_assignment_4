//
// Created by Brandon Baier
// Separation of History functions from main.cpp

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <sys/types.h>
#include <fstream>
#include <fcntl.h>
#include <cstring>
#include <bits/stdc++.h>
using namespace std;

#include "altInputOutput.h"
#include "history.h"


// gets the contents from the history.txt, assignment 3 part 1 works for this
void history::readHistory (vector<string>& history, int inputSave) {
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

    altInputOutput a;
    // so turns out, the stdin input errors out whenever the input is changed, needs to be cleared of errors whenever input is changed
    a.resetIn(inputSave);

}

// adds any input command into the history vector, while applying a numbering
void history::addHistory(vector<string>& history, string& userInput) {
    // determine the number of commands already sitting in the history vector
    int commNum = history.size() + 1;
    string commAndNum = to_string(commNum) + ": " + userInput;
    /* add the <# of command>, <user given command> info to the beginning of the vector, so
     * when printed out in a for loop, it will follow fifo standards
    */
    history.insert(history.begin(), commAndNum);

}


// exports the current history vector to history txt, assignment 3 part 2 works with this

void history::writeHistory (vector<string>& history, int outputSave) {

    // cout << "temp history dump :3 :" << endl;
    // for (int i = 0; i < history.size(); i++) {
    //     cout << history[i] << endl;
    // }

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