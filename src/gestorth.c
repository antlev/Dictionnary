// Include from tiers library
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/time.h>
// Include from our own file
#include "../headers/gestbib.h"
#include "../headers/gestorth.h"
#include "../headers/gestrech.h"
#include "../headers/utils.h"

extern node* map;
long nbNodeParcoured = 0;

// Search recursivly in the dictionary
// @param tree : root of the dictionary
// @param word : strig use to store word while recursively browsing into dictionary
// @param level  used to store the current level in tree
unsigned int getAllWordInDictionary(unsigned int tree,char* word,short level){
    nbNodeParcoured++;
    if(DEBUG >= 3){
        printf("getAllWordInDictionary is called\n");
    }
    int i=0;
    if(map[tree].endOfWord == 1){
        word[level] = '\0';
        if(DEBUG >= 3){
            printf("DEBUG>>End of word!!\n");
        }
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
    for (i = 0; i < LAST_LETTER_ACCEPTED-OFFSET_ISO8859; ++i){
        if(map[tree].letter[i] != 0){        
            // printf("DEBUG>>>letter %c spotted ! \n",i+97);
            word[level] = i+OFFSET_ISO8859;
            res = getAllWordInDictionary(map[tree].letter[i],word,level+1);
            word[level] = '\0';
        }
    }
    return res;
 }
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
        word[level] = '\0';
        if((distance = DamerauLevenshteinDistance(word,wordToCompare)) <= threshold){
            *found = 1;
            printf("word >%s< has a levenstein difference of %d with >%s<\n",word,distance,wordToCompare);
        }else{
            if(DEBUG >= 1){
                printf("word >%s< has a" " levenstein difference of %d with >%s<\n",word,distance,wordToCompare);
            }
        }
    }
    unsigned int res = 0;
    for (i = 0; i < LAST_LETTER_ACCEPTED-OFFSET_ISO8859; ++i){
        if(map[tree].letter[i] != 0){ 
            // Pruning (élagage)       
            // printf("DEBUG>>>letter %c spotted ! \n",i+97);
            if(strchr(wordToCompare,i+97) == NULL){
                if(diff > threshold){
                    continue;
               }
               diff++;
            }
            word[level] = i+OFFSET_ISO8859;
            res = levensteinInDictionary(map[tree].letter[i],level+1,wordToCompare,threshold,diff,word,found);
            word[level] = '\0';
        }
    }
    return res;
}
// Search recursivly in the dictionary for word that have a levenstein distance smaller than maxThreshold and print them on screen
// @param tree : root of the dictionary
// @param word : strig use to store word while recursively browsing into dictionary
// @param level : used to store the current level in tree
// @param wordToCompare : string containing word to compare to every word of the tree
// @param threshold : maximum difference between the wordToCompare and potential word in dictionary
// @param diff : used to optiimise and stop searching if word are too different on branches below
unsigned int printCloseWordInDic(unsigned int tree,short level,char* wordToCompare,short maxThreshold,short diff,char* word,short* found){
    nbNodeParcoured++;
    int i=0;
    int distance;

    if(map[tree].endOfWord == 1){
        // printf("DEBUG>>End of word!!\n");
        word[level] = '\0';
        if((distance = DamerauLevenshteinDistance(word,wordToCompare)) <= maxThreshold){
            if (!*found)
            {
                *found = 1;
            }
            printf(" '%s'(%d) ",word,distance);
        }else if(DEBUG >= 3){
            printf("word >%s< has a" " levenstein difference of %d with >%s<\n",word,distance,wordToCompare);
        }
    }
    unsigned int res = 0;
    for (i = 0; i < LAST_LETTER_ACCEPTED-OFFSET_ISO8859; ++i){
        if(map[tree].letter[i] != 0){ 
            // Pruning (élagage)       
            // printf("DEBUG>>>letter %c spotted ! \n",i+97);
            if(strchr(wordToCompare,i+97) == NULL){
                if(diff > maxThreshold){
                    continue;
               }
               diff++;
            }
            word[level] = i+OFFSET_ISO8859;
            res = printCloseWordInDic(map[tree].letter[i],level+1,wordToCompare,maxThreshold,diff,word,found);
            word[level] = '\0';
        }
    }
    return res;
}
// Search in dictionnary for closest word to wordToCompare and put it in closestWord
unsigned int returnClosestWordinDic(unsigned int tree,short level,char* wordToCompare,short diff,char* word,short* found,char* closestWord){

}
// Scan a file, and test for all word if it is in dictionary 
// If the word isn't found in dictionnary, it will print similar words in dictionary,
// If no word is similar in dictionary, print a message
// @param pathTofile : path to file to scan
// @param dictionary : root of the dictionary's tree
// @return -1 if  file could not have been opened
int scanFile(char* pathTofile,unsigned int dictionary){
    FILE * fileToScan;
    char * line = NULL;
    char* wordToCompare = malloc(sizeof(char)*256);
    char* word = malloc(sizeof(char)*256);
    size_t len = 0;
    ssize_t read;
    int i,j;
    short* similarWordFound = malloc(sizeof(short));

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
            if(DEBUG >= 2){
                printf("wordToCompare >%s< is contained in file\n",wordToCompare );
            }
            if(searchWord(dictionary,wordToCompare) == 1){
                printf("word >%s< is contained in dictionary\n",wordToCompare );
            }else{
                printf("word >%s< is NOT contained in dictionary\n",wordToCompare );            
                *similarWordFound = 0;
                printCloseWordInDic(dictionary,0,wordToCompare,2,0,word,similarWordFound);
                printf("similarWordFound=%d\n",*similarWordFound );
                if (!similarWordFound){
                    printf("No word similar of >%s< is contained in dictionary\n",wordToCompare);
                }
            }
            wordToCompare[0] = '\0';
            i++;
        }
    }
    fclose(fileToScan);
}
int printWordNotInDic(char* pathTofile,unsigned int dictionary,short proposeCorrection){
    FILE * fileToCorrect;
    char * line = NULL;
    
    char* wordToCompare = malloc(sizeof(char)*256);
    char* word = malloc(sizeof(char)*256);
    short* similarWordFound = malloc(sizeof(short));
    size_t len = 0;
    ssize_t read;
    int i,j;

    fileToCorrect = fopen(pathTofile, "r");
    if (fileToCorrect == NULL){
        printf("File '%s' doesn't exist\n",pathTofile);
        return -1;
    }

    while ((read = getline(&line, &len, fileToCorrect)) != -1) {
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
            if(searchWord(dictionary,wordToCompare) != 1){
                printf("Le mot '%s' à la ligne %ld n'est pas contenu dans le dictionnaire :\n",wordToCompare,read );            
                *similarWordFound = 0;
                printCloseWordInDic(dictionary,0,wordToCompare,2,0,word,similarWordFound);
                printf("\n");
                if (!similarWordFound){
                    printf("Aucun mot proche n'a été trouvé\n");
                }
                wordToCompare[0] = '\0';
                i++;
            }
        }
    }
    fclose(fileToCorrect);
}
// Read file pathToFile and write a correction into a new file suffixed by _corrected
int proposeCorrection(char* pathTofile,unsigned int dictionary){
    FILE * fileToCorrect;
    FILE * fileCorrected;

    size_t len = 0;
    ssize_t read;
    int i,j;
    short* similarWordFound = malloc(sizeof(short));
    char * line = NULL;

    char* wordToCompare = malloc(sizeof(char)*256);
    char* word = malloc(sizeof(char)*256);

    char* pathToFileCorrected = concat(pathTofile,"_corrected");

    fileToCorrect = fopen(pathTofile, "w");
    fileCorrected = fopen(pathToFileCorrected, "w");
    
    if (fileToCorrect == NULL){
        printf("File '%s' doesn't exist\n",pathTofile);
        return -1;
    }

    while ((read = getline(&line, &len, fileToCorrect)) != -1) {
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
            if(DEBUG >= 2){
                printf("wordToCompare >%s< is contained in file\n",wordToCompare );
            }
            if(searchWord(dictionary,wordToCompare) == 1){
                fprintf(fileCorrected, "%s ", wordToCompare);
            }else{
                printf("word >%s< is NOT contained in dictionary\n",wordToCompare );            
                *similarWordFound = 0;

                char* closestWord = malloc(sizeof(char)*256);

                returnClosestWordinDic(dictionary,0,wordToCompare,2,word,similarWordFound,closestWord);
                if (!similarWordFound){
                    fprintf(fileCorrected, "%s (Aucune suggestion) ", wordToCompare);
                }else{                    
                    fprintf(fileCorrected, "%s ", closestWord);
                }
            }
            wordToCompare[0] = '\0';
            i++;
        }
    }
    fclose(fileToCorrect);
}