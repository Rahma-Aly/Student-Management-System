#include <iostream>
#include <string>
#include <fstream>
//The Library that includes vectors
#include <vector>
//The library that includes the clear screen function
#include <stdlib.h>
using namespace std;
//----------------------------------------- Class Declaration -----------------------------------------//

struct Address
{
    string city;
    string residentialArea;
    int zip;
};

struct Subject
{
    string courseName;
    float mark;
};

class Student
{
private:
    int studNum;
    string name;
    string dept;
    Address add;
    //Adding the vector class instead of an array to have a flexible array size.
    vector<Subject> subjects;
    char grade;
    float total;


public:
    //----------------------------------------- Member Functions -----------------------------------------//
    //Default constructor.
    Student() {}
    //parameterized Constructor
    Student(int studNum, string name, string dept, Address add, vector<Subject> subjects)
    {
        //"this->" is a pointer to point at the private members of the class.
        this->studNum = studNum;
        this->name = name;
        this->dept = dept;
        this->add = add;
        this->subjects = subjects;
        setTotal();
        setGrade();
    }

    void addStud(vector<Student>* students)
    {
        int studNum, subjNum;
        string firstname, secondname, lastname;
        string name, dept;
        Address add;
        ofstream fout; //to write inside the file
        fout.open("Data.txt", ios::app); //ios::app appends data at the end of the file
        cout << "Please Enter The Information Below:\n";
        cout << "Enter the first name - second name - last name (separated by space): ";
        cin >> firstname >> secondname >> lastname; //to avoid the errors caused by the getline operator
        name = firstname + ' ' + secondname + ' ' + lastname;
        cout << "Student Code: ";
        cin >> studNum;
        cout << "Department(ELC - AER - ARC - CHE - CMP - CVE - EPM - MEC - MET - MIN - PET - SBE): ";
        cin >> dept;
        cout << "Address (city, residential area,  ZIP): ";
        cin >> add.city;
        cin >> add.residentialArea;
        cin >> add.zip;
        //storing the data at the end of the text file using fout
        fout << "\n" << studNum << " " << name << " " << dept << " " << add.city << " " << add.residentialArea << " " << add.zip << endl;
        cout << "Number of subjects: ";
        cin >> subjNum;
        fout << subjNum ;
        vector<Subject> subjects;
        cout << "Subjects followed by score in the subject: ";
        for (int j = 0; j < subjNum; j++)
        {
            Subject subject;
            cin >> subject.courseName;
            cin >> subject.mark;
            fout << subject.courseName << " " << subject.mark << " ";
            subjects.push_back(subject);
            //"push_back()" adds the object at the end of the vector.
        }

        Student temp(studNum, name, dept, add, subjects);
        students->push_back(temp);
        fout.close(); // closing the text file
        cout << "Student was added Successfully\n";
    }

    int searchStud(vector<Student>* students, int target1, string target2)
    {
        for (int n = 0; n < students->size(); n++)
        {
            //"at(n)" returns a reference at position n.
            if (students->at(n).studNum == target1 || students->at(n).name == target2)
                return n;
        }
        cout << "Record not found" << endl;
        return -1;
    }

    void modify(vector<Student>* students, int n, int index)
    {
        int mod1, x;
        string mod2, mod4, subj;
        float mod3, y;
        switch (n)
        {
        case 1:
        {
            cout << "Please enter your modification " << endl;
            cin >> mod1;
            students->at(index).studNum = mod1;
            break;
        }
        case 2:
        {
            cout << "Please enter your modification " << endl;
            cin.ignore();
            getline(cin, mod2);
            students->at(index).name = mod2;
            break;
        }
        case 3:
        {
            int subjNum;
            cout << "Please enter your modification " << endl;
            cin >> mod2;
            students->at(index).dept = mod2;
            break;
        }
        case 4:
        {
            cout << "Please enter the subject you want to change " << endl;
            cin >> subj;
            bool k=0;
            for (int i = 0; i<students->at(index).subjects.size(); i++)
            {
                if (subj==students->at(index).subjects[i].courseName)
                {
                    cout << "Please enter your modification " << endl;
                    cin >> mod2;
                    students->at(index).subjects[i].courseName = mod2;
                    cout << "Please enter the mark of your modified subject " << endl;
                    cin >> mod3;
                    students->at(index).subjects[i].mark = mod3;
                    students->at(index).setTotal();
                    students->at(index).setGrade();
                    k=1;
                }
            }
            if(k=0)
            {
                cout<<" Subject Not Found "<<endl;
            }
            break;
        }

        case 5:
        {
            cout << "Please enter the subject you want to change " << endl;
            cin >> subj;
            bool k=0;
            for (int i = 0; i<students->at(index).subjects.size(); i++)
            {
                if (subj==students->at(index).subjects[i].courseName)
                {
                    cout << "Please enter your modification " << endl;
                    cin >> mod3;
                    students->at(index).subjects[i].mark = mod3;
                    students->at(index).setTotal();
                    students->at(index).setGrade();
                    k=1;
                }
            }
            if(k=0)
            {
                cout<<" Subject Not Found "<<endl;
            }
            break;
        }
        case 6:
        {
            cout << "Please enter the modified full address: " << endl;
            cin >> mod2 >> mod4 >> mod1;
            students->at(index).add.city=mod2;
            students->at(index).add.residentialArea=mod4;
            students->at(index).add.zip=mod1;
            cout << "The new address is: " <<endl;
            cout << students->at(index).add.city << "\t" << students->at(index).add.residentialArea << "\t" << students->at(index).add.zip << "\t" << endl;

        }
        }
        cout << "Modification was added successfully.." << endl;
    }

