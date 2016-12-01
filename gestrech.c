// Include from tiers library
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
// Include from our own file
#include "gestrech.h"


// Return the Damerau Levenshtein Distance between 2 strings.
// the distance returned is increased by one for each deletion,insertion,substitution or transposition.
int DamerauLevenshteinDistance(char* str1, char* str2){
    // TODO strlen
    short strlen1 = strlen(str1);
    short strlen2 = strlen(str2);

    // printf("str1:>%s<\n",str1 );
    // printf("str2:>%s<\n",str2 );
    // printf("strlen1:%d\n",strlen1 );
    // printf("strlen2:%d\n",strlen2 );
    // d is a table with strlen1+1 rows and strlen2+1 columns
    int* d = calloc(sizeof(int)*((strlen1+1)*(strlen2+1)),1);
    // i and j are used to iterate over str1 and str2
    int i, j, cost;

    // printf("---------- INITIALISATION ---------->\n");

    for(i=0;i<=strlen1;i++){
        for(j=0;j<=strlen2;j++){
            if(j == 0){
                *getTab(d,strlen1+1,i,j) = i ; 
                // printf("!!!!!!!!!!!!!!! DEBUG i=%d j=%d !!!!!!!!!!\n",i,j );
            }else if(i == 0){
                *getTab(d,strlen1+1,i,j) = j ; 
                // printf("!!!!!!!!!!!!!!! DEBUG i=%d j=%d !!!!!!!!!!\n",i,j );
            }else{
                *getTab(d,strlen1+1,i,j) = 0 ; 
            }
        } 
    }
    // printf("---------- TREATMENT ---------->\n");

    for(i=0;i<strlen1;i++){
        for(j=0;j<strlen2;j++){
            if(str1[i+1] == str2[j+1]){ 
                cost = 0;
            }else {
                cost = 1;
            }
                 // printf("!!!!!!!!!!!!!!! DEBUG i=%d j=%d !!!!!!!!!!\n",i,j );
           
            *getTab(d,strlen1+1,i+1,j+1) = minimum3(
                    *getTab(d,strlen1+1,i,j+1) + 1, // deletion
                    *getTab(d,strlen1+1,i+1,j) + 1, // insertion
                    *getTab(d,strlen1+1,i,j) + cost); // substitution
      
            if(i > 0 && j > 0 && str1[i] == str2[j-1] && str1[i-1] == str2[j]){
                    *getTab(d,strlen1+1,i+1,j+1) = minimum2(
                    *getTab(d,strlen1+1,i+1,j+1),
                    *getTab(d,strlen1+1,i-1,j)); // transposition
            }
        }
    }          
    int returnValue = *getTab(d,strlen1+1,strlen1,strlen2);
    free(d);             
    return returnValue;
}
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
// Return pointer of the 'tab' of 'nbCol' at position : column 'i' line 'j'
int* getTab(int* tab,int nbCol,int i,int j){
    return &tab[i+j*nbCol];
}



