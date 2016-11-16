#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Return the lowest val between val1,val2 and val3
int minimum3(int val1, int val2, int val3){
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
// Return the lowest val between val1 and val2
int minimum2(int val1, int val2){
  if(val1 <= val2){
      return val1;
  }else{
      return val2;
  }
  return 0;
}
// Print a bidemsionnal table passing it's pointer and size
void printTab(int* tab,int nbLine,int nbCol){
  int i,j;
  for(j=0;j<nbLine;j++){
    for(i=0;i<nbCol;i++){
      printf("%d ", tab[i+j*nbCol]);
    }
    printf("\n");
  }
  printf("\n");
}

int* aide(int* ptr,int nbCol,int i,int j){
    return &ptr[i+j*nbCol];

}
// Return the Damerau Levenshtein Distance between 2 strings.
// the distance returned is increased by one for each deletion,insertion,substitution or transposition.
int DamerauLevenshteinDistance(char* str1, int lenStr1, char* str2, int lenStr2){
  // d is a table with lenStr1+1 rows and lenStr2+1 columns
  int* d = malloc(sizeof(int)*(lenStr1+lenStr2));
  // i and j are used to iterate over str1 and str2
  int i, j, cost;

  printf("---------- START ---------->\n");

  printf("---------- INITIALISATION ---------->\n");

  for(i=0;i<=lenStr1;i++){
    // d[i*lenStr1] = i;
    *aide(d,lenStr1+1,i,0) = i ;
    // printTab(d,lenStr1+1,lenStr2+1);
  }
  for(j=0;j<=lenStr2;j++){

    *aide(d,lenStr1+1,0,j) = j ;
    // d[j*lenStr2] = j;
      // printTab(d,lenStr1+1,lenStr2+1);

  }

  printTab(d,lenStr1+1,lenStr2+1);

  printf("---------- TREATMENT ---------->\n");

  // printTab(d,lenStr1,lenStr2);
  for(i=0;i<=lenStr1;i++){
    for(j=0;j<=lenStr2;j++){


      if(str1[i+1] == str2[j+1]){ 
        cost = 0;
      }else {
        cost = 1;
      }
      d[i+1+(j+1)*lenStr1] = minimum3(
                          d[i+(j+1)*lenStr1] + 1,     // deletion
                          d[i+1+j*lenStr1] + 1,     // insertion
                          d[i+j*lenStr1] + cost   // substitution
                );
      if(i > 0 && j > 0 && str1[i] == str2[j-1] && str1[i-1] == str2[j]){
                d[i+1+(j+1)*lenStr1] = minimum2(
                                    d[i+1+(j+1)*lenStr1],
                                    d[i-1+j*lenStr1-1] + cost      // transposition
                          );
      }
      printTab(d,lenStr1+1,lenStr2+1);

    }
  }                                

  printTab(d,lenStr1+1,lenStr2+1);
  return d[lenStr1+lenStr1*lenStr2];
}


