#include<iostream>
#include<string>
using namespace std;
class student {
    int id;
    string name;
    string department;
    float gpa;
public:
    student() {
        id = -1;
        name = "not found";
        department = "not found";
        gpa = -1;
    }

    student(int id, string name, float gpa, string department) {
        this->id = id;
        this->name = name;
        this->department = department;
        this->gpa = gpa;
    }

// setters
    void setId(int id) {
        this->id = id;
    }

    void setName(string name) {
        this->name = name;
    }

    void setDepartment(string department) {
        this->department = department;
    }

    void setGpa(float gpa) {
        this->gpa = gpa;
    }

//    getters
    int getId() {
        return id;
    }

    string getName() {
        return name;
    }

    string getDepartment() {
        return department;
    }

    float getGpa() {
        return gpa;
    }


//    prints the student information

    void print() {
        cout << "Student ID: " << id << endl;
        cout << "Student Name: " << name << endl;
        cout << "Student GPA: " << gpa << endl;
        cout << "Student Department: " << department << endl;
    }
};
