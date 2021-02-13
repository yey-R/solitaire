#include "Board.h"

using namespace std;

int main(int argc, char *argv[]) {
   Board game;
   game.createGame(argv[1]);
   game.applyCommands(argv[2], argv[3]);
   return 0;
}
