/*
** Name:
** Assighment: Week 1 - HW0
** Description: Student Grades Array of Structures
**
** Command-line example:
** hw0 students.csv output.csv C A
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct studentData {
   string studentName;
   int homework;
   int recitation;
   int quiz;
   int exam;
   double average;
};

void addStudentData(studentData students[], string studentName, int homework, int
recitation, int quiz, int exam, int length)
{
   // insantiate studentData struct
   // calculate average
   // populate all struct variables
   // add struct to the students array
}

char calcLetter(double avg)
{
   // calculate grade letter
   // >90 = A
   // 80-89.9 = B
   // 70-79.9 = C
   // 60-69.9 = D
   // <60 = F
   
   // return grade
}

void printList(const studentData students[], int length)
{
   // loop through students and display output
}

int main(int argc, char* argv[])
{
   // declare local variables
   
   ifstream in_file;
   ofstream out_file;
 
   // read command-line arguments
 
   studentData students[10];
 
   while()
   {
      // use getline() to parse students.csv

      // addStudentData();
   }
   
   // write to output.csv based on lower bound and upper bound 
   // which are retrieved from command-line args
   
   // printList();

   return 0;
}