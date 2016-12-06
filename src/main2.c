// Include from tiers library
#include <stdio.h>
#include <stdlib.h>
// Include from our own file
#include "../headers/gestrech.h"
#include "../headers/utils.h"

int main(int argc,char *argv[]){
	if(argc > 1){
		printf("DamerauLevenshteinDistance(toto,titi)=%d (expected 2)\n",DamerauLevenshteinDistance("toto","titi") );
		printf("DamerauLevenshteinDistance(antoine,antine)=%d (expected 1)\n",DamerauLevenshteinDistance("antoine","antine") );
		printf("DamerauLevenshteinDistance(test,tet)=%d (expected 1)\n", DamerauLevenshteinDistance("test","tet") );
		printf("DamerauLevenshteinDistance(ok,ko)=%d (expected 1)\n",DamerauLevenshteinDistance("ok","ko") );
		printf("DamerauLevenshteinDistance(vomit,titi)=%d (expected 3)\n",DamerauLevenshteinDistance("vomit","titi") );
	}

	char* input = malloc(sizeof(char)*255);
	char* input2 = malloc(sizeof(char)*255);

	while(userInput("Enter a word to compare\n>",input,255) != 0);

	while(userInput("Enter a word to compare\n>",input2,255) != 0);

	printf("The distance between %s and %s is %d\n",input,input2,DamerauLevenshteinDistance(input,input2) );

    return 0;
}
