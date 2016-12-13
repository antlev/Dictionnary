// Include from tiers library
#include <stdio.h>
#include <stdlib.h>
// Include from our own file
#include "../headers/gestbib.h"
#include "../headers/gestrech.h"
#include "../headers/utils.h"

int main(int argc,char *argv[]){
	char* input = malloc(sizeof(char)*256);
	char* input2 = malloc(sizeof(char)*256);
	short choice;
	dictionary* toto;

    do{
    	do{
			printMenu(toto,2);
    	} while((choice = numericUserInput(">",input,255, 1, 2)) == -1);
        switch(choice){
        	case 1:

				while(userInput("Entrer le premier mot\n>",input,255) != 0);

				while(userInput("Entrer le deuxi�me mot\n>",input2,255) != 0);

				printf("Les deux mots ont une distance de %d : ('%s' et '%s')\n",DamerauLevenshteinDistance(input,input2), input, input2 );
        	break;
        	case 2:
        		exit(0);
    		    free(input);
    			free(input2);
        	break;
        }
	} while(1);
	// printf("DamerauLevenshteinDistance(toto,titi)=%d (expected 2)\n",DamerauLevenshteinDistance("toto","titi") );
	// printf("DamerauLevenshteinDistance(antoine,antine)=%d (expected 1)\n",DamerauLevenshteinDistance("antoine","antine") );
	// printf("DamerauLevenshteinDistance(test,tet)=%d (expected 1)\n", DamerauLevenshteinDistance("test","tet") );
	// printf("DamerauLevenshteinDistance(ok,ko)=%d (expected 1)\n",DamerauLevenshteinDistance("ok","ko") );
	// printf("DamerauLevenshteinDistance(vomit,titi)=%d (expected 3)\n",DamerauLevenshteinDistance("vomit","titi") );
    exit(0);
}
