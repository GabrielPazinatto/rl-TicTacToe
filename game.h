#pragma once
#include <raylib.h>

class TableSquare {
public:
    bool marked = false;     //if a player has already chosen the square
    int owner = 0;           //1 if first player owns it; 2 if the second player owns it; 0 by default
    Vector2 pos;             //position of the square in the table
    float squareSize = 100;  //size of each individual square
    Rectangle collisionArea; //rectangle that will collide with mouse
    Color recColor = DARKGRAY;//the color of the square
    bool fixedColor = false;  //if the square can't change colors
};                             //individual squares of the tic tac toe table



void initTableSquares(TableSquare tableSquares[3][3]);//initializes collisionArea element of TableSquares
bool checkTableClick(Vector2* mousePos, TableSquare tableSquares[3][3], int playerTurn);//checks if a square has been clicked on
void updatePlayerTurn(int* playerTurn);
bool checkWinner(TableSquare tableSquare[3][3]);
int countCheckedSquares(TableSquare tableSquares[3][3]);//for every square, counts how many are marked
