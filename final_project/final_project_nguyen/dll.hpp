#include <iostream>
using namespace std;

struct Node{ 
    int key;
    Node* next;
    Node* prev;
};

class DLL {
    private:
        Node* head;
        Node* tail;
    public:
        DLL();
        bool insert(int value);
        Node* search(int value);
        void display();
};

