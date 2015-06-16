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

//*********************************************************************
// Author - Wendy Martell
// Constructor - initializes count to 0 and all indexes of array to
//          null pointers (0)
//*********************************************************************
Bucket::Bucket(){
    
    count = 0;
    
    for(int i=0; i< 3; i++){
        bucket_Array[i] = 0;
    }
}

//*********************************************************************
// Author - Wendy Martell
// Destructor - sets count to 0 and deletes all pointers in array
//          unless null
//*********************************************************************
Bucket::~Bucket(){    
    count = 0;
    
    for(int i=0; i< 3; i++){
        
        if (bucket_Array[i]!=0) {
            
            delete bucket_Array[i];
        }
        
    }
}


//*********************************************************************
// Author - Wendy Martell
// insert_Items_in_Bucket - inserts a new food pointer into the next
//          available index in the bucket array if not full.
// @param food - a pointer to the Food to be inserted.
// @return - an int for the index position (0-2). 3 if unable to
//          insert in array.
//*********************************************************************
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


//*********************************************************************
// Author - Wendy Martell
// print_Items_in_Bucket - prints the names of the foods from the bucket
//*********************************************************************
void Bucket::print_Items_in_Bucket(){
    
    for(int i=0; i< count; i++){
        
        cout << "\t"<<bucket_Array[i]->getName()<< endl;
    }
}

//*********************************************************************
// Author - Wendy Martell
// print_Indented_Items_from_bucket - prints the names of the foods
//          from the bucket, indenting indexes 1 and 2.  Prints empty
//          if there are no foods in the bucket.
//*********************************************************************
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
    cout <<endl;
}


//*********************************************************************
// Author - Wendy Martell
// find_Item_in_Bucket - finds a food in the bucket and modifies the
//          reference parameter with that food's information if found
// @param food - a reference parameter with the name of the Food to
//          be found
// @return - false if unable to find
//*********************************************************************
bool Bucket::find_Item_in_Bucket(Food& find_food){
    
    string search_name = find_food.getName();
    string cutName = search_name.substr(0,19);
    
    for(int i=0; i< count; i++){
        if(bucket_Array[i]->getName().substr(0,19) == cutName){
            find_food = *(bucket_Array[i]);
            return true;
        }
    }
    return false;
}

//*********************************************************************
// Author - Wendy Martell
// delete_Item_in_Bucket - deletes a food from the bucket if found
//          and rearranges the elements in the array to not leave a
//          position empty.
// @param food - a reference parameter with the name of the Food to
//          be deleted.
// @return - false if unable to find
//*********************************************************************
//bool Bucket::delete_Item_in_Bucket(Food& find_food){
int Bucket::delete_Item_in_Bucket(Food& find_food){
    
    string search_name = find_food.getName();
    string cutName = search_name.substr(0,19);
   
    //bool found = false;
    int position = 0;
    
    int j = 0;
    for(int i=0; i< count; i++){
        if(bucket_Array[i]->getName().substr(0,19)==cutName){
            bucket_Array[i] = 0;
            
           // found = true;
            position = i;
            
            j=i;
            count--;
            bucket_Array[position] = bucket_Array[count];
            bucket_Array[count]=0;
            break;
        }
    }
    /*
    if(found){
    //if (position==0||position==1){
    
        for(; j< count; j++){
            bucket_Array[j] = bucket_Array[j+1];
            bucket_Array[j+1] = 0;
        }
    }*/
    //return found;
    return count;
}

//*********************************************************************
// Author - Shannon Ladymon
// traverseBucket - traverses every Food* item in the bucket and calls
//          the visit function on each one
// @param visit - the function to call on each item
//*********************************************************************
void Bucket::traverseBucket(void visit(Food*))
{
    for(int i=0; i< count; i++){
        
        if(bucket_Array[i] != 0) //if not a null ptr
        {
            visit(bucket_Array[i]);
        }
    }
}


//*********************************************************************
// Author - Shannon Ladymon
// traverseBucket - overloaded traverse for every Food* item in the
//          Bucket which calls the visit function on each one, which
//          will print to file
// @param visit - the function to call on each item
// @param outfile - the file to write to
//*********************************************************************
void Bucket::traverseBucket(void visit(Food*, ofstream&), ofstream& outfile)
{
    for(int i=0; i< count; i++){
        
        if(bucket_Array[i] != 0) //if not a null ptr
        {
            visit(bucket_Array[i], outfile);
        }
    }
}






