#include "hashchain.hpp"
#include <iostream>
using namespace std;

// create a new node with a given key and next pointer
node* HashChain::createNode(int key, node* next) {
    node* temp = new node{key, next};
    return temp;
}

// default constructor
HashChain::HashChain() {
    table = new node*[TABLE_SIZE];
}

// hash function, remainder of key divided by the table size
unsigned int HashChain::hashFunction(int key) {
    return key % TABLE_SIZE;
}

// searches the hash table for the node with a given key
node* HashChain::searchItem(int key) {
    int index = hashFunction(key);
    if(table[index] != NULL) {
        node* temp = table[index]; 
        while(temp != NULL) {
            if(temp->key == key) {
                return temp; // if the key is found return the node
            }
            temp = temp->next; // moves along the chain
        }
    }
    return NULL;
}

// inserts a key into the hash table
bool HashChain::insertItem(int key) {
    int index = hashFunction(key);
    node* hashElement = createNode(key, NULL);
    if(table[index] == NULL) {
        table[index] = hashElement; // if the node at the hash index is empty, insert
        return 1;
    } else {
        node* temp = table[index];

        // this loop checks for duplicates in the chain
        while (temp != NULL) {
            if(temp->key == key) {
                cout << "duplicate\n";
                return 0;
            }
            temp = temp->next;
        }
        temp = table[index]; // reset temp pointer to begining of chain
        while(temp->next != NULL) {
            numOfcolision++;
            temp = temp->next; // moves to the end of the chain
        }
        temp->next = hashElement; // insert new node at the end of the chain
        
        return 1;
    }
}

// prints the hash table
void HashChain::printTable() {
    cout << "== CURRENT PATH ==" << endl;
    for(int i = 0; i < TABLE_SIZE; i++) {
        node* temp = new node;
        temp = table[i];
        cout << "Hash index " << i << ": ";
        if(table[i] == NULL) {
            cout << "" << endl; // if list is empty
        } else {
            // print keys
            while(temp != NULL) {
                cout << temp->key << " -> ";
                temp = temp->next;
            }
            cout << "NULL" << endl; // prints null for tail
        }  
    }
    cout << "===" << endl;
}

// returns number of collisions
int HashChain::getNumOfCollision() {
    return numOfcolision;
};

// resets the collisions counter to zero
void HashChain::resetCollisions() {
    numOfcolision = 0;
}