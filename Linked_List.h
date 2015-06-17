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

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Food.h"
#include <string>
using namespace std;

class Linked_List
{
private:
    // Declare a structure for the list
    struct ListNode
    {
        Food* food;
        ListNode *next;         // To point to the next node
    };
    
    ListNode *head;            // List head pointer
    int count;
    
public:
    // Constructor
    Linked_List();
    
    // Destructor
    ~Linked_List();
    
    // Accessor
    int getcount(){return count;}
    
    // Linked list operations
    void insertNode(Food* foodIn);
    bool deleteNode(Food &foodData);
    bool searchNode(Food &foodData);
    void displayList() const;
    
    // traverse list function
    void traverseList(void visit(Food*, ofstream&), ofstream& outfile);
    
};
#endif