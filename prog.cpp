#include <iostream>

using namespace std;

class Prog
{
public:
    Prog() : p(0) {};
    Prog(int p) : p(p)
    {
        arr = new double[p + 1];
        for (int i = 0; i <= p; i++)
        {
            if (i == 0)
            {
                arr[i] = 0;
            }
            else if (i == 1)
            {
                arr[i] = 1;
            }
            else
            {
                arr[i] = arr[i - 1] + i + arr[i - 2];
            }
        }
    };
    int operator[](int i) const
    { // da vrushta stoinostta
        return this->arr[i];
    }

    int operator()() const
    { // da vrushta sumata na p
        int sum = 0;
        for (int i = 0; i <= p; i++)
        {
            sum += arr[i];
        }
        return sum;
    }
    ~Prog()
    {
        delete[] arr;
    }

private:
    double *arr;
    int p;
};

int main()
{
    Prog p(3);
    cout << p();

    return 0;
}