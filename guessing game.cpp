#include iostream
#include ctime

using namespace std;
int main()
{
    int num;
    int guess;
    int tries;
    srand(time(NULL));
    num = (rand()%100) +1;

    stdcout   NUMBER GUESSING GAME  n;

    do{
        stdcout Enter a guess between(1-100);
        cinguess;
        tries ++;
        if(guess  num){
            coutToo high n;
        }
        else if (guess  num){
            coutToo lowendl;
        }
        else{
            coutyou won ! endl;
        }
    }while(guess != num);

    return 0;
}
