 #include <stdio.h>
#include <stdlib.h>

#include "../headers/gestbib.h"

#ifndef DEBUG
    #define DEBUG (0)
#endif

// Threshold is the maximum distance between 2 words to accept as a similar word
static const short THRESHOLD = 2;

int main(int argc,char *argv[]){


	if(argc > 1){
		// Execute test - 1 for verbose output
	    test(DEBUG); 
	}

    menu(init());

    return 0;
}
