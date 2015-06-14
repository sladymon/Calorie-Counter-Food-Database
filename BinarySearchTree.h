// Binary Search Tree ADT
// Created by: Deepika Metkar
// Modified by: Shannon Ladymon

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{
private:

	using BinaryTree<ItemType>::rootPtr;
	using BinaryTree<ItemType>::count;

	// internal insert node: insert newNode in nodePtr subtree
	BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);

	// internal remove node: locate and delete target node under nodePtr subtree
	BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, ItemType* target, bool& success);
    
    // internal remove node: locate and delete target node under nodePtr subtree
    //based on a different comparison function
    BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, ItemType* target, bool& success,
                                  int(*cmp) (ItemType* argu1, ItemType* argu2));

	// delete target node from tree, called by internal remove node
	BinaryNode<ItemType>* _unlinkNode(BinaryNode<ItemType>* targetNodePtr, ItemType& successor);

	// remove the leftmost node in the left subtree of nodePtr
	BinaryNode<ItemType>* _removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType& successor);

	// search for target node
	BinaryNode<ItemType>* _findNode(BinaryNode<ItemType>* treePtr, ItemType* target) const;

	bool _printTree(void(*display)(ItemType* item), BinaryNode<ItemType>* node);

	int(*compare) (ItemType* argu1, ItemType* argu2);


public:
    
    //Constructor that takes a comparison function
    BinarySearchTree(int(*cmp) (ItemType* argu1, ItemType* argu2))
    {
        rootPtr = 0;
        count = 0;
        compare = cmp;
    }
    
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

	bool printTreeInOrder(void(*display)(ItemType* item));  //FIXME: Where is this called?  Anywhere?

};


///////////////////////// public function definitions ///////////////////////////

template<class ItemType>
bool BinarySearchTree<ItemType>::printTreeInOrder(void(*display)(ItemType* item))
{
	if (rootPtr != 0) {
		_printTree(display);
	}
	return true;
}

// search function without using recursion (with iterations)
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

template<class ItemType>
bool BinarySearchTree<ItemType>::insert(ItemType* newEntry)
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
	rootPtr = _insert(rootPtr, newNodePtr);
	count++;
	return true;
}


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

// remove a node if found based on a different comparison function
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

template<class ItemType>
bool BinarySearchTree<ItemType>::_printTree(void(*display)(ItemType* item), BinaryNode<ItemType>* node)
{
	if (node != 0) {
		printTree(display, node->getLeftPtr());
		display(node->getItem());
		printTree(display, node->getRightPtr());
	}
}

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
