/** @file RushHour.cpp
* @mainpage Rush Hour
* @author Saharath Kleips
* @version 1.00
* @brief The goal of Rush Hour is to unstick a car from a traffic game. The
* puzzle involves a 6x6 grid of squares. Vehicles are scattered over the grid
* at integer locations. The goal is to move your car out of the 6x6 grid and
* escape the traffic jam.
* @details Vehicles are always 1 square wide, but cars are always 2 squares long
* and trucks are 3 squares long. Vehicles are orientated either horizontally or
* vectically relative to the grid. Vehicles cannot move through each other, 
* cannot turn, and cannot move off the edge of the grid. They may move forwards 
* and backwards with respect to their orientation only if they are not blocked 
* by another vehicle. Only one vehicle may move at a time and may only move one
* square at a time. Move vehicles until your car arrives at the rightmost edge 
* of the grid, where it has escaped the traffic jam.
* \n\n This program will solve any solvable Rush Hour puzzle and output the
* minimum possible number of (1 square at a time) moves.
* @todo Implement multiple puzzles per program execution.
*/

//
// HEADER FILES ////////////////////////////////////////////////////////////////
//
#include <stdlib.h>
#include <iostream>
using namespace std;

//
// GLOBAL VARIABLES ////////////////////////////////////////////////////////////
//
/** Debug console output and function tracing. */
const bool _DEBUG_ = false;
/** Extended console output for puzzle diagram, moves used, etc. */
const bool _FULL_OUTPUT_ = false;
/** The lowest possible number of moves to solve the puzzle. */
int minSolution = 10;
/** The total amount of vehicles in this instnace of the puzzle. */
int totalVehicles = 0;

//
// FOWARD DECLARATIONS /////////////////////////////////////////////////////////
//
struct vehicle
{
    char id;
    int x;
    int y;
    char orientation;
    int length;
};

bool loadPuzzle(vehicle [6][6]);
bool canForward(vehicle [6][6], vehicle);
bool canBackward(vehicle [6][6], vehicle);
bool moveForward(vehicle [6][6], vehicle);
bool moveBackward(vehicle [6][6], vehicle);
void bruteForce(vehicle [6][6], int);
bool isSolved(vehicle [6][6]);
void printGrid(vehicle [6][6]);

//
// FUNCTION IMPLEMENTATIONS ////////////////////////////////////////////////////
//
/** Main function that controls user input, console output, and program loops.
*/
int main()
{
    /** The 2D array of characters that represents the puzzle state. */
    vehicle grid[6][6];
    for(int x = 0; x < 6; x++)
        for(int y = 0; y < 6; y++)
        {
            grid[x][y].id = '-';
            grid[x][y].x = x;
            grid[x][y].y = y;
            grid[x][y].orientation = '-';
            grid[x][y].length = 0;
        }

    loadPuzzle(grid);
    if(_FULL_OUTPUT_ || _DEBUG_)
        printGrid(grid);

    bruteForce(grid, 0);

    cout << "Scenario 1 requires " << minSolution << " moves";
}

/** Loads grid with a Rush Hour puzzle scenario from the console.
* The first integer indicates the number of vehicles (n) in the scenario between
* 0 <= n <= 10. The next n lines represent 1 vehicle where each line consists
* of a space separated list. Each list contains a number (2 or 3) indicating
* length, a letter (H or V) indicating orientation, and a row number (0-5) of
* the up most square if orientated vertically or the column number (0-5) of the
* left most square if orientated horizontally. The first vehicle is treated as
* the escape vehicle and must be orientated horizontally.
* @pre The grid to be loaded must be empty.
* @post grid is solvable and meets the criteria of the above description.
* @param grid is the grid the Rush Hour scenario will be loaded into.
* @return True if a puzzle has been loaded, False if there is no puzzle.
*/
bool loadPuzzle(vehicle grid[6][6])
{
    if(_FULL_OUTPUT_)
        cout << "Please enter the number of vehicles: ";
    /** The number of vehicles in the puzzle. */
    int n = 0;
    cin >> n;
    totalVehicles = n;
    if (n > 0)
    {
        for(int i = 0; i < n; i++)
        {
            /** The length of the vehicle. */
            int cLen = 0;
            /** The orientation of the vehicle. */
            char cOrien = '-';
            /** The starting row of the vehicle. */
            int cRow = 0;
            /** The starting column of the vehicle. */
            int cCol = 0;
            char tmp;

            if(_FULL_OUTPUT_)
                cout << "Please enter a space separated list of the " << 
            "vehicle length(2/3), orientation(H/V), row(0-6), and column(0-6).";
            cin >> cLen;
            //cin >> tmp; //Grabs space
            cin >> cOrien;
            toupper(cOrien);
            cin >> cRow;
            cin >> cCol;

            if(_DEBUG_)
            {
                cout << "n:" << n << ',';
                cout << "cLen:" << cLen << ',';
                cout << "cOrien:" << cOrien << ',';
                cout << "cRow:" << cRow << ',';
                cout << "cCol:" << cCol << endl;
            }

            //Inserts the vehicle depending on orientation
            switch (cOrien)
            {
                case 'H':
                    for(int j = 0; j < cLen; j++)
                    {
                        grid[cRow][cCol + j].id = '0' + i;
                        grid[cRow][cCol + j].orientation = cOrien;
                        grid[cRow][cCol + j].length = cLen;
                    }
                    break;
                case 'V':
                    for(int j = 0; j < cLen; j++)
                    {
                        grid[cRow + j][cCol].id = '0' + i;
                        grid[cRow + j][cCol].orientation = cOrien;
                        grid[cRow + j][cCol].length = cLen;
                    }
                    break;
                default:
                    grid[cRow][cCol].id = '=';
                    break;
            }
        }
        return true;
    }
    else
        return false;
}

