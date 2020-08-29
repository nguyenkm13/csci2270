/*
** Name: Kevin Nguyen
** Assighment: Week 2 - HW1
** Description: Text Analyzer
**
** Command-line example:
** hw1 25 mobydick.txt ignoreWords.txt
*/

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct wordRecord { 
    string word;
    int count;
};

void getIgnoreWords(const char *ignoreWordFileName, string ignoreWords[]) {
    ifstream ignore(ignoreWordFileName); 

    if(ignore.is_open()) {
        string line;
        int lineCount = 0;

        // stores ignore words into an array
        while(getline(ignore, line)) {
            ignoreWords[lineCount] = line;
            lineCount++;
        }
    } else { // if the file is not open
        cout << "Failed to open " << *ignoreWordFileName << endl;
    }
    ignore.close();
};

bool isIgnoreWord(string word, string ignoreWords[]) {
    int matches = 0;

    // search the ignore words array for matches
    for(int i = 0; i < 50; i ++) {
        if(word == ignoreWords[i]) {
            return 1;
        }
    }
    return 0; // if no matches, return false
}

int getTotalNumberNonIgnoreWords(wordRecord distinctWords[], int length) {
    int wordCount = 0;

    // sums the count of distinct words
    for(int i = 0; i < length; i++) {
        wordCount += distinctWords[i].count;
    }
    return wordCount;
}

void sortArray(wordRecord distinctWords[], int length) {

    //sorts the distinct words array (selection)
    for(int i = 0; i < length; i++) {
        for(int j = i + 1; j < length; j++) {
            if(distinctWords[i].count < distinctWords[j].count) {
                wordRecord temp = distinctWords[i]; // place holder

                // swap i and j positions
                distinctWords[i] = distinctWords[j]; 
                distinctWords[j] = temp; 
            } else if (distinctWords[i].count == distinctWords[j].count){ //if two words have the same count
                // breaks tie by alphabetical order
                if(distinctWords[i].word > distinctWords[j].word) {
                    wordRecord temp = distinctWords[i];
                    distinctWords[i] = distinctWords[j];
                    distinctWords[j] = temp;
                }
            }
        }
    }
}

void printTenFromN(wordRecord distinctWords[], int N, int totalNumWords) {

    // print the first 10 elements from a starting rank N
    for(int i = 0; i < 10; i++) {
        int ind = N + i;
        float prob = (float) distinctWords[ind].count / totalNumWords * 1.0;
        cout << fixed << setprecision(4) << prob << " - " << distinctWords[ind].word << endl;
    }
}

int main(int argc, char* argv[]) {
    if(argc != 4) { //if there aren't 4 command line arguments
        cout << "Usage: Homework1Solution <number of words> <inputfilename.txt> <ignoreWordsfilename.txt>" << endl;
    } else {
        int arrSize = 100, wordCount = 0, doubles = 0;
        string top50[50], temp;
        wordRecord *words = new wordRecord[100];
        getIgnoreWords(argv[3], top50); //stores words in ignore file to top50 array

        ifstream file(argv[2]);
 
        while(file >> temp) {
            bool match = 0, duplicate = 0;

            // array doubling algorithm if current array is full
            if(wordCount == arrSize) {
                arrSize = arrSize * 2; // doubles the array size
                wordRecord *tempArray = new wordRecord[arrSize]; // temp array

                // fill temp array with current array elements
                for(int k = 0; k < arrSize / 2; k++) {
                    tempArray[k] = words[k];
                }
                
                // replace current array with temp array
                delete []words; 
                words = tempArray; 
                doubles++;
            }
            
            if(!isIgnoreWord(temp, top50)) { // if the word is not common

                // searches the array for the word
                for(int j = 0; j < arrSize; j++) {

                    // if the word already exists in the array, increase count by one
                    if(temp == words[j].word) {
                        words[j].count++;
                        duplicate = 1;
                    }
                } 

                // if the word doesn't already exist in the array, add to the array
                if(!duplicate) {
                    words[wordCount]= {temp, 1};
                    wordCount++;
                } 
            }
        }
        
        int totalWords = getTotalNumberNonIgnoreWords(words, wordCount); // counts the total number of non-distinct words
        sortArray(words, wordCount); // sorts array by count
        cout << "Array doubled: " << doubles << endl; // number of array doubles
        cout << "Distinct non-common words: " << wordCount << endl; // number of non-common words
        cout << "Total non-common words: " << totalWords << endl; // total non-common words in the file
        cout << "Probability of next 10 words from rank " << argv[1] << endl;
        cout << "---------------------------------------\n";
        printTenFromN(words, stoi(argv[1]), totalWords); // prints 10 words and their probabilites from the given rank
        delete []words; // relase words from memory
    }
    return 0;
}