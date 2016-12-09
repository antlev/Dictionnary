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
                printf("word >%s< already exist in dictionary\n",wordToAdd );
            }
            return 1;
        }else{
            map[tree].endOfWord = 1 ;
            if(DEBUG >= 3){
                printf("word >%s< has been successfully added to dictionary\n", wordToAdd);
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
                return 0;
            }
            tree = map[tree].letter[wordToSearch[i] - OFFSET_ISO8859] ;
            ++i;
        }
        if(map[tree].endOfWord == 1){
            return 1;
        }else{
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
            printf("word >< has been ignored because it is empty\n" );
        }
            return -1;
    }
    // TODO letter ???... provoque problem ascii = -61 -> ignored
    for (int i = 0; i < strlen(word); ++i){
        if((unsigned char)word[i] < OFFSET_ISO8859 || (unsigned char)word[i] > LAST_LETTER_ACCEPTED){
            if(DEBUG >= 3){
                printf("i=%d word >%s< has been ignored because it contains an unaccepted char (%c)[%u] <%u>\n",i,word,word[i],(unsigned char)word[i],LAST_LETTER_ACCEPTED );
            }
            return -2;
        }
    }
    // if( (posOfUnacceptedLetter = (strspn(word,"abcdefghijklmnopqrstuvwxyz"))) < strlen(word)){  
    //     if(DEBUG >= 3){
    //         printf("word >%s< has been ignored because it contains an unaccepted char (%c)\n",word,word[posOfUnacceptedLetter] );
    //     }
    //     return -2;
    // }
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
    printf("searchWord time = %ld\n",(finishMeasuringTime-startMeasuringTime) );
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
    
    unsigned long int finishMeasuringTime;
    unsigned long int startMeasuringTime = getTime();
    if(loadDictionaryFromFile(pathToDicFile,*dicInUse) != 1){
        finishMeasuringTime = getTime();
        if(DEBUG >= 1){
            printf("Dictionary import time = %ld milliseconds\n",finishMeasuringTime-startMeasuringTime );
        }
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
    // (*dicCreated)->tree = mmap(0, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED,MAP_ANONYMOUS fd, 0);


    // (*dicCreated)->tree = calloc(sizeof(node),1);
    (*dicCreated)->tree = next;
    next ++;

    // (*dicCreated)->tree = calloc(sizeof(node),1);
    map[(*dicCreated)->tree].endOfWord = -1;
}
// Erase dictionary from memory
void eraseDic(dictionary* library,int numberOfDicToDel){
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
        printf("File '%s' doesn't exist\n",pathToDicFile);
        return -1;
    }
    while ((read = getline(&line, &len, inputFile)) != -1) {
        line[strlen(line)-1] = '\0';
        if(DEBUG >= 2){
            printf("Retrieved line %s of length %zu :\n",line, read-1);
        }
        if(addWord(dicInUse->tree,line) == 0){
            dicInUse->nbWord++;
            wordAdded++;
        }else{
            wordIgnored++;
        }
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
            printf("desc : >%s<\n",dictionary->description );
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
// -------------------------- Programm Menu  --------------------------
// Program's menu
void menu(dictionary* library){
    int choice;
    char* input = malloc(sizeof(char)*255);
    int isDicInMem=0;
    int isDicInUse=0;
    int numberOfDic = 0;
    dictionary* dicInUse = NULL;

    printMenu(dicInUse);
    
    while((choice = numericUserInput(">",input,255, 1, 8)) == -1);

    do{
        isDicInMem = isDictionaryInMemory(library);

        switch(choice){
            case 1:
                addDicMenu(&library,numberOfDic,&dicInUse);
                numberOfDic++;
                printMenu(dicInUse);
                while((choice = numericUserInput(">",input,255, 1, 8)) == -1);

            break;
            case 2:
                if(isDicInMem){
                 	chooseDicMenu(library,numberOfDic,&dicInUse);
                }else{
                    printf("Veuillez d'abord créer ou charger un dictionnaire\n");                
                }                
                printMenu(dicInUse);
                while((choice = numericUserInput(">",input,255, 1, 8)) == -1);
           
            break;
            case 3:
                buildDicWithFileMenu(&library,&numberOfDic,&dicInUse);
                printMenu(dicInUse);
                while((choice = numericUserInput(">",input,255, 1, 8)) == -1);
          
            break;
            case 4:
                if(isDicInMem){
                    eraseDicMenu(library,numberOfDic,&dicInUse);
                }else{
                    printf("Veuillez d'abord créer un dictionnaire\n");                
                }
                printMenu(dicInUse);
                while((choice = numericUserInput(">",input,255, 1, 8)) == -1);
         
            break;
            case 5:
                if(dicInUse != NULL){
                    addWordMenu(dicInUse);
                }else{
                    printf("Veuillez d'abord charger un dictionnaire\n");
                }
                printMenu(dicInUse);
                while((choice = numericUserInput(">",input,255, 1, 8)) == -1);

                choice = input[0]-48;            
            break;
            case 6:
                if(dicInUse != NULL){
                    searchWordMenu(dicInUse);
                }else{
                    printf("Veuillez d'abord charger un dictionnaire\n");
                }
                printMenu(dicInUse);
                while((choice = numericUserInput(">",input,255, 1, 8)) == -1);
               
            break;
            case 7:
                printf("Au-revoir\n");
                free(library);
                munmap(map,mmapVirtualMem);
                exit(0);
            break;
            case 8:
                if(dicInUse != NULL){
                    printf("test\n");

                    scanFile("src/test",dicInUse->tree);

                    short* found= malloc(sizeof(short));

                    unsigned long int startMeasuringTime=0;
                    unsigned long int finishMeasuringTime=0;

                    printf("---------- TEST ----------\n");
                    char* word = calloc(sizeof(char)*256,1);
                    printf("Dictionary %s :\n", dicInUse->name);

                    nbNodeParcoured=0;
                    startMeasuringTime = getTime();
                    getAllWordInDictionary(dicInUse->tree,word,0);
                    finishMeasuringTime = getTime();
                    if(DEBUG){
                        printf("%ld milliseconds to access all dictionary's word\n",(finishMeasuringTime-startMeasuringTime) );
                        printf("Nombre  de noeuds parcouru = %ld\n",nbNodeParcoured );
                    }
                    
                    nbNodeParcoured=0;
                    printf("Searching for a word looking like 'titi' \n");
                    startMeasuringTime = getTime();
                    levensteinInDictionary(dicInUse->tree,0,"titi",2,0,word,found);
                    finishMeasuringTime = getTime();

                    if(!*found){
                        printf("no word seems to look like titi \n");
                    }
                    if(DEBUG){
                        printf("nbNodeParcoured=%ld\n",nbNodeParcoured );
                        printf("%ld milliseconds to access all dictionary's word and compare the levenstein distance with 'titi'\n",(finishMeasuringTime-startMeasuringTime) );
                    }
                }else{
                    printf("Veuillez d'abord charger un dictionnaire\n");
                }
                printMenu(dicInUse);
                while((choice = numericUserInput(">",input,256, 1, 8)) == -1);
            break;
            default:
            break;
        }
    } while(1);
}
// Function executed when program is launched
dictionary* init(){
    mmapVirtualMem = VIRTUAL_MEM_SIZE_MAX;
    // Using mmap instead of pointer to reduce the space used by one node
    do{
        mmapVirtualMem /= 2;
        assert(mmapVirtualMem > 0);
        map = mmap(0,mmapVirtualMem,PROT_WRITE|PROT_READ,MAP_SHARED|MAP_ANONYMOUS,0,0);
        printf("Trying to set virtual mem to %ld\n",mmapVirtualMem );


    } while(map == (void*)-1);

    printf("mmap set a virtual mem of %ld\n",mmapVirtualMem );

    dictionary* library = calloc(sizeof(dictionary),1);
    return library;
}
// -------------------------- Test functions  --------------------------
// Test function, can be verbose and print debug option 
// 0 -> no output except line telling if all tests passed or not
// 1 -> debug output
void test(int verbose){
    unsigned long finish;
    unsigned long start;
    if(verbose){ start = getTime() ; } 
    int passed=1;

    dictionary* library = init(); 
    dictionary* dicInUse = NULL;

    if(verbose){
        printf("TESTING isDictionaryInMemory() function\n");
        printf("isDictionaryInMemory(library):%d (expected 0)\n",isDictionaryInMemory(library));      
    }
    if(isDictionaryInMemory(library)){
        passed = 0 ;
        if(verbose){
            printf("Problem with isDictionaryInMemory() function\n");
        }
    }

    if(verbose){ printf("addDicAndUse() !\n");}
    addDicAndUse(&library,0,"test","test",&dicInUse);

    if(verbose){
        printf("isDictionaryInMemory(library) %d (expected 1)\n",isDictionaryInMemory(library));      
    }
    if(!isDictionaryInMemory(library)){
        passed = 0 ;
        if(verbose){
            printf("Problem with isDictionaryInMemory() function\n");
        }
    }
    unsigned int tree = library->tree;

    char* testString = "toto";
    char* testString2 = "tototutu";
    char* testString3 = "camion";
    char* testString4 = "voiture";
    char* testString5 = "chat";
    char* testString6 = "chatte";

    char* unexistantString = "tot";
    char* unexistantString2 = "helloworld";
    char* unexistantString3 = "abcdefghijklmnopqrstuvwxyz";

    char* emptyString = "";
    char* uncompatibleString = "MAJUSCULE";
    char* uncompatibleString2 = "./..";
    char* uncompatibleString3 = "&@?";
    

    
    if(verbose){
        printf("TESTING sanitiseWordForDictionary() function\n");
    }
    if(sanitiseWordForDictionary(emptyString) != -1){
        passed = 0 ;        
        if(verbose){
            printf("!!!!!!!!!! Problem detected with sanitiseWordForDictionary() function !!!!!!!!!!\n");
            printf("-> Error do not return -1 on empty string <-\n");
        }
    }    
    if(sanitiseWordForDictionary(uncompatibleString) != -2 || sanitiseWordForDictionary(uncompatibleString2) != -2 || sanitiseWordForDictionary(uncompatibleString3) != -2 ){
        passed = 0 ;        
        if(verbose){
            printf("!!!!!!!!!! Problem detected with sanitiseWordForDictionary() function !!!!!!!!!!\n");
            printf("-> Error do not return -1 on empty string <-\n");
        }
    }

    if(searchWord(tree,testString) != 0 || searchWord(tree,testString2) != 0 || searchWord(tree,testString3) != 0 || searchWord(tree,testString4) != 0 || searchWord(tree,testString5) != 0 || searchWord(tree,testString6) != 0){
        passed = 0 ;        
        if(verbose){
            printf("!!!!!!!!!! Problem detected with searchWord() function !!!!!!!!!!\n");
            printf("-> Non added word has been found in dictionnary <-\n");
        }
    }

    if(verbose) {  printf("TESTING addWord() function\n"); }
    if(addWord(tree,testString) != 0 || addWord(tree,testString2) != 0 || addWord(tree,testString3) != 0 || addWord(tree,testString4) != 0 || addWord(tree,testString5) != 0 || addWord(tree,testString6) != 0){
        passed = 0;
        if(verbose){
            printf("!!!!!!!!!! Problem detected with addWord() function !!!!!!!!!!\n");
            printf("-> Error while adding word in dictionary <-\n");
        }
    }
    if(addWord(tree,testString) != 1 || addWord(tree,testString2) != 1 || addWord(tree,testString3) != 1 || addWord(tree,testString4) != 1 || addWord(tree,testString5) != 1 || addWord(tree,testString6) != 1){
        passed = 0;
        if(verbose){
            printf("!!!!!!!!!! Problem detected with addWord() function !!!!!!!!!!\n");
            printf("-> Adding a existing word in dictionary do not return 1 <-\n");
        }
    }

    if(addWord(tree,uncompatibleString) != -2 || addWord(tree,uncompatibleString2) != -2 || addWord(tree,uncompatibleString3) != -2){
        passed = 0;
        if(verbose){
            printf("!!!!!!!!!! Problem detected with addWord() function !!!!!!!!!!\n");
            printf("-> Adding an uncompatible word in dictionary do not return -2 <-\n");
        }
    }

    if(addWord(tree,"") != -1){
        passed = 0;
        if(verbose){
            printf("!!!!!!!!!! Problem detected with addWord() function !!!!!!!!!!\n");
            printf("-> Adding an empty string in dictionary do not return -1 <-\n");
        }
    }

    if(verbose) { printf("TESTING searchWord() function\n"); }

    if(searchWord(tree,testString) != 1 || searchWord(tree,testString2) != 1 || searchWord(tree,testString3) != 1 || searchWord(tree,testString4) != 1 || searchWord(tree,testString5) != 1 || searchWord(tree,testString6) != 1){
        passed = 0 ;        
        if(verbose){
            printf("!!!!!!!!!! Problem detected with searchWord() function !!!!!!!!!!\n");
            printf("-> Searching an existant word do not return 1 <-\n");
        }
    }

    if(searchWord(tree,unexistantString) != 0 || searchWord(tree,unexistantString2) != 0 || searchWord(tree,unexistantString3) != 0 ){
        passed = 0 ;
        if(verbose){
            printf("!!!!!!!!!! Problem detected with searchWord() function\n");
            printf("-> Searching an non-existant word do not return 0 <-\n");
        }
    }

    if(searchWord(tree,emptyString) != -1){
        passed = 0 ;
        if(verbose){
            printf("!!!!!!!!!! Problem detected with searchWord() function\n");
            printf("-> Searching an empty string do not return -1 <-\n");
        }
    }

    if(searchWord(tree,uncompatibleString) != -2 || searchWord(tree,uncompatibleString2) != -2 || searchWord(tree,uncompatibleString3) != -2 ){
        passed = 0 ;
        if(verbose){
            printf("!!!!!!!!!! Problem detected with searchWord() function\n");
            printf("-> Searching an uncompatible string do not return -2 <-\n");
        }
    }

    if(verbose){
        printf("------------------- Report -------------------\n");
        printf("----------------------------------------------\n");
        printf("------------- addWord function ---------------\n");
        printf("addWord(tree,testString)=%d (expected:1)\n",addWord(tree,testString) );
        printf("addWord(tree,testString2)=%d (expected:1)\n",addWord(tree,testString2) );
        printf("addWord(tree,testString3)=%d (expected:1)\n",addWord(tree,testString3) );
        printf("addWord(tree,testString4)=%d (expected:1)\n",addWord(tree,testString4) );
        printf("addWord(tree,testString5)=%d (expected:1)\n",addWord(tree,testString5) );
        printf("addWord(tree,testString6)=%d (expected:1)\n",addWord(tree,testString6) );
        printf("addWord(tree,emptyString)=%d (expected:-1)\n",addWord(tree,emptyString) );
        printf("addWord(tree,uncompatibleString)=%d (expected:-2)\n",addWord(tree,uncompatibleString) );
        printf("addWord(tree,uncompatibleString2)=%d (expected:-2)\n",addWord(tree,uncompatibleString2) );
        printf("addWord(tree,uncompatibleString3)=%d (expected:-2)\n",addWord(tree,uncompatibleString3) );
        printf("----------------------------------------------\n");
        printf("------------ searchWord function -------------\n");
        printf("searchWord(tree,testString)=%d (expected:1)\n",searchWord(tree,testString) );
        printf("searchWord(tree,testString2)=%d (expected:1)\n",searchWord(tree,testString2) );
        printf("searchWord(tree,testString3)=%d (expected:1)\n",searchWord(tree,testString3) );
        printf("searchWord(tree,testString4)=%d (expected:1)\n",searchWord(tree,testString4) );
        printf("searchWord(tree,testString5)=%d (expected:1)\n",searchWord(tree,testString5) );
        printf("searchWord(tree,testString6)=%d (expected:1)\n",searchWord(tree,testString6) );
        printf("searchWord(tree,unexistantString)=%d (expected:0)\n",searchWord(tree,unexistantString) );
        printf("searchWord(tree,unexistantString2)=%d (expected:0)\n",searchWord(tree,unexistantString2) );
        printf("searchWord(tree,unexistantString3)=%d (expected:0)\n",searchWord(tree,unexistantString3) );
        printf("searchWord(tree,emptyString)=%d (expected:-1)\n",searchWord(tree,emptyString) );
        printf("searchWord(tree,uncompatibleString)=%d (expected:-2)\n",searchWord(tree,uncompatibleString) );
        printf("searchWord(tree,uncompatibleString2)=%d (expected:-2)\n",searchWord(tree,uncompatibleString2) );
        printf("searchWord(tree,uncompatibleString3)=%d (expected:-2)\n",searchWord(tree,uncompatibleString3) );
        printf("----------------------------------------------\n");         
    }
    // if(supWord(tree,testString) != 1 || supWord(tree,unexistantString) != 0 || supWord(tree,unexistantString2) != 0){
    //     passed = 0;
    //     printf("toto\n");
    // }

    if(verbose){
        char* word = calloc(sizeof(char)*256,1);
        char* inputFile = "test.dic";
        if(loadDictionaryFromFile("test.dic",library) != 0){
            if(verbose){
                printf("!!!!!!!!!! Problem detected in loadDictionaryFromFile !!!!!!!!!!\n");
                printf("Check that file %s exist\n",inputFile);
            }
            passed = 0;
        }
        getAllWordInDictionary(library->tree,word,0);
        short* found = malloc(sizeof(short));
        *found = 0;
        char* word2 = calloc(sizeof(char)*256,1);
        levensteinInDictionary(library->tree,0,"titi",2,0,word2,found);
    }


    if(passed){
        printf("All tests passed.\n");
    }else{
        printf("Some tests didn't passed\n");
    }

    if(verbose){
        printf("sizeof(node)=%ld\n",sizeof(node) );
        finish = getTime();
        printf("Test execution took %ld milliseconds.\n",(finish-start) );
    }
}