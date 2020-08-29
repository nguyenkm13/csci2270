#include "dll.hpp"
using namespace std;

// default constructor, sets head and tail pointers to null
DLL::DLL() {
    head = NULL;
    tail = NULL;
}

// inserts a new node at the end of the doubly linked list
bool DLL::insert(int value) {
    Node* temp = new Node{value, NULL, NULL};
    Node* search = head;

    // searches the linked list for duplicates
    while(search != NULL) {

        // if a duplicate is found, return 0
        if(search->key == value) {
            cout << "duplicate\n";
            return 0;
        }
        search = search->next; // moves along linked list
    }

    // if list is empty, set head and tail to new node
    if(head == NULL) {
        head = temp;
        tail = temp;
    } else {
        // insert new node at the end of the linked list  
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
    }
    return 1;
}

// returns the node with a given key
Node* DLL::search(int value) {
    Node* temp = head;

    // loops through list
    while(temp != NULL) {
        // if key is found, return node
        if(temp->key == value) {
            return temp;
        } 
        temp = temp->next; // moves along linked list
    }
    return NULL;
}

// displays the linked list
void DLL::display() {
    Node* temp = head;
    cout << "== CURRENT PATH ==" << endl;
    if(head == NULL) {
        cout << "nothing in path" << endl; // if list is empty
    } else {
        // print keys
        while(temp != NULL) {
            cout << temp->key << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl; // prints null for tail
    }
    cout << "===" << endl;
}