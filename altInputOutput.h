//
// Created by Brandon Baier
//

#ifndef CS442_ASSIGNMENT_4_ALTINPUTOUTPUT_H
#define CS442_ASSIGNMENT_4_ALTINPUTOUTPUT_H


class altInputOutput {
    public:
    map<char, int> charSearch;
    int checkForAltInOut(vector<string> userCommand, char huntVar);//, char huntVar);
    bool inputRedir(string fileName);
    bool outputRedir(string fileName);

    static void resetIn(int inputSave);
    static void resetOut(int outputSave);

};


#endif //CS442_ASSIGNMENT_4_ALTINPUTOUTPUT_H