    void deleteStud(vector<Student>* students, int target1)
    {
        int found = searchStud(students, target1, "\0");
        if (found == -1)
        {
            cout << "Student Not Found" << endl;
        }
        else
        {
            if (found == students->size() - 1)
            {
                //"pop_back()" deletes the last object in the vector.
                students->pop_back();
            }
            else
            {
                students->at(found) = students->at(students->size() - 1);
                students->pop_back();
            }
            cout << "The Student Is Deleted .. " << endl;
        }
    }

    void printStudInfo(vector<Student>* students, int n)
    {
        switch (n)
        {
        case 1:
        {
            int code;
            int index;
            Student s;
            cout << "Please enter the code of the student you want to display " << endl;
            cin >> code;
            index = s.searchStud(students, code, "\0");
            cout << "Name\t\t\t\t | " << students->at(index).name << endl;
            cout << "Code\t\t\t\t | " << students->at(index).studNum << endl;
            cout << "Department\t\t\t | " << students->at(index).dept << endl;
            cout << "Subjects\t\t\t | " ;
            for (int i=0; i < students->at(index).subjects.size(); i++)
            {
                cout << students->at(index).subjects[i].courseName << " ";
                cout << students->at(index).subjects[i].mark << " ";
            }
            cout << endl;
            cout << "Total Mark\t\t\t | " << students->at(index).total << endl;
            cout << "Grade \t\t\t\t | " << students->at(index).grade << endl;
            cout << "Address \t\t\t | " << students->at(index).add.city << " " << students->at(index).add.residentialArea << " " << students->at(index).add.zip << endl;
            break;
        }
        case 2:
        {
            cout << "Name\t\t\t | Code\t\t | Department\t | Total Score\t | Grade\t | Address\t\t\t | Subjects\t" << endl;
            for (int i = 0; i < students->size(); i++)
            {
                cout << students->at(i).name << "\t | " << students->at(i).studNum << "\t\t | " << students->at(i).dept;
                cout << "\t\t | " << students->at(i).total << "\t\t | " << students->at(i).grade << "\t\t | ";
                cout << students->at(i).add.city << " " << students->at(i).add.residentialArea << " " << students->at(i).add.zip <<"\t\t | ";
                for (int j=0; j < students->at(i).subjects.size(); j++)
                {
                    cout << students->at(i).subjects[j].courseName << " ";
                    cout << students->at(i).subjects[j].mark << " ";
                }

                cout << endl;
            }
        }
        }
    }
    //------------------------------------------ Accessors & Mutators -----------------------------------------//
    int getStudNum()
    {
        return studNum;
    }
    string getName()
    {
        return name;
    }

    void setTotal() //calculates the total score of the student
    {
        total = 0;
        for (int k = 0; k < subjects.size(); k++)
            total +=subjects[k].mark;
    }

    float getTotal()
    {
        return total;
    }

    void setGrade() //calculates the grade of the student
    {
        float t = getTotal();
        float percent = (t / subjects.size());
        if (percent >= 85)
            grade = 'A';
        else if (percent >= 75)
            grade = 'B';
        else if (percent >= 65)
            grade = 'C';
        else if (percent >= 50)
            grade = 'D';
        else
            grade = 'F';
    }
    char getGrade()
    {
        return grade;
    }

};
//------------------------------------------ Functions Section -----------------------------------------//
void display()
{
    //"system ("CLS") function to clear screen.
    system("CLS");
    cout << "||-------------------------------- Student Management System --------------------------------||" << endl << endl;
    cout << "||---------- Please choose The Service According To It's Number Or Enter 0 To Exit ----------||" << endl << endl;
    cout << "1. Enter a new student.\n";
    cout << "2. Search for a student.\n";
    cout << "3. Modify student data.\n";
    cout << "4. Delete student data.\n";
    cout << "5. Calculate the total score and grade of student.\n";
    cout << "6. Display students information.\n";
    cout << "||--------------------------------- Please Enter The Number ---------------------------------||" << endl;
}

