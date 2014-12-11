/** @file ExpressionTree.cpp
* @mainpage Project 8 (Expression Tree ADT)
* @author Saharath Kleips
* @version 1.00
* @brief This program will create an implmenetation of an Expression Tree using
* a linked tree structure.
* @details The specifications of this project match those of the book C++ Data
* Structures - A Laboratory Course (3rd Edition) Project 8. Mathematical
* expressions form a hierarchy of operations built upon the addition,
* subtraction, multiplication, and division operators. This hieracrhy of
* operations to preform on an expression can be explicitly expressed using a
* binary tree, specifically called a expression tree.
* \n Notes:
* \n Infix notation is when each operator is placed between its operands:
* ( 1 + 3 ) * ( 6 - 4 )
* \n Prefix notation is when each operator is placed immediately before its
* operands: * + 1 3 - 6 4
*/

//
// HEADER FILES ////////////////////////////////////////////////////////////////
//

#include "ExpressionTree.h"
#include <ctype.h>
using namespace std;

//
// Expression Tree Implementations /////////////////////////////////////////////
//

/** The default constructor
* that creates an empty expression tree.
* @post This expression tree will be a valid empty expression tree.
*/
template<typename DataType>
ExprTree<DataType>::ExprTree()
{
    root = NULL;
}

/** The copy constructor
* that initializes this ExprTree to be equivalent to the other ExprTree
* object parameter.
* @pre source is a valid ExprTree.
* @post This ExprTree will be a deep copy of the source ExprTree.
* @param source is the ExprTree that this ExprTree will be made equivalent to.
* @see operator=()
*/
template<typename DataType>
ExprTree<DataType>::ExprTree(const ExprTree& source)
{
    *this = source;
}

/** The overloaded assignment operator
* that sets this ExprTree to be equivalent to the other ExprTree object
* parameter and returns a reference to this object.
* @pre source is a valid ExprTree.
* @post This ExprTree will be a deep copy of the source ExprTree.
* @param source is the ExprTree that this ExprTree will be made equivalent to.
* @return The reference to this ExprTree.
* @see copyHelper()
*/
template<typename DataType>
ExprTree<DataType>& ExprTree<DataType>::operator=(const ExprTree<DataType>& 
    source)
{
    if(this == &source)
        return *this;

    copyHelper(root, source.root);
    return *this;
}

/** Recursive helper function for operator=().
* @post The nodes will be set equal to eachother.
* @param dest is the node to copy the values to.
* @param source is the node to copy the values from.
* @see operator=()
*/
template<typename DataType>
void ExprTree<DataType>::copyHelper(ExprTreeNode *&dest, ExprTreeNode *source)
{
    if(source != NULL)
    {
        ExprTreeNode *left = NULL;  //Store the possible left node
        ExprTreeNode *right = NULL; //Store the possible right node
        copyHelper(left, source->left); //Recursively call left
        copyHelper(right, source->right);   //Recursively call right
        dest = new ExprTreeNode(source->dataItem, left, right); //Copy the node
    }
}

/** The destructor
* that deallocates memory used to store the ExprTree.
* @post This ExprTree will be an empty, deallocated, ExprTree.
* @see clear()
*/
template<typename DataType>
ExprTree<DataType>::~ExprTree()
{
    clear();
}

/** Reads an arithmetic expression in prefix form
* from the keyboard and builds the corresponding expression tree.
* @pre The expression from the keyboard must be a valid arithmetic expression.
* @post This ExprTree will accurately represent the arithmetic expression
* entered.
* @see buildHelper()
*/
template<typename DataType>
void ExprTree<DataType>::build()
{
    buildHelper(root);
}

