//*********************************************************************
//                          BINARY SEARCH TREE CLASS
// Author: Deepika Metkar
// Modified by: Shannon Ladymon
// Description: BinarySearchTree is a child of BinaryTree.  It holds a
//              sorted binary tree.  It is templated to work with any
//              class. It uses its parent's data items (rootPtr and
//              count).  It expects to work with pointer data.  The
//              constructor allows specification of the comparison
//              function to determine how to sort the tree.
//
//*********************************************************************

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{
private:

	using BinaryTree<ItemType>::rootPtr;
	using BinaryTree<ItemType>::count;
    
    // comparison function passed in on construction
    int(*compare) (ItemType* argu1, ItemType* argu2);

	// internal insert node: insert newNode in nodePtr subtree
	BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);

	// internal remove node: locate and delete target node under nodePtr subtree
	BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, ItemType* target, bool& success);
    
    // internal remove node: locate and delete target node under nodePtr subtree
    //based on a different comparison function
    BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, ItemType* target, bool& success,
                                  int(*cmp) (ItemType* argu1, ItemType* argu2));

	// unlink target node from tree, called by internal remove node
	BinaryNode<ItemType>* _unlinkNode(BinaryNode<ItemType>* targetNodePtr, ItemType& successor);

	// remove the leftmost node in the left subtree of nodePtr
	BinaryNode<ItemType>* _removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType& successor);

	// search for target node
	BinaryNode<ItemType>* _findNode(BinaryNode<ItemType>* treePtr, ItemType* target) const;
    
    // internal print all key matches
    void _printAllMatches(ItemType* target, void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;

public:
    
    // constructor that takes a comparison function
    BinarySearchTree(int(*cmp) (ItemType* argu1, ItemType* argu2));

	// insert a node at the correct location
    bool insert(ItemType* newEntry);

	// remove a node if found
	bool remove(ItemType* target);
    
    // remove a node if found based on a different comparison function
    bool remove(ItemType* anEntry, int(*cmp) (ItemType* argu1, ItemType* argu2));

	// find a target node
	bool getEntry(ItemType* target, ItemType& returnedItem) const;

	// search function without using recursion (with iterations)
	BinaryNode<ItemType>* search(ItemType* target) const;
    
    //prints all key matches
    void printAllMatches(ItemType* target, void visit(ItemType &)) const;

};


///////////////////////// public function definitions ///////////////////////////

//*********************************************************************
// Author - Deepika Metkar
// Constructor - takes a comparison function as a parameter in order
//          to determine how the tree is sorted
// @param cmp - comparison function to determine sorting method
//*********************************************************************
template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(int(*cmp) (ItemType* argu1, ItemType* argu2))
{
    rootPtr = 0;
    count = 0;
    compare = cmp;
}


//*********************************************************************
// Author - Shannon Ladymon
// printAllMatches - prints all matches to the key
// @param display - function to use to display each node
//*********************************************************************

template<class ItemType>
void BinarySearchTree<ItemType>::printAllMatches(ItemType* target, void visit(ItemType &)) const
{
    if (rootPtr != 0) {
        _printAllMatches(target, visit, rootPtr);
    }
}


//*********************************************************************
// Author - Deepika Metkar
// getEntry - finds an entry in the tree and changes the reference
//          parameter to contain its information.
// @param anEntry - a pointer to an entry object with the key to search
//          for
// @param returnedItem - a reference parameter to hold the data for the
//          found item
// @return - true if found
//*********************************************************************
template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(ItemType* anEntry, ItemType & returnedItem) const
{
	BinaryNode<ItemType>* targetNode = _findNode(rootPtr, anEntry);
	if (targetNode != 0)
	{
        returnedItem = *(targetNode->getItem());
		return true;
	}
	return false;
}

//*********************************************************************
// Author - Deepika Metkar
// insert - inserts an item into the tree in correct sorted order
// @param newEntry - a pointer to the entry to be added
// @return - true for added
//*********************************************************************
template<class ItemType>
bool BinarySearchTree<ItemType>::insert(ItemType* newEntry)
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
	rootPtr = _insert(rootPtr, newNodePtr);
	count++;
	return true;
}

