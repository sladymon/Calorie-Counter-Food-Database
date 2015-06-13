//
//  Bucket.cpp
//  HMK_5
//
//  Created by Wendy Martell on 6/10/15.
//  Copyright (c) 2015 ___MARTELL___. All rights reserved.
//

//Author: Wendy Martell 
#include "Bucket.h"
#include "Food.h"
#include "HashTable.h"
#include "Linked_List.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

const string outputFileURL= "/Users/wendymartell/Dropbox/COLLEGE/CLASSES/Q Spring 2015/22C/Asigmments/HMK_5/HMK_5/Toys_Output.txt";

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
            count ++;
            bucket_position = 0;
            
        }else if(count == 1) {
            bucket_Array[count] = food;
            count ++;
            bucket_position = 1;
        
        }else if(count == 2) {
            bucket_Array[count] = food;
            count ++;
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
        cout << "Empty Bucket.\n";
    }
    
    for(int i=0; i< count; i++){
        if (i==0){
            cout << bucket_Array[i]->getName()<< endl;
        
        }if (i>=1){
        
            cout << "\t\t\t\t\t"<<bucket_Array[i]->getName()<< endl;
        }
        
    }
}

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
        
        if(bucket_Array[i]->getName() == cutName){
            bucket_Array[i]->displayFood();
            return true;
        }
    }
    return false;
}






