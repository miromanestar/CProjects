#include <string>

using namespace std;

class Person {
    string name;
public:
    Person(const string& name) : name(name) {}
    virtual string get() const { return name; }
};

class Student : public Person {
public:
    Student (const string& name) : Person(name) {}
    string get() const override {
        return "Student: " + Person::get(); 
    }
};

class Teacher : public Person {
public:
    Teacher(const string& name) : Person(name) {}
    string get() const override {
        return "Teacher: " + Person::get();
    }
};

class StudentTeacher : virtual public Student, virtual public Teacher {
public:
    StudentTeacher(const string& n) : Student(n), Teacher(n) {}
};