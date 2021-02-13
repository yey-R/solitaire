#include "Board.h"

void Board::createGame(string deckFile){
    tableau.createTableau(deckFile);
    foundation.createFoundation();
    stock.createStock(tableau.pile.cards);
}

void Board::applyCommands(string commandFile, string outputFile){
    ofstream output;
    output.open (outputFile);
    ifstream file(commandFile);
    string str;
    printBoard(&output);
    while (getline(file, str)){
        output << endl;
        output << str << endl;
        if(str == "exit"){
            output << endl << "****************************************" << endl << endl << "Game Over!" << endl;
            exit(0);
        }
        else if(str.substr(0,4)==("open")){
            if(str=="open from stock"){
                if(!stock.openStock()){
                    output << endl << "Invalid Move!" << endl;
                }
            }
            else{
                if(!tableau.pile.openPile(atoi(str.substr(5,1).c_str()))){
                    output << endl << "Invalid Move!" << endl;
                }
            }
        }
        else if(str.substr(0,7) == "move to"){
            if(str.substr(19,5) == "waste"){
                if(!stock.moveToFoundation(&foundation)){
                    output << endl << "Invalid Move!" << endl;
                }
            }
            else{
                if(!tableau.pile.moveToFoundation(atoi(str.substr(24,1).c_str()), &foundation)){
                    output << endl << "Invalid Move!" << endl;
                }
            }
        }
        else if(str.length()<=16 && (str.substr(0,9)=="move pile")){
            if(str.length()<16){
                if(!tableau.pile.movePile(atoi(str.substr(10,1).c_str()),
                                      atoi(str.substr(12,1).c_str()), atoi(str.substr(14,1).c_str()))){
                    output << endl << "Invalid Move!" << endl;
                }
            }
            else{
                if(!tableau.pile.movePile(atoi(str.substr(10,1).c_str()),
                                      atoi(str.substr(12,2).c_str()), atoi(str.substr(15,1).c_str()))){
                    output << endl <<"Invalid Move!" << endl;
                }
            }
        }
        else if(str.length()<13 && str.substr(0,10)=="move waste"){
            if(!stock.moveWaste(atoi(str.substr(11,1).c_str()) ,&tableau.pile)){
                output << endl << "Invalid Move!" << endl;
            }
        }
        else if (str.length()>15 && str.substr(0,15)=="move foundation"){
            if(!tableau.pile.moveFoundationToPile(atoi(str.substr(16,1).c_str()), atoi(str.substr(18,1).c_str()), &foundation)){
                output << endl << "Invalid Move!"  << endl;
            }
        }
        output << endl << "****************************************" << endl << endl;
        printBoard(&output);
    }
    if(foundation.checkWin()){
        output << endl << endl << "****************************************" << endl << endl;
        output << "You Win!" << endl << endl << "Game Over!" << endl;
    }
    file.close();
    output.close();
}

void Board::printBoard(ofstream* output){
    stock.printStock(output);
    stock.printWaste(output);
    *output << "        ";
    foundation.printFoundation(output);
    *output << endl;
    tableau.pile.printPile(output);
}

