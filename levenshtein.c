#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minimum(int val1, int val2, int val3){
  if(val1 <= val2){
      if(val1 <= val3){
          return val1;
      }else{
          return val3;
      }  
  } else if(val2 <= val3){
      return val2;
  }else{
      return val3;
  }
  return 0;
}

int minimum2(int val1, int val2){
  if(val1 <= val2){
      return val1;
  }else{
      return val2;
  }
  return 0;
}

/*
Algo de la distance de Levenstein 
 entier DistanceDeLevenshtein(caractere chaine1[1..longueurChaine1],
                             caractere chaine2[1..longueurChaine2])
   // d est un tableau de longueurChaine1+1 rangées et longueurChaine2+1 colonnes
   declarer entier d[0..longueurChaine1, 0..longueurChaine2]
   // i et j itèrent sur chaine1 et chaine2
   declarer entier i, j, coût
 
   pour i de 0 à longueurChaine1
       d[i, 0] := i
   pour j de 0 à longueurChaine2
       d[0, j] := j
 
   pour i de 1 à longueurChaine1
      pour j de 1 à longueurChaine2
          si chaine1[i] = chaine2[j] alors coût := 0
                                sinon coût := 1    
           d[i, j] := minimum(
                                d[i-1, j  ] + 1,     // effacement du nouveau caractère de chaine1
                                d[i,   j-1] + 1,     // insertion dans chaine1 du nouveau caractère de chaine2
                                d[i-1, j-1] + coût   // substitution
                             )
 
   renvoyer d[longueurChaine1, longueurChaine2]
*/
int DamerauLevenshteinDistance(char* str1, int lenStr1, char* str2, int lenStr2){
  // d is a table with lenStr1+1 rows and lenStr2+1 columns
  int d[lenStr1][lenStr2];
  // i and j are used to iterate over str1 and str2
  int i, j, cost;

  for(i=0;i<lenStr1;i++){
        d[i][0] = i;
  }
  for(i=0;i<lenStr2;i++){
    d[0][j] = j;
  }
  for(i=1;i<lenStr1;i++){
    for(j=1;i<lenStr2;j++){
      if(str1[i-1] == str2[j-1]){ 
        cost = 0;
      }else {
        cost = 1;
      }
      d[i][j] = minimum(
                          d[i-1][j] + 1,     // deletion
                          d[i][j-1] + 1,     // insertion
                          d[i-1][j-1] + cost   // substitution
                );
      if(i > 1 && j > 1 && str1[i-1] == str2[j-2] && str1[i-2] == str2[j-1]){
                d[i][j] = minimum2(
                                    d[i][j],
                                    d[i-2][j-2] + 1      // transposition
                          );
      }

    }
  }                                

  return d[lenStr1][lenStr2];
}


int main(){

	//printf("%d\n", EditDistance("toto", "titi"));

  printf("minimum>%d<\n",minimum(2,1,3) );
  printf("minimum>%d<\n",minimum(1,1,3) );
  printf("minimum>%d<\n",minimum(2,3,1) );

  printf("DamerauLevenshteinDistance(antoine,antine)=%d (expected 1)\n",DamerauLevenshteinDistance("antoine",7,"antine",6) );
  printf("DamerauLevenshteinDistance(toto,titi)=%d (expected 2)\n",DamerauLevenshteinDistance("toto",4,"titi",4) );
  printf("DamerauLevenshteinDistance(test,tet)=%d (expected 1)\n", DamerauLevenshteinDistance("test",4,"tet",3) );
  printf("DamerauLevenshteinDistance(ok,ko)=%d (expected ?2)\n",DamerauLevenshteinDistance("ok",2,"ko",2) );
	return 0;
}