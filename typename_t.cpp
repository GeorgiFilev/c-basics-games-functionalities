#include <iostream>
#define cube(x) ((x) * (x) * (x))

using namespace std;
class Point
{
public:
    Point() : x(0), y(0) {};
    Point(double x, double y) : x(x), y(y) {};
    Point operator+(const Point &rhs) const
    {
        return Point(this->x + rhs.x, this->y + rhs.y);
    }
    ostream &ins(ostream &out) const
    {
        return out << "{" << x << "," << y << "}";
    }
    Point operator*(double rhs) const
    {
        return Point(x * rhs, y * rhs);
    }
    Point operator/(unsigned rhs) const
    {
        return (rhs > 0) ? Point(x / rhs, y / rhs) : Point();
    }

private:
    double x, y;
};

ostream &operator<<(ostream &lhs, const Point &rhs)
{
    return rhs.ins(lhs);
}

template <typename T>
T sumArr(T arr[], unsigned sz)
{
    T sum = T();
    for (int i = 0; i < sz; i++)
    {
        sum = sum + arr[i];
    }
    return sum;
}

template <typename T, typename T1>
T1 avgArr(T arr[], unsigned size)
{
    return sumArr(arr, size) / size;
}

int main()
{
    int arr[] = {1, 2, 3, 4, 6};
    cout << sumArr<int>(arr, 5) << endl;

    cout << "avg double:" << avgArr<int, double>(arr, 5) << endl;
    Point arrPoints[] = {Point(2, 3), Point(3, 4)};
    cout << "avg double:" << avgArr<Point, Point>(arrPoints, 2) << endl;
    cout << "\n"
         << cube(2);

    return 0;
}