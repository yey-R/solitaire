#include "Pile.h"
#include <iostream>

using namespace std;

void Pile::createPile(string deckFile) {
    FileOperation::file(deckFile, cards);
    int addedCards = 0;
    for(int i=0; i < 7; i++){
        for(int j = i; j < 7; j++){
            Card newCard;
            newCard.cardName = cards[51-addedCards];
            newCard.ifExist = true;
            if(j == i){
                newCard.ifClosed = false;
            }
            pile[i][j] = newCard;
            addedCards++;
        }
    }
}

bool Pile::openPile(int pileNum) {
    int counter = 0;
    if(checkColm(pileNum)){
        for (int index = 0; index < pileCards; index++) {
            if (pile[index][pileNum].ifExist) {
                if (!pile[index][pileNum].ifClosed) {
                    return false;
                }
                counter++;
            }
        }
    }
    else{
        return false;
    }
    pile[counter-1][pileNum].ifClosed = false;
    return true;
}

bool Pile::movePile(int pileNum, int cardNum, int destinationNum) {
    int prevIndex = findCard(pileNum);
    int newIndex = findCard(destinationNum)-1;
    for(int index = cardNum; -1 < index; index--){
        newIndex++;
        int tempIndex = prevIndex - index;
        if (checkColm(pileNum) && checkColm(destinationNum)) {
            if (!pile[newIndex][destinationNum].ifClosed && !pile[tempIndex][pileNum].ifClosed) {
                if (checkMove(pile[tempIndex][pileNum].cardName, pile[newIndex][destinationNum].cardName)) {
                    addCard(pile[tempIndex][pileNum].cardName, destinationNum, newIndex + 1);
                    removeCard(pileNum, tempIndex);
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else if (checkColm(pileNum)) {
            if (pile[tempIndex][pileNum].ifExist) {
                if (pile[tempIndex][pileNum].cardName.substr(1, 2) == "13") {
                    addCard(pile[tempIndex][pileNum].cardName, destinationNum, newIndex + 1);
                    removeCard(pileNum, tempIndex);
                } else {
                    return false;
                }
            } else{
                return false;
            }
        } else{
            return false;
        }
    }
    return true;
}

bool Pile::moveToFoundation(int pileNum, Foundation* foundation) {
    if(checkColm(pileNum)) {
        int cardIndex = findCard(pileNum);
        if (!pile[cardIndex][pileNum].ifClosed){
            if (foundation->addCard(pile[cardIndex][pileNum].cardName)) {
                removeCard(pileNum, cardIndex);
            } else {
                return false;
            }
        } else {
            return false;
        }
    } else{
        return false;
    }
    return true;
}

bool Pile::moveFoundationToPile(int foundationNum, int pileNum, Foundation* foundation){
    int index = findCard(pileNum);
    if(!foundation->checkEmpty(foundationNum)){
        if(checkColm(pileNum)) {
            if (checkMove(foundation->foundationList[foundationNum], pile[pileNum][index].cardName)) {
                addCard(foundation->foundationList[foundationNum], pileNum, index+1);
                foundation->removeCard(foundationNum);
            }
            else{
                return false;
            }
        }
        else if(foundation->foundationList[foundationNum].substr(1,2) == "13"){
            addCard(foundation->foundationList[foundationNum], pileNum, 0);
            foundation->removeCard(foundationNum);
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
    return true;
}

void Pile::removeCard(int pileNum, int prevIndex) {
    pile[prevIndex][pileNum].cardName = "";
    pile[prevIndex][pileNum].ifExist = false;
    pile[prevIndex][pileNum].ifClosed = true;
}

void Pile::addCard(string cardName, int destination, int destinationIndex) {
    Card newCard;
    newCard.cardName = cardName;
    newCard.ifClosed = false;
    newCard.ifExist = true;
    *(*(pile+destinationIndex) + destination) = newCard;
}

int Pile::findCard(int pileNum) {
    int currentIndex = -1;
    for(int index=0; index < pileCards; index++){
        if(pile[index][pileNum].ifExist){
            currentIndex++;
        }
    }
    return currentIndex;
}

bool Pile::checkMove(string cardName, string matchedCard){
    if(stoi(cardName.substr(1, 2)) == stoi(matchedCard.substr(1, 2)) - 1) {
        if ((cardName.substr(0, 1) == "H" || cardName.substr(0, 1) == "D") &&
            (matchedCard.substr(0,1) == "C" || matchedCard.substr(0,1) == "S")) {
            if (stoi(cardName.substr(1, 2)) == stoi(matchedCard.substr(1, 2)) - 1) {
                return true;
            }
        } else if ((cardName.substr(0, 1).compare("C") == 0 || cardName.substr(0, 1).compare("S") == 0) &&
                   (matchedCard.substr(0,1).compare("D") == 0 || matchedCard.substr(0,1).compare("H") == 0)) {

            return true;

        }
        return false;
    }
    return false;
}

bool Pile::checkRow(int rowNum) {
    int counter = 0;
    for(int index = 0; index < piles; index++){
        if (pile[rowNum][index].cardName.empty()) {
            counter++;
        }
    }
    if(counter == piles){
        return false;
    }
    return true;
}

bool Pile::checkColm(int colNum) {
    int counter = 0;
    for(int index=0; index < pileCards; index++){
        if(pile[index][colNum].cardName.empty()){
            counter++;
        }
    }
    if(counter==pileCards){
        return false;
    }
    return true;
}

void Pile::printPile(ofstream* output) {
    for(int i=0; i < pileCards; i++){
        if(checkRow(i)) {
            for(int j = 0; j < 7; j++){
                if(pile[i][j].ifExist){
                    if(!pile[i][j].ifClosed) {
                        *output << pile[i][j].cardName + "   ";
                    }
                    else{
                        *output << "@@@   ";
                    }
                }
                else{
                   *output << "      ";
                }
            }
            *output << endl;
        }
    }
}