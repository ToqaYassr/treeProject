//Assume having an application which stores the data of students in binary search tree and AVL trees,
//where each student has an id, a name, department and a GPA. In case of BST and AVL the key of the
//tree is the id, there are four functions as follows:
//1. Add a student (write the id “from 0 to 100”, name, GPA, and department)
//2. Remove a student using id
//3. Search for student using id (if found print the student information)
//4. Print all and Department Report (all the information of students are printed sorted by id and
//count students per department)
//The students also can be inserted in min or max heap or displayed sorted by gpa (the key is gpa) where
//a report of department appears, the number of students per department.
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include"DataStructures.cpp"
static int CSdep = 0, AIdep = 0, DSdep = 0, ISdep = 0, ITdep = 0;

using namespace std;


// input file
fstream input(get_directory_path()+"\\inputFile.txt");

string get_directory_path(){


    return std::filesystem::current_path().parent_path().string();
}
ofstream output(get_directory_path()+"\\inputFile.txt",ios::app);

///Department functions///

// a function that counts the number of students in each department
void countDep(string dep) {
    if (dep == "CS") {
        CSdep++;
    } else if (dep == "AI") {
        AIdep++;
    } else if (dep == "DS") {
        DSdep++;
    } else if (dep == "IS") {
        ISdep++;
    } else if (dep == "IT") {
        ITdep++;
    }
}

//  a function that removes a student from the department count
void removeDep(string dep) {
    if (dep == "CS") {
        CSdep--;
    } else if (dep == "AI") {
        AIdep--;
    } else if (dep == "DS") {
        DSdep--;
    } else if (dep == "IS") {
        ISdep--;
    } else if (dep == "IT") {
        ITdep--;
    }
}

// a function that prints the number of students in each department
void printDep() {
    cout << "Number of students in CS department: " << CSdep << endl;
    cout << "Number of students in AI department: " << AIdep << endl;
    cout << "Number of students in DS department: " << DSdep << endl;
    cout << "Number of students in IS department: " << ISdep << endl;
    cout << "Number of students in IT department: " << ITdep << endl;
}

// function to convert string to int
int string_to_int(string s) {
    int num = 0;
    for (int i = 0; i < s.length(); i++) {
        num = num * 10 + (s[i] - '0');
    }
    return num;
}

// function to convert string to float
float string_to_float(string s) {
    if(s.find_first_of('.') == string::npos){
        return string_to_int(s);
    }
    float num = 0;
    int i = 0;
    while (s[i] != '.') {
        num = num * 10 + (s[i] - '0');
        i++;
    }
    i++;
    float k = 0.1;
    while (i < s.length()) {
        num = num + (s[i] - '0') * k;
        k = k / 10;
        i++;
    }
    return num;
}


