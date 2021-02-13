#include "Stock.h"
#include <iostream>

using namespace std;

void Stock::createStock(string* card) {
    stockSize =0;
    subStockSize = 0;
    wasteSize = 0;
    for(int index=0; index < 24; index++){
        stock[index].cardName = card[23-index];
        stock[index].ifExist = true;
        stockSize++;
    }
}

bool Stock::openStock() {
    if(!checkWaste()){
        restoreWaste();
    }
    if(!checkAllOpened()){
        if(!checkStock()){
            moveNum = 0;
            if(stockSize >= 3){
                for(int index=0; index < 3; index++){
                    waste[index] = stock[0];
                    wasteSize++;
                    removeCard();
                }
            }
            else {
                for(int index=0; index<stockSize; index++){
                    waste[index] = stock[index];
                    wasteSize++;
                }
                stockSize = 0;
            }
            initialWasteSize = wasteSize;
        } else{
            return false;
        }
    }
    else{
        refreshStock();
        resetWaste();
    }
    return true;
}

void Stock::removeCard() {
    for(int index=0; index<stockSize-1; index++){
        stock[index] = stock[index+1];
    }
    stockSize--;
    stock[stockSize].cardName = "";
    stock[stockSize].ifExist = false;
}

void Stock::restoreWaste() {
    for(int index=0; index<3; index++){
        if(waste[index].ifExist){
            subStock[subStockSize] = waste[index];
            waste[index].ifExist = false;
            waste[index].cardName = "";
            subStockSize++;
        }
    }
    wasteSize =0;
}

void Stock::refreshStock() {
    stockSize = subStockSize;
    for(int index=0; index<24; index++){
        stock[index] = subStock[index];
        subStock[index].cardName = "";
        subStock[index].ifExist = false;
    }
    subStockSize = 0;
}

bool Stock::checkStock() {
    if(stockSize == 0 && subStockSize == 0) {
        return true;
    }
    return false;
}

bool Stock::checkAllOpened() {
    if(stockSize==0 && subStockSize != 0){
        return true;
    }
    return false;
}

void Stock::openPrevious(){
    if(subStockSize != 0){
        subStockSize--;
        waste[0] = subStock[subStockSize];
        subStock[subStockSize].ifExist = false;
        subStock[subStockSize].cardName = "";
        wasteSize++;
    }
}

void Stock::printStock(ofstream* output) {
    if(checkAllOpened() || checkStock()) {
        *output << "___" << " ";
    }
    else{
        *output << "@@@" << " ";
    }
}

bool Stock::moveWaste(int pileNum, Pile* pile) {
    int matchedCardIndex = pile->findCard(pileNum);
    if(!checkWaste()) {
        if(pile->checkColm(pileNum)) {
            if (!pile->pile[matchedCardIndex][pileNum].ifClosed && pile->pile[matchedCardIndex][pileNum].ifExist) {
                if (pile->checkMove(waste[wasteSize-1].cardName, pile->pile[matchedCardIndex][pileNum].cardName)) {
                    pile->addCard(waste[wasteSize-1].cardName, pileNum, matchedCardIndex + 1);
                    removeWaste();
                    return true;
                }
            }
        } else{
            if(waste[wasteSize-1].cardName.substr(1,2) == "13"){
                pile->addCard(waste[wasteSize-1].cardName, pileNum, matchedCardIndex + 1);
                removeWaste();
                return true;
            }
        }
    }
    return false;
}

void Stock::removeWaste(){
    wasteSize--;
    waste[wasteSize].cardName = "";
    waste[wasteSize].ifExist = false;
    moveNum++;
    if(moveNum >= initialWasteSize){
        openPrevious();
    }
}

bool Stock::moveToFoundation(Foundation* foundation) {
    if(foundation->addCard(waste[wasteSize-1].cardName)){
        removeWaste();
        return true;
    }
    return false;
}

void Stock::resetWaste() {
    for(int index=0; index<3; index++){
        waste[index].ifExist = false;
        waste[index].cardName = "";
    }
}

bool Stock::checkWaste() {
    return wasteSize==0;
}

void Stock::printWaste(ofstream* output) {
    for(int index=0; index<3; index++){
        if(waste[index].ifExist){
            *output << waste[index].cardName << " ";
        }
        else{
            *output << "___ ";
        }
    }
}