//*********************************************************************
// Author - Deepika Metkar
// remove - removes an item from the tree
// @param target - a pointer to an item with the same key as the entry
//          to be removed
// @return - true if able to find and remove
//*********************************************************************
template<class ItemType>
bool BinarySearchTree<ItemType>::remove(ItemType* target)
{
    bool isSuccessful = false;
	rootPtr = _remove(rootPtr, target, isSuccessful);
    if (isSuccessful)
    {
        count--;
    }
	return isSuccessful;
}

//*********************************************************************
// Author - Shannon Ladymon
// remove - overloaded remove function which searches the tree based on
//          a comparison/key different from the default for this tree
//          (used for deleting correct item in a tree based on a
//          non-unique, secondary key)
// @param target - a pointer to an item with the same key as the entry
//          to be removed
// @param cmp - the comaprison to be used for this remove
// @return - true if able to find and remove
//*********************************************************************
template<class ItemType>
bool BinarySearchTree<ItemType>::remove(ItemType* target, int(*cmp) (ItemType* argu1, ItemType* argu2))
{
    bool isSuccessful = false;
    rootPtr = _remove(rootPtr, target, isSuccessful, cmp); //call with different internal cmp
    if (isSuccessful)
    {
        count--;
    }
    return isSuccessful;
}

//////////////////////////// private functions ////////////////////////////////////////////

//*********************************************************************
// Author - Shannon Ladymon
// _printAllMatches - internal recursive print all key matches
// @param display - function to use to display each node
// @param node - a BinaryNode pointer to the current subtree
//*********************************************************************

template<class ItemType>
void _printAllMatches(ItemType* target, void visit(ItemType &), BinaryNode<ItemType>* nodePtr)
{
    if (nodePtr != 0) {
        _printTree(visit, nodePtr->getLeftPtr());
        if (compare(nodePtr->getItem(), target) == 0)
        {
            visit(*(nodePtr->getItem()));
        }
        _printTree(visit, nodePtr->getRightPtr());
    }
}

//*********************************************************************
// Author - Deepika Metkar
// _insert - internal recursive function to insert entry in tree in
//          sorted order
// @param nodePtr - a BinaryNode pointer to the current subtree
// @param newNodePtr - a BinaryNode pointer to the item to be inserted
// @return - a BinaryNode pointer to the current subtree (with any
//          modifications)
//*********************************************************************
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,
                                                          BinaryNode<ItemType>* newNodePtr)
{
	if (nodePtr == 0)
		return newNodePtr;
	else if (compare(nodePtr->getItem(), newNodePtr->getItem()) > 0)
	{
		BinaryNode<ItemType>* tempPtr = _insert(nodePtr->getLeftPtr(), newNodePtr);
		nodePtr->setLeftPtr(tempPtr);
	}
	else
	{
		BinaryNode<ItemType>* tempPtr = _insert(nodePtr->getRightPtr(), newNodePtr);
		nodePtr->setRightPtr(tempPtr);
	}
	return nodePtr;
}

//*********************************************************************
// Author - Deepika Metkar
// _remove - internal recursive function to remove an item from the
//          tree without losing sorted order
// @param nodePtr - a BinaryNode pointer to the current subtree
// @param target - a pointer to an item with the key to be removed
// @param success - a reference parameter to indicate if the remove
//          was successful
// @return - a BinaryNode pointer to the current subtree (with any
//          modifications)
//*********************************************************************
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr,
	ItemType* target, bool& success)
{
    if (nodePtr == 0)
	{
        success = false;
		return 0;
	}
	if (compare(nodePtr->getItem(), target) > 0)
        nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
	else if (compare(nodePtr->getItem(), target) < 0)
        nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
	else
	{
        ItemType toDelete;
        nodePtr = _unlinkNode(nodePtr, toDelete);
        success = true;
	}
	return nodePtr;
}

