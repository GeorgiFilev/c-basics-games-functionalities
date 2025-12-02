#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Person
{
private:
    string name;
    int age;

public:
    Person(string name, int age) : name(name), age(age) {}

    string getName() const { return name; }
    int getAge() const { return age; }
};

int main()
{
    // Създаваме обект
    Person p("Ivan", 20);

    // Отваряме файл за писане
    ofstream file("person.txt");

    if (!file.is_open())
    {
        cout << "Error opening file!\n";
        return 1;
    }

    // Записваме данните на обекта
    file << "Name: " << p.getName() << endl;
    file << "Age: " << p.getAge() << endl;

    file.close();

    cout << "Person saved to file.\n";
    return 0;
}
