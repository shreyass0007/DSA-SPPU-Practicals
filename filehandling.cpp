#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student {
public:
    string rollNumber, name, division, address;

    // Function to add a student record
    void addStudent() {
        ofstream file("students.txt", ios::app);
        cout << "Enter Roll Number: ";
        cin >> rollNumber;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Division: ";
        getline(cin, division);
        cout << "Enter Address: ";
        getline(cin, address);

        file << rollNumber << "," << name << "," << division << "," << address << endl;
        file.close();
        cout << "Student record added successfully!\n";
    }

    // Function to display a student record
    void displayStudent() {
        ifstream file("students.txt");
        string searchRoll, line;
        cout << "Enter Roll Number to search: ";
        cin >> searchRoll;
        
        bool found = false;
        while (getline(file, line)) {
            if (line.find(searchRoll + ",") == 0) { // Check if roll number matches
                cout << "Student Details: " << line << endl;
                found = true;
                break;
            }
        }
        if (!found) cout << "No record found!\n";
        file.close();
    }

    // Function to delete a student record
    void deleteStudent() {
        ifstream file("students.txt");
        ofstream temp("temp.txt");
        string searchRoll, line;
        cout << "Enter Roll Number to delete: ";
        cin >> searchRoll;

        bool found = false;
        while (getline(file, line)) {
            if (line.find(searchRoll + ",") != 0) {
                temp << line << endl;
            } else {
                found = true;
            }
        }
        file.close();
        temp.close();

        remove("students.txt");
        rename("temp.txt", "students.txt");

        if (found) cout << "Record deleted successfully!\n";
        else cout << "No record found!\n";
    }
};

int main() {
    Student student;
    int choice;
    do {
        cout << "\n1. Add Student\n2. Display Student\n3. Delete Student\n4. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: student.addStudent(); break;
            case 2: student.displayStudent(); break;
            case 3: student.deleteStudent(); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 4);
    return 0;
}
