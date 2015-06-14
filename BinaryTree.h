// Binary tree abstract base class
// Created by: Deepika Metkar
// Modified by: Shannon Ladymon

#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"

template<class ItemType>
class BinaryTree
{
protected:
	BinaryNode<ItemType>* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree

public:
	// "admin" functions
 	BinaryTree() {rootPtr = 0; count = 0;}
	virtual ~BinaryTree() {clear();}

	// common functions for all binary trees
 	bool isEmpty() const {return count == 0;}
	int size() const	 {return count;}
	void clear()		 {destroyTree(rootPtr); rootPtr = 0; count = 0;}

	// Print Tree as an Indented List
	void printTreeAsIndentedList(void visit(ItemType*, int level)) const
	{ _printIndented(visit, rootPtr, 0); }

	// abstract functions to be implemented by derived class
	virtual bool insert(ItemType* newData) = 0;
	virtual bool remove(ItemType* data) = 0;

	// search by a unique key
	virtual bool getEntry(ItemType* anEntry, ItemType& returnedItem) const = 0;

    // comparison function to be used in sorting trees by different keys
	int(*compare) (ItemType* argu1, ItemType* argu2);
    
private:
	// delete all nodes from the tree
	void destroyTree(BinaryNode<ItemType>* nodePtr);

	// internal traverse: Print Tree as an Indeted List
	void _printIndented(void visit(ItemType*, int level),
		BinaryNode<ItemType>* nodePtr, int level) const;
};

//////////////////////////////////////////////////////////////////////////


template<class ItemType>
void BinaryTree<ItemType>::_printIndented(void visit(ItemType*, int level),
                                          BinaryNode<ItemType>* nodePtr, int level) const
{
	if (nodePtr != 0)
	{
		_printIndented(visit, nodePtr->getRightPtr(), level + 1);
		ItemType* item = nodePtr->getItem();
		visit(item, level);
		_printIndented(visit, nodePtr->getLeftPtr(), level + 1);
	}
}

template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr != 0)
	{
		destroyTree(nodePtr->getLeftPtr());
		destroyTree(nodePtr->getRightPtr());
		delete nodePtr;
	}
}
#endif
