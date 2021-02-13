//
// Created by EMRE on 11/20/2020.
//

#ifndef ASSIGNMENT1_STOCK_H
#define ASSIGNMENT1_STOCK_H
#include "Pile.h"
#include <iostream>
using namespace std;

class StockCard {
    public:
        string cardName = "";
        bool ifExist = false;
};

class Stock {
    public:
        int stockSize;
        int subStockSize;
        int wasteSize;
        int moveNum;
        int initialWasteSize;
        int openedCards;
        StockCard stock[24];
        StockCard subStock[24];
        StockCard waste[3];
        void createStock(string* cards);
        bool openStock();
        void refreshStock();
        void restoreWaste();
        void removeCard();
        bool checkStock();
        bool checkAllOpened();
        void printStock(ofstream* output);
        bool moveWaste(int pileNum, Pile* pile);
        bool moveToFoundation(Foundation* foundation);
        void resetWaste();
        bool checkWaste();
        void printWaste(ofstream* output);
        void openPrevious();
        void removeWaste();
};


#endif //ASSIGNMENT1_STOCK_H
