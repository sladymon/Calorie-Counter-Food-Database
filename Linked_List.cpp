//
//
//  Created by Wendy Martell on 6/10/15.
//  Copyright (c) 2015 ___MARTELL___. All rights reserved.
//
// Implementation file for the FoodList Overfloww from the hashtable
#include <iostream>  // For cout and NULL
#include <iomanip>   // For setw()
#include <string>
#include <cstring>   // For strcmp()
#include "Linked_List.h"
#include "Food.h"

//Author: Wendy Martell

using namespace std;

//**************************************************
// Constructor                                     *
//**************************************************
Linked_List::Linked_List() // dummy node
{
    head = new ListNode;
    head->next = NULL;
    count = 0;
}

//**************************************************
// displayList shows the value                     *
// stored in each node of the linked list          *
// pointed to by head.                             *
//**************************************************

void Linked_List::displayList() const
{
    ListNode *nodePtr;  // To move through the list
    
    // Position nodePtr at the head of the list.
    nodePtr = head->next;
    
    cout << "Overload - Food " << endl;
    
    // While nodePtr points to a node, traverse the list.
    while (nodePtr)
    {
        string toy  = nodePtr->food->getName();
        
        // Display the value in this node in columns.
        cout << toy<< endl;
        
        // Move to the next node.
        nodePtr = nodePtr->next;
    }
    
    cout<< "\nTotal in Overload : " << count << endl;
}

//**************************************************
// The searchNode function searches for a node     *
// with foodData.code. If the node was found       *
// then true is returned and the Food data of      *
// node found is returned in foodData. If the node *
// was not found, then false is returned and       *
// foodData reference variable is unchanged.       *
//**************************************************
bool Linked_List::searchNode(Food &foodData)
{
    ListNode *nodePtr;            // To traverse the list
    
    // Position nodePtr at the head of list.
    nodePtr = head->next;
    
    if (nodePtr==0) {
        cout << "Empty" <<endl;
    }
    if (nodePtr!=0) {
        cout << "TESTING SEARCH : "; /// delete
    }
    
     // Skip all nodes that doesn't matches code of nodeData
    while (nodePtr != NULL && nodePtr->food->getName()!= foodData.getName())
    {
        // Move to the next node
        nodePtr = nodePtr->next;
    }
    
    // If nodePtr is NULL (not found)
   
    if (!nodePtr)
        return false;
    
    // Load nodeData with data from the found node
    foodData = *nodePtr->food;
    
    return true;
}

//**************************************************
// The insertNode function inserts a node with     *
// countryIn copied to its food member.         *
//**************************************************

void Linked_List::insertNode(Food* foodIn)
{
    ListNode *newNode;             // A new node
    
    newNode = new ListNode;
    newNode->food = foodIn;
    
    // Position nodePtr at the first item.
    newNode->next = head->next;
    head->next = newNode;
    
    count++;
           
}

//**************************************************
// The deleteNode function searches for a node     *
// with the same code in foodData. If node is found*
// it is deleted from the list and from memory. The*
// function returns true if node was deleted & the *
// node to delete food information is returned     *
// in foodData. If node to delete is not found (or *
// there is nothing to delete) then a false is     *
// returned.                                       *
//**************************************************

bool Linked_List::deleteNode(Food *foodData)
{
    ListNode *nodePtr;       // To traverse the list
    ListNode *previousNode;  // To point to the previous node
    
    // Initialize nodePtr to head of list
    nodePtr = head->next;
    previousNode = head;
    
    // Skip all nodes whose code is not equal to the code pointed by pDeleteCode.
    while (nodePtr != NULL && nodePtr->food->getName()!= foodData->getName())
    {
        previousNode = nodePtr;
        nodePtr = nodePtr->next;
    }
    
    // If node-to-delete not found OR no nodes
    if (!nodePtr)
        return false;
    
        foodData = nodePtr->food;  // return the deleted data
        previousNode->next = nodePtr->next;
        delete nodePtr;
    
    count--;
    return true;
}

//**************************************************
// Destructor                                      *
// This function deletes every node in the list.   *
//**************************************************

Linked_List::~Linked_List()
{
    ListNode *nodePtr;   // To traverse the list
    ListNode *nextNode;  // To point to the next node
    
    // Position nodePtr at the head of the list.
    nodePtr = head;
    
    // While nodePtr is not at the end of the list...
    while (nodePtr != NULL)
    {
        // Save a pointer to the next node.
        nextNode = nodePtr->next;
        
        // Delete the current node.
        delete nodePtr;
        
        // Position nodePtr at the next node.
        nodePtr = nextNode;
    }
}