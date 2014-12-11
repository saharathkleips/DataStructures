/** @file Heap.cpp
* @mainpage Project 11 (Heap ADT)
* @author Saharath Kleips
* @brief This program will implement a Heap.
* @details The specifications of this project match those of the book C++ Data
* Structures - A Laboratory Course (3rd Edition) Project 11. A Heap forms a
* complete binary tree. For each data item E in the tree, all of E's descendants
* have priorities that are less than or equal to E's priority.
*/

//
// HEADER FILES ////////////////////////////////////////////////////////////////
//

#include "Heap.h"
#include "show11.cpp"
#include <stdexcept>
#include <iostream>
using namespace std;

//
// HEAP FUNCTION IMPLEMENTATIONS ///////////////////////////////////////////////
//

/** The parameterized constructor
* that creates an empty Heap that allocates enough memory for a heap containing
* maxNumber data items.
* @post This Heap will be a valid empty Heap with enough memory for maxNumber
* data items.
* @param maxNumber is how much memory to allocate for this Heap.
*/
template<typename DataType, typename KeyType, typename Comparator>
Heap<DataType, KeyType, Comparator>::Heap(int maxNumber)
{
    maxSize = maxNumber;
    size = 0;
    dataItems = new DataType[maxSize];
}

/** The copy constructor
* that initializes this Heap to be equivalent to the other Heap.
* @pre other is a valid Heap.
* @post This Heap will be a deep copy of the other Heap.
* @param other is the Heap that this Heap will be made equivalent to.
*/
template<typename DataType, typename KeyType, typename Comparator>
Heap<DataType, KeyType, Comparator>::
    Heap(const Heap<DataType, KeyType, Comparator>& other)
{
    *this = other;
}

/** The overloaded assignment operator
* that sets this Heap to be equivalent to the other Heap object parameter.
* @pre other is a valid Heap.
* @post This Heap will be a deep copy of the other Heap.
* @param other is the Heap that this Heap will be made equivalent to.
* @return The reference to this Heap.
*/
template<typename DataType, typename KeyType, typename Comparator>
Heap<DataType, KeyType, Comparator>& Heap<DataType, KeyType, Comparator>::
    operator=(const Heap<DataType, KeyType, Comparator>& other)
{
    //Check if same heap
    if(this == &other)
        return *this;
    //Check for empty
    if(isEmpty() == false)
        clear();
    //Copy Heap properties
    size = other.size;
    maxSize = other.maxSize;
    //Deep copy
    for(int i = 0; i < size; i++)
        dataItems[i] = other.dataItems[i];

    return *this;
}

/** The destructor
* that deallocates the memory used to store this Heap.
* @post This Heap will be an empty, deallocated, Heap.
*/
template<typename DataType, typename KeyType, typename Comparator>
Heap<DataType, KeyType, Comparator>::~Heap()
{
    clear();
    delete dataItems;
}

/** Inserts newDataItem
* into the heap. Inserts this data item as the rightmost data item in the heap
* and moves it upward until the properties that define a heap are restored.
* @pre This Heap is not full.
* @post newDataItem will be inserted into the Heap.
* @param newDataItem is the data item to be inserted into this Heap.
* @throw This Heap is full.
*/
template<typename DataType, typename KeyType, typename Comparator>
void Heap<DataType, KeyType, Comparator>::insert(const DataType& newDataItem)
    throw (logic_error)
{
    //Insert if not full
    if(isFull() == false)
    {
        int index = size;
        Comparator compare;
        dataItems[size] = newDataItem;
        //Compare the two data items
        while(compare(dataItems[index].getPriority(), 
            dataItems[(index - 1) / 2].getPriority()))
        {
            //Swap the two data items
            DataType data = dataItems[index];
            dataItems[index] = dataItems[(index - 1) / 2];
            dataItems[(index - 1) / 2] = data;
            index = (index - 1) / 2;
        }
        size++;
    }
    else
        throw logic_error("Full List");
}  

/** Removes the highest priority data item
* (the root) from this Heap and returns it. Replaces the root data item with the
* bottom rightmost data item and moves this data item downward until the
* properties that define a heap are restored.
* @pre This Heap is not empty.
* @post This Heap will no longer contain the highest priority data item.
* @return The highest priority data item.
* @throw This Heap is empty.
*/
template<typename DataType, typename KeyType, typename Comparator>
DataType Heap<DataType, KeyType, Comparator>::remove() throw (logic_error)
{
    if(isEmpty() == true)
    {
        throw logic_error("Empty List");
    }

    size--;
    //Set the return data
    DataType returnData = dataItems[0];
    dataItems[0] = dataItems[size];

    //Iterate through the Heap
    int index = 0;
    while(index < size)
    {
        Comparator compare;
        if((index * 2) + 2 <= size)
        {
            //No switch if same
            if(compare(dataItems[index].getPriority(), 
                dataItems[(index * 2) + 1].getPriority()) &&
                compare(dataItems[index].getPriority(),
                dataItems[(index * 2) + 2].getPriority()))
            {
                return returnData;
            }
            //Swap items if greater than
            else if(compare(dataItems[(index * 2) + 2].getPriority(),
                dataItems[(index * 2) + 1].getPriority()))
            {
                DataType temp = dataItems[index];
                dataItems[index] = dataItems[(index * 2) + 2];
                dataItems[(index * 2) + 2] = temp;
                index = (index * 2) + 2;
            }
            //Swap items if less than
            else
            {
                DataType temp = dataItems[index];
                dataItems[index] = dataItems[index + 1];
                dataItems[(index * 2) + 1] = temp;
                index = (index * 2) + 1;
            }
        }
        else if( (index * 2) + 1 <= size)
        {
            //Swap items if greater than
            if(compare(dataItems[(index * 2) + 1].getPriority(),
                dataItems[index].getPriority()))
            {
                DataType temp = dataItems[index];
                dataItems[index] = dataItems[(index * 2) + 1];
                dataItems[(index * 2) + 1] = temp;
                index = (index * 2) + 1;
            }
            else
            {
                return returnData;
            }
        }
        else
        {
            return returnData;
        }
    }
    return returnData;
}

/** Remove all data items
* from this Heap.
* @post This Heap will be an empty Heap.
*/
template<typename DataType, typename KeyType, typename Comparator>
void Heap<DataType, KeyType, Comparator>::clear()
{
    size = 0;
}

/** Return true of this Heap is empty.
* Otherwise, returns false.
* @return True if this Heap is empty. False if this Heap is not empty.
*/
template<typename DataType, typename KeyType, typename Comparator>
bool Heap<DataType, KeyType, Comparator>::isEmpty() const
{
    return (size == 0);
}

/** Return true if the heap is full.
* Otherwise, returns false.
* @return True if this heap is full. False if this heap is not full.
*/
template<typename DataType, typename KeyType, typename Comparator>
bool Heap<DataType, KeyType, Comparator>::isFull() const
{
    return (size == maxSize);
}

/** Outputs the data items in level order.
* One level per line. Only outputs each data item's priority. If the heap is
* empty, then outputs "Empty heap".
* @post The level order of this Heap will be outputted to the console.
*/
template<typename DataType, typename KeyType, typename Comparator>
void Heap<DataType, KeyType, Comparator>::writeLevels() const
{
    int levelCount = 1;
    int printCount = 0;
    for(int i = 0; i < size; i++, printCount++)
    {
        if(printCount == levelCount)
        {
            cout << endl;
            printCount = 0;
            levelCount *= 2;
        }
        cout << dataItems[i].getPriority() << " ";
    }
    cout << endl;
}