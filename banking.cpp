#include <iostream>
#include <iomanip>
using namespace std;

void showBalance(double balance);
double deposit();
double withdraw(double balance);

int main()
{
    double balance = 123.01;
    int choice = 0;

    std::cin.clear();
    fflush(stdin);

    do{
    std::cout<< "***************"<<endl;
    cout<<"**ENTER YOUR CHOICE**"<<endl;
    std::cout<< "***************"<<endl;
    std::cout<<"1. Show Balance\n";
    std::cout<<"2. Deposit money \n";
    std::cout<<"3. Withdraw money \n";
    std::cout<<"4. Exit \n";
    std::cin>>choice;

    switch(choice){
        case 1:
                showBalance(balance);
                break;
        case 2:
                balance = balance + deposit();
                showBalance(balance);
                break;
        case 3:
                balance -= withdraw(balance);
                showBalance(balance);
                break;
        case 4:
                std::cout<<" Thanks for visiting \n";
                break;
        default:
            cout<<"Invalid choice";
        }
    }while(choice != 4);

    return 0;
}
void showBalance(double balance){
    cout<<"Your balance is : $"<<std::setprecision(2)<<std::fixed << balance<<endl;
};
double deposit(){
    double amount = 0;
    std::cout<< "Enter amount to be deposited:";
    std::cin>>amount;

    if(amount>0){
        return amount;
    }
    else{
        cout<<"that is not a valid amount: \n";
        return amount;
    }
};
double withdraw(double balance){
    double amount = 0;
    cout<< "Enter amount to be withdrawn:";
    std::cin>> amount;
    if(amount > balance){
        std::cout<<"insufficient funds \n";
        return 0;
    }
    else if(amount < 0){
        cout<<"That is not a valid amount \n";
        return 0;
    }
    else{
        return amount;
    }
};

