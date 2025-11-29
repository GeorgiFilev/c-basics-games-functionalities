// Да се дефинира клас Point с две член - данни – двете декартови координати на точка и подходящи член - функции(конструктор, деструктор, аксесори, мутатори, функция за извеждане на информация за обекта, …).Като се използва дефинираният клас да се напише програма, която : 1. въвежда n различни точки от равнината, след което ги транслира с(2, 4) и извежда получените точки;
// 2. намира разстоянието между всеки две точки(все едно старите или новите);
// 𝑥2 − 𝑥1 2 + 𝑦2 − 𝑦1 2 3. намира точките, разстоянието между които е най - малко(най - голямо).

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

class Point
{
private:
    double x;
    double y;

public:
    Point() : x(0), y(0) {}
    // po podrazbirane
    Point(double xVal, double yVal) : x(xVal), y(yVal) {} // s parametri nasledqvane

    ~Point() {}

    void setX(double x)
    {
        this->x = x;
    }
    void setY(double y)
    {
        this->y = y;
    }
    void setXY(double xVal, double yVal)
    {
        x = xVal;
        y = yVal;
    }
    double getX() const { return this->x; }
    double getY() const { return this->y; }

    void print() const
    {
        cout << x << " and " << y << endl;
    }
    void translate(double dx, double dy)
    {
        x += dx;
        y += dy;
    }

    double distanceTo(const Point &p) const
    { // predavame tochkata kato referenciq i posle dostypwame obekta
        double dx = x - p.x;
        double dy = y - p.y;
        return sqrt(dx * dx + dy * dy);
    }
};

int main()
{
    int n;
    cout << "Въведете брой точки";
    cin >> n;
    vector<Point> points; // masiv ot tochki
    double x, y;
    for (int i = 0; i < n; i++)
    {
        cout << "Tochka " << i + 1 << endl;
        cin >> x >> y;
        points.push_back(Point(x, y));
    }

    cout << "\n tochki sled translaciq s (2,4): \n";
    for (auto &p : points)
    {
        p.translate(2, 4);
        p.print();
        cout << endl;
    }

    cout << "\nRazstoqniq mejdu tochkite";
    double dist;
    double minDist = 1e9, maxDist = -1;
    int minI = 0, minJ = 0, maxI = 0, maxJ = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; ++j)
        {
            dist = points[i].distanceTo(points[j]);
            cout << "Razstoqnie mejdu tochka" << i + 1 << " i tochka" << j + 1 << ": " << dist << endl;

            if (dist < minDist)
            {
                minDist = dist;
                minI = i;
                minJ = j;
            }
            if (dist > maxDist)
            {
                maxDist = dist;
                maxI = i;
                maxJ = j;
            }
        }
    }
    cout << "\nНай-малко разстояние: " << minDist << " между точки ";
    points[minI].print();
    cout << " and ";
    points[minJ].print();
    cout << endl;

    cout << "Най-голямо разстояние: " << maxDist << " между точки ";
    points[maxI].print();
    cout << " и ";
    points[maxJ].print();
    cout << endl;

    return 0;
}