class System {
    BST students_tree;
    AVL students_AVL_tree;
    MinHeap studentsMinHeap_tree;
    MaxHeap studentsMaxHeap_tree;

//// BSTPASS FUNCTIONS start ////
    // add a student to the BST
    void addStuBST() {
        student s;

        bool flag = true;
        cout << "Enter the student id: ";
        string id;

        while (flag) {
            cin >> id;
            if (string_to_int(id) <= 100 && students_tree.searchRec(string_to_int(id)).getId() == -1) {
                flag = false;
            } else if (students_tree.searchRec(string_to_int(id)).getId() != -1) {
                cout << "This id is already exist, please enter a valid id: ";
            } else {
                cout << "invalid id, please enter a valid id: ";
            }

        }
        s.setId(string_to_int(id));
        output<<"\n"<<id <<endl;

        cout << "Enter the student name: ";
        string name;
        cin.ignore();
        getline(cin,name);
        s.setName(name);
        output<<name<<endl;

        cout << "Enter the student GPA: ";
        string gpa;
        flag = true;
        while (flag) {
            cin >> gpa;
            if (string_to_float(gpa) <= 4) {
                flag = false;
            } else {
                cout << "invalid GPA, please enter a valid GPA: ";
            }
        }
        s.setGpa(string_to_float(gpa));
        output<<gpa <<endl;
        cout << "Enter the student Department: ";
        string dep;
        flag = true;
        while (flag) {
            cin >> dep;
            if (dep == "CS" || dep == "IT" || dep == "IS" || dep == "AI" || dep == "DS") {
                flag = false;
            } else {
                cout << "invalid Department, please enter a valid Department: ";
            }
        }
        s.setDepartment(dep);
        output<<dep ;
        countDep(dep);

        students_tree.insertRec(string_to_int(id), s);
    }

//    Remove a student from the BST
    void removeStuBST() {
        cout << "Enter the student id: ";
        string id;
        bool flag = true;
        while (flag) {
            cin >> id;
            if (string_to_int(id) <= 100) {
                flag = false;
            } else {
                cout << "invalid id, please enter a valid id: ";
            }
        }

//        if a student with this id is not found
        if (students_tree.searchRec(string_to_int(id)).getId() == -1) {
            cout << "student not found" << endl;
            return;
        }


        //    remove the student from the department count
        student s = students_tree.searchRec(string_to_int(id));

        ofstream temp;
        temp.open("temp.txt");
        string line;
        while (getline(input,line))
        {
            if (line != id || line!=s.getName()||line!= to_string(s.getGpa())||line!=s.getDepartment() )
            {
                temp << line << endl;
            }

        }

        temp.close();
        input.close();
        remove("inputFile.txt");
        rename("temp.txt","inputFile.txt");
        removeDep(s.getDepartment());

        students_tree.deleteRec(string_to_int(id));


    }

    // search for a student in the BST
    student searchstuBST() {

        cout << "Enter the student id: ";
        string id;
        bool flag = true;
        while (flag) {
            cin >> id;
            if (string_to_int(id) <= 100) {
                flag = false;
            } else {
                cout << "invalid id, please enter a valid id: ";
            }
        }
        return students_tree.searchRec(string_to_int(id));
    }

    void load_BST_from_file() {
        //    a program that reads the input file line by line and stores the data in a student object then prints the student information
        string n_students;
        getline(input, n_students);
        string id;
        string name;
        string department;
        string gpa;
//    printing all input file data line by line
        for (int i = 0; i < string_to_int(n_students); i++) {
            getline(input, id);
            getline(input, name);
            getline(input, gpa);
            getline(input, department);
            student s(string_to_int(id), name, string_to_float(gpa), department);
            countDep(department);
            students_tree.insertRec(string_to_int(id), s);

        }
    }

    void BST_pass() {
        load_BST_from_file();
        int choice = secondMenu();
        while (choice != 5) {
            if (choice == 1) {
                addStuBST();
            } else if (choice == 2) {
                removeStuBST();
            } else if (choice == 3) {
                student s = searchstuBST();
                if (s.getId() == -1) {
                    cout << "student not found" << endl;
                } else {
                    s.print();
                }
            } else if (choice == 4) {
                students_tree.printInOrderRecursive();
                printDep();

            }
            choice = secondMenu();
        }

    }

