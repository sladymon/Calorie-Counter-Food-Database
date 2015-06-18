//*********************************************************************
//                              HASH TABLE CLASS
//
// Author: Wendy Martell
// Description: HashTable contains a dynamically allocated array of
//              Buckets in which to store Food pointers, and a
//              dynamically allocated linked list for any overflow
//              It also contains numerous data items to track
//              statistics for the hash table, such as collisions.
//
//*********************************************************************

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


//*********************************************************************
// Author - Wendy Martell
// Constructor - initializes all statistics counters to 0 and
//          dynamically allocates the array of buckets and the overflow
//          linked list.
//*********************************************************************
HashTable::HashTable(){
    sizeTable=0;
    collisions=0;
    items_at_pos_0=0;
    load_factor= 0.00;
    full_nodes=0;
    full_buckets = 0;
    empty_nodes=sizeTable*3;
    empty_buckets=sizeTable;
    overflow=0;
    foodTable=new Bucket[sizeTable];
    foodList = new Linked_List();
}

//*********************************************************************
// Author - Wendy Martell
// Constructor - initializes all statistics counters to 0 and
//          dynamically allocates the array of buckets (to the size
//          specified) and the overflow linked list.
// @param size - the size of the array of buckets for initialization
//*********************************************************************
HashTable::HashTable(int size){
    sizeTable= size;
    collisions=0;
    items_at_pos_0=0;
    load_factor= 0.00;
    full_nodes=0;
    full_buckets = 0;
    empty_nodes=sizeTable*3;
    empty_buckets=sizeTable;
    overflow=0;
    foodTable = new Bucket[size];
    foodList = new Linked_List();
}

//*********************************************************************
// Author - Wendy Martell
// insert - inserts a new Food pointer into hash table. Calls the hash
//          function to determine which index of the table to insert at.
//          If the bucket at that index if full, it will be inserted
//          into the overflow linked list. It also keeps track of
//          collisions, load factor, full_nodes, full buckets,
//          empty nodes, empty buckets, and overflow items.
// @param food - a Food pointer with the name of the food to be inserted
// @return - true if inserted
//*********************************************************************
bool HashTable::insert(Food *food){
    
    string name;
    int index;
    int position_in_bucket;
    
    name = food->getName();
    index = hashed_Index(name);
    position_in_bucket = foodTable[index].insert_Items_in_Bucket(food);

    if (position_in_bucket == 0){
        
        items_at_pos_0++;
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
        foodList->insertNode(food);
    }
	load_factor = (static_cast<float>(items_at_pos_0 * 100)) / sizeTable;

    return true;
}


//*********************************************************************
// Author - Wendy Martell
// hashed_Index - given a unique key (food name), it will determine
//          the index in the hash table to insert the item.
// @param name - the unique key (food name)
// @return - the index where the food should be inserted in the hash
//*********************************************************************
int HashTable::hashed_Index(string name){
    
	const int size = 21;  // work for shuti's computer
	//int size=21;
    long int sum = 0;
    
    char key[size];
    
    //partial copy (only 20 chars)
    strncpy(key,name.c_str(),20);
    key[20] = '\0';                  /* null character manually added */
    
    char *index= key;
    
    while(*index) {
        
        sum += *index * *index * *index;
        index ++;
    }
    
    int returnVal = sum % sizeTable;
    return returnVal;
  }

//*********************************************************************
// Author - Wendy Martell
// find_Item - finds a food in the hash table.  First searches for the
//          item in the expected index of the array.  If not found
//          there, searches in the overflow linked list.  Modifies the
//          reference parameter with the food's information if found
// @param food - a reference parameter with the name of the food to find
// @return - true if found
//*********************************************************************
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

