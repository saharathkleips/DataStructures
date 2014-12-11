/** @file RushHour.cpp
* @mainpage Rush Hour
* @author Saharath Kleips
* @version 2.00
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
*/

//
// HEADER FILES ////////////////////////////////////////////////////////////////
//
#include <queue>
#include <map>
#include <iostream>
using namespace std;

//
// GLOBAL VARIABLES ////////////////////////////////////////////////////////////
//
/** Debug console output and function tracing. */
const bool _DEBUG_ = false;
/** Extended console output for puzzle diagram, moves used, etc. */
const bool _FULL_OUTPUT_ = false;

//
// FORWARD DECLARATIONS ////////////////////////////////////////////////////////
//
struct Vehicle
{
	/** The character representation of this Vehicle. */
	char id;
	/** The orientation, either horizontal or vertical, of this Vehicle. */
	char orientation;
	/** The length of this Vehicle. */
	int length;
};

struct Board
{
	/** The lowest possible number of moves to solve the puzzle. */
	int minSolution;
	/** The total amount of vehicles in this instance of the puzzle. */
	int totalVehicles;
	/** The current state of the board and all of its vehicles. */
	Vehicle state[6][6];

	Board();
    bool isSolved();
    bool moveForward(char);
    bool moveBackward(char);
    bool canForward(char);
    bool canBackward(char);
	void printState();
};

Board loadPuzzle();
int solve(Board&);
Board stringToBoard(string);
string boardToString(Board);

//
// MAIN FUNCTION IMPLEMENTATIONS ///////////////////////////////////////////////
//

/** Main function that controls user input, console output, and program loops.
*/
int main()
{
	Board gameBoard = Board();
    char userInput;
    int scenario = 1;
    gameBoard = loadPuzzle();
    do
    {
        if(_FULL_OUTPUT_)
        {
            cout << endl << "Game Boad:" << endl;
            gameBoard.printState();
        }
        cout << "Scenario " << scenario << " requires " <<
            solve(gameBoard) << " moves" << endl;
        scenario++;
        gameBoard = loadPuzzle();
    } while (gameBoard.totalVehicles > 0);
	return 1;
}

/** Loads Board with a Rush Hour puzzle scenario from the console.
* The first integer indicates the number of vehicles (n) in the scenario between
* 0 <= n <= 10. The next n lines represent 1 Vehicle where each line consists
* of a space separated list. Each list contains a number (2 or 3) indicating
* length, a letter (H or V) indicating orientation, and a row number (0-5) of
* the up most square if orientated vertically or the column number (0-5) of the
* left most square if orientated horizontally. The first Vehicle is treated as
* the escape Vehicle and must be orientated horizontally.
* @pre User input of a rush hour problem must be valid.
* @post Board is solvable and meets the criteria of the above description.
* @return Board is the Rush Hour scenario specified by the user.
*/
Board loadPuzzle()
{
	Board newBoard = Board();

	if(_FULL_OUTPUT_)
		cout << "Please enter the number of vehicles: ";
	/** The number of vehicles in the puzzle. */
	int n = 0;
	cin >> n;
	newBoard.totalVehicles = n;

	if (n > 0)
	{
		for(int i = 0; i < n; i++)
		{
			/** The length of the Vehicle. */
			int cLen = 0;
			/** The orientation of the Vehicle. */
			char cOrien = '-';
			/** The starting row of the Vehicle. */
			int cRow = 0;
			/** The starting column of the Vehicle. */
			int cCol = 0;
			/** Temporary variable used to grab user input. */
			char tmp;

			//Grab the user input for a Vehicle within the puzzle
			if(_FULL_OUTPUT_)
                cout << "Please enter a space separated list of the " << 
            "vehicle length(2/3), orientation(H/V), row(0-6), and column(0-6).";
            cin >> cLen;
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

            //Load the vehcile into the Board based on orientation
            switch(cOrien)
            {
            	case 'H':
            		//Update Board properties based on length
            		for(int j = 0; j < cLen; j++)
            		{
            			newBoard.state[cRow][cCol + j].id = '0' + i;
            			newBoard.state[cRow][cCol + j].orientation = cOrien;
            			newBoard.state[cRow][cCol + j].length = cLen;
            		}
            		break;
            	case 'V':
            		//Update Board properties based on length
            		for(int j = 0; j < cLen; j++)
            		{
            			newBoard.state[cRow + j][cCol].id = '0' + i;
            			newBoard.state[cRow + j][cCol].orientation = cOrien;
            			newBoard.state[cRow + j][cCol].length = cLen;
            		}
            		break;
            	default:
            		newBoard.state[cRow][cCol].id = '-';
                    newBoard.state[cRow][cCol].orientation = '-';
                    newBoard.state[cRow][cCol].length = '0';
            		break;
            }
		}
	}
	return newBoard;
}

