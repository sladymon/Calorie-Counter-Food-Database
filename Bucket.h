//
//  Bucket.h
//  HMK_5
//
//  Created by Wendy Martell on 6/10/15.
//  Copyright (c) 2015 ___MARTELL___. All rights reserved.
//

#ifndef HMK_5_Bucket_h
#define HMK_5_Bucket_h

#include "Food.h"
#include "Linked_List.h"
#include <iostream>
#include <cstring>
#include <string>

//Author: Wendy Martell
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//                      BUCKET CLASS
//
//  This is Bucket Class which holds all the data need it in order
//  to create a new Bucket object to host the food pointer in it.
//
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

using namespace std;

class Bucket
{
private:
   
    int count;
    Food *bucket_Array[3];

public:
    //Constructor
    Bucket();
    //
    ~Bucket(); // delete each *
    
    // accessors
    int get_count() const	 {return count;}
    
    // mutators
    void set_count(int count) { this->count = count;}
    
    // insert food pointer into bucket
    int insert_Items_in_Bucket(Food *food);
    
    // find an item and modify the reference parameter with its details
    bool find_Item_in_Bucket(Food& find_food);
    
    // deletes an item 
    bool delete_Item_in_Bucket(Food& find_food);
    
    // print functions
    void print_Items_in_Bucket();  
    void print_Indented_Items_from_bucket();



};

#endif
