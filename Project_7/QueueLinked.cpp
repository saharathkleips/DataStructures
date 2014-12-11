/** @file QueueLinked.cpp
* @mainpage Project 7 (Queue ADT)
* @author Saharath Kleips
* @version 2.00
* @brief This program will implement the Linked List version of a Queue.
* @details The specifications of this project match those of the book C++ Data
* Structures - A Laboratory Course (3rd Edition) Project 7. Data items in the
* Queue are of generic type DataType. The Queue data items are linearly ordered
* from least recently added (front) to most recently added (rear.) Data items
* are inserted at the rear of the Queue (enqueue) and are removed from the front
* of the Queue (dequeue.)
*/

//
// HEADER FILES ////////////////////////////////////////////////////////////////
//

#include "QueueLinked.h"
using namespace std;

//
// Queue Function Implementations //////////////////////////////////////////////
//

/** The default constructor
* that creates an empty Queue. Will allocate neough memory for the Queue
* containing maxNumber data items (if necessary.)
* @param maxNumber is provided for call compatibility with the array
* implementation.
*/
template<class DataType>
QueueLinked<DataType>::QueueLinked(int maxNumber)
{
    front = back = NULL;
}

/** The copy constructor
* that initializes the Queue to be equivalent to the other Queue object
* parameter.
* @param other is the Queue to be equivalent to this Queue.
* @see operator=(const QueueLinked<DataType>& other)
*/
template<class DataType>
QueueLinked<DataType>::QueueLinked(const QueueLinked& other)
{
    front = back = NULL;
    this = other;
}

/** The overloaded assignment operator
* that sets the Queue to be equivalent to the other Queue object parameter and
* returns a reference to the modified Queue.
* @param other is the Queue that this Queue will be made equivalent to.
* @return The reference to this object.
*/
template<class DataType>
QueueLinked<DataType>& QueueLinked<DataType>::
    operator=(const QueueLinked<DataType>& other)
{
    clear();
    QueueNode* temp = other.front;
    while(temp != NULL)
    {
        insert(temp->dataItem);
        temp = temp->next;
    }
    return *this;
}

/** The destructor
* that deallocates the memory used to store the Queue.
* @see clear()
*/
template<class DataType>
QueueLinked<DataType>::~QueueLinked()
{
    clear();
}

/** Inserts newDataItem
* at the rear of the Queue.
* @pre Queue is not full.
* @param newDataItem is the data to be added to the Queue.
*/
template<class DataType>
void QueueLinked<DataType>::enqueue(const DataType& newDataItem)
    throw (logic_error)
{
    if(!isFull())
        if(!isEmpty())
            back = back->next = new QueueNode(newDataItem, NULL);
        else
            front = back = new QueueNode(newDataItem, NULL);
    else
        throw logic_error("enqueue() while queue is full");
}

/** Removes the data item
* that was least recently added from the Queue and returns it.
* @pre Queue is not empty.
* @return DataType is the data removed from the Queue.
*/
template<class DataType>
DataType QueueLinked<DataType>::dequeue() throw (logic_error)
{
    if(!isEmpty())
    {
        QueueNode* temp = front->next;
        DataType tempData = front->dataItem;
        delete front;
        front = temp;
        return tempData;
    }
    else
        throw logic_error("dequeue() while queue is empty");
    return (DataType)NULL;
}

/** Removes all data items in the Queue.
* It will deallocate memory used for the nodes to store the data. Accomplishes
* this by iterating with dequeue().
* @see dequeue()
*/
template<class DataType>
void QueueLinked<DataType>::clear()
{
    while (front != NULL)
        dequeue();
    front = back = NULL;
}

/** Returns true if the Queue is empty.
* Otherwise, returns false.
* @return The Queue is empty or not.
*/
template<class DataType>
bool QueueLinked<DataType>::isEmpty() const
{
    if (front == NULL)
        return true;
    else
        return false;
}

/** Returns true if the Queue is full.
* Otherwise, returns false.
* @return The Queue is full or not.
* @todo Implement overflow check. Currently always returns false.
*/
template<class DataType>
bool QueueLinked<DataType>::isFull() const
{
    return false;
}

/** Inserts newDataItem at the front
* of the Queue. The order of preexisting data items is left unchanged.
* @pre The Queue is not full.
* @param newDataItem is the data item to be added to the Queue.
*/
template<class DataType>
void QueueLinked<DataType>::putFront(const DataType& newDataItem)
    throw (logic_error)
{
    if(!isFull())
    {
        front = new QueueNode(newDataItem, front);
        if (front->next == NULL)
            back = front;
    }
    else
        throw logic_error("putFront() while queue is full");
}

/** Removes the most recently added data item
* from the Queue and returns it. The remainder of the Queue is left unchanged.
* @pre The Queue is not empty.
* @return DataType is the data removed from the Queue.
*/
template<class DataType>
DataType QueueLinked<DataType>::getRear() throw (logic_error)
{
        if(!isEmpty())
    {
        if(back != front)
        {
            QueueNode* temp = back;
            DataType tempData = back->dataItem;
            back = front;
            while (back->next != temp)
                back = back->next;
            delete back->next;
            back->next = NULL;
            return tempData;
        }
        else
        {
            DataType tempData = front->dataItem;
            delete front;
            front = back = NULL;
            return tempData;
        }
    }
    else
        throw logic_error("getRear() while queue is empty");
    return (DataType)NULL;
}

/** Returns the number of data items
* in the Queue.
* @return int is the number of data items in a the Queue.
*/
template<class DataType>
int QueueLinked<DataType>::getLength() const
{
    int i = 0;
    QueueNode* temp = front;
    while(temp != NULL)
    {
        temp = temp->next;
        i++;
    }
    return i;
}

/* Outputs the elements in a Queue.
* If the Queue is empty, outputs "Empty queue". This operation is intended for
* testing and debugging purposes only.
*/
template<class DataType>
void QueueLinked<DataType>::showStructure() const
{
    // Iterates through the queue
    QueueNode* p;

    if ( isEmpty() )
    cout << "Empty queue" << endl;
    else
    {
    cout << "Front\t";
    for ( p = front ; p != NULL ; p = p->next )
    {
        if( p == front )
        {
        cout << '[' << p->dataItem << "] ";
        }
        else
        {
        cout << p->dataItem << " ";
        }
    }
    cout << "\trear" << endl;
    }
}

//
// QueueNode Function Implementations //////////////////////////////////////////
//

/** The parameterized constructor
* that sets the QueueNode's data item to the value nodeData and the QueueNode's
* next pointer to the value of nextPtr.
* @param nodeData is the data to be stored within the node.
* @param nextPTr is the pointer to the next node that this node is linked to.
*/
template<class DataType>
QueueLinked<DataType>::QueueNode::QueueNode(const DataType& nodeData,
    QueueNode* nextPtr)
{
    dataItem = nodeData;
    next = nextPtr;
}