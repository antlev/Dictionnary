#include <stdio.h>
#include <stdlib.h>

#include "../headers/gestbib.h"

#ifndef DEBUG
    #define DEBUG (0)
#endif

// Threshold is the maximum distance between 2 words to accept as a similar word
static const short THRESHOLD = 2;
// The following variable allow change the  used set of letters for dictionary
// O -> "abcdefghijklmnopqrstuvwxyz"
// 1 -> all ascii from "!" (33) to "~N" (165)
// 2 -> "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
// 3 -> "abcdefghijklmnopqrstuvwxyz0123456789"
// 4 -> "abcçdefghijklmnopqrstuvwxyzàâáéèêëîïíôûüù" : French
// static const short SETOFLETTERSACCEPTED = 0; 

int main(int argc,char *argv[]){


	if(argc > 1){
		// Execute test - 1 for verbose output
	    test(DEBUG); 
	}

    menu(init());

    return 0;
}
