#ifndef ASSIGNMENT1_FOUNDATION_H
#define ASSIGNMENT1_FOUNDATION_H

#include <iostream>
#include <fstream>

using namespace std;

class Foundation {
    public:
        string foundationList[4];
        string *pFoundationList;
        void createFoundation();
        bool addCard(string cardName);
        void removeCard(int foundationNum);
        void printFoundation(ofstream* output);
        bool checkEmpty(int foundationNum);

    bool checkWin();
};


#endif //ASSIGNMENT1_FOUNDATION_H
