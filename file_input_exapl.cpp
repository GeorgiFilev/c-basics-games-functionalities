#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    string name;
    cout << "Enter your name";
    cin >> name;

    ofstream file("names.txt");

    if (!file.is_open())
    {
        cout << "Error opening the file";
        return 1;
    }

    file << name << endl;

    file.close();

    cout << "name saved succesfully" << endl;
    return 0;
}