#include "drawGame.h"
#include "raylib.h"

#define screenWidth 300
#define screenHeight 400

void drawHeader(int playerTurn, bool thereIsWinner, int squaresChecked, bool illegalMove)//draws some text above the table, depending on the situation of the game
{

    if (!illegalMove) {//if an illegal move hasn't been made, proceeds normally
        if (squaresChecked == 9 && !thereIsWinner)
            DrawText("Tie!", (screenWidth - MeasureText("Tie!", 30)) / 2, 35, 30, RED); // if nobody won, displays "Tie!"

        else if (!thereIsWinner) {//if there is not a winner
            if (playerTurn == 1)
                //and it's player 1's turn, displays it
                DrawText("Player 1's turn.", (screenWidth - MeasureText("Player 1's turn.", 30)) / 2, 35, 30, WHITE);
            else
                //same for player 2
                DrawText("Player 2's turn.", (screenWidth - MeasureText("Player 1's turn.", 30)) / 2, 35, 30, WHITE);
        }

        else if (thereIsWinner) {//if there is a winner
            if (playerTurn == 2)//and it's player 2's turn
                //player 1 won in his last turn
                DrawText("Player 1 won!", (screenWidth - MeasureText("Player 1 won!", 30)) / 2, 35, 30, YELLOW);
            else if (playerTurn == 1)//same for player 2
                DrawText("Player 2 won!", (screenWidth - MeasureText("Player 2 won!", 30)) / 2, 35, 30, YELLOW);
        }
    }
    else// in case of an illegal move, displays this message
        DrawText("ILLEGAL MOVE!", (screenWidth - MeasureText("ILLEGAL MOVE!", 30)) / 2, 35, 30, RED);

    DrawText("Press SPACE to reset.", (screenWidth - MeasureText("Press SPACE to reset", 10)) / 2, 90, 10, WHITE);

}

void drawTableSquares(TableSquare tableSquares[3][3])//draws the table squares
{
    int i, j;
    float squareSize;
    Color recColor;

    //draws 9 squares
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {

            //if mouse is hovering the squares changes it's color to green
            if (CheckCollisionPointRec(GetMousePosition(), tableSquares[i][j].collisionArea))
                tableSquares[i][j].recColor = GREEN;
            //if mouse is NOT hovering the square and the square's color is not fixed, resets it to dark gray
            else if (tableSquares[i][j].fixedColor == false)
                tableSquares[i][j].recColor = DARKGRAY;

            recColor = tableSquares[i][j].recColor;
            squareSize = tableSquares[i][j].squareSize;

            //draws each square with it's respective position size and color
            DrawRectangle(i * squareSize, j * squareSize + 100, squareSize, squareSize, recColor);

            //if player 1 owns the square, draws a square above it
            if (tableSquares[i][j].owner == 1)
                DrawRing({ i * squareSize + squareSize / 2, j * squareSize + squareSize / 2 + 100 }, squareSize / 4, squareSize / 5, 0, 360, 0, BLACK);

            //if player 2 owns the square, draws a ring above it
            else if (tableSquares[i][j].owner == 2) {
                DrawRectangle(i * squareSize + squareSize / 4, j * squareSize + squareSize / 4 + 100, squareSize / 2, squareSize / 2, BLACK);
                DrawRectangle(i * squareSize + squareSize / 3.25, j * squareSize + squareSize / 3.25 + 100, squareSize / 2.5, squareSize / 2.5, recColor);
            }
            DrawRectangleLines(i * squareSize, j * squareSize + 100, squareSize, squareSize, LIGHTGRAY);
        }
    }
}