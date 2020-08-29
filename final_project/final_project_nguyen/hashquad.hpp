#ifndef HASHQUAD_HPP
#define HASHQUAD_HPP

#include <string>

using namespace std;


class HashQuad
{
    const int TABLE_SIZE = 40009;  // No. of buckets 

    // Pointer to an array containing buckets
    int *table;
    int numOfcolision =0;
public:
    HashQuad();  // Constructor

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
