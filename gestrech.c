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

int* getTab(int* ptr,int nbCol,int i,int j){
    return &ptr[i+j*nbCol];
}
// Return the Damerau Levenshtein Distance between 2 strings.
// the distance returned is increased by one for each deletion,insertion,substitution or transposition.
int DamerauLevenshteinDistance(char* str1, int lenStr1, char* str2, int lenStr2){
  // d is a table with lenStr1+1 rows and lenStr2+1 columns
  int* d = calloc(sizeof(int)*(lenStr1+lenStr2),1);
  // i and j are used to iterate over str1 and str2
  int i, j, cost;

  printf("---------- START ---------->\n");

  printf("---------- INITIALISATION ---------->\n");


  for(i=0;i<=lenStr1;i++){
    for(j=0;j<=lenStr2;j++){
      *getTab(d,lenStr1+1,i,j) = 0 ; 
    }
  }

  for(i=0;i<=lenStr1;i++){
    // d[i*lenStr1] = i;
    *getTab(d,lenStr1+1,i,0) = i ;
    // printTab(d,lenStr1+1,lenStr2+1);
  }
  for(j=0;j<=lenStr2;j++){

    *getTab(d,lenStr1+1,0,j) = j ;
  }


  printf("---------- TREATMENT ---------->\n");

  for(i=0;i<=lenStr1;i++){
    for(j=0;j<=lenStr2;j++){


      if(str1[i+1] == str2[j+1]){ 
        cost = 0;
      }else {
        cost = 1;
      }
      *getTab(d,lenStr1,i+1,j+1) = minimum3(
                          *getTab(d,lenStr1,i,j+1) + 1, // deletion
                          *getTab(d,lenStr1,i+1,j) + 1, // insertion
                          *getTab(d,lenStr1,i,j) + cost // substitution
                );
      if(i > 0 && j > 0 && str1[i] == str2[j-1] && str1[i-1] == str2[j]){
                *getTab(d,lenStr1,i+1,j+1) = minimum2(
                                    *getTab(d,lenStr1,i+1,j+1),
                                    *getTab(d,lenStr1,i-1,j) // transposition
                          );
      }

    }
  }                                

  // printTab(d,lenStr1+1,lenStr2+1);
  // int returnValue = *getTab(d,lenStr1,lenStr1,lenStr2);
  // free(d);
  return *getTab(d,lenStr1,lenStr1,lenStr2);
}


