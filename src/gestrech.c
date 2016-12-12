// Include from tiers library
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
// Include from our own file
#include "../headers/gestrech.h"


#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))

int DamerauLevenshteinDistance(char *s1, char *s2) {
    unsigned int x, y, s1len, s2len;
    s1len = strlen(s1);
    s2len = strlen(s2);
    unsigned int matrix[s2len+1][s1len+1];
    matrix[0][0] = 0;
    for (x = 1; x <= s2len; x++)
        matrix[x][0] = matrix[x-1][0] + 1;
    for (y = 1; y <= s1len; y++)
        matrix[0][y] = matrix[0][y-1] + 1;
    for (x = 1; x <= s2len; x++)
        for (y = 1; y <= s1len; y++)
            matrix[x][y] = MIN3(matrix[x-1][y] + 1, matrix[x][y-1] + 1, matrix[x-1][y-1] + (s1[y-1] == s2[x-1] ? 0 : 1));

    return(matrix[s2len][s1len]);
}

// // Return the Damerau Levenshtein Distance between 2 strings.
// // Distance correspond to number of deletion,insertion,substitution or transposition.
// // @param str1 : string of first word to compare
// // @param str2 : string of second word to compare
// // @return levenstein distance as int
// int DamerauLevenshteinDistance(char* str1, char* str2){
//     short strlen1 = strlen(str1);
//     short strlen2 = strlen(str2);

//     if(DEBUG >= 3){
//         printf("str1:>%s<\n",str1 );
//         printf("str2:>%s<\n",str2 );
//         printf("strlen1:%d\n",strlen1 );
//         printf("strlen2:%d\n",strlen2 );
//     }
//     // d is a table with strlen1+1 rows and strlen2+1 columns
//     int* d = calloc(sizeof(int)*((strlen1+1)*(strlen2+1)),1);
//     // i and j are used to iterate over str1 and str2
//     int i, j, cost;
    
//     if(DEBUG >= 3){
//         printf("---------- INITIALISATION ---------->\n");
//     }
//     for (i = 0; i < strlen1; ++i){
//         *getTab(d,strlen1+1,i,0) = i;
//     }
//     for (j = 0; j < strlen2; ++j){
//         *getTab(d,strlen1+1,0,j) = j;
//     }

//     if(DEBUG >= 3){
//         printf("---------- TREATMENT ---------->\n");
//     }
//     for(i=1;i<=strlen1;i++){
//         for(j=1;j<=strlen2;j++){
//             if(str1[i] == str2[j]){ 
//                 cost = 0;
//             }else {
//                 cost = 1;
//             }
//             if(DEBUG >= 3){
//                 printf(">>>DEBUG i=%d j=%d\n",i,j );
//             }
           
//             *getTab(d,strlen1+1,i,j) = minimum3(
//                     *getTab(d,strlen1+1,i-1,j) + 1, // deletion
//                     *getTab(d,strlen1+1,i,j-1) + 1, // insertion
//                     *getTab(d,strlen1+1,i-1,j-1) + substitution); // cost
      
//             if(i > 1 && j > 1 && str1[i] == str2[j-1] && str1[i-1] == str2[j]){
//                     *getTab(d,strlen1+1,i,j) = minimum2(
//                     *getTab(d,strlen1+1,i,j),
//                     *getTab(d,strlen1+1,i-2,j-2)); // transposition
//             }
//         }
//     }          
//     int returnValue = *getTab(d,strlen1+1,strlen1,strlen2);
//     free(d); 
//     return returnValue;
// }
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
// Print a bidemsionnal table using a simple table of int
// @param tab : pointer on table of int
// @param nbLine : number of line of bidimensionnal table
// @param nbCol : number of column of bidimensionnal table
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
// Function used to manipulate a bidimensionnal table using a simple table
// @return value of int in table at line 'line' and column 'column' 
// @param tab : pointer on table of int
// @param nbLine : number of line of bidimensionnal table
// @param nbCol : number of column of bidimensionnal table
int* getTab(int* tab,int nbCol,int column,int line){
    return &tab[column+line*nbCol];
}