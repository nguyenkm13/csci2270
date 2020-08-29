// CS2270 Summer 2020
// Author: Kevin Nguyen
// Recitation: 321 - James Watson
// Lab 1

#include<iostream>
using namespace std;

using namespace std;
int main(int argc, char const *argv[]) {
  int foo[5] = {1, 2, 3, 4, 5};

  cout << "Addresses of elements: " << endl;
  for(int i = 0; i < 5; i++) {
    cout << "foo[" << i << "]: " << &foo[i] << endl;
  }

  cout << endl;

  cout << "Elements:" << endl;;
  
  for(int i = 0; i < 5; i++) {
    int *ptr = &foo[i];

    cout << "foo[" << i << "]: " << *ptr << endl;
  }

  cout << endl;

  return 0;
}
