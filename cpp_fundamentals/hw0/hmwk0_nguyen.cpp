/*
** Name: Kevin Nguyen
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

void addStudentData(studentData students[], string studentName, int homework, int recitation, int quiz, int exam, int length) {
   double avg = (homework + recitation + quiz + exam) / 4.0; // calculate average

   // insantiate studentData struct
   // populate all struct variables
   studentData newStudent = {studentName, homework, recitation, quiz, exam, avg}; 
   students[length] = newStudent; // add struct to the students array
}

char calcLetter(double avg) {
   if(avg >= 90) {
        return 'A';
   } else if (avg >= 80) {
        return 'B';
   } else if (avg >= 70) {
        return 'C';
   } else if (avg >= 60) {
        return 'D';
   } else {
        return 'F';
   }
}

void printList(const studentData students[], int length) {
   // loop through students and display output
   for(int i = 0; i < length; i++) {
      cout << students[i].studentName << " earned " << students[i].average << " which is an " << calcLetter(students[i].average) << endl;
   }
}

int main(int argc, char* argv[]) {
   // declare local variables
   // read command-line arguments
   ifstream in_file(argv[1]);
   ofstream out_file(argv[2]);

   studentData students[10];
   string line, comp, name;
   int studentCount = 0, hw, rec, quiz, exam;

   while(getline(in_file, line)) {
      istringstream ss(line);

      // use getline() to parse students.csv
      int count = 1;
      while(getline(ss, comp, ',')) {
         switch(count) {
            case 1:
               name = comp;
               break;
            case 2:
               hw = stoi(comp);
               break;
            case 3: 
               rec = stoi(comp);
               break;
            case 4: 
               quiz = stoi(comp);
               break;
            case 5:
               exam = stoi(comp);
               break;
            default:
               break;
         }
         count++;
      }
      addStudentData(students, name, hw, rec, quiz, exam, studentCount); // adds student to the array
      studentCount++; //counts the number of students in the array
   }

   printList(students, studentCount);
   
   // write to output.csv based on lower bound and upper bound 
   // which are retrieved from command-line args
   for(int i = 0; i < studentCount; i++) {
      char grade = calcLetter(students[i].average);
      if(grade <= *argv[3] && grade >= *argv[4]) {
         out_file << students[i].studentName << "," << students[i].average << "," << grade << endl;
      }
   }

   out_file.close();
   in_file.close();

   return 0;
}