#include <iostream>
using namespace std;

class IEmployee
{
    virtual void AskForPromotion() = 0;
};

class Employee : IEmployee
{
private:
    string Company;
    int age;

protected:
    string Name;

public:
    void setName(string name)
    {
        this->Name = name;
    }
    string getName()
    {
        return Name;
    }
    void setCompany(string company)
    {
        this->Company = company;
    }
    string getCompany()
    {
        return Company;
    }
    void setAge(int age)
    {
        this->age = age;
    }
    int getAge()
    {
        if (age >= 18)
        {
            return this->age;
        }
    }

    void introduceYourself()
    {
        cout << "Name -" << Name << endl;
        cout << "Company -" << Company << endl;
        cout << "Age -" << age << endl;
    };
    Employee(string name, string company, int age)
    {
        Name = name;
        Company = company;
        this->age = age;
    }
    void AskForPromotion()
    {
        if (age > 30)
        {
            cout << Name << " got promotion" << endl;
        }
        else
        {
            cout << Name << " no promotion for you" << endl;
        }
    }

    virtual void Work()
    {
        cout << this->Name << " is checking mail, task backlog,performin tasks" << endl;
    }
};

class Developer : public Employee
{
public:
    string FavProgrammingLanguage;
    Developer(string name, string company, int age, string favProgrammingLanguage)
        : Employee(name, company, age)
    {
        this->FavProgrammingLanguage = favProgrammingLanguage;
    }
    void FixBug()
    {
        cout << this->Name << "fixed bug using " << this->FavProgrammingLanguage;
    }
    void Work()
    {
        cout << this->Name << " is writing code in " << this->FavProgrammingLanguage << endl;
    }
};

class Teacher : public Employee
{
public:
    string Subject;
    void PrepareLesson()
    {
        cout << this->Name << " is preparing " << Subject << " lesson";
    }
    Teacher(string name, string company, int age, string subject)
        : Employee(name, company, age)
    {
        Subject = subject;
    }
    void Work()
    {
        cout << this->Name << " is teaching " << this->Subject << endl;
    }
};

int main()
{

    Employee employee1 = Employee("Georgi", "AZIZ", 25);

    employee1.introduceYourself();

    Developer d = Developer("Salvina", "Youtuvbe", 25, "C++");
    d.FixBug();
    d.AskForPromotion();
    Teacher t = Teacher("Jack", "Cool School", 25, "History");
    t.PrepareLesson();
    t.AskForPromotion();
    d.Work();
    t.Work();

    // THE most common use of polymorphism is when a parent class refference is used to refer to a child class object
    Employee *e1 = &d;
    Employee *e2 = &t;
    e1->Work(); // указател е1 сочи към адреса на функцията Work
    e2->Work();
    return 0;
}