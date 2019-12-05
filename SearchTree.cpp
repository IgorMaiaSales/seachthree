#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#define max 26

using namespace std;

struct Ternary{
    char c;
    Ternary *left, *mid, *right;
    bool endOfWord;
    int balance;
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
    tmp->balance = 0;
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

    printf("%c ", arv->c);
    printTree(arv->left);
    printTree(arv->mid);
    printTree(arv->right);
}

int arvProfundidade(Ternary *a){
    if(a == NULL) return -1;
    if(a->left == NULL && a->right == NULL){
        return 0;
    }else{
        if(arvProfundidade(a->left) > arvProfundidade(a->right)) return 1 + arvProfundidade(a->left);
        else return 1 + arvProfundidade(a->right);
    }
}

int arvBalanceamento(Ternary *a){
    if(a == NULL) return 0;
    if(a->left == NULL && a->right == NULL) return 0;
    return arvProfundidade(a->left) - arvProfundidade(a->right);
}

void arvRotDir(Ternary **a){
    Ternary *tmp1, *tmp2;
    tmp1 = (*a)->left;
    tmp2 = tmp1->right;
    tmp1->right= *a;
    (*a)->left = tmp2;
    *a=tmp1;
}

void arvRotEsq(Ternary **a){
    Ternary *tmp1, *tmp2;
    tmp1 = (*a)->right;
    tmp2 = tmp1->left;
    tmp1->left = *a;
    (*a)->right = tmp2;
    *a=tmp1;
}

void arvRotaciona(Ternary **a){
    if(a == NULL) return;

    if(arvBalanceamento(*a) > 1){
        if(arvBalanceamento((*a)->left) < 0) arvRotEsq(&(*a)->left);
        arvRotDir(&(*a));
    }else{
        if(arvBalanceamento((*a)->right) > 0) arvRotDir(&(*a)->right);
        arvRotEsq(&(*a));
    }
}

Ternary **arvBuscaDesb(Ternary **a){
    if(*a == NULL || (*a)->balance == 3) return NULL;

    if((*a)->left != NULL && (*a)->balance == 0){
        Ternary **tmp = arvBuscaDesb(&(*a)->left);
        if(tmp != NULL) return tmp;
    }
    (*a)->balance++;

    if((*a)->right != NULL && (*a)->balance == 1){
        Ternary **tmp = arvBuscaDesb(&(*a)->right);
        if(tmp != NULL) return tmp;
    }
    (*a)->balance++;

    if(arvBalanceamento(*a) > 1 || arvBalanceamento(*a) < -1) return a;

    if((*a)->mid != NULL && (*a)->balance == 2){
        Ternary **tmp = arvBuscaDesb(&(*a)->mid);
        if(tmp != NULL) return tmp;
    }
    (*a)->balance++;

    return NULL;
}

void printTernary(Ternary *arv, string tmp){
    if(arv == NULL) return;
    printTernary(arv->left, tmp);

    tmp.push_back(arv->c);
    if(arv->endOfWord == true) cout << tmp << endl;
    printTernary(arv->mid, tmp);

    tmp.pop_back();
    printTernary(arv->right, tmp);
}

void searchTernary(char *word, Ternary *arv, string tmp){
    if (arv->c == word[0] && word[1] == '\0'){
        tmp.push_back(arv->c);
        printTernary(arv->mid, tmp);
    }
    else if (arv->c == word[0]){
        tmp.push_back(arv->c);
        word++;
        searchTernary(word, arv->mid, tmp);
    }else if(word[0] < arv->c) searchTernary(word, arv->left, tmp);
    else if(word[0] > arv->c) searchTernary(word, arv->right, tmp);
}

int main()
{
    Generic myArv;
    myArv.avrTernary = NULL;
    myArv.arvPrefix = NULL;

    string line;
    ifstream mystream("palavras.txt");
    int counter=0;
    if(mystream.is_open()){
        while(getline(mystream, line)){
            addToThree(0, &myArv, line.c_str());
//            Ternary **b = arvBuscaDesb(&myArv.avrTernary);
//            arvRotaciona(b);
            counter++;
            if (counter%100==0) {
                cout << counter << endl;
            }
        }
    }
    cout << "done" <<endl;
//    printTree(myArv.avrTernary);
//    cout << endl;
    Ternary **a;
    counter=0;
    do{
       a = arvBuscaDesb(&myArv.avrTernary);
        arvRotaciona(a);
        counter++;
            if (counter%100==0) {
                cout << counter << endl;
            }
    }while(a != NULL);
    cout << "done" <<endl;

//    printTree(myArv.avrTernary);
//    cout << endl;

    string tmp = "";

    searchTernary((char*)"palav", myArv.avrTernary, tmp);

    return 0;
}
