#include <stdio.h>
#include <stdlib.h>

int minimum3(int val1, int val2, int val3);

int minimum2(int val1, int val2);

void printTab(int* tab,int nbLine,int nbCol);

int DamerauLevenshteinDistance(char* str1, int lenStr1, char* str2, int lenStr2);


int main(){

  printf("minimum>%d<\n",minimum3(2,1,3) );
  printf("minimum>%d<\n",minimum3(1,1,3) );
  printf("minimum>%d<\n",minimum3(2,3,1) );

  printf("DamerauLevenshteinDistance(toto,titi)=%d (expected 2)\n",DamerauLevenshteinDistance("toto",4,"titi",4) );
  printf("DamerauLevenshteinDistance(antoine,antine)=%d (expected 1)\n",DamerauLevenshteinDistance("antoine",7,"antine",6) );
  printf("DamerauLevenshteinDistance(test,tet)=%d (expected 1)\n", DamerauLevenshteinDistance("test",4,"tet",3) );
  printf("DamerauLevenshteinDistance(ok,ko)=%d (expected 1)\n",DamerauLevenshteinDistance("ok",2,"ko",2) );
	
    return 0;
}
