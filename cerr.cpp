#include <iostream>

using namespace std;

class Person
{
public:
    Person() : age(0), height(0), name("N/A") {}
    Person(int a, int h, string n) : age(a), height(h), name(n) {}

    Person(const Person &p)
    {
        age = p.age;
        height = p.height;
        name = p.name;
    }

    Person &operator=(const Person &p)
    {
        if (this != &p)
        {
            this->age = p.age;
            this->name = p.name;
            this->height = p.height;
        }
        return *this;
    }
    ~Person()
    {
    }

private:
    int age;
    int height;
    string name;
};

int main()
{
    int number;
    cin >> number;
    if (number < 0)
    {
        throw logic_error("this is a logic error");
    }

    return 0;
}