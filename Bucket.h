//*********************************************************************
//                              BUCKET CLASS
//
// Author: Wendy Martell
// Description: Bucket contains a count of items in the bucket and an
//              array of 3 pointers to Food objects.
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
    
    // find an item and modify the reference parameter with its details
    bool find_Item_in_Bucket(Food& find_food);
    
    // deletes an item
    int delete_Item_in_Bucket(Food& find_food);
    
    // print functions
    void print_Items_in_Bucket();  
    void print_Indented_Items_from_bucket();

    // traverse bucket function
    void traverseBucket(void visit(Food*, ofstream&), ofstream& outfile);


};

#endif
