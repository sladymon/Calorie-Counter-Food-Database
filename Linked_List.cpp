//*********************************************************************
//                              LINKED LIST CLASS
//
// Author: Wendy Martell
// Description: LinkedList is a singlely-linked list with a dummy node
//              which contains a pointer the the head of the list, a
//              count of items in the list, and ListNodes, which each
//              hold a Food pointer and a pointer to the next item in
//              the list.
//
//*********************************************************************

#include <iostream>  // For cout and NULL
#include <iomanip>   // For setw()
#include <string>
#include <cstring>   // For strcmp()
#include "Linked_List.h"
#include "Food.h"
using namespace std;


//*********************************************************************
// Author - Wendy Martell
// Constructor - initializes the dummy node at head and sets count to 0
//*********************************************************************
Linked_List::Linked_List() // dummy node
{
    head = new ListNode;
    head->next = NULL;
    count = 0;
}

//*********************************************************************
// Author - Wendy Martell
// Destructor - deletes all the nodes in the list
//*********************************************************************

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

//*********************************************************************
// Author - Wendy Martell
// displayList - shows the value stored in each node of the linked list
//          pointed to by head.
//*********************************************************************

void Linked_List::displayList() const
{
    ListNode *nodePtr;  // To move through the list
    
    // Position nodePtr at the head of the list.
    nodePtr = head->next;
    
    // While nodePtr points to a node, traverse the list.
    while (nodePtr)
    {
        // Display the value in this node in columns.
        cout << "\t" << nodePtr->food->getName() << endl;
        
        // Move to the next node.
        nodePtr = nodePtr->next;
    }
}

//*********************************************************************
// Author - Wendy Martell
// searchNode - searches for a node with matching food name.  If the
//          node is found, the reference parameter is updated with the
//          food information.
// @param foodData - reference parameter with food name to find
// @return - true if found
//*********************************************************************
bool Linked_List::searchNode(Food& foodData)
{
    ListNode *nodePtr;            // To traverse the list
    
    // Position nodePtr at the head of list.
    nodePtr = head->next;
    
    if (nodePtr==0) {
        //cout << "Empty" <<endl;
        return false;
    }
    
     // Skip all nodes that doesn't matches code of nodeData
    while (nodePtr != NULL && nodePtr->food->getName()!= foodData.getName())
    {
        // Move to the next node
        nodePtr = nodePtr->next;
    }
   
    if (!nodePtr)
        return false;
    
    // Load nodeData with data from the found node
    foodData = *(nodePtr->food);
    
    return true;
}


//*********************************************************************
// Author - Wendy Martell
// insertNode - inserts a node into the beginning of the linked list
//
// @param foodIn - a pointer to the food to be inserted
//*********************************************************************

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

//*********************************************************************
// Author - Wendy Martell
// deleteNode - searches for a node in the list with matching food
//          name.  If found, deletes the node and modifies the
//          reference parameter with the information for the deleted
//          food.
// @param foodData - reference parameter with the food to delete
// @return - true if found and deleted.
//*********************************************************************

bool Linked_List::deleteNode(Food& foodData)
{
    ListNode *nodePtr;       // To traverse the list
    ListNode *previousNode;  // To point to the previous node
    
    // Initialize nodePtr to head of list
    nodePtr = head->next;
    previousNode = head;
    
    // Skip all nodes whose code is not equal to the code pointed by pDeleteCode.
    while (nodePtr != NULL && nodePtr->food->getName()!= foodData.getName())
    {
        previousNode = nodePtr;
        nodePtr = nodePtr->next;
    }
    
    // If node-to-delete not found OR no nodes
    if (!nodePtr)
        return false;
    
        foodData = *nodePtr->food;  // return the deleted data
        previousNode->next = nodePtr->next;
        delete nodePtr->food;
        delete nodePtr;
    
    count--;
    return true;
}

//*********************************************************************
// Author - Shannon Ladymon
// traverseList - traverses every Food* item in the list and calls
//          the visit function on each one
// @param visit - the function to call on each item
//*********************************************************************
void Linked_List::traverseList(void visit(Food*))
{
    ListNode *nodePtr;
    nodePtr = head->next;

    while (nodePtr)
    {
        visit(nodePtr->food);
        nodePtr = nodePtr->next;
    }
    
}


