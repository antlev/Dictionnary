// Include from tiers library
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/time.h>
#include <sys/mman.h>
// Include from our own file
#include "gestbib.h"
#include "gestrech.h"
#include "gestorth.h"

#ifndef DEBUG
    #define DEBUG (0)
#endif

#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

static const int MAXNBLETTERINWORD = 20;
static const int THRESHOLD = 2;

char* map=0;
long int next=0; 
// -------------------------- Inside Dictionary functions --------------------------

// Add the 'wordToAdd' into dictionary
// @param tree : root of the dictionary
// @param wordToAdd : word to add in the dictionary
// @return 1 if the word has been successfully added 
// @return O if word is already in tree
// @return -1 if word contain unaccepted character
int addWord(node* tree,char* wordToAdd){
    int i=0;
    // TODO see why thisline doesn't work
    // if(strspn(line,"abcdefghijklmnopqrstuvwxyz") != 0){  
    while(wordToAdd[i] != '\0'){
        if (wordToAdd[i] < 97 || wordToAdd[i] > (97+26)){
            if(DEBUG >= 3){
                printf("word %s has been ignored because it contains an unaccepted char (%c)\n",wordToAdd,wordToAdd[i] );
            }
            return -1;
        }
        i++;
    }
    i=0;
    while(wordToAdd[i] != '\0'){
        if(!tree->letter[wordToAdd[i] - 97]){
            // calloc same as malloc but initialise all bit at 0
            // tree->letter[wordToAdd[i] - 97] = calloc(sizeof(node),1);

            tree->letter[wordToAdd[i] - 97] = (node*)(map+next);
            next += sizeof(node);

        }
        tree = tree->letter[wordToAdd[i] - 97] ;
        i++;
    }
    if (tree->endOfWord == 1){
        if(DEBUG >= 3){
            printf("word %s already exist in dictionary\n",wordToAdd );
        }
        return 0;
    }else{
        tree->endOfWord = 1 ;
        if(DEBUG >= 3){
            printf("word %s has been successfully added to dictionary\n", wordToAdd);
        }
        return 1;
    }
}
// @param tree : root of the dictionary
// @param wordToSearch : word to search in the dictionary
// @Return 1 if wordToSearch exist in dictionary, 0 if not
int searchWord(node* tree,char* wordToSearch){
    int i=0;
    while(wordToSearch[i] != '\0'){
        if(!tree->letter[wordToSearch[i] - 97]){
            return 0;
        }
        tree = tree->letter[wordToSearch[i] - 97] ;
        i++;
    }
    if(tree->endOfWord == 1){
        return 1;
    }else{
        return 0;
    }
}
// @param tree : root of the dictionary
// @param wordToSup : word to erase from the dictionary
// @Return 1 if wordToSup has been found and suppresed, 0 if not
int supWord(node* tree,char* wordToSup){
    int i=0;
    int j;
    while(wordToSup[i] != '\0'){
        if(!tree->letter[wordToSup[i] - 97]){
            return 0;
        }
        tree = tree->letter[wordToSup[i] - 97] ;
        i++;
    }
    if(tree->endOfWord == 0){
        return 0;
    }else{
        tree->endOfWord = 0 ;
        i--;
        while(i >= 0){
            for (j = 0; j < 26; ++j){
                if(tree->letter[j]){
                    return 1;
                }
            }
            // TODO
            // tree = &tree;
            free(tree->letter[i]);
            i--;
        }
        return 1;   
    }
}
// Prompt a word and call addWord() to add it to the dictionary
// @param dictionary : pointer on dictionary in which we want to add a word
void addWordMenu(dictionary* dictionary){
    node* tree = dictionary->tree;
    char wordToInsert[MAXNBLETTERINWORD];    
    while(userInput("Veuillez entrer le mot à insérer dans le dictionnaire\n>",wordToInsert,MAXNBLETTERINWORD) != 0);
    
    if(addWord(tree,wordToInsert)){
        printf("%s has been successfully added to the dictionary\n",wordToInsert );
        dictionary->nbWord++;
    }else{
        printf("%s already exist in dictionary\n",wordToInsert);
    }
}
// Prompt a word and call searchWord() to search it to the dictionary
// @param dictionary : pointer on dictionary in which we want to search a word
void searchWordMenu(dictionary* dictionary){
    node* tree = dictionary->tree;
    char wordToSearch[MAXNBLETTERINWORD];


    unsigned long int startMeasuringTime;
    unsigned long int finishMeasuringTime;

    while(userInput("Veuillez entrer le mot à chercher dans le dictionnaire\n>",wordToSearch,MAXNBLETTERINWORD) != 0);
   
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
// -------------------------- Programm functions's menu  --------------------------

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
    if(loadDictionaryFromFile(pathToDicFile,*dicInUse) == 1){
        printf("Le fichier dictionnaire \'%s\' n'éxiste pas\n",pathToDicFile );
    }else{
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
    while((numOfDicToUse = numericUserInput("Veuillez entrer le numéro du dictionnaire que vous voulez utiliser ?\n>",input,4,1,(short)numberOfDic)) == -1);
    
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
    (*dicCreated)->tree = (node*)(map+next);
    next += sizeof(node);

    // (*dicCreated)->tree = calloc(sizeof(node),1);
    (*dicCreated)->tree->endOfWord = -1;
}
// Erase dictionary from memory
void eraseDic(dictionary* library,int numberOfDicToDel){
    // dictionnnary* dicToDel = library;
    // dicToDel+=numberOfDicToDel;
}
// Read file and call addWord on each line
// @param pathToDicFile : path to dictionary file to load 
// @param dicInUse : pointer on dictionary in use
// @return 1 : failure
// @return 0 : success
int loadDictionaryFromFile(char pathToDicFile[255],dictionary* dicInUse){   
    FILE * inputFile;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int wordIgnored = 0;

    inputFile = fopen(pathToDicFile, "r");
    if (inputFile == NULL){
        return EXIT_FAILURE;
    }
    while ((read = getline(&line, &len, inputFile)) != -1) {
        line[strlen(line)-1] = '\0';
        if(DEBUG >= 2){
            printf("Retrieved line %s of length %zu :\n",line, read-1);
        }
        if(addWord(dicInUse->tree,line) == 1){
            dicInUse->nbWord++;
        }else{
            wordIgnored++;
        }
    }
    if(DEBUG >= 1){
        printf("word added = %d ignored = %d\n",dicInUse->nbWord,wordIgnored );
    }
    fclose(inputFile);
    if (line){
        free(line);
    }
    return EXIT_SUCCESS;
}
// -------------------------- Utils functions's  --------------------------

// Function used to prompt something to user
// @param prmpt : store the message to print on screen
// @param buff : store the user input
// @param sz : maximum size of input 
// @return 0 if input is ok
// @return 1 if input is empty
// @return 2 if input is too long
int userInput (char *prmpt, char *buff, size_t sz) {
    int ch, extra;

    // Get line with buffer overrun protection.
    if (prmpt != NULL) {
        printf ("%s", prmpt);
        fflush (stdout);
    }

    fgets(buff, sz, stdin);

    if(*buff == '\n'){
        return NO_INPUT;
    }
    // If it was too long, there'll be no newline. In that case, we flush
    // to end of line so that excess doesn't affect the next call.
    if (buff[strlen(buff)-1] != '\n') {
        extra = 0;
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = 1;
        return (extra == 1) ? TOO_LONG : OK;
    }
    // Otherwise remove newline and give string back to caller.
    buff[strlen(buff)-1] = '\0';
    return OK;
}
// Function used to prompt numeric value to user (call userInput)
// @param prmpt : store the message to print on screen
// @param buff : store the user input
// @param sz : maximum size of input 
// @param lowLimit : numerical values under it won't be accepted
// @param highLimit : numerical values upper it won't be accepted
// @return 0 if input is ok
// @return 1 if input is empty
// @return 2 if input is too long
// @return -1 if input is out of bound
int numericUserInput(char* prmpt, char* buff, size_t sz,short lowLimit,short highLimit){

    if( userInput(prmpt,buff,sz) == 0 ){
        short nbDigit=0;
        short i=0,j=0;

        while( buff[i]-48 >= 0 && buff[i]-48 <= 9 ){
            nbDigit++;   
            i++;
        }
        int returnValue = 0;
        for(i=nbDigit-1;i>=0;i--){
            returnValue+=(buff[i]-48)*pow(10,j);
            j++;
        }
        if(returnValue >= lowLimit && returnValue <= highLimit){
            return returnValue;
        }else{
            return -1;
        }
    }else{
        return -1;
    }
}
// What does the function is obvious
void printMenu(dictionary* dicInUse){
    if(dicInUse->name){
        printf("---------- Vous utilisez maintenant le dictionnaire %s ----------\n",dicInUse->name);
    }
    printf("1) Créer un fichier dictionnaire\n");
    printf("2) Utiliser un dictionnaire existant\n");
    printf("3) Fabriquer un dictionnaire à partir d'un fichier texte\n");
    printf("4) Détruire un fichier dictionnaire\n");
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
// @param dicInUse : pointer on dicInUse
// @return 1 if dictionary contain a dictionary
// @return 0 if dictionary in use is empty
int isDictionaryInUse(dictionary* dicInUse){
    if(dicInUse->tree->endOfWord == -1){
        return 1;
    }else{
        return 0;
    }
}
// @param dicInUse : pointer on dicInUse
// @return 1 if library contain a dictionary
// @return 0 if library in use is empty
int isDictionaryInMemory(dictionary* library){
    if(library->tree == NULL){
        return 0;
    }else{
        return 1;
    }
}
// @return the time of the day in milliseconds
unsigned long getTime(){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    unsigned long millisec;
    return millisec = (tv.tv_usec / 1000)+(tv.tv_sec * 1000) ;
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
        if(isDicInMem){
            isDicInUse = isDictionaryInUse(dicInUse);
        }
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
                exit(0);
            break;
            case 8:
               if(dicInUse != NULL){
                    unsigned long int startMeasuringTime;
                    unsigned long int finishMeasuringTime;

                    printf("---------- TEST ----------\n");
                    char* word = calloc(sizeof(char)*255,1);


                    printf("Dictionary %s :\n", dicInUse->name);

                    startMeasuringTime = getTime();
                    getAllWordInDictionary(dicInUse->tree,word,0);
                    finishMeasuringTime = getTime();
                    printf("%ld milliseconds to access all dictionary's word\n",(finishMeasuringTime-startMeasuringTime) );
                    
                    printf("Searching for a word looking like 'titi' \n");
                    startMeasuringTime = getTime();
                    levensteinInDictionary(dicInUse->tree,word,0,"titi",2,0);
                    finishMeasuringTime = getTime();
                    // printf("nbNodeParcoured=%d\n",nbNodeParcoured );
                    printf("%ld milliseconds to access all dictionary's word and compare the levenstein distance with 'titi'\n",(finishMeasuringTime-startMeasuringTime) );
                }else{
                    printf("Veuillez d'abord charger un dictionnaire\n");
                }
                printMenu(dicInUse);
                while((choice = numericUserInput(">",input,255, 1, 8)) == -1);
            break;
            default:
            break;
        }
    } while(1);
}
// Function executed when program is launched
dictionary* init(){
    map = mmap(0,1L<<32,PROT_WRITE|PROT_READ,MAP_SHARED|MAP_ANONYMOUS,0,0);


    dictionary* library = calloc(sizeof(dictionary),1);
    // dictionary* library = (dictionary*)(map+next);
    // next += sizeof(dictionary);
    return library;
}
// -------------------------- Test functions  --------------------------