//
// BOARD FUNCTION IMPLEMENTATIONS //////////////////////////////////////////////
//

/** Default constructor
for class Board. */
Board::Board()
{
	minSolution = -1;
	totalVehicles = -1;
	//Initializes the 2D array that represents the puzzle state
	for(int x = 0; x < 6; x++)
		for(int y = 0; y < 6; y++)
		{
			state[x][y].id = '-';
			state[x][y].orientation = '-';
			state[x][y].length = 0;
		}
}

/** Solves the current state of the Board
* by implementing a breath-first search with previous state comparisons.
* @post minSolutions will be updated with the minimum amount of moves it takes
* to solve the puzzle.
*/
int solve(Board& board)
{
    queue<Board> currentStates;
    map<string, int> previousStates;

    //If the Board is solved, then return the solution
    if(board.isSolved())
        return board.minSolution;

    //Add the initial states to the queue and map
    currentStates.push(board);
    previousStates[boardToString(board)] = 0;

    //If there is still instances of the board in the queue
    while(currentStates.size() > 0)
    {
        //Set the board to a different state
        board = currentStates.front();
        currentStates.pop();
        //Adds the board to the map if it has not been checked before
        board.minSolution = (previousStates.find(boardToString(board)))->second;

        if(board.isSolved())
             return board.minSolution;

        //Iterate through all of the vehicles movement options
        for(int i = 0; i < board.totalVehicles; i++)
        {
            //Move the vehicle forward
            if(board.moveForward(i + '0'))
            {
                //Check if the previous state has been checked before
                if(previousStates.count(boardToString(board)) == 0)
                {
                    //Add this state to the map so it's not checked again
                    previousStates[boardToString(board)] = 
                        board.minSolution + 1;
                    //Add this state to the queue to check
                    currentStates.push(board);
                }
                //Reset the board
                board.moveBackward(i + '0');
            }

            //Move the vehicle backwards
            if(board.moveBackward(i + '0'))
            {
                //Check if the previous state has been checked before
                if(previousStates.count(boardToString(board)) == 0)
                {
                    //Add this state to the map so it's not checked again
                    previousStates[boardToString(board)] = 
                        board.minSolution + 1;
                        //Add this state to the queue to check
                    currentStates.push(board);
                }
                //Reset the board
                board.moveForward(i + '0');
            }
        }
    }

}

/** Moves a vehicle forward
* on the Board corresponding to its ID.
* @post The Board will be updated with the new positions of the vehicles.
* @param cID is the ID of the vehicle on the Board.
* @return True if the vehicle was moved. False if the vehicle was not moved.
*/
bool Board::moveForward(char cID)
{
    int row, col;
    bool _break = false;
    //Find the top-left most index of the vehicle
    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            if(state[i][j].id == cID)
            {
                row = i;
                col = j;
                _break = true;
                break;
            }
        }
        if (_break == true)
            break;
    }

    //Switch the IDs to "move" the car based on orientation
    int cLen = state[row][col].length;
    switch(state[row][col].orientation)
    {
        case 'H':
            if(!canForward(cID))
                return false;

            state[row][col + cLen].id = state[row][col].id;
            state[row][col + cLen].orientation = state[row][col].orientation;
            state[row][col + cLen].length = state[row][col].length;

            state[row][col].id = '-';
            state[row][col].orientation = '-';
            state[row][col].length = 0;
            return true;
            break;
        case 'V':
            if(!canForward(cID))
                return false;

            state[row + cLen][col].id = state[row][col].id;
            state[row + cLen][col].orientation = state[row][col].orientation;
            state[row + cLen][col].length = state[row][col].length;

            state[row][col].id = '-';
            state[row][col].orientation = '-';
            state[row][col].length = 0;
            return true;
            break;
        default:
            return false;
    }
}

