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


#ifndef HMK_5_Hash_h
#define HMK_5_Hash_h

#include "Food.h"
#include "Bucket.h"
#include "Linked_List.h"
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

class HashTable
{
private:
    
    Bucket* foodTable;
    Linked_List* foodList;
    int sizeTable;
    int collisions;
    int items_at_pos_0;
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
        delete []foodTable;  //FIXME: Is this correct?
        delete foodList;
    }
    
    // mutators
    void set_sizeTable(int sizeTable) {this->sizeTable = sizeTable;}
    void set_collision(int collision) {this->collisions = collision;}
    void set_items_at_position_0(int items_at_pos_0){this->items_at_pos_0=items_at_pos_0;}
    void set_load_factor(float load_factor) {this->load_factor = load_factor;}
    void set_full_nodes(int full_nodes) {this->full_nodes = full_nodes;}
    void set_full_buckets(int full_buckets) {this->full_buckets = full_buckets;}
    void set_empty_nodes(int empty_nodes) {this->empty_nodes = empty_nodes;}
    void set_empty_buckets(int empty_buckets) {this->empty_buckets = empty_buckets;}
    void set_overflow(int overflow) {this->overflow = overflow;}
    
    // accessors
    int get_sizeTable() const {return sizeTable;}
    int get_collision() const {return collisions;}
    int get_items_at_position_0(){return items_at_pos_0;}
    float get_load_factor() const {return load_factor;}
    int get_full_nodes() const {return full_nodes;}
    int get_full_buckets() const {return full_buckets;}
    int get_empty_nodes() const {return empty_nodes;}
    int get_empty_buckets() const {return empty_buckets;}
    int get_overflow()const {return overflow;}
    
    // hashing function to determine index based on unique key (name)
    int hashed_Index (string name);
    
    // finds item in hash
    bool find_Item (Food& find_food);
    
    // inserts food pointer into hash
    bool insert(Food* food);
    
    // deletes item in hash
    bool delete_Item (Food& find_food);
    
    // displays statistics on hash
    void statistics ();
    
    // print functions
    void print_Table();
    void print_Indented_Items_with_Index_from_Bucket();
    
    // traverse all items in hash
	void traverseHash(void visit(Food*, ofstream&), ofstream& outfile);
    
    // sets all pointers in the hash to null - to be used when rehashing
    void setAllPointersToNull();
    
    
};

#endif