#include "MovieInventory.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// MovieItem: node struct that will be stored in the MovieInventory BST

// this function sums the ratings in the BST
double sumRatingsHelper(MovieItem *node) {
  double sumRatings = 0.0;
  if(node == NULL) {
    return sumRatings;
  } else {
    sumRatings += node->rating;
    sumRatings += sumRatingsHelper(node->left);
    sumRatings += sumRatingsHelper(node->right);
    return sumRatings;
  }
}

//This function counts the number of nodes in the BST
int numNodesHelper(MovieItem *node) {
  int numNodes = 0;
  if(node == NULL) {
    return numNodes; // if empty, return 0
  } else {
    numNodes++;
    numNodes += numNodesHelper(node->left);
    numNodes += numNodesHelper(node->right);
    return numNodes;
  }
}

//This function searches the BST for a specific movie and returns a pointer to the node
MovieItem* searchTitleHelper(MovieItem *node, string title) {
  if(node == NULL) {
    return NULL;
  } else if(title == node->title) { 
      return node;
  } else if(title < node->title) {
      node = searchTitleHelper(node->left, title);
  } else if (title > node->title) {
      node = searchTitleHelper(node->right, title);
  }
    return node;
}

// prints a all movies on a given subtree, in order
void printMoviesHelper(MovieItem *m) {
  if(m != NULL) {
    printMoviesHelper(m->left);
    cout << "Movie: " << m->title << " " << m->rating << endl;
    printMoviesHelper(m->right);
  }
}

// searches for movies based on minimum rating and minimum year, in order
void searchMoviesHelper(MovieItem* m, float rating, int year) {
  if(m != NULL) { 
    searchMoviesHelper(m->left, rating, year);
    if(m->rating >= rating && m->year >= year) {
      cout << m->title << "(" << m->year << ") " << m->rating << endl;
    }
    searchMoviesHelper(m->right, rating, year);
  } 
}

// finds the parent node in a tree and returns a pointer to the parent node
MovieItem* findParentHelper(MovieItem *subRoot, MovieItem *m) {
  if(subRoot == NULL) {
    return NULL; 
  } else {
    string search = m->title, currNode = subRoot->title;
    MovieItem* node = NULL;
    if(subRoot->left->title == search || subRoot->right->title == search) { // parent found
      return node;
    } else if(search < currNode){ 
      node = findParentHelper(node->left, m);
    } else if (search > currNode) {
      node = findParentHelper(node->right, m);
    }
    return node;
  }
}

// finds the minimum node in a tree and returns a pointer to that node
MovieItem* findMinHelper(MovieItem* node) {
  if(node == NULL) {
    return NULL;
  } else if(node->left != NULL){ // min node found
    node = findMinHelper(node->left);
  } 
  return node;
}

// deletes a specific node from the tree and rebalances
MovieItem* deleteNodeHelper(MovieItem* currNode, string title) {
  if(currNode == NULL) {
    return NULL;
  } else if (title < currNode->title){
    currNode->left = deleteNodeHelper(currNode->left, title);
  } else if (title > currNode->title) {
    currNode->right = deleteNodeHelper(currNode->right, title);
  } else { // node found
    if(currNode->left == NULL && currNode->right == NULL) { // no children 
      delete currNode;
      currNode = NULL;
    } else if(currNode->left == NULL) { // only right child
      delete currNode;
      currNode = currNode->right;
      delete currNode->right;
      currNode->right = NULL;
    } else if(currNode->right == NULL) { // only left child
      delete currNode;
      currNode = currNode->left;
      delete currNode->left;
      currNode->left = NULL;
    } else { // two children
      MovieItem* min = findMinHelper(currNode->right);

      //replace components of deleted node
      delete currNode;
      currNode = min;
      currNode->right = deleteNodeHelper(currNode->right, min->title);
    }
  }
  return currNode;
}

// default constructor, sets root to null
MovieInventory::MovieInventory() {
  root = NULL;
}

// destructor, empties tree
MovieInventory::~MovieInventory() {
  while(root != NULL) {
    deleteMovieItem(root->title);
  }
}


// prints all movies
void MovieInventory::printMovieInventory() {
  if(root == NULL) {
    cout << "Tree is Empty. Cannot print" << endl;
  } else {
    printMoviesHelper(root);
  }
}


// adds movie to tree
void MovieInventory::addMovieItem(int ranking, string title, int year, float rating) {
  MovieItem *newNode = new MovieItem{ranking, title, year, rating};
  MovieItem *temp = root;
  MovieItem *parent = NULL;
  if(root == NULL) { // if BST is empty, set new node as root
    root = newNode;
  } else {
    while(temp != NULL) { //while not at leaf
      parent = temp;

      //traverses BST
      if(title < temp->title) {
        temp = temp->left;
      } else {
        temp = temp->right;
      }
    }

    //inserts node at appropriate position
    if(title < parent->title) {
      parent->left = newNode; 
    } else {
      parent->right = newNode;
    }
  } 
}

// prints the details of a given movie
void MovieInventory::getMovie(string title) {
  MovieItem* node = searchTitleHelper(root, title); // finds node with matching title
  if(node == NULL) {
    cout << "Movie not found." << endl; // if movie not found in BST
  } else {
    cout << "Movie Info:" << endl;
    cout << "==================" << endl;
    cout << "Ranking:" << node->ranking << endl; 
    cout << "Title :" << node->title << endl; 
    cout << "Year :" << node->year << endl; 
    cout << "rating :" << node->rating << endl;
  }
}

// returns a selection of movies with given min ratings and earliest year
void MovieInventory::searchMovies(float rating, int year) {
  if(root == NULL) {
    cout << "Tree is Empty. Cannot query Movies" << endl;  // if tree is empty
  } else {
    cout << "Movies that came out after " << year << " with rating at least " << rating << ":" << endl;
    searchMoviesHelper(root, rating, year); // prints movies that satisfy criteria
  }
}

// calculates the average rating of all movies in the BST
void MovieInventory::averageRating() {
  int numNodes = numNodesHelper(root); // counts number of nodes
  cout << "Average rating:";
  if(numNodes == 0) {
    cout << "0.0\n";
  } else {
    double average = sumRatingsHelper(root) / numNodes * 1.0; // calculates average
    cout << average << endl;
  }
}

// deletes specific movie with given title (see deleteNodeHelper function)
void MovieInventory::deleteMovieItem(string title)
{
  deleteNodeHelper(root, title);
}

//left rotates the BST
void MovieInventory::leftRotate(string title)
{ 
  MovieItem *pivotNode = searchTitleHelper(root, title); // finds node to rotate about
  if(pivotNode != NULL) { 
    MovieItem *temp = pivotNode->right;
    pivotNode->right = temp->left;
    temp->left = pivotNode;
    MovieItem *parent = findParentHelper(root, pivotNode); // finds parent node
    if(parent == NULL) {
      root = temp; // if rotating at root, replace root
    } else if(parent->left->title == pivotNode->title) { 
      parent->left = temp; 
    } else if (parent->right->title == pivotNode->title) {
      parent->right = temp;
    }
    //resets parent pointers depending on which child the pivot node was to the 
    // parent node
  }
}