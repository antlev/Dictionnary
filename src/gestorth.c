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

// @brief Search recursivly in the dictionary
// @param tree : root of the dictionary
// @param word : strig use to store word while recursively browsing into dictionary
// @param level  used to store the current level in tree
unsigned int getAllWordInDictionary(unsigned int tree,char* word,short level){
    nbNodeParcoured++;
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
    }
    unsigned int res = 0;
    for (i = 0; i < LAST_LETTER_ACCEPTED-OFFSET_ISO8859; ++i){
        if(map[tree].letter[i] != 0){        
            word[level] = i+OFFSET_ISO8859;
            res = getAllWordInDictionary(map[tree].letter[i],word,level+1);
            word[level] = '\0';
        }
    }
    return res;
 }
//**********************************************************************
//************** Funcions that compare word in dictionary **************
//**********************************************************************
// 

// @brief Search recursivly in the dictionary for word that have a levenstein distance smaller than maxThreshold and print them on screen
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
            *found = 1;
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
            // if(strchr(wordToCompare,i+97) == NULL){
            //     if(diff > maxThreshold){
            //         continue;
            //    }
            //    diff++;
            // }
            word[level] = i+OFFSET_ISO8859;
            res = printCloseWordInDic(map[tree].letter[i],level+1,wordToCompare,maxThreshold,diff,word,found);
            word[level] = '\0';
        }
    }
    return res;
}
// @brief Search in dictionnary for closest word to wordToCompare and put it in closestWord
// @param tree : node 
// @param level : level of node (root is 0)
// @param wordToCompare : string containing the word to compare with all dictionary words
// @param diff : Distance accepted to consider word of dic close to wordToCompare
// @param word : String that store the resulting word while browsing dictionary
// @param found : put 1 in if one 
// @param closestWord : String that store the closest word in dictionary of wordToCompare 
unsigned int returnClosestWordinDic(unsigned int tree,short level,char* wordToCompare,short diff,char* word,short* found,char* closestWord){
    nbNodeParcoured++;
    int i=0;
    int distance;

    if(map[tree].endOfWord == 1){
        if(DEBUG == 3){
            printf("DEBUG>>End of word!!\n");
        }
        word[level] = '\0';
        if((distance = DamerauLevenshteinDistance(word,wordToCompare)) <= 1){
            strcpy(closestWord, word);
            *found = 1 ;
        }else if(DEBUG >= 3){
            printf("word >%s< has a" " levenstein difference of %d with >%s<\n",word,distance,wordToCompare);
        }
    }
    unsigned int res = 0;
    for (i = 0; i < LAST_LETTER_ACCEPTED-OFFSET_ISO8859; ++i){
        if(map[tree].letter[i] != 0){ 
            // Pruning (élagage)       
            // if(strchr(wordToCompare,i+97) == NULL){
            //     if(diff > 1){
            //         continue;
            //    }
            //    diff++;
            // }
            word[level] = i+OFFSET_ISO8859;
            res = returnClosestWordinDic(map[tree].letter[i],level+1,wordToCompare,diff,word,found,closestWord);
            word[level] = '\0';
        }
    }
    return res;
}
//**********************************************************************
//********* Functions that scan files to check with dictionary *********
//**********************************************************************
// @brief Scan a file and print word that are in file but not in dictionary
// @param pathToFile : string containing the path of the file to scan 
// @param dictionary : pointer on dictionary
// @param proposeCorrection set To 0 to only print words that are not in dictionary, set to 1 if you want to propose correction
int printWordNotInDic(char* pathToFile,dictionary* dictionary,short proposeCorrection){
    FILE * fileToCorrect;
    char * line = NULL;
    
    char* wordToCompare = malloc(sizeof(char)*256);
    char* word = malloc(sizeof(char)*256);
    short* similarWordFound = malloc(sizeof(short));
    size_t len = 0;
    ssize_t read;
    int i,j,lineInFile=0;

    fileToCorrect = fopen(pathToFile, "r");
    if (fileToCorrect == NULL){
        printf("Le fichier '%s' n'éxiste pas\n",pathToFile);
        return -1;
    }

    if (!proposeCorrection){
        printf("Mots du fichier '%s' non contenu dans le dictionnaire %s\n",pathToFile,dictionary->name );
    }
    while ((read = getline(&line, &len, fileToCorrect)) != -1) {
        ++lineInFile;
        line[strlen(line)-1] = '\0';
        i=0;
        while(line[i] != '\0'){
            j=0;
            while(line[i] != ' ' && line[i] != '\0' && line[i] != '\''){        
                wordToCompare[j] = line[i];
                i++;
                j++;
            }
            wordToCompare[j] = '\0';
            if(wordToCompare[0] != '\0' && searchWord(dictionary->tree,wordToCompare) != 1){
                printf("'%s' (ligne %d) \n",wordToCompare,lineInFile );            
                if(proposeCorrection){
                    *similarWordFound = 0;
                    printCloseWordInDic(dictionary->tree,0,wordToCompare,2,0,word,similarWordFound);
                    printf("\n");
                    if (!similarWordFound){
                        printf("Aucun mot proche n'a été trouvé\n");
                    }
                }
            }   
            wordToCompare[0] = '\0';
            i++;
        }
    }
    fclose(fileToCorrect);
    free(wordToCompare);
    free(word);
    free(similarWordFound);
}
// @brief Scan file pathToFile and write a correction into a new file suffixed by _corrected
// @param pathToFile : string containing the path of the file to scan 
// @param dictionary : pointer on dictionary
int proposeCorrection(char* pathToFile,unsigned int dictionary){
    FILE* fileToCorrect;
    FILE* fileCorrected;

    size_t len = 0;
    ssize_t read;
    int i,j;
    short* similarWordFound = malloc(sizeof(short));
    char * line = NULL;

    char* wordToCompare = malloc(sizeof(char)*256);
    char* word = malloc(sizeof(char)*256);
    char* closestWord = calloc(sizeof(char)*256,1);

    char* pathToFileCorrected = concat(pathToFile,"_corrected");

    fileToCorrect = fopen(pathToFile, "r");
    fileCorrected = fopen(pathToFileCorrected, "w");
    
    if (fileToCorrect == NULL){
        printf("File '%s' doesn't exist\n",pathToFile);
        return -1;
    }else if(fileCorrected == NULL){
        printf("Problem happened with file %s\n",pathToFileCorrected);
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
                // fprintf(fileCorrected, "%s ", wordToCompare);
                fwrite(wordToCompare,sizeof(char),strlen(wordToCompare),fileCorrected);
                fwrite(" ",sizeof(char),1,fileCorrected);
            }else{
                printf("word >%s< is NOT contained in dictionary\n",wordToCompare );            
                *similarWordFound = 0;


                returnClosestWordinDic(dictionary,0,wordToCompare,2,word,similarWordFound,closestWord);
                printf("on return closestWord = %s\n",closestWord );

                // printf("on return &closestWord = %p\n",&closestWord );
                if (!similarWordFound){
                    fwrite("_",sizeof(char),1,fileCorrected);
                    fwrite(wordToCompare,sizeof(char),strlen(wordToCompare),fileCorrected);
                    fwrite("_",sizeof(char),1,fileCorrected);
                }else{                    
                    // fprintf(fileCorrected, "%s ", closestWord);
                    fwrite(closestWord,sizeof(char),strlen(closestWord),fileCorrected);
                    fwrite(" ",sizeof(char),1,fileCorrected);
                    *closestWord = '\0' ;
                }
            }
            wordToCompare[0] = '\0';
            i++;
        }
    }
    fclose(fileToCorrect);
    fclose(fileCorrected);

    fclose(fileToCorrect);
    free(wordToCompare);
    free(word);
    free(similarWordFound);
    free(closestWord);
}