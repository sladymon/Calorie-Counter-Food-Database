//*********************************************************************
//                              BUCKET CLASS
//
// Author: Wendy Martell
// Description: Bucket contains a count of items in the bucket and an
//              array of 3 pointers to Food objects.
//
//*********************************************************************

#include "Bucket.h"
#include "Food.h"
#include "HashTable.h"
#include "Linked_List.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

// constructor
Bucket::Bucket(){
    
    count = 0;
    
    for(int i=0; i< 3; i++){
        bucket_Array[i] = 0;
    }
}

// Destructor
Bucket::~Bucket(){    
    count = 0;
    
    for(int i=0; i< 3; i++){
        
        if (bucket_Array[i]!=0) {
            
            delete bucket_Array[i];
        }
        
    }
}

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//+ Function Name = insert_Items_in_Bucket()
//
// Inserts a new food pointer into the bucket array. If the bucket
// is full the food will be send it to the rejected output file.
//
// @Parameter       : Food *food
// @Return          : int
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
int Bucket::insert_Items_in_Bucket(Food *food){
    
    int bucket_position;
    
    if(count < 3) {
        
        if (count == 0){
            bucket_Array[count] = food;
            count++;
            bucket_position = 0;
            
        }else if(count == 1) {
            bucket_Array[count] = food;
            count++;
            bucket_position = 1;
        
        }else if(count == 2) {
            bucket_Array[count] = food;
            count++;
            bucket_position = 2;
        }
    }else{
        bucket_position = 3;
    }
    
    return bucket_position;
}

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//+ Function Name = print_Items_in_Bucket()
//
// Prints the Name of the food from the bucket.
//
// @Parameter       : none
// @Return          : void
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
void Bucket::print_Items_in_Bucket(){
    
    for(int i=0; i< count; i++){
        
        cout << "\t"<<bucket_Array[i]->getName()<< endl;
    }
}

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//+ Function Name = print_Indented_Items_from_bucket()
//
// Prints the name of the food by indexes indenting positions 1 and 2
//
// @Parameter       : none
// @Return          : void
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
void Bucket::print_Indented_Items_from_bucket(){
    
    if (count == 0) {
        cout << "//Empty Bucket";
    }
    //FIXME: Change this to else?
    
    for(int i=0; i< count; i++){
        if (i==0){
            cout << bucket_Array[i]->getName();
        
        }if (i>=1){
        
            cout << "\n\t\t\t\t"<<bucket_Array[i]->getName();
        }
        
    }
}

//FIXME: Modify to change the reference parameter

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//+ Function Name = find_Item_in_Bucket()
//
// Find the name of the food in the hash table
//
// @Parameter       : Food& find_food
// @Return          : bool
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
bool Bucket::find_Item_in_Bucket(Food& find_food){
    
    string search_name = find_food.getName();
    string cutName = search_name.substr(0,5);
    
    for(int i=0; i< count; i++){
        if(bucket_Array[i]->getName().substr(0,5) == cutName){
            find_food = *(bucket_Array[i]);
            return true;
        }
    }
    return false;
}

//FIXME: Check this function and j

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//+ Function Name = delete_Item_in_Bucket()
//
// Deletes food in the hash table & rearranges the elements in
// the array to not leave a position empty.
//
// @Parameter       : Food& find_food
// @Return          : bool
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
bool Bucket::delete_Item_in_Bucket(Food& find_food){
    
    string search_name = find_food.getName();
    string cutName = search_name.substr(0,5);
    
    bool found = false;
    int j;
    for(int i=0; i< count; i++){
        if(bucket_Array[i]->getName().substr(0,5)==cutName){
            bucket_Array[i] = 0;
            found = true;
            j=i;
            count--;
            break;
        }
    }
    
    if(found){
        for(; j< count; j++){
            bucket_Array[j] = bucket_Array[j+1];
            bucket_Array[j+1] = 0;
        }
    }
    return found;
}






