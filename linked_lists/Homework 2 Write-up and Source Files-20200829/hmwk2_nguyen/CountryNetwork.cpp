/****************************************************************/
/*                CountryNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CountryNetwork */
/*     This class uses a linked-list of Country structs to      */
/*     represent communication paths between nations             */
/****************************************************************/

#include "CountryNetwork.hpp"

using namespace std;

/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
CountryNetwork::CountryNetwork()
{
    head = NULL; // sets head to null for empty list
}


/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool CountryNetwork::isEmpty()
{
    if(head == NULL) {
        return 1; // if head is null (empty), return true
    } else {
        return 0; // if head is not null (not empty), return false
    }
}


/* DONE
 * Purpose: Add a new Country to the network
 *   between the Country *previous and the Country that follows it in the network.
 * @param previous name of the Country that comes before the new Country
 * @param countryName name of the new Country
 * @return none
 */
void CountryNetwork::insertCountry(Country* previous, string countryName) 
{    
    Country *temp = new Country; // temp country
    temp->name = countryName; // sets temp country name
    if(previous == NULL) { // if previous is null, set temp to head
        temp->next = head; 
        head = temp;
        cout << "adding: " << countryName << " (HEAD)" << endl;
    } else if(previous->next == NULL) { // if previous pointer is null, temp is tail
        previous->next = temp;
        temp->next = NULL;
        cout << "adding: " << countryName << " (prev: " << previous->name << ")" << endl;
    } else { // insert temp into middle of linked list
        temp->next = previous->next; 
        previous->next = temp;
        cout << "adding: " << countryName << " (prev: " << previous->name << ")" << endl;
    }
}


/* DONE
 * Purpose: delete the country in the network with the specified name.
 * @param countryName name of the country to delete in the network
 * @return none
 */
void CountryNetwork::deleteCountry(string countryName) 
{
    Country *temp = new Country; // temp country
    Country *left = new Country; // left country
    left = head; // set left country as head
    temp = head->next; // set temp country to next node
    if(head->name == countryName) { // if head is country to be deleted
        head = head->next; // sets next node as head
        delete left; // delete previous head
    } else {
        if(searchNetwork(countryName) == NULL) { // if country is not in linked list
            cout << "Country does not exist.\n";
        } else {
            while(temp != NULL) {
                if(temp->name == countryName) { // is temp country is delete country
                    left->next = temp->next; // reassign left pointer
                    delete temp; // delete node
                    return;
                }

                // shift temp and left
                left = temp; 
                temp = temp->next;
            }
        } 
    }
}

/* DONE
 * Purpose: populates the network with the predetermined countries
 * @param none
 * @return none
 */
void CountryNetwork::loadDefaultSetup()
{
    deleteEntireNetwork(); // deletes all nodes
    string countryArr[] = {"United States", "Canada", "Brazil", "India", "China", "Australia"}; // array of country names
    Country *temp = new Country; // temp country
    for(int i = 0; i < 6; i++) {
        Country *right = new Country; // placeholder country
        temp->name = countryArr[i]; // sets name of temp country
        if(i != 5) { // if the loop is not on the tail
            temp->next = right; 
        } else { // if the loop is on the tail, sets pointer to null
            temp->next = NULL; 
        }
        cout << "adding: " << countryArr[i]; 
        if(i == 0) { // if loop is on head
            head = temp; 
            cout << " (HEAD) \n";
        } else { // if loop is not on head
            cout << " (prev: " << countryArr[i-1] << ")\n";
        }
        temp = right; // shift temp along nodes
    }
}


/* DONE
 * Purpose: Search the network for the specified country and return a pointer to that node
 * @param countryName name of the country to look for in network
 * @return pointer to node of countryName, or NULL if not found
 * @see insertCountry, deletecountry
 */
Country* CountryNetwork::searchNetwork(string countryName)
{
    Country *temp = new Country; // temp country
    temp = head; // sets temp to head
    while(temp != NULL) { 
        if(temp->name == countryName) { 
            return temp; // returns the matching country node
        } else {
            temp = temp->next; // shifts anlong the linked list
        }
    }
    return NULL; // if no match found, return null
}

/* DONE
 * Purpose: deletes all countries in the network starting at the head country.
 * @param none
 * @return none
 */
void CountryNetwork::deleteEntireNetwork()
{
    if(head == NULL) {
        return; // does nothing if list is already empty
    } else {
        Country *temp = new Country; // temp country 
        temp = head->next; // sets temp to next node after head
        while(temp != NULL) { 
            cout << "deleting: " << head->name << endl;
            delete head; // deletes node
            head = temp; // resets head to next node in list
            temp = temp->next; // shifts temp to next node in list
        }
        // delete tail node
        cout << "deleting: " << head->name << endl; 
        delete head;
        head = NULL;
        cout << "Deleted network" << endl;
    }
}

/* DONE
 * Purpose: Transmit a message across the network to the
 *   receiver. Msg should be stored in each country it arrives
 *   at, and should increment that country's count.
 * @param receiver name of the country to receive the message
 * @param message the message to send to the receiver
 * @return none
 */
void CountryNetwork::transmitMsg(string receiver, string message)
{
    if(head == NULL) {
        cout << "Empty list\n"; // if head is null, list is empty
    } else {
        if(searchNetwork(receiver) == NULL) {
            cout << "Country not found\n"; // if country not found in list
        } else {
            Country *temp = new Country; // temp country
            temp = head; // sets temp country to head
            while(temp != NULL) {
                temp->message = message; // sets message of temp country
                temp->numberMessages++; // increments number of messages
                cout << temp->name << " [# messages received: " << temp->numberMessages << "] received: " << temp->message << endl;
                if(temp->name == receiver) {
                    return; // exists loop when the reciever is found
                }
                temp = temp->next; // shifts temp along nodes of list
            }
        }
    }
}

/* DONE
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CountryNetwork::printPath() 
{
    Country *temp = new Country; // temp country 
    temp = head; // sets temp to head
    cout << "== CURRENT PATH ==" << endl;
    if(head == NULL) {
        cout << "nothing in path" << endl; // if list is empty
    } else {
        // print country names
        while(temp != NULL) {
            cout << temp->name << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl; // prints null for tail
    }
    cout << "===" << endl;
}