/** Determines whether a vehicle can move forwards.
* It can move forwards so long as it is not at the edge of the grid and there
* are no other vehicles blocking it.
* @pre The vehicle is the left most piece for horizontal and top most piece
* for vertical.
* @param grid is the current state of the grid to check.
* @param aVehicle is the character representation of the vehicle in the grid.
* @return True if the vehicle can move backwards, Flase if the vehicle cannot.
*/
bool canForward(vehicle grid[6][6], vehicle aVehicle)
{
    int row;
    int col;
    if(aVehicle.orientation == 'H')
    {
        row = aVehicle.x;
        col = aVehicle.y;

        //Vehicle is at the edge or another vehicle is blocking
        if(col + aVehicle.length > 5 || 
            grid[row][col + aVehicle.length].id != '-')
            return false;
        else
            return true;
    }
    else if (aVehicle.orientation == 'V')
    {
        row = aVehicle.x;
        col = aVehicle.y;

        //Vehicle is at the edge or another vehicle is blocking
        if(row + aVehicle.length > 5 || 
            grid[row + aVehicle.length][col].id != '-')
            return false;
        else
            return true;
    }
}

/** Determines whether a vehicle can move backwards.
* It can move backwards so long as it is not at the edge of the grid and there
* are no other vehicles blocking it.
* @pre The vehicle is the left most piece for horizontal and top most piece
* for vertical.
* @param grid is the current state of the grid to check.
* @param aVehicle is the character representation of the vehicle in the grid.
* @return True if the vehicle can move backwards, Flase if the vehicle cannot.
*/
bool canBackward(vehicle grid[6][6], vehicle aVehicle)
{
    int row;
    int col;
    if(aVehicle.orientation == 'H')
    {
        row = aVehicle.x;
        col = aVehicle.y + aVehicle.length - 1;

        //Vehicle is at the edge or another vehicle is blocking
        if(col - aVehicle.length < 0 || 
            grid[row][col - aVehicle.length].id != '-')
            return false;
        else
            return true;
    }
    else if (aVehicle.orientation == 'V')
    {
        row = aVehicle.x + aVehicle.length - 1;
        col = aVehicle.y;

        //Vehicle is at the edge or another vehicle is blocking
        if(row - aVehicle.length < 0 ||
            grid[row - aVehicle.length][col].id != '-')
            return false;
    }
}

