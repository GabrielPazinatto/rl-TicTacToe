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
    Color recColor = DARKGRAY;//the color of the square
    bool fixedColor = false;  //if the square can't change colors
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

bool checkWinner(TableSquare tableSquare[3][3])//checks every winning case
{
    int i,j;
    bool winner = false;

    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            
            //tests if all 3 squares of a row are owned by the same player
            if(tableSquare[i][0].owner == tableSquare[i][1].owner && tableSquare[i][2].owner == tableSquare[i][1].owner){
                if(tableSquare[i][0].owner != 0){//necessary test as all squares are initialized with owner element = 0 
                    //if tests are true, player won
                    //changes respective squares' color permanently
                    tableSquare[i][0].recColor = GREEN;
                    tableSquare[i][1].recColor = GREEN;
                    tableSquare[i][2].recColor = GREEN;
                    tableSquare[i][0].fixedColor= true;
                    tableSquare[i][1].fixedColor= true;
                    tableSquare[i][2].fixedColor= true;
                    winner = true;}}

            //tests if all 3 squares of a collumn are owned by the same player
            else if(tableSquare[0][i].owner == tableSquare[1][i].owner && tableSquare[2][i].owner == tableSquare[1][i].owner){
                if(tableSquare[0][i].owner != 0){
                    //if tests are true, player won
                    //changes respective squares' color permanently
                    winner = true;
                    tableSquare[0][i].recColor = GREEN;
                    tableSquare[1][i].recColor = GREEN;
                    tableSquare[2][i].recColor = GREEN;
                    tableSquare[0][i].fixedColor= true;
                    tableSquare[1][i].fixedColor= true;
                    tableSquare[2][i].fixedColor= true;}}
        }

        //tests if all squares of leading diagonal are owned by the same player
        if(tableSquare[0][0].owner == tableSquare[1][1].owner && tableSquare[2][2].owner == tableSquare[0][0].owner)
            if(tableSquare[0][0].owner != 0){
                //if tests are true, player won
                //changes respective squares' color permanently
                winner = true;
                tableSquare[0][0].recColor = GREEN;
                tableSquare[1][1].recColor = GREEN;
                tableSquare[2][2].recColor = GREEN;
                tableSquare[0][0].fixedColor= true;
                tableSquare[1][1].fixedColor= true;
                tableSquare[2][2].fixedColor= true;
            }
        //tests if all squares of secondary diagonal are owned by the same player
        if(tableSquare[0][2].owner == tableSquare[1][1].owner && tableSquare[2][0].owner == tableSquare[0][2].owner)
            if(tableSquare[0][2].owner != 0){
                //if tests are true, player won
                //changes respective squares' color permanently
                winner = true;
                tableSquare[0][2].recColor = GREEN;
                tableSquare[1][1].recColor = GREEN;
                tableSquare[2][0].recColor = GREEN;
                tableSquare[0][2].fixedColor= true;
                tableSquare[1][1].fixedColor= true;
                tableSquare[2][0].fixedColor= true;
            }
    }

return winner;}

void drawHeader(int playerTurn, bool thereIsWinner, int squaresChecked, bool illegalMove)//draws some text above the table, depending on the situation of the game
{

    if(!illegalMove){//if an illegal move hasn't been made, proceeds normally
        if(squaresChecked == 9 && !thereIsWinner)
            DrawText("Tie!", (screenWidth - MeasureText("Tie!", 30))/2, 35, 30, RED); // if nobody won, displays "Tie!"

        else if(!thereIsWinner){//if there is not a winner
            if(playerTurn == 1)
                //and it's player 1's turn, displays it
                DrawText("Player 1's turn.", (screenWidth - MeasureText("Player 1's turn.", 30))/2, 35, 30, WHITE);
            else
                //same for player 2
                DrawText("Player 2's turn.", (screenWidth - MeasureText("Player 1's turn.", 30))/2, 35, 30, WHITE);}

        else if (thereIsWinner){//if there is a winner
            if(playerTurn == 2)//and it's player 2's turn
                //player 1 won in his last turn
                DrawText("Player 1 won!", (screenWidth - MeasureText("Player 1 won!", 30))/2, 35, 30, YELLOW);
            else if(playerTurn == 1)//same for player 2
                DrawText("Player 2 won!", (screenWidth - MeasureText("Player 2 won!", 30))/2, 35, 30, YELLOW);
        }
    }
    else// in case of an illegal move, displays this message
        DrawText("ILLEGAL MOVE!", (screenWidth - MeasureText("ILLEGAL MOVE!", 30))/2, 35, 30, RED);

    DrawText("Press SPACE to reset.", (screenWidth - MeasureText("Press SPACE to reset", 10))/2, 90, 10, WHITE);

}

