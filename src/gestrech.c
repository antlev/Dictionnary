// Include from tiers library
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
// Include from our own file
#include "../headers/gestrech.h"


#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))

// // @brief Return the Damerau Levenshtein Distance between 2 strings.
// // @brief Distance correspond to number of deletion,insertion,substitution or transposition.
// // @param str1 : string of first word to compare
// // @param str2 : string of second word to compare
// // @return levenstein distance as int
int DamerauLevenshteinDistance(char* str1, char* str2) {
    int i, j, s1len, s2len;
    s1len = strlen(str1);
    s2len = strlen(str2);

    unsigned int table[s2len+1][s1len+1];
    table[0][0] = 0;
    for (i = 1; i <= s2len; i++){
        table[i][0] = table[i-1][0] + 1;
    }
    for (j = 1; j <= s1len; j++){
        table[0][j] = table[0][j-1] + 1;
    }

    for (i = 1; i <= s2len; i++){
        for (j = 1; j <= s1len; j++){
            table[i][j] = MIN3(table[i-1][j] + 1, table[i][j-1] + 1, table[i-1][j-1] + (str1[j-1] == str2[i-1] ? 0 : 1));
        }
    }
    return(table[s2len][s1len]);
}

// // @brief Return the Damerau Levenshtein Distance between 2 strings.
// // @brief Distance correspond to number of deletion,insertion,substitution or transposition.
// // @param str1 : string of first word to compare
// // @param str2 : string of second word to compare
// // @return levenstein distance as int
// int DamerauLevenshteinDistance(char* str1, char* str2){
//     short strlen1 = strlen(str1);
//     short strlen2 = strlen(str2);

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
           
//             *getTab(d,strlen1+1,i,j) = minimum3(
//                     *getTab(d,strlen1+1,i-1,j) + 1, // deletion
//                     *getTab(d,strlen1+1,i,j-1) + 1, // insertion
//                     *getTab(d,strlen1+1,i-1,j-1) + cost); // cost
      
//             // if(i > 1 && j > 1 && str1[i] == str2[j-1] && str1[i-1] == str2[j]){
//             //         *getTab(d,strlen1+1,i,j) = minimum2(
//             //         *getTab(d,strlen1+1,i,j),
//             //         *getTab(d,strlen1+1,i-2,j-2)); // transposition
//             // }
//         }
//     }          
//     int returnValue = *getTab(d,strlen1+1,strlen1,strlen2);
//     free(d); 
//     return returnValue;
// }
// @brief Return the lowest val between val1,val2 and val3
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
// @brief Return the lowest val between val1 and val2
int minimum2(int val1, int val2){
    if(val1 <= val2){
        return val1;
    }else{
        return val2;
    }
    return 0;
}
// @brief Print a bidemsionnal table using a simple table of int
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
// @brief Function used to manipulate a bidimensionnal table using a simple table
// @return value of int in table at line 'line' and column 'column' 
// @param tab : pointer on table of int
// @param nbLine : number of line of bidimensionnal table
// @param nbCol : number of column of bidimensionnal table
int* getTab(int* tab,int nbCol,int column,int line){
    return &tab[column+line*nbCol];
}