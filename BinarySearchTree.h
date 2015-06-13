// Binary Search Tree ADT
// Created by: Deepika Metkar

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{
private:

	using BinaryTree<ItemType>::rootPtr; //TODO: added by Shannon
	using BinaryTree<ItemType>::count;//TODO: added by Shannon


	// internal insert node: insert newNode in nodePtr subtree
	BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);

	// internal remove node: locate and delete target node under nodePtr subtree
	BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool & success);

	// delete target node from tree, called by internal remove node
	BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);

	// remove the leftmost node in the left subtree of nodePtr
	BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor);

	// search for target node
	BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, ItemType & target) const;

	bool printTree(void(*display)(ItemType item));

	int(*compare) (ItemType argu1, ItemType argu2);


public:
	// insert a node at the correct location
    bool insert(const ItemType & newEntry);

	// remove a node if found
	bool remove(const ItemType & anEntry);

	// find a target node
	bool getEntry(ItemType & target, ItemType & returnedItem) const;

	// search function without using recursion (with iterations)
	BinaryNode<ItemType>* search(ItemType & target) const;

	bool printTreeInOrder(void(*display)(ItemType item));

	BinarySearchTree(int(*cmp) (ItemType argu1, ItemType argu2))
	{
		rootPtr = 0;
		count = 0;
		compare = cmp;
	}
};


///////////////////////// public function definitions ///////////////////////////

template<class ItemType>
bool printTreeInOrder(void(*display)(ItemType item))
{
	if (rootPtr != 0) {
		printTree(display);
	}
	return true;
}

// search function without using recursion (with iterations)
template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(ItemType& anEntry, ItemType & returnedItem) const
{
	BinaryNode<ItemType> * targetNode = findNode(rootPtr, anEntry);
	if (targetNode != 0)
	{
		returnedItem = targetNode->getItem();
		return true;
	}
	return false;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType & newEntry)
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
	rootPtr = _insert(rootPtr, newNodePtr);
	count++;
	return true;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType & target)
{
	bool isSuccessful = false;
	rootPtr = _remove(rootPtr, target, isSuccessful);
	count--; //TODO: Shannon added this
	return isSuccessful;
}

//////////////////////////// private functions ////////////////////////////////////////////

template<class ItemType>
bool printTree(void(*display)(ItemType item), BinaryNode<ItemType> node)
{
	if (node != null) {
		printTree(display, node.getLeftPtr());
		display(node.getItem());
		printTree(display, node.getRightPtr());
	}
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,
                                                          BinaryNode<ItemType>* newNodePtr)
{
	if (nodePtr == 0)
		return newNodePtr;
	else if (compare(nodePtr->getItem(), newNodePtr->getItem()) < 0)
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
	ItemType target, bool & success)
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
		nodePtr = deleteNode(nodePtr);
		success = true;
	}
	return nodePtr;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr->isLeaf())
	{
		delete nodePtr;
		nodePtr = 0;
		return nodePtr;
	}
	else if (nodePtr->getLeftPtr() == 0)
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else if (nodePtr->getRightPtr() == 0)
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else
	{
		ItemType newNodeValue;
		nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
		nodePtr->setItem(newNodeValue);
		return nodePtr;
	}
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
                                                                     ItemType & successor)
{
	if (nodePtr->getLeftPtr() == 0)
	{
		successor = nodePtr->getItem();
		return deleteNode(nodePtr);
	}
	else
	{
		nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
		return nodePtr;
	}
}


template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* nodePtr,
                                                           ItemType & target) const
{
	if (nodePtr == 0)
		return 0;
	else if (compare(nodePtr->getItem(), target) > 0)
		return findNode(nodePtr->getRightPtr(), target);
	else if (compare(nodePtr->getItem(), target) < 0)
		return findNode(nodePtr->getLeftPtr(), target);
	else
		return nodePtr;
}
#endif