/** Moves a vehicle backwards
* on the Board corresponding to its ID.
* @post The Board will be updated with the new positions of the vehicles.
* @param cID is the ID of the vehicle on the Board.
* @return True if the vehicle was moved. False if the vehicle was not moved.
*/
bool Board::moveBackward(char cID)
{
    int row, col;
    bool _break = false;
    //Find the top-left most index of the vehicle
    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            if(state[i][j].id == cID)
            {
                row = i;
                col = j;
                _break = true;
                break;
            }
        }
        if (_break == true)
            break;
    }

    //Switch the IDs to "move" the car based on orientation
    int cLen = state[row][col].length;
    switch(state[row][col].orientation)
    {
        case 'H':
            if(!canBackward(cID))
                return false;

            col = col + cLen - 1;

            state[row][col - cLen].id = state[row][col].id;
            state[row][col - cLen].orientation = state[row][col].orientation;
            state[row][col - cLen].length = state[row][col].length;

            state[row][col].id = '-';
            state[row][col].orientation = '-';
            state[row][col].length = 0;
            return true;
            break;
        case 'V':
            if(!canBackward(cID))
                return false;

            row = row + cLen - 1;

            state[row - cLen][col].id = state[row][col].id;
            state[row - cLen][col].orientation = state[row][col].orientation;
            state[row - cLen][col].length = state[row][col].length;

            state[row][col].id = '-';
            state[row][col].orientation = '-';
            state[row][col].length = 0;
            return true;
            break;
        default:
            return false;
    }
}

/** Checks if a vehicle can move backwards
* on the Board corresponding to its ID.
* @param cID is the ID of the vehicle on the Board.
* @return True if the vehicle can move. False if the vehicle can not move.
*/
bool Board::canForward(char cID)
{
    int row, col;
    bool _break = false;
    //Find the top-left most index of the vehicle
    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            if(state[i][j].id == cID)
            {
                row = i;
                col = j;
                _break = true;
                break;
            }
        }
        if (_break == true)
            break;
    }

    //Check if the vehicle can move based on orientation
    int cLen = state[row][col].length;
    switch(state[row][col].orientation)
    {
        case 'H':
            if(col + cLen > 5 || state[row][col + cLen].id != '-')
                return false;
            else
                return true;
            break;
        case 'V':
            if(row + cLen > 5 || state[row + cLen][col].id != '-')
                return false;
            else
                return true;
            break;
        default:
            return false;
    }
}

/** Checks if a vehicle can move backwards
* on the Board corresponding to its ID.
* @param cID is the ID of the vehicle on the Board.
* @return True if the vehicle can move. False if the vehicle can not move.
*/
bool Board::canBackward(char cID)
{
    int row, col;
    bool _break = false;
    //Find the top-left most index of the vehicle
    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            if(state[i][j].id == cID)
            {
                row = i;
                col = j;
                _break = true;
                break;
            }
        }
        if (_break == true)
            break;
    }

    //Check if the vehicle can move based on orientation
    int cLen = state[row][col].length;
    switch(state[row][col].orientation)
    {
        case 'H':
            col = col + cLen - 1;
            if(col - cLen < 0 || state[row][col - cLen].id != '-')
                return false;
            else
                return true;
            break;
        case 'V':
            row = row + cLen - 1;
            if(row - cLen < 0 || state[row - cLen][col].id != '-')
                return false;
            else
                return true;
            break;
        default:
            return false;
    }
}

/** Determines whether the state of the grid is solved
* by checking the last column for any 0s.
* @return True if the grid is solved, False if it is not.
*/
bool Board::isSolved()
{
    return (state[0][5].id == '0' ||
            state[1][5].id == '0' ||
            state[2][5].id == '0' ||
            state[3][5].id == '0' ||
            state[4][5].id == '0' ||
            state[5][5].id == '0');
}

/** Converts a Board to a String
* of IDs followed by orientations without character breaks for new rows or
* columns.
* @param b is the Board to convert to a String.
* @return The converted Board.
*/
string boardToString(Board b)
{
    string s;
    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            s += b.state[i][j].id;
            s += b.state[i][j].orientation;
        }
    }
    if(_DEBUG_)
        cout << s << endl;
    return s;
}

/** Converts a String to a Board
* with full IDs and Orientations, but does not contain lengths.
* @param s is the String to convert to a Board.
* @return The converted String.
*/
Board stringToBoard(string s)
{
    Board b;
    int count = 0;
    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 6; j++, count+=2)
        {
            if(_DEBUG_)
                cout << s[count] << s[count+1] << endl;
            b.state[i][j].id = s[count];
            b.state[i][j].orientation = s[count+1];
        }
    }
    return b;
}

/** Prints a formatted representation of the state of the Board.
* @param state is the current state of the puzzle to print out.
*/
void Board::printState()
{    
	for(int x = 0; x < 6; x++)
    {
        for(int y = 0; y < 6; y++)
            cout << state[x][y].id << " ";
        	cout << endl;
    }
}