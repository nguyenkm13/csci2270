#ifndef HASHLINEAR_HPP
#define HASHLINEAR_HPP

#include <string>


using namespace std;


class HashLinear
{
    const int TABLE_SIZE = 40009;  // No. of buckets (linked lists)

    // Pointer to an array containing buckets
    int *table;
    int numOfcolision =0;

public:
    HashLinear();  // Constructor

    // inserts a key into hash table
    bool insertItem(int key);

    // hash function to map values to key
    unsigned int hashFunction(int key);

    void printTable();
    int getNumOfCollision();
    void resetCollisions();
    int searchItem(int key);
};

#endif
