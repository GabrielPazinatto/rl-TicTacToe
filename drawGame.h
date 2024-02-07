#pragma once

#include "game.h"

void drawHeader(int playerTurn, bool thereIsWinner, int squaresChecked, bool illegalMove);//draws some text above the table, depending on the situation of the game
void drawTableSquares(TableSquare tableSquares[3][3]);//draws the table squares