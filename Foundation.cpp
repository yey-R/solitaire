
#include "Foundation.h"

void Foundation::createFoundation() {
    pFoundationList = foundationList;
    *(pFoundationList + 0) = "H00";
    *(pFoundationList + 1) = "D00";
    *(pFoundationList + 2) = "S00";
    *(pFoundationList + 3) = "C00";
}

bool Foundation::addCard(string cardName) {
    for(int index=0; index < 4; index++){
        if(cardName.substr(0, 1) == (*(pFoundationList + index)).substr(0,1)){
            if(stoi(cardName.substr(1, 2)) == stoi((*(pFoundationList + index)).substr(1,2))+1) {
                *(pFoundationList + index) = cardName;
                return true;
            }
        }
    }
    return false;
}

void Foundation::removeCard(int foundationNum){
    string cardName;
    if(!checkEmpty(foundationNum)) {
        string cardType = foundationList[foundationNum].substr(0, 1);
        int cardNum = atoi(foundationList[foundationNum].substr(1, 2).c_str()) - 1;
        if (cardNum >= 10) {
            cardName = cardType + to_string(cardNum);
        } else {
            cardName = cardType + "0" + to_string(cardNum);
        }
        foundationList[foundationNum] = cardName;
    }
}

bool Foundation::checkEmpty(int foundationNum){
    if(foundationList[foundationNum].substr(1,2) == "00"){
        return true;
    }
    return false;
}

bool Foundation::checkWin() {
    int counter =0;
    for(int index=0; index<4; index++){
        if(foundationList[index].substr(1,2) == "13"){
            counter++;
        }
    }
    if(counter==4){
        return true;
    }
    return false;
}

void Foundation::printFoundation(ofstream* output) {
    for(int index=0; index < 4; index++){
        if(atoi((*(pFoundationList + index)).substr(1,2).c_str()) != 0){
            *output << (*(pFoundationList + index)) << " ";
        }
        else{
            *output << "___ ";
        }
    }
    *output << endl;
}