    /////// BST PATH FUNCTIONS END ///////



//// AVL PATH FUNCTIONS START ////

// insert a student in the AVL
    void addStuAVL() {
        student s;

        bool flag = true;
        cout << "Enter the student id: ";
        string id;
        while (flag) {
            cin >> id;
            if (string_to_int(id) <= 100 && students_AVL_tree.searchRec(string_to_int(id)).getId() == -1) {
                flag = false;
            } else if (students_AVL_tree.searchRec(string_to_int(id)).getId() != -1) {
                cout << "This id is already exist, please enter a valid id: ";
            } else {
                cout << "invalid id, please enter a valid id: ";
            }

        }
        s.setId(string_to_int(id));
        output<<"\n"<<id <<endl;
        cout << "Enter the student name: ";
        string name;
        cin.ignore();
        getline(cin,name);
        s.setName(name);
        output<<name <<endl;
        cout << "Enter the student GPA: ";
        string gpa;
        flag = true;
        while (flag) {
            cin >> gpa;
            if (string_to_float(gpa) <= 4) {
                flag = false;
            } else {
                cout << "invalid GPA, please enter a valid GPA: ";
            }
        }
        s.setGpa(string_to_float(gpa));
        output<<gpa<<endl;
        cout << "Enter the student Department: ";
        string dep;
        flag = true;
        while (flag) {
            cin >> dep;
            if (dep == "CS" || dep == "IT" || dep == "IS" || dep == "AI" || dep == "DS") {
                flag = false;
            } else {
                cout << "invalid Department, please enter a valid Department: ";
            }
        }
        s.setDepartment(dep);
        output<<dep;
        countDep(dep);
        students_AVL_tree.insertRec(string_to_int(id), s);
    }

//    search for a student in the AVL
    student searchStuAVL() {

        cout << "Enter the student id: ";
        string id;
        bool flag = true;
        while (flag) {
            cin >> id;
            if (string_to_int(id) <= 100) {
                flag = false;
            } else {
                cout << "invalid id, please enter a valid id: ";
            }
        }
        return students_AVL_tree.searchRec(string_to_int(id));
    }



//delete a student from the AVL
    void removeStuAVL() {
        cout << "Enter the student id: ";
        string id;
        bool flag = true;
        while (flag) {
            cin >> id;
            if (string_to_int(id) <= 100) {
                flag = false;
            } else {
                cout << "invalid id, please enter a valid id: ";
            }
        }

//        if a student with this id is not found
        if (students_AVL_tree.searchRec(string_to_int(id)).getId() == -1) {
            cout << "student not found" << endl;
            return;
        }

        //    remove the student from the department count
        student s = students_AVL_tree.searchRec(string_to_int(id));
        removeDep(s.getDepartment());

        students_AVL_tree.deleteRec(string_to_int(id));
    }





    void load_AVL_from_file() {
        //    a program that reads the input file line by line and stores the data in a student object then prints the student information
        string n_students;
        getline(input, n_students);
        string id;
        string name;
        string department;
        string gpa;
        for (int i = 0; i < string_to_int(n_students); i++) {
            getline(input, id);
            getline(input, name);
            getline(input, gpa);
            getline(input, department);
            student s(string_to_int(id), name, string_to_float(gpa), department);
            countDep(department);
            students_AVL_tree.insertRec(string_to_int(id), s);
        }
    }


    void AVL_pass() {
        load_AVL_from_file();
        int choice = secondMenu();
        while (choice != 5) {
            if (choice == 1) {
                addStuAVL();
            } else if (choice == 2) {
                removeStuAVL();
            } else if (choice == 3) {
                student s = searchStuAVL();
                if (s.getId() == -1) {
                    cout << "student not found" << endl;
                } else {
                    s.print();
                }
            } else if (choice == 4) {

                students_AVL_tree.printInOrderRecursive();

                printDep();

            }
            choice = secondMenu();
        }

    }







//// AVL PASS FUNCTIONS END ////



//// MINHEAP PASS FUNCTIONS START ////


//add a student to the minheap
    void addStuMinHeap() {
        student s;

        bool flag = true;
        cout << "Enter the student id: ";
        string id;
        while (flag) {
            cin >> id;
            if (string_to_int(id) <= 100 && studentsMinHeap_tree.search(string_to_int(id)).getId() == -1) {
                flag = false;
            } else if (studentsMinHeap_tree.search(string_to_int(id)).getId() != -1) {
                cout << "This id is already exist, please enter a valid id: ";
            } else {
                cout << "invalid id, please enter a valid id: ";
            }

        }
        s.setId(string_to_int(id));
        output<<"\n"<<id <<endl;
        cout << "Enter the student name: ";
        string name;
        cin.ignore();
        getline(cin,name);
        s.setName(name);
        output<<name <<endl;
        cout << "Enter the student GPA: ";
        string gpa;
        flag = true;
        while (flag) {
            cin >> gpa;
            if (string_to_float(gpa) <= 4) {
                flag = false;
            } else {
                cout << "invalid GPA, please enter a valid GPA: ";
            }
        }
        s.setGpa(string_to_float(gpa));
        output<<gpa<<endl;
        cout << "Enter the student Department: ";
        string dep;
        flag = true;
        while (flag) {
            cin >> dep;
            if (dep == "CS" || dep == "IT" || dep == "IS" || dep == "AI" || dep == "DS") {
                flag = false;
            } else {
                cout << "invalid Department, please enter a valid Department: ";
            }
        }
        s.setDepartment(dep);
        output<<dep;
        countDep(dep);
        studentsMinHeap_tree.insert(s);
    }



//    search for a student in the minheap
    student searchStuMinHeap() {

        cout << "Enter the student id: ";
        string id;
        bool flag = true;
        while (flag) {
            cin >> id;
            if (string_to_int(id) <= 100) {
                flag = false;
            } else {
                cout << "invalid id, please enter a valid id: ";
            }
        }
        return studentsMinHeap_tree.search(string_to_int(id));
    }


//    delete a student from the minheap
    void removeStuMinHeap() {
        cout << "Enter the student id: ";
        string id;
        bool flag = true;
        while (flag) {
            cin >> id;
            if (string_to_int(id) <= 100) {
                flag = false;
            } else {
                cout << "invalid id, please enter a valid id: ";
            }
        }

//        if a student with this id is not found
        if (studentsMinHeap_tree.search(string_to_int(id)).getId() == -1) {
            cout << "student not found" << endl;
            return;
        }

//        remove the student from the department count
        student s = studentsMinHeap_tree.search(string_to_int(id));
        removeDep(s.getDepartment());

        studentsMinHeap_tree.deleteMinHeap(string_to_int(id));


    }


// load the minheap from the file
    void load_minheap_from_file() {
        //    a program that reads the input file line by line and stores the data in a student object then prints the student information
        string n_students;
        getline(input, n_students);
        string id;
        string name;
        string department;
        string gpa;
        for (int i = 0; i < string_to_int(n_students); i++) {
            getline(input, id);
            getline(input, name);
            getline(input, gpa);
            getline(input, department);
            student s(string_to_int(id), name, string_to_float(gpa), department);
            countDep(department);
            studentsMinHeap_tree.insert(s);
        }
    }




