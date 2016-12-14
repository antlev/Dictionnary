#include <stdio.h>
#include <stdlib.h>

#include "../headers/gestbib.h"
#include "../headers/gestrech.h"
#include "../headers/gestorth.h"
#include "../headers/gestreg.h"
#include "../headers/utils.h"
#include <sys/mman.h>

extern long nbNodeParcoured;
node* map;

// @brief Search recursivly in the dictionary
// @param tree : root of the dictionary
// @param word : strig use to store word while recursively browsing into dictionary
// @param level  used to store the current level in tree
unsigned int getWordInDicWithReg(unsigned int tree,char* word,short level,char* reg){
    nbNodeParcoured++;
    int i=0;
    if(map[tree].endOfWord == 1){
        word[level] = '\0';
        if(DEBUG >= 3){
            printf("DEBUG>>End of word!!\n");
        }
		regSearch(reg,word);
    }
    unsigned int res = 0;
    for (i = 0; i < LAST_LETTER_ACCEPTED-OFFSET_ISO8859; ++i){
        if(map[tree].letter[i] != 0){        
            word[level] = i+OFFSET_ISO8859;
            res = getWordInDicWithReg(map[tree].letter[i],word,level+1,reg);
            word[level] = '\0';
        }
    }
    return res;
 }

void regSearch(char* reg,char* word) {

	 int i, rlen, tlen, f = 0;
	 //char ans;
	 for (rlen = 0; reg[rlen] != '\0'; rlen++);
	 if (reg[0] == '*') {
	     printf("\nInvalid regular expression");
	 }

	 if ((reg[0] >= 65 && reg[0] <= 90) || (reg[0] >= 97 && reg[0] <= 122)) {
	     if (reg[0] == word[0]) {
	         switch (reg[1]) {
	             case '.' :
	                 switch (reg[2]) {
	                     case '*':
	                         if (tlen != 1) {
	                             if (reg[3] == word[tlen - 1]) {
	                                 printf("%s \n", word);
	                             } else {
	                                 // printf("wrong way");
	                             }
	                         } else {
	                             // printf("wrong way");
	                         }
	                         break;
	                 }
	             case '*':
	                 if (reg[rlen - 1] == word[tlen - 1]) {
	                     for (i = 0; i <= tlen - 2; i++) {
	                         if (word[i] == reg[0]) {
	                             f = 1;
	                         } else {
	                             f = 0;
	                         }
	                     }
	                     if (f == 1) {
	                         printf("%s \n", word);
	                     } else {
	                         // printf("wrong way");
	                     }
	                 } else {
	                     // printf("wrong way");
	                 }
	                 break;
	         }
	     }

	}
}




