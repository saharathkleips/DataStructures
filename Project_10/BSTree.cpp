/** @file BSTree.cpp
* @author Saharrath Kleips
* @brief This program will implement a Binary Search Tree using a linked tree
* structure.
* @details The specifications of this project match those of the book C++ Data
* Structures - A Laboratory Course (3rd Edition) Project 9.  Data items within
* the data structure form a binary tree. Data items are of generic type DataType
* and each data item has a key of generic type KeyType. For each data item D in 
* the tree, all the data items in D's left subtree have keys that are less than 
* D's key and all the data items in D's right subtree have keys that are greater
* than D's key.
* /n Note: Binary Search Tree == BSTree, Binary Search Tree Node == BSTreeNode
*/

//
// HEADER FILES ////////////////////////////////////////////////////////////////
//

#include "BSTree.h"
#include "show9.cpp"
using namespace std;

//
// Binary Search Tree Function Implementations /////////////////////////////////
//

/* The default constructor
* that creates an empty binary search tree.
* @post This BSTree will be a valid empty BSTree.
*/
template<typename DataType, class KeyType>
BSTree<DataType,KeyType>::BSTree()
{
    root = NULL;
}

/** The copy constructor
* that initializes this BSTree to be equivalent to the other BSTree object
* parameter.
* @pre other is a valid BSTree.
* @post This BSTree will be a deep copy of the other BSTree.
* @param other is the BSTree that this BSTree will be made equivalent to.
* @see BSTree<DataType,KeyType>::operator=(const BSTree<DataType,KeyType>&)
*/
template<typename DataType, class KeyType>
BSTree<DataType,KeyType>::BSTree(const BSTree<DataType,KeyType>& other)
{
    *this = other;
}

/** The overloaded assignment operator
* that sets this BSTree to be equivalent to the other BSTree object parameter
* and returrns a reference to this object.
* @pre other is a valid BSTree.
* @post This BSTree will be a deep copy of the other BSTree
* @param other is this BSTree that this BSTree will be made equivalent to.
* @return The reference to this BSTree.
* @see BSTree<DataType,KeyType>::copyHelper(BSTreeNode*&, BSTreeNode*)
*/
template<typename DataType, class KeyType>
BSTree<DataType,KeyType>& BSTree<DataType,KeyType>::operator=(
    const BSTree<DataType,KeyType>& other)
{
    if(*this == &other)
        return *this;
    clear();
    copyHelper(root, other.root);
    return *this;
}

/** Recursive helper function.
* @param p is the node to copy into (destination node).
* @param other is the node to copy from (source node).
* @see BSTree<DataType,KeyType>::operator=(const BSTree<DataType,KeyType>&)
*/
template<typename DataType, class KeyType>
void BSTree<DataType,KeyType>::copyHelper(BSTreeNode*& p, BSTreeNode* other)
{
    if(other != NULL)
    {
        BSTreeNode *left = NULL;
        BSTreeNode *right = NULL;
        copyHelper(left, other->left);  //Copy left branch
        copyHelper(right, other-right); //Copy right branch
        p = new BSTreeNode(other->dataItem, left, right); //Reached leaf
    }
}

/** The destructor
* that deallocates the memory used to store this BSTree.
* @post This BSTree will be an empty, deallocated, BSTree.
* @see BSTree<DataType,KeyType>::clear()
*/
template<typename DataType, class KeyType>
BSTree<DataType,KeyType>::~BSTree()
{
    clear();
}

/** Inserts newDataItem into this BSTree.
* If a data item with the same key as newDataItem already exists in this tree,
* then updates that data item with newDataItem.
* @post newDataItem will be inserted with respect to left and right BSTreeNodes.
* @param newDataItem is the data item to be inserted into this BSTree.
*/
template<typename DataType, class KeyType>
void BSTree<DataType,KeyType>::insert(const DataType& newDataItem)
{
    insertHelper(newDataItem, root);
}

/** Recursive helper function.
* @param newDataItem is the data item to insert into the BSTree.
* @param p is the current node to check against.
* @see BSTree<DataType,KeyType>::insert(const DataType&)
*/
template<typename DataType, class KeyType>
void BSTree<DataType,KeyType>::insertHelper(const DataType& newDataItem, 
    BSTreeNode*& p)
{
    //Base case, p is NULL so there is room to insert
    if(p == NULL)
    {
        p = new BSTreeNode(newDataItem, NULL, NULL);
    }
    else
    {
        //new data is equal to, so update
        if((p->dataItem).getKey() == newDataItem.getKey())
            p->dataItem = newDataItem;
        //new data is greater than, so insert left
        else if((p->dataItem).getKey() > newDataItem.getKey())
            insertHelper(newDataItem, p->left);
        //new data is less than, so insert right
        else
            insertHelper(newDataItem, p->right);
    }
}