/** Attempts to move the vehicle forward.
* If there is nothing blocking the vehicle, then it will move one space forward.
* If there is something blocking the vehicle, then it will stay still. Moving
* right for horizontal vehicles and moving down for vertical vehicles is
* considered to be moving forward.
* @pre The vehicle is the left most piece for horizontal and top most piece
* for vertical.
* @post The grid will be updated with the new vehicle position.
* @param grid is the grid that will be updated with the new vehicle 
* position.
* @param aVehicle is the character representation of the vehicle in the grid.
* @return True if the vehicle moves, Flase if the vehicle stays still.
*/
bool moveForward(vehicle grid[6][6], vehicle aVehicle)
{
    /** Placeholder variable for readability. */
    int row;
    /** Placeholder variable for readability. */
    int col;
    if(aVehicle.orientation == 'H')
    {
        if(_DEBUG_)
            cout << "Move Horizontal Forward" << endl;
        //Sets the checking piece of the vehicle to the left most piece
        //This is for readability of code
        row = aVehicle.x;
        col = aVehicle.y;

        //Vehicle is at the edge or another vehicle is blocking
        if(!canForward(grid, aVehicle))
            return false;

        if(_DEBUG_)
            cout << "No Collision" << endl;
        //We can swap places and make the 'rear' the new 'head' to 'move foward'
        grid[row][col + aVehicle.length].id = aVehicle.id;
        grid[row][col + aVehicle.length].orientation =
            aVehicle.orientation;
        grid[row][col + aVehicle.length].length = 
            aVehicle.length;

        grid[row][col].id = '-';
        grid[row][col].orientation = '-';
        grid[row][col].length = 0;
        return true;
    }
    else if(aVehicle.orientation == 'V')
    {
        if(_DEBUG_)
            cout << "Move Veritcal Forward" << endl;
        //Sets the checking piece of the vehicle to the left most piece
        //This is for readability of code
        row = aVehicle.x;
        col = aVehicle.y;

        //Vehicle is at the edge or another vehicle is blocking
        if(!canForward(grid, aVehicle))
            return false;

        if(_DEBUG_)
            cout << "No Collision" << endl;
        //We can swap places and make the 'rear' the new 'head' to 'move foward'
        grid[row + aVehicle.length][col].id = aVehicle.id;
        grid[row + aVehicle.length][col].orientation =
            aVehicle.orientation;
        grid[row + aVehicle.length][col].length = 
            aVehicle.length;

        grid[row][col].id = '-';
        grid[row][col].orientation = '-';
        grid[row][col].length = 0;
        return true;
    }
    else
        return false;
}

/** Attempts to move the vehicle backward.
* If there is nothing blocking the vehicle, then it will move one space backward.
* If there is something blocking the vehicle, then it will stay still. Moving
* left for horizontal vehicles and moving up for vertical vehicles is
* considered to be moving backwards.
* @pre The vehicle is the left most piece for horizontal and top most piece
* for vertical.
* @post The grid will be updated with the new vehicle position.
* @param grid is the grid that will be updated with the new vehicle 
* position.
* @param aVehicle is the character representation of the vehicle in the grid.
* @return True if the vehicle moves, False if the vehicle stays still.
*/
bool moveBackward(vehicle grid[6][6], vehicle aVehicle)
{
    /** The row of the piece to check against. */
    int row;
    /** The column of the piece to check against. */
    int col;
    if(aVehicle.orientation == 'H')
    {
        if(_DEBUG_)
            cout << "Move Horizontal Backward" << endl;
        //Set the checking piece of the vehicle to the right most piece
        row = aVehicle.x;
        col = aVehicle.y + aVehicle.length - 1;

        //Vehicle is at the edge or another vehicle is blocking
        if(!canBackward(grid, aVehicle))
            return false;

        if(_DEBUG_)
            cout << "No Collision" << endl;
        //We can swap places and make the 'rear' the new 'head' to 'move foward'
        grid[row][col - aVehicle.length].id = aVehicle.id;
        grid[row][col - aVehicle.length].orientation =
            aVehicle.orientation;
        grid[row][col - aVehicle.length].length = 
            aVehicle.length;

        grid[row][col].id = '-';
        grid[row][col].orientation = '-';
        grid[row][col].length = 0;
        return true;
    }
    else if(aVehicle.orientation == 'V')
    {
        if(_DEBUG_)
            cout << "Move Veritcal Backward" << endl;
        //Set the checking piece of the vehicle to the right most piece
        row = aVehicle.x + aVehicle.length - 1;
        col = aVehicle.y;

        //Vehicle is at the edge or another vehicle is blocking
        if(!canBackward(grid, aVehicle))
            return false;

        if(_DEBUG_)
            cout << "No Collision" << endl;
        //We can swap places and make the 'rear' the new 'head' to 'move foward'
        grid[row - aVehicle.length][col].id = aVehicle.id;
        grid[row - aVehicle.length][col].orientation =
            aVehicle.orientation;
        grid[row - aVehicle.length][col].length = 
            aVehicle.length;

        grid[row][col].id = '-';
        grid[row][col].orientation = '-';
        grid[row][col].length = 0;
        return true;
    }
    else
        return false;
}

