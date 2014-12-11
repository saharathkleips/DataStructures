/** @file HashTable.cpp
* @mainpage Project 10 (Binary Search Tree ADT)
* @author Saharath Kleips
* @brief This program will implement a Hash Table using an array of binary
* search trees.
* @details The specifications of this project match those of the book C++ Data
* Structures - A Laboratory Course (3rd Edition) Project 10. A Hash Table maps
* a unique key onto a specific location in an array. The generation of these
* keys is called a hash function. Certain hash functions will occasionally
* generate identical indexes for different keys, to prevent this, Binary Search
* Trees are used to implement chaining.
*/

//
// HEADER FILES ////////////////////////////////////////////////////////////////
//

#include "HashTable.h"
#include "show10.cpp"
using namespace std;

//
// Hash Table Function Implmentations //////////////////////////////////////////
//

/** The parameterized constructor
* that creates an empty HashTable of size initTableSize.
* @post This HashTable will be a valid empty HashTable of size initTableSize.
* @param initTableSize is the size of the table
*/
template <typename DataType, typename KeyType>
HashTable<DataType,KeyType>::HashTable(int initTableSize)
{
    tableSize = initTableSize;
    dataTable = new BSTree<DataType, KeyType>[initTableSize];
}

/** The copy constructor
* that initializes this HashTable to be equivalent to the other HashTable.
* @pre other is a valid HashTable.
* @post This HashTable will be a deep copy of the other HashTable.
* @param other is the HashTable that this HashTable will be made equivalent to.
*/
template <typename DataType, typename KeyType>
HashTable<DataType,KeyType>::HashTable(const HashTable& other)
{
    *this = other;
}

/** The overloaded assignment operator
* that sets this HashTable to be equivalent to the other HashTable object 
* parameter.
* @pre other is a valid HashTable.
* @post This HashTable will be a deep copy of the other HashTable.
* @param other is the HashTable table that this HashTable will be made
* equivalent to.
* @return The reference to this HashTable.
* @see HashTable<DataType,KeyType>::copyTable(const HashTable& source)
*/
template <typename DataType, typename KeyType>
HashTable<DataType,KeyType>& HashTable<DataType,KeyType>::operator=(
    const HashTable& other)
{
    if(this = &other)
        return *this;
    if(!isEmpty())
        clear();
    copyTable(other);
    return *this;
}

/** The destructor
* that deallocates the memory used to store this HashTable
* @post This HashTable will be an empty, deallocated, HashTable.
* @see HashTable<DataType,KeyType>::clear()
*/
template <typename DataType, typename KeyType>
HashTable<DataType,KeyType>::~HashTable()
{
    clear();
}

/** Inserts newDataItem
* into the appropriate binary search tree. If a data item with the same key as
* newDataItem already exists in the binary search tree, then update item with
* newDataItem. Otherwise, it inserts it in the binary search tree.
* @post newDataItem will be inserted into the HashTable.
* @param newDataItem is the data item to be inserted into this HashTable.
*/
template <typename DataType, typename KeyType>
void HashTable<DataType,KeyType>::insert(const DataType& newDataItem)
{
    //The index is based on the modulus operation
    int index = newDataItem.hash(newDataItem.getKey()) % tableSize;
    //Insert into the BST
    dataTable[index].insert(newDataItem);
}

/** Removes the data item
* from this HashTable by searching for the data item with the key deleteKey. If
* the data item is found, return true. Otherwise, return false.
* @post This HashTable will no longer contain the data item with key deleteKey.
* @param deleteKey is the key to search which data item to delete in this
* HashTable.
* @return True if the data item is found. False if the data item is not found.
*/
template <typename DataType, typename KeyType>
bool HashTable<DataType,KeyType>::remove(const KeyType& deleteKey)
{
    DataType temp;
    //The index is based on the modulus operation
    int index = temp.hash(deleteKey) % tableSize;
    //Remove from BST
    return dataTable[index].remove(deleteKey);
}

/** Searches for the data item
* from this HashTable with key searchkey. If the data item is found, then copy
* the data item into returnItem and returns true. Otherwise, returns false with
* returnItem undefined.
* @post searrchDataItem will be the copied data item if the data item is found.
* @param searchKey is the key to search this HashTable for.
* @param returnItem is the data item that will contain the search key's data
* item if found.
* @return True if the data item is found. False if the data item is not found.
*/
template <typename DataType, typename KeyType>
bool HashTable<DataType,KeyType>::retrieve(const KeyType& searchKey, 
    DataType& returnItem) const
{
    //The index is based on the modulus operation
    int index = returnItem.hash(searchKey) % tableSize;
    //Retrieve from BST
    return dataTable[index].retrieve(searchKey,returnItem);
}

/** Removes all data items
* from the HashTable.
* @post This HashTable will be an empty HashTable.
*/
template <typename DataType, typename KeyType>
void HashTable<DataType,KeyType>::clear()
{
    //Iterate all BSTs and clear them
    for(int i = 0; i < tableSize; i++)
        dataTable[i].clear();
}

/** Returns true if this HashTable is empty.
* Otherwise, returns false.
* @return True if this HashTable is empty. False if this HashTable is not empty.
*/
template <typename DataType, typename KeyType>
bool HashTable<DataType,KeyType>::isEmpty() const
{
    //Iterate all BSTs and check if empty
    for(int i = 0; i < tableSize; i++)
        if(dataTable[i].isEmpty() == false)
            return false;
    return true;
}

/** Computes the standard deviation
* for key distribution in the hash table and returns the result.
* @return The standard deviation (Currently always -1.0).
* @todo Implement function.
*/
template <typename DataType, typename KeyType>
double HashTable<DataType,KeyType>::standardDeviation() const
{
    return -1.0;
}

/** Recursive helper function.
* @param other is the HashTable to copy from (source HashTable).
* @see HashTable<DataType,KeyType>::operator=(const HashTable& other)
*/
template <typename DataType, typename KeyType>
void HashTable<DataType,KeyType>::copyTable(const HashTable& source)
{
    //delete the previous dataTable
    delete dataTable;
    //set the new data table size
    dataTable = new BSTree<DataType, KeyType>[source.tableSize];
    //copy each element over
    for(int i = 0; i < source.tableSize; i++)
        dataTable[i] = source.dataTable[i];
}