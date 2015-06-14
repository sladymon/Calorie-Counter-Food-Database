//
//  HashTable.cpp
//  HMK_5
//
//  Created by Wendy Martell on 6/10/15.
//  Copyright (c) 2015 ___MARTELL___. All rights reserved.
//

#include "HashTable.h"
#include "Food.h"
#include "Linked_List.h"
#include <iostream>
#include <cstring>
#include <string>
#include <stdio.h>
#include <string.h>
#include <iomanip>
#include <cctype>

//Author: Wendy Martell

// constructors
HashTable::HashTable(){
    sizeTable=0;
    collisions=0.00;
    load_factor= 0.00;
    empty_nodes=sizeTable*3;
    full_nodes=0;
    empty_buckets=sizeTable;
    full_buckets = 0;
    overflow=0;
    foodTable=new Bucket[sizeTable];
    foodList = new Linked_List();
}

HashTable::HashTable(int size){
    sizeTable= size;
    collisions=0.00;
    load_factor= 0.00;
    empty_nodes=sizeTable*3;
    full_nodes=0;
    empty_buckets=sizeTable;
    full_buckets = 0;
    overflow=0;
    foodTable = new Bucket[size];
    foodList = new Linked_List();
}

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//+ Function Name = insert()
//
// Inserts a new Food pointer into the bucket array. If the bucket
// is full the food will be send it to the overflow linked list.
// At the same time keep track of collisions, load factor, full_nodes,
// full buckets, empty nodes, empty buckets, and overflow items.
//
// @Parameter       : Food *food
// @Return          : bool
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
bool HashTable::insert(Food *food){
    
    string name;
    int index;
    int bucket_count;
    int position_in_bucket;
    
    name = food->getName();
    index = hashed_Index (name);
    
    bucket_count++;
    position_in_bucket = foodTable[index].insert_Items_in_Bucket(food);

    
    if (position_in_bucket == 0){
        
        load_factor++;
        full_nodes++;
        empty_nodes--;
        empty_buckets--;
        
    }if(position_in_bucket == 1){
        
        collisions++;
        full_nodes++;
        empty_nodes--;
        
    }if(position_in_bucket == 2){
        
        collisions++;
        empty_nodes--;
        full_nodes++;
        full_buckets++;
        
    }else if(position_in_bucket == 3){
        overflow++;
       // cout << "TESTING: inserting into overflow linked list: " << food->getName() << endl;
        foodList->insertNode(food);
        cout <<endl;
    }
    return true;
}

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//+ Function Name = hashed_Index()
//
// Creates a unique ID & match the unique ID with the index
//
// @Parameter       : string name
// @Return          : int
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
int HashTable::hashed_Index(string name){
    
    int size=7;
    long int sum = 0;
    
    char key[size];
    
    //partial copy (only 6 chars)
    strncpy(key,name.c_str(),6);
    key[6] = '\0';                  /* null character manually added */
    
    char *index= key;
    
    while(*index) {
        
        sum += *index * *index * *index;
        index ++;
    }
    
    int returnVal = sum % sizeTable;
    return returnVal;
  }

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//+ Function Name = print_Table()
//
// prints the table by indexes displaying the unique ID.
//
// @Parameter       : none
// @Return          : void
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
void HashTable::print_Table(){
    
    for (int i=0; i < sizeTable ; i++) {
        
        foodTable[i].print_Items_in_Bucket();
    }
    foodList->displayList();
}


//FIXME: What is this, and why doesn't it match the name?  What uses this???

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//+ Function Name = hashed_Index()
//
// Prints list of food per bucket.
//
// @Parameter       : none
// @Return          : void
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
void HashTable::print_Items_in_Bucket(){
    
   foodTable->print_Items_in_Bucket();
}

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//+ Function Name = print_Indented_Items_with_Index_from_Bucket()
//
// Prints indented list of food including their indexes.
// This one calls print_Indented_Items_from_bucket() function.
//
// @Parameter       : none
// @Return          : void
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
void HashTable::print_Indented_Items_with_Index_from_Bucket(){
    
    for (int i=0; i < sizeTable ; i++) {
        
        cout << "Index " << i << " : ";
        foodTable[i].print_Indented_Items_from_bucket();
        cout << endl;
    }
    foodList->displayList();
}

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//+ Function Name = find_Item()
//
// Finds a food in the Bucket of food based on his index.
// This one calls find_Item_in_Bucket(name)function.
//
// @Parameter       : Food& find_food
// @Return          : bool
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
bool HashTable::find_Item(Food& find_food){

    int index;
    bool found;

    index = hashed_Index (find_food.getName());
    
    found = foodTable[index].find_Item_in_Bucket(find_food);
    
    if (!found) {
    
        found = foodList->searchNode(find_food);
    }
    if (!found){
        return false;
    }
    
    return true;
}

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//+ Function Name = statistics()
//
// Calculates and display the statistics of the Hash Table.
//
// @Parameter       : none
// @Return          : void
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
void HashTable::statistics (){
    int total_nodes=0;
    int non_empty=0;
    total_nodes= sizeTable*3;
    non_empty = total_nodes-sizeTable;
    double average = collisions/load_factor;
    
    //FIXME: Add a total number of items in table
    
    cout << "Hash Table Statistics" << endl;
    cout <<"\tHash Table Size    : " << sizeTable << endl;
    cout<< "\tTotal Nodes        : "<<total_nodes<< endl;
    cout<< "\tFilled Nodes       : "<< full_nodes << endl;  //FIXME: What is this?
    cout<< "\tEmpty Nodes        : "<< empty_nodes <<endl;  //FIXME: WHat is this?
    cout<< "\tCollisions         : " << collisions << endl;
    cout<< "\tLoad Factor        : " << (load_factor*100)/sizeTable << " %"<< endl;
    //cout<< "\tFulFill Buckets    : "<< load_factor << endl;  //FIXME: What is this? change name
    cout<< "\tFull  Buckets      : "<< full_buckets <<endl;
    cout<< "\tEmpty Buckets      : "<< empty_buckets <<endl;
    cout<< "\tOverflow           : "<< overflow << endl;
    cout<<" \tAvg buckets index 1 or 2 : "<<fixed << setprecision(2)<<average<<endl;

}