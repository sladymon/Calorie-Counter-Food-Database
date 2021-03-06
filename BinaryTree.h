//*********************************************************************
//                          BINARY TREE CLASS
// Author: Deepika Metkar
// Modified by: Shannon Ladymon
// Class: 22C Spring2015
//
// Description: BinaryTree holds a binary tree with BinaryNodes.  It
//              is templated to work with any class.  It contains a
//              pointer to the root BinaryNode and maintains a count.
//              It expects to work with pointer data.
//
// Purpose: This file is the base parent class for our binary search
//              tree.  It handles functions that are not based on
//              tree being sorted, such as printing the tree as an
//              indented list.  It also destroys the tree once the
//              destructor is called and deletes the nodePtrs (but
//              note that it will not delete the Food*)
//
//*********************************************************************

#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
#include "HashTable.h"

template<class ItemType>
class BinaryTree
{
protected:
	BinaryNode<ItemType>* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree

public:
	// constructor/destructor
 	BinaryTree() {rootPtr = 0; count = 0;}
	virtual ~BinaryTree() {clear();}

	// common functions for all binary trees
 	bool isEmpty() const {return count == 0;}
	int size() const	 {return count;}
	void clear()		 {_destroyTree(rootPtr); rootPtr = 0; count = 0;}

	// abstract functions to be implemented by derived class
	virtual bool insert(ItemType* newData) = 0;
	virtual bool remove(ItemType* data) = 0;

	// search by a unique key
	virtual bool getEntry(ItemType* anEntry, ItemType& returnedItem) const = 0;
    virtual void printAllMatches(ItemType* target, void visit(ItemType &)) const = 0;

    // comparison function to be used in sorting trees by different keys
	int(*compare) (ItemType* argu1, ItemType* argu2);
    
    // print tree as an indented list
    void printTreeAsIndentedList(void visit(ItemType*, int level)) const
    { _printIndented(visit, rootPtr, 0); }
    
    // traverses tree to rehash table
    void rehashTraverse(void visit(ItemType*, HashTable*), HashTable* newHash)
    {_rehashTraverse(visit, rootPtr, newHash);}
    
private:
	// delete all nodes from the tree
	void _destroyTree(BinaryNode<ItemType>* nodePtr);

	// internal traverse: print tree as an indeted list
	void _printIndented(void visit(ItemType*, int level),
                        BinaryNode<ItemType>* nodePtr, int level) const;
    
    // internal traverse of tree to rehash table
    void _rehashTraverse(void visit(ItemType*, HashTable*),
                         BinaryNode<ItemType>* nodePtr, HashTable* newHash);
};

//////////////////////////////////////////////////////////////////////////

//*********************************************************************
// Author - Deepika Metkar
// destroyTree - internal recursive function to delete all nodes in tree
// @param nodePtr - BinaryNode ptr to root of current subtree
//*********************************************************************
template<class ItemType>
void BinaryTree<ItemType>::_destroyTree(BinaryNode<ItemType>* nodePtr)
{
    if (nodePtr != 0)
    {
        _destroyTree(nodePtr->getLeftPtr());
        _destroyTree(nodePtr->getRightPtr());
        delete nodePtr;
    }
}

//*********************************************************************
// Author - Deepika Metkar
// _printIndented - internal recursive traverse of binary tree to
//          print all nodes in tree based on level with indenting.
// @param visit - display function to be called on each node
// @param nodePtr - BinaryNode ptr to root of current subtree
// @param level - int of current level in tree
//*********************************************************************
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

//*********************************************************************
// Author - Shannon Ladymon
// _rehashTraverse - internal recursive traverse of binary tree to
//          rehash - will use visit function on each Food*
// @param visit - function to be called on each node
// @param nodePtr - BinaryNode ptr to root of current subtree
// @param newHash - HashTable* to the new hash table to be filled
//*********************************************************************
template<class ItemType>
void BinaryTree<ItemType>::_rehashTraverse(void visit(ItemType*, HashTable*),
                     BinaryNode<ItemType>* nodePtr, HashTable* newHash)
{
    if (nodePtr != 0)
    {
        _rehashTraverse(visit, nodePtr->getRightPtr(), newHash);
        ItemType* item = nodePtr->getItem();
        visit(item, newHash);
        _rehashTraverse(visit, nodePtr->getLeftPtr(), newHash);
    }
}


#endif
