/*
 * Created by Brandon Baier
 * Class created to house functions related to input redirection & piping from part 4 & 5
*/


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
map<char, int> charSearch = {
    { '<',  60},
    { '>',  62},
    { '|',  124}
};



int altInputOutput::checkForAltInOut(vector<string> userCommand) {
    vector <int> alternatives;
    char huntVar = '<';
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
    return charSearch[huntVar];
}