    void MinHeap_pass(){

        load_minheap_from_file();
        int choice = secondMenu();
        while (choice != 5) {
            if (choice == 1) {
                addStuMinHeap();
            } else if (choice ==2) {
                removeStuMinHeap();
            } else if (choice == 3) {
                student s = searchStuMinHeap();
                if (s.getId() == -1) {
                    cout << "student not found" << endl;
                } else {
                    s.print();
                }
            } else if (choice == 4) {

                studentsMinHeap_tree.printHeap();
                printDep();

            }
            choice = secondMenu();
        }



    }








//// MINHEAP PASS FUNCTIONS END ////


//// MAXHEAP PASS FUNCTIONS START ////

//  load the max heap from the file
    void load_maxheap_from_file() {
        //    a program that reads the input file line by line and stores the data in a student object then prints the student information
        string n_students;
        getline(input, n_students);
        string id;
        string name;
        string department;
        string gpa;
        for (int i = 0; i < string_to_int(n_students); i++) {
            getline(input, id);
            getline(input, name);
            getline(input, gpa);
            getline(input, department);
            student s(string_to_int(id), name, string_to_float(gpa), department);
            countDep(department);
            studentsMaxHeap_tree.insert(s);
        }
    }


//    add student
    void addStuMaxHeap() {
        student s;
        cout << "Enter the student id: ";
        bool flag = true;
        string id;
        while (flag) {
            cin >> id;
            if (string_to_int(id) <= 100 && studentsMaxHeap_tree.search(string_to_int(id)).getId() == -1) {
                flag = false;
            } else if (studentsMaxHeap_tree.search(string_to_int(id)).getId() != -1) {
                cout << "This id is already exist, please enter a valid id: ";
            } else {
                cout << "invalid id, please enter a valid id: ";
            }

        }
        s.setId(string_to_int(id));
        output<<"\n"<<id <<endl;
        cout << "Enter the student name: ";
        string name;
        cin.ignore();
        getline(cin,name);
        s.setName(name);
        output<<name<<endl;
        cout << "Enter the student GPA: ";
        string gpa;
        flag = true;
        while (flag) {
            cin >> gpa;
            if (string_to_float(gpa) <= 4) {
                flag = false;
            } else {
                cout << "invalid GPA, please enter a valid GPA: ";
            }
        }
        s.setGpa(string_to_float(gpa));
        output<<gpa<<endl;
        cout << "Enter the student Department: ";
        string dep;
        flag = true;
        while (flag) {
            cin >> dep;
            if (dep == "CS" || dep == "IT" || dep == "IS" || dep == "AI" || dep == "DS") {
                flag = false;
            } else {
                cout << "invalid Department, please enter a valid Department: ";
            }
        }
        s.setDepartment(dep);
        output<<dep;
        countDep(dep);
        studentsMaxHeap_tree.insert(s);
    }


//    remove student from the maxheap

