// Include from tiers library
#include <stdio.h>
#include <stdlib.h>
// Include from our own file
#include "gestrech.h"


int main(){

	printf("DamerauLevenshteinDistance(toto,titi)=%d (expected 2)\n",DamerauLevenshteinDistance("toto","titi") );
	printf("DamerauLevenshteinDistance(antoine,antine)=%d (expected 1)\n",DamerauLevenshteinDistance("antoine","antine") );
	printf("DamerauLevenshteinDistance(test,tet)=%d (expected 1)\n", DamerauLevenshteinDistance("test","tet") );
	printf("DamerauLevenshteinDistance(ok,ko)=%d (expected 1)\n",DamerauLevenshteinDistance("ok","ko") );
	
	printf("DamerauLevenshteinDistance(vomit,titi)=%d (expected 3)\n",DamerauLevenshteinDistance("vomit","titi") );


    return 0;
}
