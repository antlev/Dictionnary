// Include from tiers library
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/mman.h>
#include <assert.h>
// Include from our own file
#include "../headers/gestbib.h"
#include "../headers/gestrech.h"
#include "../headers/gestorth.h"
#include "../headers/utils.h"
// Allow us to set a $DEBUG at compilation
#ifndef DEBUG
    #define DEBUG (0)
#endif

#ifndef VIRTUAL_MEM_SIZE_MAX
    #define VIRTUAL_MEM_SIZE_MAX (1L<<35)
#endif

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

extern long nbNodeParcoured;

node* map=0;
long int mmapVirtualMem=-1;
long int next=1; 
// -------------------------- Tree manipulation functions --------------------------

// Add the 'wordToAdd' into dictionary
// @param tree : root of the dictionary
// @param wordToAdd : word to add in the dictionary
// @return 0 if the wordToAdd has been successfully added 
// @return 1 if wordToAdd is already in tree
// @return -1 if wordToAdd is empty
// @return -2 if wordToAdd is uncompatible with dictionnary
int addWord(unsigned int tree,char* wordToAdd){
    assert(wordToAdd != 0);
    assert(map != 0);
    assert(&map[tree] != 0);
    int i=0;
    int sanReturn;
    if((sanReturn = sanitiseWordForDictionary(wordToAdd)) != 0){
        return sanReturn;
    }else{
        while(wordToAdd[i] != '\0'){
            if(!map[tree].letter[wordToAdd[i] - OFFSET_ISO8859]){
                map[tree].letter[wordToAdd[i] - OFFSET_ISO8859] = next;
                next ++;
            }
            tree = map[tree].letter[wordToAdd[i] - OFFSET_ISO8859] ;
            ++i;
        }
        if (map[tree].endOfWord == 1){
            if(DEBUG >= 3){
                printf("DEBUG>>> Le mot >%s< éxiste déjà dans le dictionnaire\n",wordToAdd );
            }
            return 1;
        }else{
            map[tree].endOfWord = 1 ;
            if(DEBUG >= 3){
                printf("DEBUG>>> Le mot >%s< a été ajouté avec succès dans le dictionnaire\n",wordToAdd );
            }
            return 0;
        }       
    }
}
// Search wordToSearch into the given tree
// @param tree : root of the dictionary
// @param wordToSearch : word to search in the dictionary
// @return 1 if wordToSearch exist in dictionary
// @return 0 if word doesn't exist in dictionnary
// @return -2 if wordToSearch is uncompatible with dictionnary
// @return -1 if wordToSearch is empty
int searchWord(unsigned int tree,char* wordToSearch){
    int i=0;
    int sanReturn;
    if((sanReturn = sanitiseWordForDictionary(wordToSearch)) != 0){
        return sanReturn;
    }else{
        while(wordToSearch[i] != '\0'){
            if(!map[tree].letter[wordToSearch[i] - OFFSET_ISO8859]){
                if(DEBUG >= 3){
                    printf("DEBUG>>>Le mot %s n'a pas été trouvé dans le dictionnaire\n",wordToSearch );
                }
                return 0;
            }
            tree = map[tree].letter[wordToSearch[i] - OFFSET_ISO8859] ;
            ++i;
        }
        if(map[tree].endOfWord == 1){
            if(DEBUG >= 3){
                printf("DEBUG>>>Le mot %s a été trouvé dans le dictionnaire\n",wordToSearch );
            }
            return 1;
        }else{
            if(DEBUG >= 3){
                printf("DEBUG>>>Le mot %s n'a pas été trouvé dans le dictionnaire\n",wordToSearch );
            }
            return 0;
        }
    }
}
// Suppress wordToSup into the given tree
// @param tree : root of the dictionary
// @param wordToSup : word to erase from the dictionary
// @return 1 if wordToSup has been found and suppresed, 0 if not
int supWord(unsigned int tree,char* wordToSup){
    int i=0;
    int j;
    int sanReturn;
    if((sanReturn = sanitiseWordForDictionary(wordToSup)) != 0){
        return sanReturn;
    }else{
        while(wordToSup[i] != '\0'){
            if(!map[tree].letter[wordToSup[i] - OFFSET_ISO8859]){
                return 0;
            }
            tree = map[tree].letter[wordToSup[i] - OFFSET_ISO8859] ;
            ++i;
        }
        if(map[tree].endOfWord == 0){
            return 0;
        }else{
            map[tree].endOfWord = 0 ;
            --i;
            while(i >= 0){
                for (j = 0; j < 26; ++j){
                    if(map[tree].letter[j]){
                        return 1;
                    }
                }
                // TODO
                // tree = &tree;
                // free(map[tree].letter[i]);
                --i;
            }
            return 1;   
        }
    }
}
// Sanitise word for dictionary
// @return 0 if word is compatible with dictionnary
// @return -1 if word is empty
// @return -2 if word is incompatible with dictionnary
// @param word : String containing word to sanitise
int sanitiseWordForDictionary(char* word){
    int i=0;
    short posOfUnacceptedLetter=0;
    if(strlen(word) < 1){
        if(DEBUG >= 3){
            printf("DEBUG>>>Le mot a été ignoré car il est vide\n" );
        }
        return -1;
    }
    for (int i = 0; i < strlen(word); ++i){
        if((unsigned char)word[i] < OFFSET_ISO8859 || (unsigned char)word[i] > LAST_LETTER_ACCEPTED){
            if(DEBUG >= 3){
                printf("DEBUG>>>Le mot %s a été ignoré car il contient un caractère non supporté (%c)[%u]\n",word,word[i],(unsigned char)word[i] );
            }
            return -2;
        }
    }
    return 0;
}
// -------------------------- Programm functions's menu  --------------------------
// Prompt a word and call addWord() to add it to the dictionary
// @param dictionary : pointer on dictionary in which we want to add a word
void addWordMenu(dictionary* dictionary){
    int addWordReturn;
    unsigned int tree = dictionary->tree;
    char wordToInsert[MAXNBLETTERINWORD];    
    while(userInput("Veuillez entrer le mot à insérer dans le dictionnaire\n>",wordToInsert,MAXNBLETTERINWORD) != 0);
    
    if((addWordReturn = addWord(tree,wordToInsert)) == 0){
        dictionary->nbWord++;
        printf("Le mot %s a été ajouté au dictionnaire %s\n",wordToInsert,dictionary->name );
    }else if(addWordReturn == 1){
        printf("Le mot %s éxiste déjà dans le dictionnaire %s\n",wordToInsert,dictionary->name );
    }else{
        printf("Le mot %s contient des caractères non supportés %s\n",wordToInsert,dictionary->name );
    }
}
// Prompt a word and call searchWord() to search it to the dictionary
// @param dictionary : pointer on dictionary in which we want to search a word
void searchWordMenu(dictionary* dictionary){
    unsigned int tree = dictionary->tree;
    char wordToSearch[MAXNBLETTERINWORD];


    unsigned long int startMeasuringTime;
    unsigned long int finishMeasuringTime;

    while(userInput("Veuillez entrer le mot à rechercher dans le dictionnaire\n>",wordToSearch,MAXNBLETTERINWORD) != 0);
   
    startMeasuringTime = getTime();
    if(searchWord(tree,wordToSearch)){
        finishMeasuringTime = getTime();
        printf("Le mot \'%s\' EST BIEN CONTENU dans le dictionnaire %s\n",wordToSearch,dictionary->name );
    }else{
        finishMeasuringTime = getTime();
        printf("Le mot \'%s\' N'EST PAS CONTENU dans le dictionnaire %s\n",wordToSearch,dictionary->name );
    }
    if(DEBUG >= 1){
        printf("DEBUG>>>Temps de recherche : %ldms\n",(finishMeasuringTime-startMeasuringTime));
    }
}
// Prompt user for a name and description and add a new dictionnnary to the library
// @param library : pointer on library
// @param numberOfDic : Total number of dictionary in memory
// @param dicInUse : pointer on dictionary in use
void addDicMenu(dictionary** library,int numberOfDic,dictionary** dicInUse){
    int i;
    char dicName[255] = "";
    char dicDesc[255] = "";
 
    char* pdicName = dicName;

    while(userInput("Choisissez un nom de dictionnaire\n>",dicName,255) != 0);

    while(userInput("Vous pouvez donner une description\n>",dicDesc,255) > 1);

    addDicAndUse(library,numberOfDic,dicName,dicDesc,dicInUse);
}
// Ask for dic to erase and call eraseDic
// @param library : pointer on library
// @param numberOfDic : Total number of dictionary in memory
// @param dicInUse : pointer on dictionary in use
void eraseDicMenu(dictionary* library,int numberOfDic,dictionary** dicInUse){
    int numOfDicToDel=0;
    char* input = malloc(sizeof(char)*255);
    printLibrary(library,numberOfDic);

    while((numOfDicToDel = numericUserInput("Quel dictionnaire voulez vous supprimer ?\n>",input,4,1,(short)numberOfDic)) == -1);

    // eraseDic(library,numOfDicToDel);
}
// Prompt a file path and call loadDictionaryFromFile passing it the dicInUse
// @param library : pointer on library
// @param numberOfDic : pointer on total number of dictionary in memory
// @param dicInUse : pointer on dictionary in use
void buildDicWithFileMenu(dictionary** library,int* numberOfDic,dictionary** dicInUse){
    char pathToDicFile[255];
    char input[2];

    if(*numberOfDic == 0){
        while(userInput("Vous n'avez pas de dictionnaire en mémoire voulez vous en créer un ? (O/N)\n>",input,4) != 0);
        if(input[0] == 'O' || input[0] == 'o'){
            addDicMenu(library,*numberOfDic,dicInUse);
            (*numberOfDic)++;
        }else{
            return;
        }
    } else {
        do{
            while(userInput("Voulez vous (C)réer un nouveau dictionnaire ou (A)jouter le fichier à un dictionnaire existant ?\n>",input,4) != 0);
        }
        while(input[0] != 'a' && input[0] != 'A' && input[0] != 'c' && input[0] != 'C');

        if(input[0] == 'a' || input[0] == 'A'){
            chooseDicMenu(*library,*numberOfDic,dicInUse);
        }else{
            addDicMenu(library,*numberOfDic,dicInUse);
            (*numberOfDic)++;
        }
    }
    
    while(userInput("Veuillez entrer le chemin du fichier dictionnaire\n>",pathToDicFile,255) != 0);
    

    if(loadDictionaryFromFile(pathToDicFile,*dicInUse) != 1){
        printf("Le fichier '%s' n'éxiste pas\n",pathToDicFile);
    }
 }
