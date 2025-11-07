#include <iostream>
#include <cmath>
using namespace std;

int main(){
    double temp;
    char unit;

    std::cout<<"****** Temperature conversion******* \n";
    std::cout<<"F= Fahrenheit\n";
    std::cout<<"C = Celsius \n";
    std::cout << "******************************";
    std::cin>> unit;

    if(unit =='F' || unit == 'f'){
        std:: cout<< "Enter the temperature in celsius: ";
        std::cin >> temp;

        temp =(1.8* temp)+ 32.0;
        std::cout<<"Temperature is: "<< temp<<"F\n";
    }
    else if(unit == 'C' || unit == 'c'){
         std:: cout<< "Enter the temperature in Farenheit: ";
        std::cin >> temp;       

        temp = (temp - 32) / 1.8;
        std::cout<<"Temperature is:"<< temp<< "C\n";
    }
    else {
        std::cout<<"incorrect type of measure(Please enter only C or F)";
    }
    return 0;
}
