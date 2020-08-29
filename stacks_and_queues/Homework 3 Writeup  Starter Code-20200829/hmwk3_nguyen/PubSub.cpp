#include "PubSub.hpp"
#include <iostream>
using namespace std;

// contructor sets queue front and end to index 0
PubSub::PubSub(){
    queueFront = 0;
    queueEnd = 0;
}

// if queue is empty, return true
bool PubSub::isEmpty() {
    if(counter == 0) {
        return 1; // if there are no elements in the array
    }
    return 0;
}

// if queue is full, return true
bool PubSub::isFull() {
    if(counter == SIZE) {
        return 1; // if the number of elements is equal to the size of the array
    } 
    return 0;
}

// adds an element to the end queue array
void PubSub::enqueue(string item) {
    if(isFull()) {
        cout << "Queue full, cannot add new item\n"; // if queue is full
    } else {
        queue[queueEnd] = item; // populate queue end with item
        counter++; // increase counter by 1
        if(queueEnd == SIZE - 1) {
            queueEnd = 0; // if queue end is at the last index of the array, loop around to the front
        } else {
            queueEnd++; // otherwise, increase queue end index by 1
        }
    }
}

// removes the first element of the queue array
void PubSub::dequeue() {
    if(isEmpty()) {
        cout << "Queue empty, cannot dequeue an item\n"; // if queue is empty
    } else {
        queue[queueFront] = ""; // replace queue front with an empty string
        counter--; // decrease counter by 1
        if(queueFront == SIZE - 1) {
            queueFront = 0; // if queue front is at the end of the array, loop around to the front
        } else {
            queueFront++; // otherwise, increase queue front index by 1
        }
    }
}

// returns the first element in the queue
string PubSub::peek() {
    if(isEmpty()) {
        cout << "Queue empty, cannot peek\n";
        return ""; // if queue is empty, print statement and return an empty string
    } 
    return queue[queueFront]; // otherwise return the element at the beginning of the queue
}

// returns the number of elements in the queue array
int PubSub::queueSize() {
    return counter;
}