// Print the library and ask user to choose a dictionary
// The choosen dictionary will be pointed by dicInUse
// @param library : pointer on library
// @param numberOfDic : Total number of dictionary in memory
// @param dicInUse : pointer on dictionary in use
void chooseDicMenu(dictionary* library,int numberOfDic,dictionary** dicInUse){
    int numOfDicToUse;
    int i;
    *dicInUse = library; // using first dictionary of library
    char* input = malloc(sizeof(int));

    printLibrary(library,numberOfDic);
    while((numOfDicToUse = numericUserInput("Veuillez entrer le numéro du dictionnaire que vous voulez utiliser\n>",input,4,1,(short)numberOfDic)) == -1);
    
    *dicInUse += numOfDicToUse-1; // using the dictionary n° numOfDicToUse of library
}
// -------------------------- Dictionary manipulation functions --------------------------
// Add a new dictionary with the name and description passed as parameters
// @param library : pointer on library
// @param numberOfDic : Total number of dictionary in memory
// @param name : name of dictionary to create
// @param desc : description of dictionary to create
// @param dicCreated : pointer on dictionary created
void addDicAndUse(dictionary** library,int numberOfDic,char name[255],char desc[255],dictionary** dicCreated){
    if(numberOfDic){ // if numberOfDic=0, the first dictionary is already allocated by init()
        *library = realloc(*library,(numberOfDic+1)*sizeof(dictionary));
        memset(*library+numberOfDic,0,sizeof(dictionary)); // Setting new space to 0
    }
    *dicCreated = *library;
    (*dicCreated)+=numberOfDic;    

    strcpy((*dicCreated)->name,name);
    strcpy((*dicCreated)->description,desc);
    (*dicCreated)->nbWord=0;

    (*dicCreated)->tree = next;
    next ++;

    map[(*dicCreated)->tree].endOfWord = -1;
}
// Erase dictionary from memory
void eraseDic(dictionary* library,int numberOfDicToDel){
    //TODO
    // dictionnnary* dicToDel = library;
    // dicToDel+=numberOfDicToDel;
}
// Read file and call addWord on each line
// @param pathToDicFile : path to dictionary file to load 
// @param dicInUse : pointer on dictionary in use
// @return -1 : failure on opening file
// @return 0 : success
int loadDictionaryFromFile(char pathToDicFile[255],dictionary* dicInUse){   
    FILE * inputFile;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int wordIgnored = 0;
    int wordAdded = 0;

    inputFile = fopen(pathToDicFile, "r");
    if (inputFile == NULL){
        return -1;
    }

    unsigned long int finishMeasuringTime;
    unsigned long int startMeasuringTime = getTime();
    while ((read = getline(&line, &len, inputFile)) != -1) {
        line[strlen(line)-1] = '\0';
        if(DEBUG >= 3){
            printf("Retrieved line %s of length %zu :\n",line, read-1);
        }
        if(addWord(dicInUse->tree,line) == 0){
            dicInUse->nbWord++;
            wordAdded++;
        }else{
            wordIgnored++;
        }
    }
    finishMeasuringTime = getTime();
    if(DEBUG >= 1){
        printf("DEBUG>>>Temps d'importation du dictionnaire = %ldms\n",finishMeasuringTime-startMeasuringTime );
    }
    printf("Nombre de mots ajouté= %d Nombre de mots ignoré= %d\n",wordAdded,wordIgnored );
    fclose(inputFile);
    if(line){
        free(line);
    }
    return 0;
}

