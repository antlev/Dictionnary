#include <stdio.h>
#include <stdlib.h>

#include "../headers/gestbib.h"


#ifndef DEBUG
    #define DEBUG (0)
#endif

int main(int argc,char *argv[]){

	if(argc > 1){
		// Execute test - 1 for verbose output
	    test(DEBUG); 
	}

    menu(init());

    return 0;
}