    void removeStuMaxHeap() {
        cout << "Enter the student id: ";
        string id;
        bool flag = true;
        while (flag) {
            cin >> id;
            if (string_to_int(id) <= 100) {
                flag = false;
            } else {
                cout << "invalid id, please enter a valid id: ";
            }
        }

//        if the student is not found
        if (studentsMaxHeap_tree.search(string_to_int(id)).getId() == -1) {
            cout << "student not found" << endl;
            return;
        }

//        remove the student from the department count
        student s = studentsMaxHeap_tree.search(string_to_int(id));
        removeDep(s.getDepartment());

        studentsMaxHeap_tree.deleteMaxHeap(string_to_int(id));
    }

//    search for a student in the maxheap
    student searchStuMaxHeap() {
        cout << "Enter the student id: ";
        string id;
        bool flag = true;
        while (flag) {
            cin >> id;
            if (string_to_int(id) <= 100) {
                flag = false;
            } else {
                cout << "invalid id, please enter a valid id: ";
            }
        }
        return studentsMaxHeap_tree.search(string_to_int(id));
    }


    void MaxHeap_pass(){

        load_maxheap_from_file();
        int choice = secondMenu();
        while (choice != 5) {
            if (choice == 1) {
                addStuMaxHeap();
            } else if (choice ==2) {
                removeStuMaxHeap();
            } else if (choice == 3) {
                student s = searchStuMaxHeap();
                if (s.getId() == -1) {
                    cout << "student not found" << endl;
                } else {
                    s.print();
                }
            } else if (choice == 4) {

                studentsMaxHeap_tree.printHeap();
                printDep();

            }
            choice = secondMenu();
        }


    }




//// MAXHEAP PASS FUNCTIONS END ////

//// system class functions start ////
// a function that uses the first menu
    void firstMenu() {
        cout << "Choose Data Structure: " << endl;
        cout << "1. BST" << endl;
        cout << "2. AVL" << endl;
        cout << "3. Min Heap" << endl;
        cout << "4. Max Heap" << endl;
        cout << "5. Exit Program" << endl;
//        defensive programming to make sure that the user enters a valid choice
        bool flag = true;
        string choice;
        while (flag) {
            cin >> choice;
            if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5") {
                flag = false;
            } else {
                cout << "Invalid choice, please enter a valid choice: " << endl;
            }
        }

        if (choice == "5") {
            exit(0);
        } else if (choice == "1") {
            BST_pass();
        } else if (choice == "2") {
            AVL_pass();
        } else if (choice == "3") {
            MinHeap_pass();
        } else if (choice == "4") {
            MaxHeap_pass();
        }

    }
//    a function that uses the second menu

    int secondMenu() {
        cout << "Choose one of the following options: " << endl;
        cout << "1. Add student" << endl;
        cout << "2. Remove student" << endl;
        cout << "3. Search student" << endl;
        cout << "4. Print All (sorted by id)" << endl;
        cout << "5. Return to main menu" << endl;
        cout << "Enter your choice: " << endl;
//        defensive programming to make sure that the user enters a valid choice
        bool flag = true;
        string choice;

        while (flag) {
            cin >> choice;
            if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5") {
                flag = false;
            } else {
                cout << "Invalid choice, please enter a valid choice: " << endl;
            }
        }
        return string_to_int(choice);
    }
    //// system class functions end ////


public:

//    display application interface
    void display_app() {
        cout << "Welcome to our application" << endl;
        while (true) {
            firstMenu();
        }
    }

};


int main() {
    System s;
    s.display_app();



    return 0;

}





