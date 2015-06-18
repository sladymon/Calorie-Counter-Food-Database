
//*********************************************************************
//                          BINARY NODE CLASS
// Author: Deepika Metkar
// Modified by: Shannon Ladymon
// Class: 22C Spring2015
//
// Description: BinaryNode is a node for use with BinaryTree and
//              BinarySearchTree.  It is templated to work with any
//              class.  It contains a pointer data item of that class
//              and two BinaryNode pointers for its children.
//
// Purpose: This file provides the base class used in our binary search
//              tree.  It holds the pointer to our data (Food).  It
//              does not manage its own data deletion since HashTable
//              has taken responsibility for all Food* deletions in
//              our program.
//
//*********************************************************************

#ifndef _BINARY_NODE
#define _BINARY_NODE

template<class ItemType>
class BinaryNode
{
private:
	ItemType*              item;        // Pointer to data of ItemType class
	BinaryNode<ItemType>* leftPtr;		// Pointer to left child
	BinaryNode<ItemType>* rightPtr;		// Pointer to right child

public:
	// constructors
	BinaryNode() { leftPtr = 0; rightPtr = 0; }
    
    /*destructor - not used in this file to limit deletes of items to hash
    ~BinaryNode()
    {
        delete item;
    }*/
    
	BinaryNode(ItemType* anItem)
	{item = anItem; leftPtr = 0; rightPtr = 0;}
    
	BinaryNode(ItemType* anItem, BinaryNode<ItemType>* left, BinaryNode<ItemType>* right)
	{item = anItem; leftPtr = left; rightPtr = right;}

	// accessors
	ItemType* getItem() const
	{return item;}

	BinaryNode<ItemType>* getLeftPtr() const
	{return leftPtr;}

	BinaryNode<ItemType>* getRightPtr() const
	{return rightPtr;}

    // mutators
    void setItem(ItemType* anItem)
    {item = anItem;}
    
    void setLeftPtr(BinaryNode<ItemType>* left)
    {leftPtr = left;}
    
    void setRightPtr(BinaryNode<ItemType>* right)
    {rightPtr = right;}
    
    // determines if a node has any children
	bool isLeaf() const
	{return (leftPtr == 0 && rightPtr == 0);}
};

#endif
