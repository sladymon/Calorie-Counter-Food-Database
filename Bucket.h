//*********************************************************************
//                              BUCKET CLASS
//
// Author: Wendy Martell
// Class: 22C Spring2015
//
// Description: Bucket contains a count of items in the bucket and an
//              array of 3 pointers to Food objects.
//
// Purpose: This file is used as the main conflict resolution method
//              for our project.  When up to three items are hashed to
//              the same index, they are able to be placed in
//              subsequent indexes of the bucket.  Once the bucket is
//              full, the HashTable class will instead place any items
//              in the LinkedList instead.  Because Bucket is part of
//              the HashTable class, it manages the deletion of Food*
//              when its deletion or destructor methods are called.
//
//*********************************************************************

#ifndef HMK_5_Bucket_h
#define HMK_5_Bucket_h

#include "Food.h"
#include "Linked_List.h"
#include <iostream>
#include <cstring>
#include <string>


using namespace std;

class Bucket
{
private:
   
    int count;
    Food *bucket_Array[3];

public:
    // constructor
    Bucket();
    
    // destructor
    ~Bucket();
    
    // accessors
    int get_count() const	 {return count;}
    
    // mutators
    void set_count(int count) { this->count = count;}
    
    // insert food pointer into bucket
    int insert_Items_in_Bucket(Food *food);
    
    // deletes an item
    int delete_Item_in_Bucket(Food& find_food);
    
    // find an item and modify the reference parameter with its details
    bool find_Item_in_Bucket(Food& find_food);
    
    // print functions
    void print_Items_in_Bucket();  
    void print_Indented_Items_from_bucket();

    // traverse bucket function
    void traverseBucket(void visit(Food*, ofstream&), ofstream& outfile);
    
    // sets all pointers to null - to be used when rehashing
    void setAllPointersToNull();


};

#endif
