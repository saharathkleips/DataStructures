/** @file pumpkin.cpp
* @mainpage The Great Pumpkin Patch Problem
* @author Saharath Kleips
* @version 1.00
* @brief It's almost Halloween and Linus is setting out to the garden to wait
* for the Great Pumpkin. Unfortunately, due to diversification, there are lots
* of other gourds in the garden this year. This program will determine how many
* patches of pumpkins there are and how big they are.
* @details Consider a 10 x 10 garden with zucchini (z), yellow squash (y),
* spaghetti squash (s), and pumpkins (p):
* \n      pzzzzzzzzp
* \n      pyypzzzzzy
* \n      ppppssssyy
* \n      ssspssssyy
* \n      ssssppssyy
* \n      ssssppsspy
* \n      zzzzzzsspy
* \n      zzzzzzsspy
* \n      yyyypzsspy
* \n      yyyypppppy
* \n
* This garden has four patches of pumpkins: one at the top left corner covering
* 8 squares, one in the top right corner covering 1 square, one in the center
* covering 4 squares, and one near the buttom right covering 10 squares. Note:
* in order for a square to be a part of a patch, it must connect with another
* square in that patch along an edge, not just a corner.
* 
* Description has been modified from Professor Frederick C. Harris' PA03-PC1
* assignment (University of Nevada, Reno - CS302).
*/

//
// HEADER FILES ////////////////////////////////////////////////////////////////
//
#include <stdlib.h>
#include <iostream>
using namespace std;

//
// GLOBALS VARIABLES ///////////////////////////////////////////////////////////
//
/** The max row size of the garden. */
int row = 0;
/** The max column size of the garden. */
int column = 0;

//
// FORWARD DECLARTIONS /////////////////////////////////////////////////////////
//
int calculateSize(char**, int, int);
void quickSort(int[], int, int);

//
// FUNCTION IMPLEMENTATIONS ////////////////////////////////////////////////////
//

/** Main function that controls user input, console output, and program loops.
*/
int main()
{
    int iterations = 0;
    do
    {
        iterations++;
        // Grab User Inputs (Row & Column Size) //
        cin >> row;
        cin >> column;

        // Initialize Garden //
        char** garden = new char*[row];
        for(int i = 0; i < row; i++)
            garden[i] = new char[column];

        // Grab User Inputs (Gourds In The Garden) //
        if(row > 0 && column > 0)
            for(int i = 0; i < row; i++)
                for(int j = 0; j < column; j++)
                {
                    cin >> garden[i][j];
                    garden[i][j] = tolower(garden[i][j]);
                }

        // Initializes Sizes //
        int sizes[row*column];
        for(int i = 0; i < row*column; i++)
            sizes[i] = 0;

        // Compute the pumpkins!! //
        /*
        * Iterates through each square within the garden. If the square is a
        * pumpkin, check the patch size, and put the size within array sizes.
        */
        int count = 0;
        for(int i = 0; i < row; i++)
            for(int j = 0; j < column; j++)
                if(garden[i][j] == 'p')
                {
                    sizes[count] = calculateSize(garden, i, j);
                    count++;
                }

        quickSort(sizes, 0, row*column - 1);

        // Print Statistics //
        if(row > 0 && column > 0)
        {
            cout << "Garden # " << iterations << ": " << count <<
                " patches, sizes:";
            for(int i = 0; i < row*column; i++)
                if(sizes[i] > 0)
                    cout << " " << sizes[i];
            cout << endl;
        }


        // // Print Garden //
        // for(int i = 0; i < row; i++)
        // {
        //     for(int j = 0; j < column; j++)
        //     {
        //         cout << garden[i][j];
        //     }
        //     cout << endl;
        // }

        // Deallocate The Garden //
        for(int i = 0; i < row; i++)
            delete[] garden[i];
        delete[] garden;
    } while ( row != 0 || column != 0);
    return 1;
}

/** Calculates the size of a patch
* recursively checking if the right, bottom, left, and then up patches are also
* pumpkins.
* @pre garden must not be empty.
* @param garden is a two dimensional array of characters representing gourds.
* @param i is the row index of the pumpkin.
* @param j is the column index of the pumpkin.
* @return The size of the patch.
*/
int calculateSize(char** garden, int i, int j)
{
    garden[i][j] = '-';
    int tCount = 0;

    if(i + 1 < row)
        if(garden[i+1][j] == 'p')
            tCount += calculateSize(garden, i+1, j);

    if(j + 1 < column)
        if(garden[i][j+1] == 'p')
            tCount += calculateSize(garden, i, j+1);

    if(i - 1 >= 0)
        if(garden[i-1][j] == 'p')
            tCount += calculateSize(garden, i-1, j);

    if(j - 1 >= 0)
        if(garden[i][j-1] == 'p')
            tCount += calculateSize(garden, i, j-1);

    return tCount + 1;
}

/** Preforms a quick sort from least to greatest
* on an array of integers using the middle as a pivot point.
* @pre elements must not be empty.
* @param elements is the list of integers to be sorted.
* @param leftBound is the left most index to be sorted.
* @param rightBound is the right most index to be sorted.
* @post elements is a sorted from least to greatest.
*/
void quickSort(int elements[], int leftBound, int rightBound)
{
    int i = leftBound;
    int j = rightBound;
    int pivot = elements[leftBound + (rightBound - leftBound) / 2];

    while (i <= j)
    {
        while (elements[i] < pivot)
            i++;

        while (elements[j] > pivot)
            j--;

        if (i<=j)
        {
            int temp = elements[i];
            elements[i] = elements[j];
            elements[j] = temp;
            i++;
            j--;
        }
    }

    if(leftBound < j)
        quickSort(elements, leftBound, j);
    if(i < rightBound)
        quickSort(elements, i, rightBound);
}