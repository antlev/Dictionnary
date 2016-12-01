typedef struct __attribute__((__packed__)) node{
    short endOfWord;
    struct node* letter[26];
}node;
typedef struct dictionnary{
    char name[255];
    char description[255];
    int nbWord;
    node* tree;
}dictionnary;

#include <stdio.h>
#include <stdlib.h>

void menu(dictionnary* library);
dictionnary* init();
void test(int verbose);

int main(){

    // test(1); 

    menu(init());

    return 0;
}
