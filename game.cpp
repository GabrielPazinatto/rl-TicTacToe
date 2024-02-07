#include "game.h"

void initTableSquares(TableSquare tableSquares[3][3])//initializes collisionArea element of TableSquares
{
    int i, j;
    Rectangle collisionRec;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {

            collisionRec.x = i * 100;
            collisionRec.y = j * 100 + 100;
            collisionRec.height = tableSquares[i][j].squareSize;
            collisionRec.width = tableSquares[i][j].squareSize;

            tableSquares[i][j].marked = false;     //makes every square unmarked
            tableSquares[i][j].owner = 0;          //makes it so that every square does not have an owner
            tableSquares[i][j].fixedColor = false; //makes it so that every square can change color

            tableSquares[i][j].collisionArea = collisionRec;
        }
    }
}


bool checkTableClick(Vector2* mousePos, TableSquare tableSquares[3][3], int playerTurn)//checks if a square has been clicked on
{
    int i, j;
    bool click = false;

    //for every square
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {

            //updates the mouse position rec
            mousePos->x = GetMousePosition().x;
            mousePos->y = GetMousePosition().y;

            if (CheckCollisionPointRec(*mousePos, tableSquares[i][j].collisionArea))//if mouse collides with a rectangle
            {
                if (IsMouseButtonPressed(0) && tableSquares[i][j].marked == false)//and left mouse button is pressed
                {
                    tableSquares[i][j].owner = playerTurn;//gives that square to the respective player
                    tableSquares[i][j].marked = true;//change the square's state to marked
                    click = true;
                }//returns true
            }
        }
    }
    return click;
}

void updatePlayerTurn(int* playerTurn)//once a move has been made, changes the player's turn
{
    if (*playerTurn == 1)
        *playerTurn = 2;
    else
        *playerTurn = 1;
}

bool checkWinner(TableSquare tableSquare[3][3])//checks every winning case
{
    int i, j;
    bool winner = false;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {

            //tests if all 3 squares of a row are owned by the same player
            if (tableSquare[i][0].owner == tableSquare[i][1].owner && tableSquare[i][2].owner == tableSquare[i][1].owner) {
                if (tableSquare[i][0].owner != 0) {//necessary test as all squares are initialized with owner element = 0 
                    //if tests are true, player won
                    //changes respective squares' color permanently
                    tableSquare[i][0].recColor = GREEN;
                    tableSquare[i][1].recColor = GREEN;
                    tableSquare[i][2].recColor = GREEN;
                    tableSquare[i][0].fixedColor = true;
                    tableSquare[i][1].fixedColor = true;
                    tableSquare[i][2].fixedColor = true;
                    winner = true;
                }
            }

            //tests if all 3 squares of a column are owned by the same player
            else if (tableSquare[0][i].owner == tableSquare[1][i].owner && tableSquare[2][i].owner == tableSquare[1][i].owner) {
                if (tableSquare[0][i].owner != 0) {
                    //if tests are true, player won
                    //changes respective squares' color permanently
                    winner = true;
                    tableSquare[0][i].recColor = GREEN;
                    tableSquare[1][i].recColor = GREEN;
                    tableSquare[2][i].recColor = GREEN;
                    tableSquare[0][i].fixedColor = true;
                    tableSquare[1][i].fixedColor = true;
                    tableSquare[2][i].fixedColor = true;
                }
            }
        }

        //tests if all squares of leading diagonal are owned by the same player
        if (tableSquare[0][0].owner == tableSquare[1][1].owner && tableSquare[2][2].owner == tableSquare[0][0].owner)
            if (tableSquare[0][0].owner != 0) {
                //if tests are true, player won
                //changes respective squares' color permanently
                winner = true;
                tableSquare[0][0].recColor = GREEN;
                tableSquare[1][1].recColor = GREEN;
                tableSquare[2][2].recColor = GREEN;
                tableSquare[0][0].fixedColor = true;
                tableSquare[1][1].fixedColor = true;
                tableSquare[2][2].fixedColor = true;
            }
        //tests if all squares of secondary diagonal are owned by the same player
        if (tableSquare[0][2].owner == tableSquare[1][1].owner && tableSquare[2][0].owner == tableSquare[0][2].owner)
            if (tableSquare[0][2].owner != 0) {
                //if tests are true, player won
                //changes respective squares' color permanently
                winner = true;
                tableSquare[0][2].recColor = GREEN;
                tableSquare[1][1].recColor = GREEN;
                tableSquare[2][0].recColor = GREEN;
                tableSquare[0][2].fixedColor = true;
                tableSquare[1][1].fixedColor = true;
                tableSquare[2][0].fixedColor = true;
            }
    }

    return winner;
}

int countCheckedSquares(TableSquare tableSquares[3][3])//for every square, counts how many are marked
{
    int i, j;
    int count = 0;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (tableSquares[i][j].marked == true)
                count++;
        }
    }

    return count;
}