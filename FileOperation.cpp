#include <iostream>
#include <fstream>
#include "FileOperation.h"

using namespace std;

string* FileOperation::file(string fileName,string array[]) {
    string line;
    ifstream inFile;
    inFile.open(fileName);
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    int index = 0;
    while (inFile >> line) {
        array[index]= line;
        index++;
        }
    inFile.close();

    return array;
}
