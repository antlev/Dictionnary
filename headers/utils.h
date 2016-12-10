#include "gestbib.h"

// Allow us to set a $DEBUG at compilation
#ifndef DEBUG
    #define DEBUG (0)
#endif

unsigned long getTime();
unsigned long getTimeMicro();
int userInput (char *prmpt, char *buff, size_t sz);
int numericUserInput(char* prmpt, char* buff, size_t sz,short lowLimit,short highLimit);
// Print menu on screen
void printMenu(dictionary* dicInUse,short main);
char* concat(const char *s1, const char *s2);