void bruteForce(vehicle grid[6][6], int solutionAmt)
{
    static int iterations = 0;
    iterations++;
    if(_DEBUG_)
    {
        cout << "Iterations: " << iterations << endl;
        cout << "Best:" << minSolution << endl;
        //cout << "Current Steps: " << solutionAmt << endl;
        printGrid(grid);
        char pause = ' ';
        cout << "Paused. Enter Any Character." << endl;
        cin >> pause;
    }

    //Check if the puzzle is solved (the car has reached the right edge)
    if(isSolved(grid))
    {
        if(_DEBUG_)
            cout << "Solved!" << endl;
        if (solutionAmt < minSolution) //Update the minSolution
            minSolution = solutionAmt;
        return;
    }

    //The current instance already has more steps than a better solution
    if(solutionAmt > minSolution)
    {
        if(_DEBUG_)
            cout << "Solutions exceeded current minimum steps." << endl;
        return;
    }

    //The escape car should always take priority moves
    int eX, eY = 0;
    bool eBreakX = false;
    for(int x = 0; x < 6; x++)
    {
        for(int y = 0; y < 6; y++)
        {
            if(grid[x][y].id == '0')
            {
                eX = x;
                eY = y;
                eBreakX = true; //Stop the loop, 0 has been found
                break;
            }
        }
        if(eBreakX)
            break;
    }
    if(canForward(grid, grid[eX][eY]))
    {
        char tmpOrient = grid[eX][eY].orientation;
        moveForward(grid, grid[eX][eY]);
        bruteForce(grid, solutionAmt + 1);
        if(tmpOrient = 'H')
            moveBackward(grid, grid[eX][eY + 1]);
        else if(tmpOrient = 'V')
            moveBackward(grid, grid[eX + 1][eY]);
    }


    //Move vehicles FORWARD in order 1 to n recursively
    for(int i = 1; i < totalVehicles; i++)
    {
        if(_DEBUG_)
            cout << "Searching for: " << i << endl;
        //Find the i car
        int m, n = 0;
        bool breakX = false;
        for(int x = 0; x < 6; x++)
        {
            for(int y = 0; y < 6; y++)
            {
                //Kind of gross way to compare...
                //Had problems trying to see if 0 is '0'
                //Find a way to type cast int to char???
                if(grid[x][y].id - '0' == i)
                {
                    if(_DEBUG_)
                        cout << "Found (" << i <<") at [" << x << "," 
                            << y << "]" << endl;
                    m = x;
                    n = y;
                    breakX = true; //Stop for loop, the id has been found
                    break;
                }
            }
            if (breakX)
                break;
        }

        //Try Moving Forwards
        if(canForward(grid,grid[m][n]))
        {
            char tmpOrient = grid[m][n].orientation;
            moveForward(grid, grid[m][n]);
            bruteForce(grid, solutionAmt + 1);
            if(tmpOrient = 'H')
                moveBackward(grid, grid[m][n + 1]);
            else if(tmpOrient = 'V')
                moveBackward(grid, grid[m + 1][n]);
        }
    }
    // //Move vehicles BACKWARD in order 0 to n recursively
    // for(int i = 0; i < totalVehicles; i++)
    // {
    //     if(_DEBUG_)
    //         cout << "Searching for: " << i << endl;
    //     //Find the i car
    //     int m, n = 0;
    //     bool breakX = false;
    //     for(int x = 0; x < 6; x++)
    //     {
    //         for(int y = 0; y < 6; y++)
    //         {
    //             //Kind of gross way to compare...
    //             //Had problems trying to see if 0 is '0'
    //             //Find a way to type cast int to char???
    //             if(grid[x][y].id - '0' == i)
    //             {
    //                 if(_DEBUG_)
    //                     cout << "Found (" << i <<") at [" << x << "," 
    //                         << y << "]" << endl;
    //                 m = x;
    //                 n = y;
    //                 breakX = true; //Stop for loop, the id has been found
    //                 break;
    //             }
    //         }
    //         if (breakX)
    //             break;
    //     }

    //     //Try Moving Backwards
    //     if(moveBackward(grid,grid[m][n]))
    //     {
    //         bruteForce(grid, 1 + solutionAmt);
    //         moveForward(grid,grid[m][n]);
    //         solutionAmt -= 1;
    //     }
    // }
    //Vehicle cannot move forward or backwards
    return;
}

/** Determines whether the state of the grid is solved
* by checking the last column for any 0s.
* @param grid is the grid to check if it has been solved.
* @return True if the grid is solved, False if it is not.
*/
bool isSolved(vehicle grid[6][6])
{
    return (grid[0][5].id == '0' ||
            grid[1][5].id == '0' ||
            grid[2][5].id == '0' ||
            grid[3][5].id == '0' ||
            grid[4][5].id == '0' ||
            grid[5][5].id == '0');
}

/** Prints a formatted representation of the grid.
* @pre The grid must not be empty.
* @param grid is the grid to print out.
*/
void printGrid(vehicle grid[6][6])
{
    for(int x = 0; x < 6; x++)
    {
        for(int y = 0; y < 6; y++)
            cout << grid[x][y].id << " ";
        cout << endl;
    }
}