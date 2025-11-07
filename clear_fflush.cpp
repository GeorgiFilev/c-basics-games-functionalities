#include <iostream>

using namespace std;
void changePerson(string &name,int &age,double &height,string &name2,int &age2,double &height2);
int main(){
    string name = "Georgi";
    int age = 25;
    double height = 1.80;

    string name2 = "Ivan";
    int age2;
    double height2;
    cout<<"Enter your name"<<'\n';
    cin>>name2;
    cout<<"Enter your age:\n";
    cin>>age2;
    cout<<"Enter your height \n";
    cin>>height2;

    char answer;
    cout<<"Do you want to swap you with another person? "<<endl<<"Y ? N "<<endl;
    HERE:

    cin>>answer;

    cin.clear();
    fflush(stdin);

    if(answer == 'Y'){
        changePerson(name,age,height,name2,age2,height2);
    }
    else if(answer == 'N'){
        cout<<"you are fine";
    }
    else {
        cout<<"Only Y or N"<<endl;
        goto HERE;
    }

    cout<<"WOW -"<<name2<<" "<<age2<<" "<<height2<<endl;

    return 0;
}
void changePerson(string &name,int &age,double &height,string &name2,int &age2,double &height2){
    string temp_name;
    int  temp_age;
    double temp_height;

    temp_name = name;
    name = name2;
    name2 = temp_name;

    temp_age = age;
    age= age2;
    age2= temp_age;

    temp_height= height;
    height = height2;
    height2= temp_height;
};