//*********************************************************************
// Author - Shannon Ladymon
// _remove - overloaded internal recursive function to remove an item from the
//          tree using a different comparison/key than the default
//          (used for deleting correct item in a tree based on a
//          non-unique, secondary key)
// @param nodePtr - a BinaryNode pointer to the current subtree
// @param target - a pointer to an item with the key to be removed
// @param success - a reference parameter to indicate if the remove
//          was successful
// @param cmp - the comaprison to be used for this remove
// @return - a BinaryNode pointer to the current subtree (with any
//          modifications)
//*********************************************************************
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr,
                        ItemType* target, bool& success, int(*cmp) (ItemType* argu1, ItemType* argu2))
{
    if (nodePtr == 0)
    {
        success = false;
        return 0;
    }
    
    if (cmp(nodePtr->getItem(), target) == 0) //use cmp parameter to compare
    {
        ItemType toDelete;
        nodePtr = _unlinkNode(nodePtr, toDelete);
        success = true;
    }
    else
    {
        nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success, cmp));
        if (!success)
        {
            nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success, cmp));
        }
    }
    
    return nodePtr;
}

//*********************************************************************
// Author - Deepika Metkar
// _unlinkNode - internal recursive funciont that unlinks a node from
// the tree without deleting the node
// @param nodePtr - a BinaryNode pointer to the current subtree
// @param toRemove - a reference parameter to store the item that is
//          removed from the tree (need to save so that can be
//          reinserted elsewhere if necessary)
// @return - a BinaryNode pointer to the current subtree (with any
//          modifications)
//*********************************************************************
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_unlinkNode(BinaryNode<ItemType>* nodePtr, ItemType& toRemove)
{
    toRemove = *(nodePtr->getItem()); //Set reference parameter to node that needs to be removed
    if (nodePtr->isLeaf())
	{
		return 0;
	}
	else if (nodePtr->getLeftPtr() == 0)
	{
		return nodePtr->getRightPtr();
	}
	else if (nodePtr->getRightPtr() == 0)
	{
		return nodePtr->getLeftPtr();
	}
	else
	{
		ItemType* newNodeValue = new ItemType();
		nodePtr->setRightPtr(_removeLeftmostNode(nodePtr->getRightPtr(), *newNodeValue));
		nodePtr->setItem(newNodeValue);
		return nodePtr;
	}
    
}

//*********************************************************************
// Author - Deepika Metkar
// _removeLeftmostNode - internal recursive function to find and remove
//          the leftmost node in a subtree so as to maintain sorted
//          order
// @param nodePtr - a BinaryNode pointer to the current subtree
// @param successor - a reference parameter to store the item that is
//          removed from the tree (need to save so that can be
//          reinserted elsewhere if necessary)
// @return - a BinaryNode pointer to the current subtree (with any
//          modifications)
//*********************************************************************
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
                                                                     ItemType& successor)
{
	if (nodePtr->getLeftPtr() == 0)
	{
        return _unlinkNode(nodePtr, successor);
	}
	else
	{
		nodePtr->setLeftPtr(_removeLeftmostNode(nodePtr->getLeftPtr(), successor));
		return nodePtr;
	}
}


//*********************************************************************
// Author - Deepika Metkar
// _findNode - internal recursive function to find a node in the tree
// @param nodePtr - a BinaryNode pointer to the current subtree
// @param target - a pointer to an item with the key to be found
// @return - a BinaryNode pointer to the current subtree (with any
//          modifications)
//*********************************************************************
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_findNode(BinaryNode<ItemType>* nodePtr,
                                                           ItemType* target) const
{
	if (nodePtr == 0)
		return 0;
	else if (compare(nodePtr->getItem(), target) < 0)
		return _findNode(nodePtr->getRightPtr(), target);
	else if (compare(nodePtr->getItem(), target) > 0)
		return _findNode(nodePtr->getLeftPtr(), target);
	else
		return nodePtr;
}
#endif