/** Recursive helper function for the build() function.
* It takes a reference to a pointer to an expression tree node so that if a new
* node should be added to the tree, it can be allocated and added by assigning
* the newly allocated node to the node parameter.
* @parm node is the node to put data into.
* @see build()
*/
template<typename DataType>
void ExprTree<DataType>::buildHelper(ExprTreeNode *&node)
{
    char c;
    cin >> c;
    node = new ExprTreeNode(c, NULL, NULL); //The node is the character entered

    //If it's an operator, recursively call -- digits are leafs
    if(c == '+' || c == '-' || c == '*' || c == '/')
    {
        buildHelper(node->left);    //Recursively call left
        buildHelper(node->right);   //Recursively call right
    }
}

/** Outputs the expression
* corresponding to the value of the tree in fully parenthesized infix form.
* @pre This ExprTree represents a valid arithmetic expression.
* @post The expression will be outputed to the console.
* @see expressionHelper()
*/
template<typename DataType>
void ExprTree<DataType>::expression() const
{
    expressionHelper(root);
}

/** Recursive helper function for expression() function.
* @see expression()
*/
template<typename DataType>
void ExprTree<DataType>::expressionHelper(ExprTreeNode *p) const
{
    //Base case, if it's a digit, simply print out the number
    if(isdigit(p->dataItem))
    {
        cout << p->dataItem;
        return;
    }
    //Build the parenthesis around the expression
    cout << '(';
    expressionHelper(p->left);  //Recursively call left
    cout << p->dataItem;
    expressionHelper(p->right); //Recursively call right
    cout << ')';
}

/** Returns the value
* of the corresponding arithmetic expression.
* @pre This ExprTree is not empty.
* @return The value of the arithmetic expression.
* @throw The ExprTree is empty.
* @see evalHelper()
*/
template<typename DataType>
DataType ExprTree<DataType>::evaluate() const throw (logic_error)
{
    if(root == NULL)
        throw("ExprTree is empty.");
    return evalHelper(root);
}

/** Recursive helper function for evaluate() function.
* @see evaluate()
*/
template<typename DataType>
DataType ExprTree<DataType>::evalHelper(ExprTreeNode *p) const
{
    //Switch statement to determine the proper operator
    switch(p->dataItem)
    {
        //Case is addition
        case '+':
            return (evalHelper(p->left) + evalHelper(p->right));
            break;
        //Case is subtraction
        case '-':
            return (evalHelper(p->left) - evalHelper(p->right));
            break;
        //Case is multiplication
        case '*':
            return (evalHelper(p->left) * evalHelper(p->right));
            break;
        //Case is division
        case '/':
            return (evalHelper(p->left) / evalHelper(p->right));
            break;
        //Case is a digit, so convert from char to int
        default:
            return (p->dataItem - '0');
            break;
    }
}

/** Removes all the data items
* in the expression tree.
* @post This ExprTree will be an empty, deallocated, ExprTree.
* @see clearHelper()
*/
template<typename DataType>
void ExprTree<DataType>::clear()
{
    clearHelper(root);
}

/** Recursive helper function for clear() function.
* @see clear()
*/
template<typename DataType>
void ExprTree<DataType>::clearHelper(ExprTreeNode *&p)
{
    //Node is not null, so must be deleted
    if(p != NULL)
    {
        clearHelper(p->left);   //Recursively call left
        clearHelper(p->right);  //Recursively call right
        delete p;   //Delete the node
        p = NULL;   //Set to null for dangling pointer
    }
}

/** Commutes the operates
* for every arithmetic operator in the expression tree.
* @post Every operator in ExprTree is commuted.
* @see commuteHelper()
*/
template<typename DataType>
void ExprTree<DataType>::commute()
{
    commuteHelper(root);
}

/** Recursive helper function for commute() function.
* @see commute()
*/
template<typename DataType>
void ExprTree<DataType>::commuteHelper(ExprTreeNode *&p)
{
    //Base case, cannot commute if node is null
    if(p == NULL)
        return;
    //If the character is an operator, then switch the nodes
    if(!isdigit(p->dataItem))
    {
        ExprTreeNode* temp = p->left;
        p->left = p->right;
        p->right = temp;
    }
    commuteHelper(p->left);     //Recursively call left
    commuteHelper(p->right);    //Recursively call right
}

