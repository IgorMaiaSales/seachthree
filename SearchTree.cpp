#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define max 26

using namespace std;



struct Ternary{
    char c;
    Ternary* left, mid, right;
    bool endOfWord;
};

struct Prefix{
    char c;
    Prefix* alfabet[max];
    bool endOfWord;
};



void addToThree(int type, char* word){

}

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}