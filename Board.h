#ifndef ASSIGNMENT1_BOARD_H
#define ASSIGNMENT1_BOARD_H

#include "Foundation.h"
#include "Stock.h"
#include "Tableau.h"

class Board {
    public:
        Tableau tableau;
        Stock stock;
        Foundation foundation;
        void createGame(string deckFile);
        void applyCommands(string commandFile, string outputFile);
        void printBoard(ofstream* output);
};


#endif //ASSIGNMENT1_BOARD_H