int counter() //to know the number of students in the list
{
    int count = 0;
    string s;
    ifstream fin;
    fin.open("Data.txt");
    while (getline(fin, s))
    {
        count++;
    }
    fin.close();
    return (count / 2);
}

vector<Student> loadStudents()
{
    vector<Student> students;
    int count;
    int studNum;
    string firstname, secondname, lastname;
    string name;
    string dept;
    Address add;
    Subject subj;
    int subjNum;
    ifstream fin;
    fin.open("Data.txt");
    count = counter();
    for (int i = 0; i < count; i++)
    {
        fin >> studNum >> firstname >> secondname >> lastname >> dept >> add.city >> add.residentialArea >> add.zip;
        fin >> subjNum;
        vector<Subject> subjects;
        for (int j = 0; j < subjNum; j++)
        {
            fin >> subj.courseName >> subj.mark;
            subjects.push_back(subj);
        }
        name = firstname + ' ' + secondname + ' ' + lastname;
        Student temp(studNum, name, dept, add, subjects);
        students.push_back(temp);
    }
    fin.close();
    return students;
}
//------------------------------------------ Main Function -----------------------------------------//
int main()
{
    char ch;
    //Vector Declaration
    vector<Student> students = loadStudents();
    Student s;
    //The switch case which operates according to the user's selection
repeat:
    display();
label:
    cin >> ch;
    switch (ch)
    {
    case '0':
        return 0;
    case '1':
    {

        s.addStud(&students);
        break;
    }

    case '2':
    {
        string firstname, secondname, lastname;
        cout << "Please choose your search method:\n1.By Name\n2.By student code\nYour choice:";
        int cn;
        cin >> cn;
        if (cn == 1)
        {
            string choice;
            cout << "Please enter the name\nFirst name - second name - last name (separated by a space) ";
            cin.ignore();
            getline(cin, choice);
            int p = s.searchStud(&students, 0, choice);
            if (p == -1)
                break;
            cout << "Student Found at " << p + 1 << "\nstudent code: " << students[p].getStudNum() << endl;
        }
        else if (cn == 2)
        {
            cout << "Please enter student code\n";
            int j;
            cin >> j;
            int p = s.searchStud(&students, j, "\0");
            if (p == -1)
                break;
            cout << "Student Found at " << p + 1 << "\nstudent name: " << students[p].getName() << endl;
        }
        else
        {
            cout << "wrong input\n";
        }
        break;

    }
    case '3':
    {
        int target1, k, n;
        cout << "Please enter the code of the student you want to modify" << endl;
        cin >> target1;
        k = s.searchStud(&students, target1, "\0");
        if (k != -1)
        {
            cout << "Please choose what you want to modify" << endl;
            cout << "1-Code" << endl;
            cout << "2-Name" << endl;
            cout << "3-Department" << endl;
            cout << "4-Subject" << endl;
            cout << "5-Marks" << endl;
            cout << "6-Address" << endl;
            cin >> n;
            s.modify(&students, n, k);
        }
        else
            cout << "Record not found " << endl;
        break;
    }
    case '4':
    {
        cout << "Please enter student code\n";
        int j;
        cin >> j;
        s.deleteStud(&students, j);
        break;
    }

    case '5':
    {

        string req_name;
        cout << "Please enter the student name: ";
        cin.ignore();
        getline(cin, req_name);
        int index = s.searchStud(&students, 0, req_name);
        if (index == -1)
        {

        }
        else
        {
            cout << "Total score: " << students[index].getTotal() << endl;
            cout << "Grade: " << students[index].getGrade() << endl;
        }
        break;
    }
    case '6':
    {
        int n;
        cout << "Please choose what you want to display" << endl;
        cout << "1-Only one student" << endl;
        cout << "2-All students in the list" << endl;
        cin >> n;
        s.printStudInfo(&students,n);
        break;
    }
    default:
    {

        cout << "Please choose a correct option\n";
        goto label;
    }
    }

    cout << "Do you want to do another operation?(y/n)\n";
    cin >> ch;

    if (ch == 'y')
        goto repeat;
    return 0;
}
