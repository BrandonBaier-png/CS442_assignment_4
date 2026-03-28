/*
 * Created by Brandon Baier
 * Class created to house functions related to input redirection & piping from part 4 & 5
*/


#include <fcntl.h>
#include <string>
#include <vector>
#include <bits/stdc++.h>
using namespace std;


#include "altInputOutput.h"

/* Returns an int based on what character was found
 * -1 means none of the searched characters were found
 *  rest are based on their decimal ASCII unicode values
 *  [< : 60] [> : 62] [| : 124]
 */




int altInputOutput::checkForAltInOut(vector<string> userCommand, char huntVar) {
    vector <int> alternatives;

    string output =  "undef";
    int pos = -1;
    // loop through to find any instances of searched character
    for (int x = 0; x < userCommand.size(); x++) {
        for (int y = 0; y < userCommand[x].length(); y++) {
            if (userCommand[x].find(huntVar) != string::npos) {
                // add it to the vector containing each instance of
                pos = x;
            }

        }
    }
    if (pos == -1) {
        return -1;
    }
    cout << huntVar << " was found, in spot: " << pos << endl;
    return pos;
}

// redirects the input to target file
bool altInputOutput::inputRedir(string fileName) {
    int fd = open((char*)fileName.c_str(), O_RDWR, 0666);
    if (fd < 0) {
        cout << "Error opening " << fileName << endl;
        return false;
    }
    dup2(fd, 0);
    return true;
}

// redirects the output to target fi__struct_FILE_defined
bool altInputOutput::outputRedir(string fileName) {
    int fd = open((char*)fileName.c_str(), O_CREAT | O_TRUNC | O_WRONLY, 0666);
    if (fd < 0) {
        cout << "Error opening " << fileName << endl;
        return false;

    }
    // change the stdout to the opened file
    dup2(fd ,1);
    return true;
}

// returns input redirection to the initial save (keyoard)
void altInputOutput::resetIn(int inputSave) {
    // input reset
    cin.clear();
    clearerr(stdin);
    dup2(inputSave, 0);
}

// return output redirection to the initial save (command line)
void altInputOutput::resetOut(int outputSave) {
    cout.clear();
    dup2(outputSave, 1);

}