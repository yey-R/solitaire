#ifndef ASSIGNMENT1_PILE_H
#define ASSIGNMENT1_PILE_H

#include <iostream>
#include "Foundation.h"
#include "FileOperation.h"

using namespace std;

class Card {
    public:
        string cardName = "";
        bool ifExist = false;
        bool ifClosed = true;
};

class Pile{
    public:
        const int piles = 7;
        const int pileCards = 19;
        string cards[52];
        Card pile[19][7];
        Card *(*(pPile));
        void createPile(string deckFile);
        bool movePile(int pileNum, int cardNum, int newPileNum);
        bool openPile(int pileNum);
        bool moveToFoundation(int pileNum, Foundation* foundation);
        bool moveFoundationToPile(int foundationNum, int pileNum, Foundation *foundation);
        void printPile(ofstream* output);
        void addCard(string newCard, int destination, int destinationIndex);
        void removeCard(int pileNum, int cardNum);
        int findCard(int pileNum);
        bool checkMove(string cardName, string matchedCard);
        bool checkRow(int rowNum);
        bool checkColm(int colNum);
};
#endif //ASSIGNMENT1_PILE_H
