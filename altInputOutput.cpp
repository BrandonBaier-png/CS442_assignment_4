/*
 * Created by Brandon Baier
 * Class created to house functions related to input redirection & piping from part 4 & 5
*/


#include <fcntl.h>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <sys/wait.h>
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

void altInputOutput::pipingRedir(vector<string> runVec, int charPos) {

    //Interpret the final command of the user into a cstring
    char* finalCommand[runVec.size() + 1];
    for (int i = 0; i <=runVec.size(); i++) {
        finalCommand[i] = (char*) runVec[i].c_str();
    }

    // split the 2 commands into 2 pieces, then add a null to the end of each char


    vector<string> vecCmd1;
    copy(runVec.begin(), runVec.end() - (runVec.size() - charPos), back_inserter(vecCmd1));
    char* cmd1[vecCmd1.size() + 1];
    for (int i = 0; i <=vecCmd1.size(); i++) {
        cmd1[i] = (char*) vecCmd1[i].c_str();
    }
    cmd1[vecCmd1.size()] = NULL;

    int runVecVar = runVec.size();
    int charPosVar = charPos;


    vector<string> vecCmd2;
    copy(runVec.begin() + (charPos + 1), runVec.end(), back_inserter(vecCmd2));
    char* cmd2[vecCmd2.size() + 1];
    for (int i = 0; i <=vecCmd2.size(); i++) {
        cmd2[i] = (char*) vecCmd2[i].c_str();
    }
    cmd2[vecCmd1.size()] = NULL;


    // run the double instance of forking to and get the output of the first run to be the input of the second run



    int fds[2]; // this is for the pipe file descriptors

    if (pipe(fds) <0){
        cout<<"Error: Cannot create the pipe"<<endl;
        exit(1);
    }



    int originalSTDIN= dup(0);
    int originalSTDOUT=dup(1);

    pid_t pid;
    pid = fork();

    if( pid < 0){
        cout<<"Error: Cannot create a process"<<endl;
        exit(2);
    } else if(pid==0){ // I am inside the first child

        /*We change the stdout for the first child*/
        dup2( fds[1] , 1);
        close(fds[1]);
        /*closing the reading end*/
        close(fds[0]);

        //change the execution image of the child with the first command (program) entered by the user.
        if(execvp(cmd1[0], cmd1)<0){
            cout<<"Error: Cannot chnage the process exe image a process"<<endl;
            exit(3);
        }

    }else if(pid>0){ /*inside the parent*/
        wait(0); // wait for the first child

        /*We change the stdin for the second child*/
        dup2( fds[0] , 0);
        close(fds[0]); // closing the duplicated end

        cout << "in second child, input was " << fds[0] << endl;
        /*closing the wrting end*/
        dup2(originalSTDOUT, 1);
        close(fds[1]);
        pid_t pid2;
        pid2 = fork(); // second child
        if( pid2 < 0){
            cout<<"Error: Cannot create a process"<<endl;
            exit(4);
        } else if(pid2==0){ // I am inside the second child
            //change the execution image of the second child with the second command (program) entered by the user.
            if(execvp(cmd2[0], cmd2)<0){
                cout<<"Error: Cannot change the process exe image of the second child process "<<endl;
                exit(5);
            }

        } else if(pid2>0){
            wait(0); // wait for the second child
            //we get things stdin and out back to normal

            dup2(originalSTDIN, 0);
            dup2(originalSTDOUT, 1);
            close(originalSTDIN);
            close(originalSTDOUT);

            fflush(stdout);
            cout<<"I am the parent and done with the children work!"<<endl;
        }
    }
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