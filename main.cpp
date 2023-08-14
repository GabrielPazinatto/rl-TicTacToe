#include <iostream>
#include <raylib.h>

using namespace std;

typedef struct{
    bool marked = false;     //if a player has already chosen the specific square
    int owner = 0;           //1 if first player owns it; 2 if the second player owns it;
    Vector2 pos;             //position of the square in the table
    float squareSize = 100;  //size of each individual square
    Rectangle collisionArea; //rectangle that will collide with mouse
}TableSquare;                //individual squares of the tictactoe table

void drawTableSquares(TableSquare tableSquares[3][3])//draws the table squares
{
    int i, j;
    float squareSize;
    Color recColor;

    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            
            if (CheckCollisionPointRec(GetMousePosition(), tableSquares[i][j].collisionArea))
                recColor = GREEN;
            else
                recColor = DARKGRAY;

            squareSize = tableSquares[i][j].squareSize;

            DrawRectangle(i*squareSize, j*squareSize + 100, squareSize, squareSize, recColor);

            if(tableSquares[i][j].owner == 1)
                DrawRing((Vector2) {i*squareSize+squareSize/2, j*squareSize+squareSize/2 + 100}, squareSize/4, squareSize/5, 0, 360, 0, BLACK);

            else if(tableSquares[i][j].owner == 2){
                DrawRectangle(i*squareSize + squareSize/4 ,j*squareSize+squareSize/4 + 100, squareSize/2, squareSize/2, BLACK);
                DrawRectangle(i*squareSize + squareSize/3.25, j*squareSize + squareSize/3.25 + 100, squareSize/2.5, squareSize/2.5, recColor);
            }
            DrawRectangleLines(i*squareSize, j*squareSize + 100, squareSize, squareSize, LIGHTGRAY);
        }
    }
}

void initTableSquares(TableSquare tableSquares[3][3])//initiallizes collisionArea element of TableSquares
{
    int i, j;
    Rectangle collisionRec;

    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            
            collisionRec.x = i*100;
            collisionRec.y = j*100 + 100;
            collisionRec.height = tableSquares[i][j].squareSize;
            collisionRec.width = tableSquares[i][j].squareSize;

            tableSquares[i][j].collisionArea = collisionRec;
        }
    }
}

bool checkTableClick(Vector2* mousePos, TableSquare tableSquares[3][3], int playerTurn){
    int i, j;
    bool click = false;

    for(i=0; i<3; i++){
        for(j=0; j<3; j++){

            mousePos->x = GetMousePosition().x;
            mousePos->y = GetMousePosition().y;

            if(CheckCollisionPointRec(*mousePos, tableSquares[i][j].collisionArea)){
                if(IsMouseButtonPressed(0) && tableSquares[i][j].marked == false){
                    tableSquares[i][j].owner = playerTurn;
                    tableSquares[i][j].marked = true;
                    click = true;}
            }
        }
    }
return click;}

void updatePlayerTurn(int* playerTurn){
    if (*playerTurn == 1)
        *playerTurn = 2;
    else
        *playerTurn = 1;
}

bool checkWinner(TableSquare tableSquare[3][3]){
    int i,j;
    bool winner = false;

    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            
            if(tableSquare[i][0].owner == tableSquare[i][1].owner && tableSquare[i][2].owner == tableSquare[i][1].owner){
                if(tableSquare[i][0].owner != 0)
                    winner = true;}

            else if(tableSquare[0][i].owner == tableSquare[1][i].owner && tableSquare[2][i].owner == tableSquare[1][i].owner){
                if(tableSquare[0][i].owner != 0)
                    winner = true;}
        }
        if(tableSquare[0][0].owner == tableSquare[1][1].owner && tableSquare[2][2].owner == tableSquare[0][0].owner)
            if(tableSquare[0][0].owner != 0)
                winner = true;
    }

return winner;}

int main () {

    const int screenWidth = 300;
    const int screenHeight = 400;

    TableSquare tableSquares[3][3];
    Vector2 mousePos;
    int playerTurn = 1;

    InitWindow(screenWidth, screenHeight, "TicTacToe");
    SetTargetFPS(60);

    initTableSquares(tableSquares);

    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);

        drawTableSquares(tableSquares);

        if(!checkWinner(tableSquares)){
            if(checkTableClick(&mousePos, tableSquares, playerTurn))
                updatePlayerTurn(&playerTurn);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}