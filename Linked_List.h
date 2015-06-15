//
//
//  Created by Wendy Martell on 6/10/15.
//  Copyright (c) 2015 ___MARTELL___. All rights reserved.
//
// Specification file for the LinkedList class

#ifndef LINKEDLIST_H
#define LINKEDLIST_H


//Author: Wendy Martell

#include "Food.h"
#include <string>
using namespace std;

class Linked_List
{
private:
    // Declare a structure for the list
    struct ListNode
    {
        //Food* food;        // The value in this node
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
    
    int getcount(){return count;}
    
    // Linked list operations
    void insertNode(Food* foodIn);
    bool deleteNode(Food &foodData);
    bool searchNode(Food &foodData);
    void displayList() const;
    
};
#endif