/** Searches this BSTree for the data item with key searchKey.
* If this data item is found, then copies the data item to searchDataItem and
* returns true. Otherwise, returns false with searchDataItem equal to null.
* @post searchDataItem will be the copied data item if the data item is found.
* @param searchKey is the key to search this BSTree for.
* @param searchDataItem is the data item that will contain the search key's
* data item if found.
* @return True if the data item is found. False if the data item is not found.
* @see BSTree<DataType,KeyType>::retrieveHelper(const KeyType&, DataType&,
* BSTreeNode*)
*/
template<typename DataType, class KeyType>
bool BSTree<DataType,KeyType>::retrieve(const KeyType& searchKey, 
    DataType& searchDataItem) const
{
    return retrieveHelper(searchKey, searchDataItem, root);
}

/** Recursive helper function.
* @param searchKey is the key to compare all nodes within the BSTree to.
* @param searchDataItem will contain the search key's data item if found.
* @param p is the current node to check against.
* @see BSTree<DataType,KeyType>::retrieve(const KeyType&, DataType&)
*/
template<typename DataType, class KeyType>
bool BSTree<DataType,KeyType>::retrieveHelper(const KeyType& searchKey,
    DataType& searchDataItem, BSTreeNode* p) const
{
    if(p != NULL)
    {
        //Base case, key has been found in tree
        if(searchKey == (p->dataItem).getKey())
        {
            //Update the search data item
            searchDataItem = p->dataItem;
            return true;
        }
        //Key is less than, so check left
        else if (searchKey < (p->dataItem).getKey())
            return retrieveHelper(searchKey, searchDataItem, p->left);
        //Key is greater than so check right
        else
            return retrieveHelper(searchKey, searchDataItem, p->right);
    }
    //Base case, key not found
    else
        return false;
}

/** Deletes the data item with key deleteKey
* from this BSTree. If the data item is found, then deletes it from the tree and
* returns true. Otherwise, returns false.
* @post This BSTree will no longer contain the data item with key deleteKey if
* found.
* @param deleteKey is the key to search which data item to delete in this 
* BSTree.
* @return True if the data item is found. False if the data item is not found.
* @see BSTree<DataType,KeyType>::removeHelper(const KeyType&, BSTreeNode*&)
*/
template<typename DataType, class KeyType>
bool BSTree<DataType,KeyType>::remove(const KeyType& deleteKey)
{
    return removeHelper(deleteKey, root);
}

/** Recursive helper function.
* @param deleteKey is the key to compare all the nodes within BSTree to.
* @param p is the current node to check against.
* @see BSTree<DataType,KeyType>::remove(const KeyType&)
*/
template<typename DataType, class KeyType>
bool BSTree<DataType,KeyType>::removeHelper(const KeyType& deleteKey, 
    BSTreeNode*& p)
{
    if(p != NULL)
    {
        //Delete key found
        if(deleteKey == (p->dataItem).getKey())
        {
            //Node has no children, simply delete
            if(p->left == NULL && p->right == NULL)
            {
                delete p;
                p = NULL;
            }
            //Node only has right child, swap child with parent
            else if(p->left == NULL)
            {
                BSTreeNode* temp = p;
                p = p->right;
                delete temp;
            }
            //Node only has left child, swap child with parent
            else if(p->right == NULL)
            {
                BSTreeNode* temp = p;
                p = p->left;
                delete temp;
            }
            //Node has both children, find the node that is directly before the
            //node in sorted order, delete that one from the tree, and place
            //its data into the original node
            else
            {
                //Go left one node
                BSTreeNode* temp = p->left;
                //Go right as far as you can
                while(temp->right != NULL)
                    temp = temp->right;
                //Temp should now be the node before it in sorted orrder
                //Swap the data items
                p->dataItem = temp->dataItem;
                //Remove the temp node in the tree
                removeHelper((temp->dataItem).getKey(), p->left);
            }
            return true;
        }
        //Delete key is less than the current node, go left
        else if(deleteKey < (p->dataItem).getKey())
            return removeHelper(deleteKey, p->left);
        //Delete key is greater than the current node, go right
        else
            return removeHelper(deleteKey, p->right);
    }
    //Node is null
    else
        return false;
}

/** Outputs the keys of the data items
* in this BSTree. The keys are output in ascending order on one line, separated
* by spaces.
* @post The keys of each data item are outputted to the console.
* @see BSTree<DataType,KeyType>::writeKeysHelper(BSTreeNode*)
*/
template<typename DataType, class KeyType>
void BSTree<DataType,KeyType>::writeKeys() const
{
    writeKeysHelper(root);
    cout << endl;
}

/** Recursive helper function.
* @param p is the current node to check against.
* @see BSTree<DataType,KeyType>::writeKeys()
*/
template<typename DataType, class KeyType>
void BSTree<DataType,KeyType>::writeKeysHelper(BSTreeNode* p) const
{
    if(p != NULL)
    {
        //To write in ascending order, go left, print, then go right
        writeKeysHelper(p->left);
        cout << (p->dataItem).getKey() << " ";
        writeKeysHelper(p->right);
    }
}

