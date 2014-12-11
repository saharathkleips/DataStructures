// HashTable.h

#ifndef HASHTABLE_H
#define HASHTABLE_H


#include <stdexcept>
#include <iostream>

using namespace std;

#include "BSTree.cpp"

template <typename DataType, typename KeyType>
class HashTable {
  public:
    HashTable(int initTableSize);
    HashTable(const HashTable& other);
    HashTable& operator=(const HashTable& other);

    ~HashTable();

    void insert(const DataType& newDataItem);
    bool remove(const KeyType& deleteKey);
    bool retrieve(const KeyType& searchKey, DataType& returnItem) const;
    void clear();

    bool isEmpty() const;

    void showStructure() const;

    double standardDeviation() const;

  private:
    void copyTable(const HashTable& source);

    int tableSize;
    BSTree<DataType, KeyType>* dataTable;
};

#endif	// ifndef HASHTABLE_H
