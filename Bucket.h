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
    
    // mutators
    void set_count(int count) { this->count = count;}
    int insert_Items_in_Bucket(Food *food);
    void print_Items_in_Bucket();  
    void print_Indented_Items_from_bucket();
    bool find_Item_in_Bucket(Food& find_food);
    
    // accessors
    int get_count() const	 {return count;}

};

#endif
