#include "StackCalculator.hpp"
using namespace std;

// sets head to null
StackCalculator::StackCalculator() {
    head = NULL;
}

// clears stack
StackCalculator::~StackCalculator() {
    while(!isEmpty()) {
        pop();
    }
}

// returns true if stack is empty, fale otherwise
bool StackCalculator::isEmpty() {
    if(head) {
        return 0;
    }
    return 1;
}

// adds a node to the stack
void StackCalculator::push(float num) {
    Op* newNode = new Op{num, NULL}; //contstruct a new node with given value
    if(isEmpty()) {
        head = newNode; // if stack is empty set new node to head
    } else {
        newNode->next = head; // add new node to stack
        head = newNode; // set head to new node
    }
}


// removes most recently added node from stack
void StackCalculator::pop() {
    if(isEmpty()) {
        cout << "Stack empty, cannot pop an item.\n"; 
        return; // if stack is empty, print statement and do nothing else
    } else {
        Op *temp = head; // temp node points to head
        head = head->next; // shift head along to next node is stack
        delete temp; // release memory of the last node
        temp = NULL; 
    }
}

// returns the last node in the stack
Op* StackCalculator::peek() {
    if(isEmpty()) {
        cout << "Stack empty, cannot peek.\n";
        return NULL; // if empty, return null
    } else {
        return head; // return head in stack
    }
}

// calculation operator for last two items in the stack
bool StackCalculator::calculate(string symbol) {
    if(symbol != "*" && symbol != "+") {
        cout << "err: invalid operation\n";
        return 0; // if the operator is not * or +, print statement and return false 
    } else {
        float nums[2], newNum; // array to store keys of last two stack elements and a float to store new number to be pushed to stack
        for(int i = 0; i < 2; i++) { // for last two elements in the stack
            if(isEmpty()) {
                cout << "err: not enough operands\n";
                if(i > 0) {
                    push(nums[0]); // if the stack is empty after popping last element, push last number back onto stack
                }
                return 0; // if empty return false
            } else {
                nums[i] = head->num; // store node key into array
                pop(); // remove last node from stack
            }
        }
        if(symbol == "+") { 
            newNum = nums[0] + nums[1]; // if operator is +, add last two elements in stack
        } else {
            newNum = nums[0] * nums[1]; // if operator is *, multiply last two elements in the stack
        }
        push(newNum); // push new number onto stack
        return 1; // return true if successful
    }
}