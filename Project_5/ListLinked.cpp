/** @file ListLinked.cpp
* @mainpage Project 5 (Singly Linked List)
* @author Saharath Kleips
* @version 3.00
* @brief This program will implement a singly linked list.
* @details The specifications of this project match those of the book C++ Data
* Structures - A Laboratory Course (3rd Edition) Project 5.
* @date August 29th, 2014
*/

//
// HEADER FILES ///////////////////////////////////////////////////////////////
//

#include "ListLinked.h"
using namespace std;

//
// List Function Implementations //////////////////////////////////////////////
//

/** The default constructor
* that creates an empty List.
* @param ignored is provided for call compatibility with the array 
* implementation.
*/
template<class DataType>
List<DataType>::List(int ignored)
{
    head = cursor = NULL;
}

/** The copy constructor
* that initializes the List to be equivalent to the other List.
* @param other is the List to be equivalent to this List.
*/
template<class DataType>
List<DataType>::List(const List& other)
{
    head = cursor = NULL;
    ListNode* temp = other.head;
    while(temp != NULL)
    {
    	insert(temp->dataItem);
    	temp = temp->next;
    }
}

/** The overloaded assignment operator
* that sets the List to be equivalent to the other List and returns a reference
* to this object.
* @param other is the List that this List will be made equivalent to.
* @return The reference to this object.
*/
template<class DataType>
List<DataType>& List<DataType>::operator=(const List& other)
{
    clear();
    ListNode* temp = other.head;
    while(temp != NULL)
    {
    	insert(temp->dataItem);
    	temp = temp->next;
    }   
    return *this;
}

/** The destructor
* that deallocates the memory used to store the nodes in the List.
* @see clear()
*/
template<class DataType>
List<DataType>::~List()
{
    clear();
}

/** Inserts newDataItem into the List.
* If the List is not empty, then inserts newDataItem after the cursor.
* Otherwise, inserts newDataItem as the first (and only) data item in the List.
* In either case, moves the cursor to newDataItem.
* @pre The List is not full.
* @param newDataItem is the data to be added to the List.
* @todo Implement exception handling and make sense of exception specifications
*/
template<class DataType>
void List<DataType>::insert(const DataType& newDataItem) throw (logic_error)
{
    if(!isFull())
        if(!isEmpty())
        {
            cursor->next = new ListNode(newDataItem, cursor->next);
            cursor = cursor->next;
        }
        else
        {
            head = new ListNode(newDataItem, NULL);
            cursor = head;
        }
}

/** Removes the data item marked by the cursor
* from the List. If the resulting List is not empty, then moves the cursor to
* the data item that followed the deleted data item. If the deleted data item
* was at the end of the List, then moves the cursor to the beginning of the
* List.
* @pre The List is not empty.
* @todo Implement exception handling and make sense of exception specifications
*/
template<class DataType>
void List<DataType>::remove()  throw (logic_error)
{
    if(!isEmpty())
    {
        ListNode* temp = cursor->next;
        gotoPrior();
        if (cursor->next == temp) //Did not go to prior
        {
            delete cursor;
            head = temp;
        }
        else //Went to prior
            delete cursor->next;
        cursor->next = temp;
        cursor = temp;
        if(cursor == NULL)
            gotoBeginning();
    }
}

/** Replaces the data item marked by the cursor
* with newDataItem. The cursor remains at newDataItem.
* @pre The List is not empty.
* @param newDataItem is the data that will replace the data at the cursor.
* @todo Implement exception handling and make sense of exception specifications
*/
template<class DataType>
void List<DataType>::replace(const DataType& newDataItem) throw (logic_error)
{
    if(!isEmpty())
        cursor->dataItem = newDataItem;
}

/** Removes all the data items in the List.
* Will deallocate memory used for the nodes to store the data.
*/
template<class DataType>
void List<DataType>::clear()
{
    while (cursor != NULL)
    {
        remove();
    }
    head = cursor = NULL;
}

/** Returns true if the List is empty.
* Otherwise, returns false.
* @return The List is empty or not.
*/
template<class DataType>
bool List<DataType>::isEmpty() const
{
    if(head == NULL)
        return true;
    else
        return false;
}

/** Returns true if the List is full.
* Otherwise, returns false.
* @todo Will always return false, check if memory can be allocated. 
* @return The List is full or not.
*/
template<class DataType>
bool List<DataType>::isFull() const
{
    return false;
}

