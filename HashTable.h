//
//  Hash.h
//  
//
//  Created by Wendy Martell on 6/10/15.
//  Copyright (c) 2015 ___MARTELL___. All rights reserved.
//

#ifndef HMK_5_Hash_h
#define HMK_5_Hash_h

#include "Food.h"
#include "Bucket.h"
#include "Linked_List.h"
#include <iostream>
#include <cstring>
#include <string>

//Author: Wendy Martell

using namespace std;

class HashTable
{
private:
    
    Bucket* foodTable;
    Linked_List* foodList;
    int sizeTable;
    float collisions;
    float load_factor;
    int full_nodes;
    int full_buckets;
    int empty_nodes;
    int empty_buckets;
    int overflow;
    
public:
    
    // constructors
    HashTable();
    HashTable(int size);
    
    // Destructor
    ~HashTable(){
        delete []foodTable;  //FIXME: Is this the correct destructor?
        delete foodList;
    }
    
    // mutators
    void set_sizeTable(int sizeTable) {this->sizeTable = sizeTable;}
    void set_collision(float coallision) {this->collisions = coallision;}
    void set_load_factor(float load_factor) {this->load_factor = load_factor;}
    void set_empty_nodes(int empty_nodes) {this->empty_nodes = empty_nodes;}
    void set_empty_buckets(int empty_buckets) {this->empty_buckets = empty_buckets;}
    void set_full_nodes(int full_nodes) {this->full_nodes = full_nodes;}
    void set_full_buckets(int full_buckets) {this->full_buckets = full_buckets;}
    void set_overflow(int overflow) {this->overflow = overflow;}
    
    // accessors
    float get_collision() const {return collisions;}
    int get_sizeTable() const {return sizeTable;}
    float get_load_factor() const {return load_factor;}
    int get_full_nodes() const {return full_nodes;}
    int get_full_buckets() const {return full_buckets;}
    int get_empty_nodes() const {return empty_nodes;}
    int get_empty_buckets() const {return empty_buckets;}
    int get_overflow()const {return overflow;}
    
    
    int hashed_Index (string name);
    bool insert(Food* food);
    void print_Table();
    void print_Items_in_Bucket();
    void print_Indented_Items_with_Index_from_Bucket();
    bool find_Item (Food& find_food);
    bool delete_Item (Food& find_food);
    void statistics ();                      
    
};

#endif