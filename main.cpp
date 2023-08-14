#include <iostream>
#include <raylib.h>
#include <string.h>

#define screenWidth 300
#define screenHeight 400

using namespace std;

typedef struct{
    bool marked = false;     //if a player has already chosen the square
    int owner = 0;           //1 if first player owns it; 2 if the second player owns it; 0 by default
    Vector2 pos;             //position of the square in the table
    float squareSize = 100;  //size of each individual square
    Rectangle collisionArea; //rectangle that will collide with mouse
    Color recColor = DARKGRAY;
}TableSquare;                //individual squares of the tictactoe table

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

bool checkTableClick(Vector2* mousePos, TableSquare tableSquares[3][3], int playerTurn)//checks if a square has been clicked on
{
    int i, j;
    bool click = false;

    //for every square
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){

            //updates the mouse position rec
            mousePos->x = GetMousePosition().x;
            mousePos->y = GetMousePosition().y;

            if(CheckCollisionPointRec(*mousePos, tableSquares[i][j].collisionArea))//if mouse collides with a rectangle
            {
                if(IsMouseButtonPressed(0) && tableSquares[i][j].marked == false)//and left mouse button is pressed
                {
                    tableSquares[i][j].owner = playerTurn;//gives that square to the respective player
                    tableSquares[i][j].marked = true;//change the square's state to marked
                    click = true;}//returns true
            }
        }
    }
return click;}

void updatePlayerTurn(int* playerTurn)//once a move has been made, changes the player's turn
{
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
                if(tableSquare[i][0].owner != 0){
                    tableSquare[i][0].recColor = GREEN;
                    tableSquare[i][1].recColor = GREEN;
                    tableSquare[i][2].recColor = GREEN;
                    winner = true;}}

            else if(tableSquare[0][i].owner == tableSquare[1][i].owner && tableSquare[2][i].owner == tableSquare[1][i].owner){
                if(tableSquare[0][i].owner != 0){
                    winner = true;
                    tableSquare[0][i].recColor = GREEN;
                    tableSquare[1][i].recColor = GREEN;
                    tableSquare[2][i].recColor = GREEN;}}
        }

        if(tableSquare[0][0].owner == tableSquare[1][1].owner && tableSquare[2][2].owner == tableSquare[0][0].owner)
            if(tableSquare[0][0].owner != 0){
                winner = true;
                tableSquare[0][0].recColor = GREEN;
                tableSquare[1][1].recColor = GREEN;
                tableSquare[2][2].recColor = GREEN;
            }

        if(tableSquare[0][2].owner == tableSquare[1][1].owner && tableSquare[2][0].owner == tableSquare[0][2].owner)
            if(tableSquare[0][2].owner != 0){
                winner = true;
                tableSquare[0][2].recColor = GREEN;
                tableSquare[1][1].recColor = GREEN;
                tableSquare[2][0].recColor = GREEN;
            }
        
    }

return winner;}

void drawHeader(int playerTurn, bool thereIsWinner, int squaresChecked)
{
    if(squaresChecked == 9 && !thereIsWinner)
        DrawText("Tie!", (screenWidth - MeasureText("Tie!", 30))/2, 35, 30, RED);

    else if(!thereIsWinner){
        if(playerTurn == 1)
            DrawText("Player 1's turn.", (screenWidth - MeasureText("Player 1's turn.", 30))/2, 35, 30, WHITE);
        else
            DrawText("Player 2's turn.", (screenWidth - MeasureText("Player 1's turn.", 30))/2, 35, 30, WHITE);}

    else if (thereIsWinner){
        if(playerTurn == 2)
            DrawText("Player 1 won!", (screenWidth - MeasureText("Player 1 won!", 30))/2, 35, 30, YELLOW);
        else if(playerTurn == 1)
            DrawText("Player 2 won!", (screenWidth - MeasureText("Player 2 won!", 30))/2, 35, 30, YELLOW);
    }

    DrawText("Press SPACE to reset.", (screenWidth - MeasureText("Press SPACE to reset", 10))/2, 90, 10, WHITE);

}

void drawTableSquares(TableSquare tableSquares[3][3])//draws the table squares
{
    int i, j;
    float squareSize;
    Color recColor;

    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            
            if (CheckCollisionPointRec(GetMousePosition(), tableSquares[i][j].collisionArea) && !checkWinner(tableSquares))
                tableSquares[i][j].recColor = GREEN;
            else if (!checkWinner (tableSquares))
                tableSquares[i][j].recColor = DARKGRAY;

            recColor = tableSquares[i][j].recColor;
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

int main () {
    TableSquare tableSquares[3][3];
    Vector2 mousePos;
    int playerTurn = 1;
    int squaresChecked = 0;
    int i, j;

    InitWindow(screenWidth, screenHeight, "TicTacToe");
    SetTargetFPS(60);

    initTableSquares(tableSquares);

    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);

        drawHeader(playerTurn, checkWinner(tableSquares), squaresChecked);
        drawTableSquares(tableSquares);

        if(!checkWinner(tableSquares)){
            if(checkTableClick(&mousePos, tableSquares, playerTurn)){
                updatePlayerTurn(&playerTurn);
                squaresChecked++;}
        }

        if(IsKeyPressed(KEY_SPACE)){
            for(i=0; i<3; i++){
                for(j=0; j<3; j++){
                    tableSquares[i][j].marked = false;
                    tableSquares[i][j].owner = 0;
                    squaresChecked = 0;
                    playerTurn = 1;
                 }
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}