//*********************************************************************
// Author - Wendy Martell
// delete_Item - deletes an item from the hash.  First tries to delete
//          the item the expected index of the array.  If not found
//          there, tries to delete it in the overflow linked list.
//          Modifies the reference parameter with the food's
//          information if found
// @param food - a reference parameter with the name of the food to
//          delete
// @return - true if found and deleted
//*********************************************************************
bool HashTable::delete_Item (Food& find_food){
    
    int index;
    int bucket_count;
    
    index = hashed_Index (find_food.getName());
    
    bucket_count  = foodTable[index].delete_Item_in_Bucket(find_food);
    if (bucket_count==0){
        
        empty_nodes++;
        empty_buckets++;
        items_at_pos_0--;
        full_nodes--;
        load_factor=(static_cast<float>(items_at_pos_0 *100))/sizeTable ;
        return true;
    
    }if (bucket_count==1){
        full_nodes--;
        collisions--;
        empty_nodes++;
		load_factor = (static_cast<float>(items_at_pos_0 * 100)) / sizeTable;
        return true;
        
    }if (bucket_count==2){
        collisions--;
        empty_nodes++;
        full_buckets--;
        full_nodes--;
		load_factor = (static_cast<float>(items_at_pos_0 * 100)) / sizeTable;
        return true;
        
    }else{
        bool deleteSuccessful = foodList->deleteNode(find_food);
        overflow--;
		load_factor = (static_cast<float>(items_at_pos_0 * 100)) / sizeTable;
        return deleteSuccessful;
    }

return false;
}

//*********************************************************************
// Author - Wendy Martell
// statistics - displays the statistics for the hash table
//*********************************************************************
void HashTable::statistics (){
    int total_nodes=0;
    int non_empty=0;
    total_nodes= sizeTable*3;
    non_empty = total_nodes-sizeTable;
    double average = (static_cast<double>(collisions))/items_at_pos_0;
    
	load_factor = (static_cast<float>(items_at_pos_0 * 100)) / sizeTable;
    int items_in_the_Hash_and_List=full_nodes + overflow;
    
    cout << "\n\t\t\tHash Table Statistics\n" << endl;
    
    cout <<"\tHash Table Size                      : " << sizeTable << endl;
    cout<< "\tHash Table - Elements capacity       : "<< total_nodes<< endl;
    cout<< "\tTotal Number of items in the Hash    : "<< items_in_the_Hash_and_List << endl;
    cout<< "\tNumber of items in the Array         : "<< full_nodes << endl;
    cout<< "\tNumber of items in the Overflow      : "<< overflow << endl;
    cout<< "\tHash Table - Empty Nodes             : "<< empty_nodes <<endl;
    cout<< "\tCollisions                           : " << collisions << endl;
    cout<< "\tLoad Factor                          : " <<fixed << setprecision(2) << load_factor << " %"<< endl;
    cout<< "\tFull Buckets                         : "<< full_buckets <<endl;
    cout<< "\tEmpty Buckets                        : "<< empty_buckets <<endl;
    cout<< "\tBuckets with at least one item       : "<<fixed << setprecision(2)<< items_at_pos_0 <<endl;
    cout<<" \tAvg buckets index 1 or 2             : "<<fixed << setprecision(2)<<average<<endl;
    cout<< endl;

}

//*********************************************************************
// Author - Wendy Martell
// print_Table - prints all foods in the array and overflow linked list
//*********************************************************************

void HashTable::print_Table(){
    
    for (int i=0; i < sizeTable ; i++) {
        
        foodTable[i].print_Items_in_Bucket();
    }
    foodList->displayList();
}

//*********************************************************************
// Author - Wendy Martell
// print_Indented_Items_with_Index_from_Bucket - prints indented list
//          of all foods in the array by index and also prints
//          items in the overflow linked list
//*********************************************************************
void HashTable::print_Indented_Items_with_Index_from_Bucket(){
    
    for (int i=0; i < sizeTable ; i++) {
        
        cout << "Index " << i << " : ";
        foodTable[i].print_Indented_Items_from_bucket();
        cout << endl;
    }
    cout << "Items in overflow linked list (" << foodList->getcount() << "): " << endl;
    foodList->displayList();
}


//*********************************************************************
// Author - Shannon Ladymon
// traverseHash - overloaded traverse for every Food* item in the
//          hash which calls the visit function on each one, which
//          will print to file
// @param visit - the function to call on each item
// @param outfile - the file to write to
//*********************************************************************
void HashTable::traverseHash(void visit(Food*, ofstream&), ofstream& outfile)
{
    for (int i=0; i < sizeTable ; i++) {
        
        foodTable[i].traverseBucket(visit, outfile);
    }
    foodList->traverseList(visit, outfile);
}

//*********************************************************************
// Author - Shannon Ladymon
// setAllPointersToNull - sets all Food* pointers in the hash to null
//          which is to be used when rehashing to avoid deleting data
//          upon the destruction of the previous hashtable
//*********************************************************************
void HashTable::setAllPointersToNull()
{
    for (int i=0; i < sizeTable ; i++) {
        
        foodTable[i].setAllPointersToNull();
    }
    foodList->setAllPointersToNull();
}