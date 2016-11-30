// Structs
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
#include <math.h>
#include <string.h>
#include <sys/time.h>

#ifndef DEBUG
    #define DEBUG (0)
#endif


#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

static const int MAXNBLETTERINWORD = 20;
static const int THRESHOLD = 2;