void drawTableSquares(TableSquare tableSquares[3][3])//draws the table squares
{
    int i, j;
    float squareSize;
    Color recColor;

    //draws 9 squares
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            
            //if mouse is hovering the squares changes it's color to green
            if (CheckCollisionPointRec(GetMousePosition(), tableSquares[i][j].collisionArea))
                tableSquares[i][j].recColor = GREEN;
            //if mouse is NOT hovering the square and the square's color is not fixed, resets it to dark gray
            else if(tableSquares[i][j].fixedColor == false)
                tableSquares[i][j].recColor = DARKGRAY;

            recColor = tableSquares[i][j].recColor;
            squareSize = tableSquares[i][j].squareSize;

            //draws each square with it's respective position size and color
            DrawRectangle(i*squareSize, j*squareSize + 100, squareSize, squareSize, recColor);
            
            //if player 1 owns the square, draws a square above it
            if(tableSquares[i][j].owner == 1)
                DrawRing((Vector2) {i*squareSize+squareSize/2, j*squareSize+squareSize/2 + 100}, squareSize/4, squareSize/5, 0, 360, 0, BLACK);
            
            //if player 2 owns the square, draws a ring above it
            else if(tableSquares[i][j].owner == 2){
                DrawRectangle(i*squareSize + squareSize/4 ,j*squareSize+squareSize/4 + 100, squareSize/2, squareSize/2, BLACK);
                DrawRectangle(i*squareSize + squareSize/3.25, j*squareSize + squareSize/3.25 + 100, squareSize/2.5, squareSize/2.5, recColor);
            }
            DrawRectangleLines(i*squareSize, j*squareSize + 100, squareSize, squareSize, LIGHTGRAY);
        }
    }
}

int countCheckedSquares(TableSquare tableSquares[3][3])//for every square, counts how many are marked
{
    int i, j;
    int count = 0;
    
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            if(tableSquares[i][j].marked == true)
                count++;
        }
    }

return count;}

int main () {
    TableSquare tableSquares[3][3]; 
    Vector2 mousePos;
    int playerTurn = 1;
    int squaresChecked;
    int turns = 0;
    bool illegalMove = false;

    InitWindow(screenWidth, screenHeight, "TicTacToe");
    SetTargetFPS(60);

    initTableSquares(tableSquares); //creates collision recs for each square of the table

    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);

        squaresChecked = countCheckedSquares(tableSquares);//updates the amount of checked squares

        if(turns != squaresChecked)//if the number of turns differs from the number of checked squares, it means that more than 1 square has been clicked at once
            illegalMove = true;//so it's an illegal move

        drawHeader(playerTurn, checkWinner(tableSquares), squaresChecked, illegalMove);//draws text on top of the table
        drawTableSquares(tableSquares);//draws the table

        //if an illegal move has been made, does not proceed with the game
        if(!illegalMove){
            if(!checkWinner(tableSquares) && checkTableClick(&mousePos, tableSquares, playerTurn)){//if nobody won the game yet AND a click occurred on the table
                    updatePlayerTurn(&playerTurn);//changes the player turn
                    turns++;}//increments the turns count
        }

        //if SPACE is pressed, the game is reset
        if(IsKeyPressed(KEY_SPACE)){
            initTableSquares(tableSquares);
            illegalMove = false;
            turns = 0;
            playerTurn = 1;
            squaresChecked = 0;}
        
        printf("\n%d %d", squaresChecked, turns);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}