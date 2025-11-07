#include <iostream>
#include <cmath>
using namespace std;

int main(){
    char op;
    double num1;
    double num2;
    double result;
    std::cout<<"********CALCULATOR***********\n";

    std::cout<<" Enter either (+ - * /)";
    std::cin >> op;
    
    std::cout<<"Enter #1: ";
    std::cin>>num1;

    std::cout<<"Enter #2: ";
    std::cin>>num2;
    
    switch (op)
    {
    case '+':
    std::cout<<"here";
        result = num1 + num2;
        std::cout <<"result " << result <<'\n';
        break;
    case '-':
        result = num1 - num2;
        std::cout <<"result " << result <<'\n';
        break;
    case '*':
        result = num1 * num2;
        std::cout <<"result " << result <<'\n';
        break;
    case '/':
        result = num1 / num2;
        std::cout <<"result " << result <<'\n';
        break;
    default:
        std::cout<<"That wasnt a valid response";
        break;
    }


    std::cout<<"*****************************";
    return 0;
}
