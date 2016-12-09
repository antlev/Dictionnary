#include <stdio.h>
#include <stdlib.h>

#include "../headers/gestbib.h"

#ifndef DEBUG
    #define DEBUG (0)
#endif

// Threshold is the maximum distance between 2 words to accept as a similar word
static const short THRESHOLD = 2;
// The following variable allow change the  used set of letters for dictionary
// O -> "abcdefghijklmnopqrstuvwxyz" ISO8859-1 : 97 -> 112
// 1 -> "ABCDEFGHIJKLMNOPQRSTUVWXYZ" ISO8859-1 : 65 -> 90
// 2 -> "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" ISO8859-1 : 65 -> 112
// 3 -> "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" ISO8859-1 : 48 -> 90
// 4 -> ALL ISO8859-1 : 33 -> 255

// static const short SETOFLETTERSACCEPTED = 0; 

int main(int argc,char *argv[]){


	if(argc > 1){
		// Execute test - 1 for verbose output
	    test(DEBUG); 
	}

    menu(init());

    return 0;
}
