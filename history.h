//
// Created by Brandon Baier
//

#ifndef CS442_ASSIGNMENT_4_HISTORY_H
#define CS442_ASSIGNMENT_4_HISTORY_H


class history {
    public:
    void readHistory (vector<string>& history, int inputSave);
    void addHistory(vector<string>& history, string& userInput);
    void writeHistory (vector<string>& history, int outputSave);
};


#endif //CS442_ASSIGNMENT_4_HISTORY_H