/** Removes all data items
* in this BSTree.
* @post This BSTree will be an empty, deallocated, BSTree.
* @see BSTree<DataType,KeyType>::clearHelper(BSTreeNode*& p)
*/
template<typename DataType, class KeyType>
void BSTree<DataType,KeyType>::clear()
{
    clearHelper(root);
}

/** Recursive helper function.
* @param p is the current node to check against.
* @see BSTree<DataType,KeyType>::clear()
*/
template<typename DataType, class KeyType>
void BSTree<DataType,KeyType>::clearHelper(BSTreeNode*& p)
{
    if(p != NULL)
    {
        //Clear left branch
        clearHelper(p->left);
        //Clear right branch
        clearHelper(p->right);
        //Can't go left or right, so delete self
        delete p;
        //Set all to NULL
        if(p->left != NULL)
            p->left = NULL;
        if(p->right != NULL)
            p->right = NULL;
        p = NULL;
    }
}

/** Returns true if this BSTree is empty.
* Otherwise, returns false.
* @return True if this BSTree is empty. False if this BSTree is not empty.
*/
template<typename DataType, class KeyType>
bool BSTree<DataType,KeyType>::isEmpty() const
{
    //If the root is NULL, then obviously the tree doesn't have anything in it
    return (root == NULL);
}

/** Returns the height
* of this BSTree.
* @return An integer representation of the height of this BSTree.
* see BSTree<DataType,KeyType>::getHeightHelper(BSTreeNode*, int)
*/
template<typename DataType, class KeyType>
int BSTree<DataType,KeyType>::getHeight() const
{
    return getHeightHelper(root, 0);
}

/** Recursive helper function.
* @param p is the current node to check against.
* @param currentLevel is the level of the current node.
* @see BSTree<DataType,KeyType>::getHeight()
*/
template<typename DataType, class KeyType>
int BSTree<DataType,KeyType>::getHeightHelper(BSTreeNode* p, 
    int currentLevel) const
{
    static int maxLevel = 0;
    //If the node is null, then check the current level with the max level
    if(p == NULL)
    {
        if(currentLevel > maxLevel)
            maxLevel = currentLevel;
    }
    //Continue left and right
    else
    {
        getHeightHelper(p->left, currentLevel + 1);
        getHeightHelper(p->right, currentLevel + 1);
    }
    return maxLevel;
}

/** Returns the count
* of the number of data items in this BSTree.
* @return An integer representation of how many data items are in this BSTree.
* @see BSTree<DataType,KeyType>::getCountHelper(BSTreeNode*)
*/
template<typename DataType, class KeyType>
int BSTree<DataType,KeyType>::getCount() const
{
    return getCountHelper(root);
}

/** Recursive helper function.
* @param p is the current node to check against.
* @see BSTree<DataType,KeyType>::getCount()
*/
template<typename DataType, class KeyType>
int BSTree<DataType,KeyType>::getCountHelper(BSTreeNode* p) const
{
    //Base case, no node so don't add
    if(p == NULL)
        return 0;
    //Add 1 and go left and go right
    else
        return 1 + getCountHelper(p->left) + getCountHelper(p->right);
}

/** Outputs all keys in this BSTree that are less than searchKey.
* The keys are output in ascending order on one line, separated by spaces.
* searchKey does not need to be a key in this BSTree.
* @post The keys less than searchKey are outputted to the console.
* @param searchKey is the key to compare if this BSTree's keys are less than to.
* @see BSTree<DataType,KeyType>::writeLessThanHelper(const keyType&, 
* BSTreeNode*)
* @todo Function implementation.
*/
template<typename DataType, class KeyType>
void BSTree<DataType,KeyType>::writeLessThan(const KeyType& searchKey) const
{

}

/** Recursive helper function.
* @param searchKey is the key to compare if this BSTree's keys are less than to.
* @param p is the current node to check against.
* @see BSTree<DataType,KeyType>::writeLessThan(const KeyType&)
* @todo Function implementation.
*/
template<typename DataType, class KeyType>
void BSTree<DataType,KeyType>::writeLessThanHelper(const KeyType& searchKey, 
    BSTreeNode* p) const
{

}

//
// Binary Search Tree Node Function Implmentations /////////////////////////////
//

/** The parameterized constructor
* that sets the BSTreeNode's data item to the value nodeDataItem, BSTreeNode's
* previous pointer to the value leftPtr, and BSTreeNode's next pointer to the
* value rightPtr.
* @post This BSTreeNode will be a valid initialized BSTreeNode.
* @param nodeDataItem is the data to be stored within the node.
* @param leftPtr is the pointer to the previous BSTreeNode that this BSTreeNode
* is linked to.
* @param rightPtr is the pointer to the next BSTreeNode that this BSTreeNode is 
* linked to.
*/
template<typename DataType, class KeyType>
BSTree<DataType,KeyType>::BSTreeNode::BSTreeNode(const DataType& nodeDataItem,
    BSTreeNode* leftPtr, BSTreeNode* rightPtr)  : dataItem(nodeDataItem),
    left(leftPtr), right(rightPtr)
{
}