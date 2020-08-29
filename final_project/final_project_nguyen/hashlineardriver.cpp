#include <iostream>
#include <fstream>
#include "hashlinear.hpp"
using namespace std;

// returns a random number between 0 and a given value
int random(int end) {
    int dif = end - 1;
    int value = rand() % dif;
    return value;
}

void timer(string filename) {
    int testData[10000]; // stores data
    float insert[100], search[100], sumTime = 0;

    // input and output files
    ifstream data(filename);
    ofstream out_file("insert_search_performance_hash_linear_" + filename);
    out_file << "iteration,avg_collisions,insert_nano,search_nano\n";

    string temp;
    int numElems = 0, elemCount = 0;
    
    // read data from given csv file
    while(getline(data, temp, ',')) {
        testData[numElems] = stoi(temp);
        numElems++;
    }

    HashLinear linearHash;
    srand(time(NULL)); // seed for random number generator
    for (int i = 0; i < 100; i++) {
        int start = elemCount; // sets where to begin reading data from testData array
        linearHash.resetCollisions(); // resets the number of collision after each iteration
        sumTime = 0;// resets sum of time

        // reads next 100 ID numbers from the test data array
        for(int j = start; j< start + 100; j++) {
            if(j < 10000) {
                auto start = chrono::steady_clock::now(); // start timer
                linearHash.insertItem(testData[j]);// insert test data to hash table
                auto end = chrono::steady_clock::now();// end timer
                
                // add time to sumTime
                sumTime += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            
                elemCount++;
            }

        }
        insert[i] = sumTime / (100 * 1.0); // average insert time per 100 inserts

        sumTime = 0; // reset time counter
        
        // perform searches of 100 random IDs 
        for(int k = 0; k < 100; k++) {
            auto start2 = chrono::steady_clock::now();
            linearHash.searchItem(testData[random(elemCount - 1)]);
            auto end2 = chrono::steady_clock::now();
            
            // add time to sumTime
            sumTime += chrono::duration_cast<chrono::nanoseconds>(end2 - start2).count();

        }
        search[i] = sumTime / (100 * 1.0); // average search time per 100 searches

        float avg_collisions = linearHash.getNumOfCollision() / (100 * 1.0); // average number of collisions per 100 inserts/searches

        // record iteration, avgerage number of collisions, average insert time, and average search time
        out_file << i + 1 << ',' << avg_collisions << ',' << insert[i] << "," << search[i] << endl;
    }

    // close fstream objects
    data.close();
    out_file.close();

}

int main() {

    // perform operations on both datasets
    timer("dataSetA.csv");
    timer("dataSetB.csv");

    return 0;
}