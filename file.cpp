#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class Student {
    int rollNo;
    string name;
    string div;
    string address;
public:

    void addData() {
        ofstream file("students.txt", ios::app);
        cout << "Enter Roll No: ";
        cin >> rollNo;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Division: ";
        cin >> div;
        cout << "Enter Address: ";
        cin.ignore();
        getline(cin, address);
        file << rollNo << " " << name << " " << div << " " <<address << endl;
        file.close();
        cout << "Student data added successfully.\n";
    }

    void displayData() {
        ifstream file("students.txt");
        if (!file) {
            cout << "No student data found.\n";
        return;
        }
        int searchRoll;
        cout << "Enter Roll No to display (0 to display all): ";
        cin >> searchRoll;
        bool found = false;
        while (file >> rollNo) {
            file.ignore();
            getline(file, name, ' ');
            file >> div;
            file.ignore();
            getline(file, address);
            if (searchRoll == 0 || searchRoll == rollNo) {
                cout << "Roll No: " << rollNo << ", \nName: " << name << ", Division: " << div << ", Address: " << 					address << endl;
                found = true;
            }
        }
        if (!found && searchRoll != 0) {
            cout << "No student found with Roll No: " << searchRoll << endl;
        }
        file.close();
    }

    void deleteData() {
        ifstream file("students.txt");
        ofstream temp("temp.txt");
        if (!file) {
            cout << "No student data found.\n";
            return;
        }
        int deleteRoll;
        cout << "Enter Roll No to delete: ";
        cin >> deleteRoll;
        bool found = false;
        while (file >> rollNo) {
            file.ignore();
            getline(file, name, ' ');
            file >> div;
            file.ignore();
            getline(file, address);
            if (rollNo != deleteRoll) {
                temp << rollNo << " " << name << " " << div << " " << address << endl;
            } else {
            found = true;
            }
        }
        file.close();
        temp.close();
        if (found) {remove("students.txt");
            rename("temp.txt", "students.txt");
            cout << "Student with Roll No " << deleteRoll << " deleted successfully.\n";
        } else {
        remove("temp.txt");
        cout << "No student found with Roll No: " << deleteRoll << endl;
        }
    }
};

int main() {
    Student student;
    int choice;
    do {
        cout << "\n1. Add Student\n2. Display Student(s)\n3. Delete Student\n4. Exit\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                student.addData();
                break;
            case 2:
                student.displayData();
                break;
            case 3:
                student.deleteData();
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 4);
return 0;
}