/** Compares the expression tree to another expression tree
* for equivalence. If the two trees are equivalent, then returns true. Otherwise
* returns false.
* @pre Both trees are valid expression trees
* @param source is the ExprTree to compare to this ExprTree
* @return True if the trees are equivalent. False if they are not equivalent.
* @see isEquivHelper()
*/
template<typename DataType>
bool ExprTree<DataType>::isEquivalent(const ExprTree& source) const
{
    return isEquivHelper(root, source.root);
}

/** Recursive helper function for isEquivalent() function.
* @see isEquivalent()
*/
template<typename DataType>
bool ExprTree<DataType>::isEquivHelper(ExprTreeNode *dest, 
    ExprTreeNode *source) const
{
    //It's equivalent if the nodes are empty
    if(dest == NULL && source == NULL)
        return true;
    //The nodes aren't empty
    else if (dest != NULL && source != NULL)
    {
        //The two data items are equivalent
        if(dest->dataItem == source->dataItem)
        {
            //Check if non-swap is equivalent
            if(isEquivHelper(dest->left, source->left) &&
                isEquivHelper(dest->right, source->right))
                return true;
            //Check is swap is equivalent
            else if (isEquivHelper(dest->left, source->right) &&
                isEquivHelper(dest->right, source->left))
            {
                //Addition and multiplication can commute
                if(dest->dataItem == '+' || dest->dataItem == '*')
                    return true;
                //Subtraction and division cannot commute
                else
                    return false;
            }
            else
                return false;
        }
    }
    return false;
}

/** Outputs an expression tree
* with its branches orientated from left (root) to right (leaves). The tree
* output is rotated counterclockwise ninty degrees from the conventional
* orientation. If the tree is empty, it outputs "Empty tree." This function is
* for testing purposes only and assumes arithmetic expressions contain only
* single-digit, non-negative integers, and the arithmetic operators for
* addition, subtraction, multiplication, and division.
* @post The expression tree will be outputed to the console.
*/
template<typename DataType>
void ExprTree<DataType>::showStructure() const
{
    if ( root == NULL )
       cout << "Empty tree" << endl;
    else
    {
       cout << endl;
       showHelper(root,1);
       cout << endl;
    }
}

/** Recursive helper for showStructure() function.
* Outputs the subtree whose root node is pointed to by p. Parameter level is the
* level of this node within the expression tree.
* @param p is the root node of the subtree.
* @param level is the current depth of the subtree.
* @post The subtree will be outputed to the console.
*/
template<typename DataType>
void ExprTree<DataType>::showHelper(ExprTreeNode *p, int level) const
{
    int j;   // Loop counter

     if ( p != 0 )
     {
        showHelper(p->right,level+1);        // Output right subtree
        for ( j = 0 ; j < level ; j++ )   // Tab over to level
            cout << "\t";
        cout << " " << p->dataItem;        // Output dataItem
        if ( ( p->left != 0 ) &&          // Output "connector"
             ( p->right != 0 ) )
           cout << "<";
        else if ( p->right != 0 )
           cout << "/";
        else if ( p->left != 0 )
           cout << "\\";
        cout << endl;
        showHelper(p->left,level+1);         // Output left subtree
     }
}

/** The parameterized constructor
* that sets ExprTreeNode's data item, left pointer, and right pointer.
* @post This ExprTreeNode will be a valid ExprTreeNode.
* @param elem is the character data to store within the node.
* @param leftPtr is the left branch within the node.
* @param rightPtr is the right branch within the node.
*/
template<typename DataType>
ExprTree<DataType>::ExprTreeNode::ExprTreeNode(char elem, ExprTreeNode *leftPtr,
    ExprTreeNode *rightPtr)
{
    dataItem = elem;
    left = leftPtr;
    right = rightPtr;
}