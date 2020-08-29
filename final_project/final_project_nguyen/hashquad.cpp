#include "hashquad.hpp"
#include <iostream>
#include <cmath>
using namespace std;

// defualt constructor, declare a table with size 40009
HashQuad::HashQuad() {
    table = new int[TABLE_SIZE];
}

// inserts a key into the hash table
bool HashQuad::insertItem(int key) {
    int index = hashFunction(key);
    int baseIndex = index; // keep note of initial index
    int increments = 0; // increments for quadratic hash
    bool insert = 0;
    while(!insert) {
        if(increments > 0) {
            numOfcolision++; // record collision if hash index is not empty
        }
        if(table[index] == 0) {
            //if index is empty, insert
            table[index] = key;
            insert = 1;
            return 1;
        } else if (table[index] == key) {
            // if duplicate is found, exit
            cout << "duplicate\n";
            return 0;
        } else {
            increments++; // increase increment each loop
            index = baseIndex + pow(increments, 2); // new index is the initial index + i^2, where i is the increments
            
            // circular array, if new index reaches the end of the array, loop to the beginning
            if(index >= TABLE_SIZE) {
                index = index - TABLE_SIZE; 
            }
        }
    }
    return 0;
}

// hash function, remainder of key divided by the table size
unsigned int HashQuad::hashFunction(int key){ 
    return key % TABLE_SIZE;
}


// prints the hash table
void HashQuad::printTable() {
    cout << "== CURRENT PATH ==" << endl;

    // loop through the table
    for(int i = 0; i < TABLE_SIZE; i++) {
        cout << "Hash index " << i << ": ";
        if(table[i] == 0) {
            cout << "" << endl; // if list is empty
        } else {
            cout << table[i] << endl; // output the key
        }  
    }
    cout << "===" << endl;
}


// returns the number of collisions
int HashQuad::getNumOfCollision() {
    return numOfcolision;
}

// resets the number of collisions to zero
void HashQuad::resetCollisions() {
    numOfcolision = 0;
}

// searches the table for a given key
int HashQuad::searchItem(int key) {
    int index = hashFunction(key);
    if(table[index] != key) {
        bool found = 0;
        int baseIndex = index; // note initial index for quadratic hash
        int increments = 0; // increments for quadratic hash
        while(!found) {
            increments++; // increment for each loop
            index = baseIndex + pow(increments, 2); // new index = initial index + i^2, where i is the increment
            
            // circular array, if index reaches the end of the table, loop to the beginning
            if(index >= TABLE_SIZE) {
                index = index - TABLE_SIZE;
            }

            // if key is found, exit
            if(table[index] == key) {
                found = 1;
            }
        }
    }
    return index; // if key is at initial index, return index
}

