//*********************************************************************
//                              LINKED LIST CLASS
//
// Author: Wendy Martell
// Class: 22C Spring2015
//
// Description: LinkedList is a singlely-linked list with a dummy node
//              which contains a pointer the the head of the list, a
//              count of items in the list, and ListNodes, which each
//              hold a Food pointer and a pointer to the next item in
//              the list.
//
// Purpose: This file is used as our overflow storage for Food* not
//              able to fit in the main collision resolution method,
//              Bucket.  It can store a virtually unlimited number of
//              extra Food*; however, it will usually store no more
//              than a few due to the automatic rehashing that occurs
//              when the HashTable load factor is greater than 75%.
//              Because it is part of the HashTable, it manages the
//              deletion of Food* in its destructor and remove function.
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
    
    // set all pointers to null - to be used when rehashing
    void setAllPointersToNull();
    
};
#endif