/** Moves the cursor to the beginning
* of the List.
* @pre The List is not empty.
* @todo Implement exception handling and make sense of exception specifications
*/
template<class DataType>
void List<DataType>::gotoBeginning() throw (logic_error)
{
    if(!isEmpty())
        cursor = head;
}

/** Moves the cursor to the end
* of the List.
* @pre The List is not empty.
* @todo Implement exception handling and make sense of exception specifications
*/
template<class DataType>
void List<DataType>::gotoEnd() throw (logic_error)
{
    if(!isEmpty())
        while(gotoNext());
}

/** Moves the cursor the next data item.
* If the cursor is not at the end of the List, the cursor moves to the next
* data item and returns true. Otherwise, returns false. 
* @pre The List is not empty.
* @return The cursor was not at the end of the List.
* @todo Implement exception handling and make sense of exception specifications
*/
template<class DataType>
bool List<DataType>::gotoNext() throw (logic_error)
{
    if(!isEmpty())
    {
        if(cursor->next != NULL)
        {
            cursor = cursor->next;
            return true;
        }
    }
    return false;
}

/** Moves the cursor to the preceding data item.
* If the cursor is not at the beginning of the List, the cursor moves to the
* preceding data item and returns true. Otherwise, returns false.
* @pre The List is not empty.
* @return The cursor was not at the beginning of the List.
* @todo Implement exception handling and make sense of exception specifications
*/
template<class DataType>
bool List<DataType>::gotoPrior() throw (logic_error)
{
    if(!isEmpty())
    {
        if(cursor != head)
        {
            ListNode* temp = cursor;
            cursor = head;
            while (cursor->next != temp)
                gotoNext();
        }
        else
            return false;
    }
    return true;
}

/** Returns the value of the data item
* marked by the cursor.
* @pre The List is not empty.
* @return The data item marked by the cursor.
* @todo Implement exception handling and make sense of exception specifications
*/
template<class DataType>
DataType List<DataType>::getCursor() const throw (logic_error)
{
    if(!isEmpty())
        return cursor->dataItem;
    return (DataType)NULL;
}

//Exercise 2
/** Removes and reinserts the data item
* marked by the cursor to the beginning of the List. Moves the cursor to the
* beginning of the List.
* @pre The List is not empty.
* @todo Implement exception handling and make sense of exception specifications
*/
template<class DataType>
void List<DataType>::moveToBeginning() throw (logic_error)
{
    if(!isEmpty())
    {
        if (cursor != head)
        {
            ListNode* tempN = cursor->next;
            ListNode* tempC = cursor;
            gotoPrior();
            cursor->next = tempN;
            tempC->next = head;
            cursor = head = tempC;
        }
    }
}

//Exercise 3
/** Inserts newDataItem into a List.
* If the List is not empty, then inserts newDataItem immediately before the
* cursor. Otherwise, inserts newDataItem as the first (and only) data item in
* the List. In either case, moves the cursor to newDataItem.
* @pre The List is not full.
*/
template<class DataType>
void List<DataType>::insertBefore(const DataType& newDataItem) throw 
    (logic_error)
{
    if(!isFull())
    {
        if(cursor != head)
        {
            gotoPrior();
            insert(newDataItem);
        }
        else
            head = cursor = new ListNode(newDataItem, head);
    }
}

/** Outputs the items in a List.
* If the List is empty, outputs "Empty list." This operation is intended for
* testing and debugging purposes only.
*/
template<class DataType>
void List<DataType>::showStructure() const
{
    if ( isEmpty() )
    {
       cout << "Empty list" << endl;
    } 
    else
    {
    for (ListNode* temp = head; temp != 0; temp = temp->next) {
        if (temp == cursor) {
        cout << "[";
        }

        // Assumes that dataItem can be printed via << because
        // is is either primitive or operator<< is overloaded.
        cout << temp->dataItem; 

        if (temp == cursor) {
        cout << "]";
        }
        cout << " ";
    }
    cout << endl;
    }
}

//
// ListNode Function Implementations //////////////////////////////////////////
//

/** The parameterized constructor
* that sets the ListNode's data item to the value nodeData and the ListNode's
* next pointer to the value of nextPtr.
* @param nodeData is the data to be stored within the node.
* @param nextPtr is the pointer to the next node that this node is linked to.
*/
template<class DataType>
List<DataType>::ListNode::ListNode(const DataType& nodeData, ListNode* nextPtr)
{
    dataItem = nodeData;
    next = nextPtr;
}