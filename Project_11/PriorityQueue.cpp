/** @file PriorityQueue.cpp
* @author Saharath Kleips
* @brief This program will implement a Priority Queue.
* @details The specifications of this project match those of the book C++ Data
* Structures - A Laboratory Course (3rd Edition) Project 11. A Priority Queue
* is a linear data structure in which data items are maintained in descending
* order based on priority. You can only access data at the front of the queue,
* examining this data item entails removing it from the queue.
*/

//
// HEADER FILES ////////////////////////////////////////////////////////////////
//

#include "PriorityQueue.h"
#include <stdexcept>
#include <iostream>
using namespace std;

//
// PRIORITY QUEUE FUNCTION IMPLEMENTATIONS /////////////////////////////////////
//

/** The parameterized constructor
* that creates an empty Priority Queue that allocates enough memory for
* maxNumber data items.
* @post This Priority Queue will be a valid empty Priority Queue with enough
* memory for maxNumber data items.
* @param maxNumber is how much memory to allocate for this Priority Queue.
*/
template<typename DataType, typename KeyType, typename Comparator>
PriorityQueue<DataType,KeyType,Comparator>::PriorityQueue(int maxNumber)
{
}

/** Inserts newDataItem
* into this Priority Queue.
* @pre This Priority Queue is not full.
* @post newDataItem will be inserted into the Priority Queue.
* @param newDataItem is the data item to be inserted into the Priority Queue.
*/
template<typename DataType, typename KeyType, typename Comparator>
void PriorityQueue<DataType,KeyType,Comparator>::enqueue(
    const DataType& newDataItem)
{
    Heap<DataType,KeyType,Comparator>::insert(newDataItem);
}

/** Removes the highest priority item
* from this Priority Queue and returns it.
* @pre This Priority Queue is not empty.
* @post This Priority Queue will no longer contain the highest priority item.
* @return The highest priority data item.
*/
template<typename DataType, typename KeyType, typename Comparator>
DataType PriorityQueue<DataType,KeyType,Comparator>::dequeue()
{
    return Heap<DataType>::remove();
}