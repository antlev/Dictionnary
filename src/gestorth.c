// Include from tiers library
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/time.h>
// Include from our own file
#include "../headers/gestbib.h"
// #include "../headers/gestorth.h"
#include "../headers/utils.h"

#ifndef DEBUG
    #define DEBUG (0)
#endif

extern node* map;

// Search recursivly in the dictionary
// @param tree : root of the dictionary
// @param word : strig use to store word while recursively browsing into dictionary
// @param level  used to store the current level in tree
unsigned int getAllWordInDictionary(unsigned int tree,char* word,short level){
    int i=0;
    if(map[tree].endOfWord == 1){
        // printf("DEBUG>>End of word!!\n");
        while(word[i] != '\0'){
            if(DEBUG >= 3){
                printf("%c",word[i] );
            }
            i++;
        }
        if(DEBUG >= 3){
            printf("\n");
        }
        // printf(" has been found in dictionary\n");
    }
    unsigned int res = 0;
    for (i = 0; i < 26; ++i){
        if(map[tree].letter[i] != 0){        
            // printf("DEBUG>>>letter %c spotted ! \n",i+97);
            word[level] = i+97;
            res = getAllWordInDictionary(map[tree].letter[i],word,level+1);
            word[level] = '\0';
        }
    }
    return res;
 }
// TODO
int nbNodeParcoured = 0;
int levenstein = 0;
// Search recursivly in the dictionary for word that have a levenstein distance smaller than threshold and print them on screen
// @param tree : root of the dictionary
// @param word : strig use to store word while recursively browsing into dictionary
// @param level : used to store the current level in tree
// @param wordToCompare : string containing word to compare to every word of the tree
// @param threshold : maximum difference between the wordToCompare and potential word in dictionary
// @param diff : used to optiimise and stop searching if word are too different on branches below
unsigned int levensteinInDictionary(unsigned int tree,short level,char* wordToCompare,short threshold,short diff,char* word,short* found){
    nbNodeParcoured++;
    // printf("nbNodeParcoured=%d | word possibly found =%d\n",nbNodeParcoured,levenstein );
    int i=0;
    int distance;

    if(map[tree].endOfWord == 1){
        // printf("DEBUG>>End of word!!\n");

        if((distance = DamerauLevenshteinDistance(word,wordToCompare)) <= threshold){
        	levenstein++;
            *found = 1;
            if(DEBUG >= 1){
                printf("word >%s< has a levenstein difference of %d with >%s<\n",word,distance,wordToCompare);
            }
        }else{
             // printf("word >%s< has a" " levenstein difference of %d with >%s<\n",word,distance,wordToCompare);
        }
    }
    unsigned int res = 0;
    for (i = 0; i < 26; ++i){
        if(map[tree].letter[i] != 0){ 
            // Pruning (élagage)       
            // printf("DEBUG>>>letter %c spotted ! \n",i+97);
            if(strchr(wordToCompare,i+97) == NULL){
                if(diff > threshold){
                    continue;
               }
               diff++;
            }
            word[level] = i+97;
            res = levensteinInDictionary(map[tree].letter[i],level+1,wordToCompare,threshold,diff,word,found);
            word[level] = '\0';
        }
    }
    return res;
}
int scanFile(char* pathTofile,unsigned int dictionary){
    FILE * fileToScan;
    char * line = NULL;
    char* wordToCompare = malloc(sizeof(char)*256);
    char* word = malloc(sizeof(char)*256);
    size_t len = 0;
    ssize_t read;
    int i,j;
    short similarWordFound = 0;

    fileToScan = fopen(pathTofile, "r");
    if (fileToScan == NULL){
        printf("File '%s' doesn't exist\n",pathTofile);
        return -1;
    }


    while ((read = getline(&line, &len, fileToScan)) != -1) {
        line[strlen(line)-1] = '\0';
        i=0;
        while(line[i] != '\0'){
            j=0;
            while(line[i] != ' ' && line[i] != '\0'){        
                wordToCompare[j] = line[i];
                i++;
                j++;
            }
            wordToCompare[j] = '\0';
            similarWordFound=0;
            // printf("wordToCompare >%s< is contained in file\n",wordToCompare );
            if(searchWord(dictionary,wordToCompare) == 1){
                printf("word >%s< is contained in dictionary\n",wordToCompare );
            }else{
                printf("word >%s< is NOT contained in dictionary\n",wordToCompare );
                levensteinInDictionary(dictionary,0,wordToCompare,2,0,word,&similarWordFound);
                if (!similarWordFound){
                    printf("No word similar of >%s< is contained in dictionary\n",wordToCompare);
                }
            }

            wordToCompare[0] = '\0';
            // TODO search word in dic and levenstein if not
            i++;
        }
    }

     fclose(fileToScan);


}