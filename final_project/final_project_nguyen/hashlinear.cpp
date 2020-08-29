#include "hashlinear.hpp"
#include <iostream>
#include <fstream>
using namespace std;

// default constructor, declare and hash table of size 40009
HashLinear::HashLinear() {
    table = new int[TABLE_SIZE];
}


// inserts into hash table
bool HashLinear::insertItem(int key) {
    int index = hashFunction(key);
    int hashIndex = index;
    bool insert = 0;
    while(!insert) {
        if(index > hashIndex) {
            numOfcolision++; // record a collision if initial index after hash function is not empty
        }
        if(table[index] == 0) {

            // if bucket at index is empty, insert
            table[index] = key;
            insert = 1;
            return 1;
        } else if (table[index] == key){
            // exit if duplicate is found
            cout << "duplicate\n";
            return 0;
        } else {
            index++; // linear hash, increase index by one and check again

            //circular array, if index reaches end of table, go to 0 index
            if(index == TABLE_SIZE) {
                index = 0;
            }
        }
    }
    return 0;
}

// hash function, remainder of key divided by table size
unsigned int HashLinear::hashFunction(int key) {
    return key % TABLE_SIZE;
}

// prints the hash table
void HashLinear::printTable() {
    cout << "== CURRENT PATH ==" << endl;

    // loop through full table
    for(int i = 0; i < TABLE_SIZE; i++) {
        cout << "Hash index " << i << ": ";
        if(table[i] == 0) {
            cout << "" << endl; // if list is empty
        } else {
            cout << table[i] << endl;
        }  
    }
    cout << "===" << endl;
}

// returns number of collisions
int HashLinear::getNumOfCollision() {
    return numOfcolision;
}

// resets the collision counter to zero
void HashLinear::resetCollisions() {
    numOfcolision = 0;
}

// searches for a given key in the hash table
int HashLinear::searchItem(int key) {
    int index = hashFunction(key);
    if(table[index] != key) {
        bool found = 0;
        while(!found) {
            index++; // linear hash, increase index by 1 and try again

            // circular array, if index reaches the end of the table, go to the beginning
            if(index == TABLE_SIZE) {
                index = 0;
            }

            // if key is found, exit loop
            if(table[index] == key) {
                found = 1;
            }
        }
    } 
    return index; // return when correct index is found
}
