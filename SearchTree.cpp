#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

#define max 26

using namespace std;

struct Ternary{
    char c;
    Ternary *left, *mid, *right;
    bool endOfWord;
};

struct Prefix{
    char c;
    Prefix* alfabet[max];
    bool endOfWord;
};

union Generic{
    Ternary *avrTernary;
    Prefix *arvPrefix;
};

Ternary* criaTernary(char c, int endOfWord){
    Ternary* tmp = (Ternary*) malloc(sizeof(Ternary));
    tmp->c = c;
    tmp->endOfWord = endOfWord;
    tmp->left = tmp->mid = tmp->right = NULL;
    return tmp;
}

void addTernaryTree(Ternary** arv, const char* word){
    if(*arv == NULL){
        *arv = criaTernary(word[0], word[1] == '\0');
        if (word[1] == '\0') return;
    }

    if(word[0] == (*arv)->c){
        addTernaryTree(&(*arv)->mid, word+1);
    }else  if(word[0] > (*arv)->c){
        addTernaryTree(&(*arv)->right, word);
    }else{
        addTernaryTree(&(*arv)->left, word);
    }
}

void addToThree(int type, Generic* avr, const char* word){
    switch (type){
        case 0:
            addTernaryTree(&(avr->avrTernary), word);
            break;
        case 1:
            break;
    }
}

void printTree(Ternary *arv){
    if(arv == NULL) return;

    printf("%c \n", arv->c);
    printTree(arv->left);
    printTree(arv->mid);
    printTree(arv->right);
}

int main()
{
    Generic myArv;
    myArv.avrTernary = NULL;
    myArv.arvPrefix = NULL;

    string line;
    ifstream mystream("palavras.txt");
    if(mystream.is_open()){
        while(getline(mystream, line)){
            addToThree(0, &myArv, line.c_str());
        }
    }

    printTree(myArv.avrTernary);

    return 0;
}