// Test function, can be verbose and print debug option 
// 0 -> no output
// 1 -> debug output
void test(int verbose){

    if(verbose){ printf("test getTime() = %ld\n",getTime() ); }
    
    int passed=1;

    node* tree = calloc(sizeof(node),1);

    char* testString = "toto";
    char* testString2 = "tototutu";
    char* testString3 = "camion";
    char* testString4 = "voiture";
    char* testString5 = "chat";
    char* testString6 = "chatte";

    char* unexistantString = "tot";
    char* unexistantString2 = "helloworld";
    char* unexistantString3 = "abcdefghijklmnopqrstuvwxyz";

    // TESTING ADDING WORD
    addWord(tree,testString);
    addWord(tree,testString2);
    addWord(tree,testString3);
    addWord(tree,testString4);
    addWord(tree,testString5);
    addWord(tree,testString6);

    if(verbose){
        printf("searchWord(tree,testString)=%d (expected:1)\n",searchWord(tree,testString) );
        printf("searchWord(tree,testString2)=%d (expected:1)\n",searchWord(tree,testString2) );
        printf("searchWord(tree,testString3)=%d (expected:1)\n",searchWord(tree,testString3) );
        printf("searchWord(tree,testString4)=%d (expected:1)\n",searchWord(tree,testString4) );
        printf("searchWord(tree,testString5)=%d (expected:1)\n",searchWord(tree,testString5) );
        printf("searchWord(tree,testString6)=%d (expected:1)\n",searchWord(tree,testString6) );
        printf("searchWord(tree,unexistantString)=%d (expected:0)\n",searchWord(tree,unexistantString) );
        printf("searchWord(tree,unexistantString2)=%d (expected:0)\n",searchWord(tree,unexistantString2) );
        printf("searchWord(tree,unexistantString3)=%d (expected:0)\n",searchWord(tree,unexistantString3) );

    }
    if(searchWord(tree,testString) != 1 || searchWord(tree,testString2) != 1 || searchWord(tree,testString3) != 1 || searchWord(tree,testString4) != 1 || searchWord(tree,testString5) != 1 || searchWord(tree,testString6) != 1){
        passed = 0 ;
    }
    if(searchWord(tree,unexistantString) != 0 || searchWord(tree,unexistantString) != 0 || searchWord(tree,unexistantString) != 0){
        passed = 0 ;
    }


    if(supWord(tree,testString) != 1 || supWord(tree,unexistantString) != 0 || supWord(tree,unexistantString2) != 0){
        passed = 0;
        printf("toto\n");
    }

    if(searchWord(tree,testString) != 0){
        passed = 0;
        printf("tutu\n");
    }

    free(tree);



    dictionary* library = calloc(sizeof(dictionary),1);

    if(verbose){
    	printf("%d (expected 0)\n",isDictionaryInMemory(library));    	
    }
    if(isDictionaryInMemory(library)){
    	passed = 0 ;
    }

	strcpy(library->name , "test");
	strcpy(library->description , "desc");


    library->tree = calloc(sizeof(node),1);
    library->tree->endOfWord = -1; 

	// library->tree->letter[0] = malloc(sizeof(node));
    if(verbose){
    	printf("%d (expected 1)\n",isDictionaryInMemory(library));
    }
    if(!isDictionaryInMemory(library)){
    	passed = 0 ;
    }

    if(verbose){
        char word[25];
        printf("flag2\n");
   
        loadDictionaryFromFile("testDicInFile.dic",library);
        // getAllWordInDictionary(library->tree,word,0);
        levensteinInDictionary(library->tree,word,0,"titi",2,0);
    }



    if(verbose){

        printf("sizeof(node)=%ld\n",sizeof(node) );



        if(passed){
            printf("All tests passed.\n");
        }else{
            printf("Some tests didn't passed\n");
        }
    }
}