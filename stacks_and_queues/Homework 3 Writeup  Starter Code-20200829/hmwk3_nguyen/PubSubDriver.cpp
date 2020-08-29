/****************************************************************/
/*                Publisher Subscriber Driver File              */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "PubSub.hpp"
#include <iostream>
// you may include more libraries as needed

using namespace std;

/*
 * Purpose: displays a menu with options
 * @param none
 * @return none
 */
void menu()
{
	cout << "*----------------------------------------*" << endl;
	cout << "Choose an option:" << endl;
    cout << "1. Publisher (Publish items to the queue)" << endl;
	cout << "2. Subscriber (Retrieve items from the queue)" << endl;
	cout << "3. Return the queue size and exit" << endl;
	cout << "*----------------------------------------*" << endl;
}
// Use getline for reading
int main(int argc, char const *argv[])
{
	PubSub queue; // declare an empty queue
	int selection = 0; // int to store menu selection
	do { // loop while selection is not 3
		menu(); // menu function
		string input;
		getline(cin, input); //stores user input
		selection = stoi(input); // converts user input into an int
		switch(selection) { // switch based on user input
			case 1: {
				cout << "Enter the number of items to be published:\n";
				getline(cin, input); // user enters the number of items to be published
				int numItems = stoi(input);
				for(int i = 0; i < numItems; i++) { // prompts user to enter the item 
					cout << "Item" << i+1 << ":\n";
					getline(cin, input); // stores item
					queue.enqueue(input); // enqueues item onto queue
				}
				break;
			}
			case 2: {
				cout << "Enter the number of items to be retrieved:\n";
				getline(cin, input); // user enters the number of items to be retrieved
				int numItems = stoi(input);
				for(int j = 0; j < numItems; j++) { 
					if(queue.isEmpty()) {
						cout << "No more items to retrieve from queue\n";
						break; // if queue is empty, print statement and break out of loop
					} 
					cout << "Retrieved: " << queue.peek() << endl; //returns the item retrieved
					queue.dequeue(); //dequeues
				}
				break;
			}
			case 3: { 
				cout << "Number of items in the queue:" << queue.queueSize() << endl; // returns the number of items in the queue
				break;
			}
			default: {
				break;
			}
		}
	} while(selection != 3);

	return 0;
}