// What does the function is obvious
void printMenu(dictionary* dicInUse){
    if(dicInUse->name){
        printf("---------- Vous utilisez maintenant le dictionnaire %s ----------\n",dicInUse->name);
    }
    printf("1) Créer un fichier dictionnaire\n");
    printf("2) Utiliser un dictionnaire existant\n");
    printf("3) Fabriquer un dictionnaire à partir d'un fichier texte\n");
    printf("4) Déruire un fichier dictionnaire\n");
    printf("5) Insérer un mot dans un dictionnaire\n");
    printf("6) Rechercher un mot dans un dictionnaire\n");
    printf("7) Quitter l'application\n");    
}
// Print all the dictionnaries contained in the library
// @param library : pointer on library (first dictionary)
// @param numberOfDic : number of dictionary in memory
void printLibrary(dictionary* library, int numberOfDic){
    dictionary* dictionary = library;
    printf("Bibliothèque :\n");
   	printf("---------------------------------------\n");
    int count=0;
    int i;
	for (i = 0; i < numberOfDic; ++i){
        printf("Dictionnaire n°%d : %s\n",count+1,dictionary->name);
        if(dictionary->description[0] != '\n'){
            printf("description : >%s<\n",dictionary->description );
        }
        printf("Nombre de mots contenu dans le dictionnaire : %d\n",dictionary->nbWord );
        dictionary++;
        count++;
        printf("---------------------------------------\n");
    }
}
// Tell if a dictionnary exist in memory
// @param dicInUse : pointer on dicInUse
// @return 1 if library contain a dictionary
// @return 0 if library in use is empty
int isDictionaryInMemory(dictionary* library){
    if(library->tree == 0){
        return 0;
    }else{
        return 1;
    }
}
// TODO COMMENT
// Function executed when program is launched
dictionary* init(){
    mmapVirtualMem = VIRTUAL_MEM_SIZE_MAX;
    // Using mmap instead of pointer to reduce the space used by one node
    do{
        mmapVirtualMem /= 2;
        assert(mmapVirtualMem > 0);
        map = mmap(0,mmapVirtualMem,PROT_WRITE|PROT_READ,MAP_SHARED|MAP_ANONYMOUS,0,0);
        if(DEBUG >= 1){
            printf("DEBUG>>>Tentative d'allocation d'un mémoire virtuel de %ld bits\n",mmapVirtualMem );
        }
    } while(map == (void*)-1);
    if(DEBUG >= 1){
        printf("DEBUG>>>Mmap a alloué un espace de %ld bits\n",mmapVirtualMem );
    }
    dictionary* library = calloc(sizeof(dictionary),1);
    return library;
}