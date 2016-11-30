// Structs
typedef struct __attribute__((__packed__)) node{
    short endOfWord;
    struct node* letter[26];
}node;

typedef struct dictionnary{
    char name[255];
    char description[255];
    int nbWord;
    node* tree;
}dictionnary;

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/time.h>

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

// Prototypes
// -------------------------- Inside Dictionnary functions --------------------------
int addWord(node* tree,char* wordToAdd);
int searchWord(node* tree,char* wordToSearch);
int supWord(node* tree,char* wordToSup);
node* getAllWordInDictionnary(node* tree,char* word,short level);
node* levensteinInDictionnary(node* tree,char* word,short level,char* wordToCompare,short threshold,short diff);

void addWordMenu(dictionnary* dictionnary);
void searchWordMenu(dictionnary* dictionnary);
// -------------------------- Programm functions's menu  --------------------------
void buildDicWithFileMenu(dictionnary** library,int* numberOfDic,dictionnary** dicInUse);
void chooseDicMenu(dictionnary* library,int numberOfDic,dictionnary** dicInUse);
void addDicMenu(dictionnary** library,int numberOfDic,dictionnary** dicInUse);
void eraseDicMenu(dictionnary* library,int numberOfDic,dictionnary** dicInUse);

// -------------------------- Dictionnary manipulation functions --------------------------
void eraseDic(dictionnary* library,int dicToDel);
void askForDicInfo(char* dicName,char* description);
void addDicAndUse(dictionnary** library,int numberOfDic,char name[255],char desc[255],dictionnary** dicCreated);
// -------------------------- Utils functions's  --------------------------
int loadDictionnaryFromFile(char pathToDicFile[255],dictionnary* dicInUse);
int userInput(char *prmpt, char *buff, size_t sz);
int numericUserInput(char* prmpt, char* buff, size_t sz,short lowLimit,short highLimit);
unsigned long getTime();

void printMenu(dictionnary* dicInUse);
void printLibrary(dictionnary* library, int numberOfDic);

int isDictionnaryInUse(dictionnary* dictionnary);
int isDictionnaryInMemory(dictionnary* dictionnary);

void menu(dictionnary* library);
dictionnary* init();
// -------------------------- Test function  --------------------------
void test(int verbose);

// -------------------------- Inside Dictionnary functions --------------------------

// Add the 'wordToAdd' into the tree 'tree'
// Return 1 if the word has been successfully added and O if word is already in tree
int addWord(node* tree,char* wordToAdd){
    int i=0;
    while(wordToAdd[i] != '\0'){
        if(!tree->letter[wordToAdd[i] - 97]){
            // calloc same as malloc but initialise all bit at 0
            tree->letter[wordToAdd[i] - 97] = calloc(sizeof(node),1);
        }
        tree = tree->letter[wordToAdd[i] - 97] ;
        i++;
    }
    if (tree->endOfWord == 1){
        return 0;
    }else{
        tree->endOfWord = 1 ;
        return 1;
    }
}
// Return 1 if word exist in tree, 0 if not
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
// Suppress the wordToSup into the tree tree
// Return 1 if the word has been founnd and suppresed, else return 0
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
// Search recursivly in the dictionnary and print
// on screen all word contained in the dictionnary
node* getAllWordInDictionnary(node* tree,char* word,short level){
    int i=0;

    if(tree->endOfWord == 1){
        // printf("DEBUG>>End of word!!\n");
        while(word[i] != '\0'){
            if(DEBUG){
                printf("%c",word[i] );
            }
            i++;
        }
        if(DEBUG){
            printf("\n");
        }
        // printf(" has been found in dictionnary\n");
    }
    node* res = NULL;
    for (i = 0; i < 26; ++i){
        if(tree->letter[i] != NULL){        
            // printf("DEBUG>>>letter %c spotted ! \n",i+97);
            word[level] = i+97;
            res = getAllWordInDictionnary(tree->letter[i],word,level+1);
            word[level] = '\0';
        }
    }
    return res;
 }

int nbNodeParcoured = 0;
// Search recursivly in the dictionnary for word that have a levenstein distance smaller than threshold and print them on screen
node* levensteinInDictionnary(node* tree,char* word,short level,char* wordToCompare,short threshold,short diff){
    nbNodeParcoured++;
    int i=0;
    int distance;

    if(tree->endOfWord == 1){
        // printf("DEBUG>>End of word!!\n");
        if(DEBUG){
            if((distance = DamerauLevenshteinDistance(word,wordToCompare)) <= threshold){
                printf("word >%s< has a levenstein difference of %d with >%s<\n",word,distance,wordToCompare);
            }else{
                 printf("word >%s< has a" " levenstein difference of %d with >%s<\n",word,distance,wordToCompare);
            }
        }
    }
    node* res = NULL;
    for (i = 0; i < 26; ++i){

        if(tree->letter[i] != NULL){        
            // printf("DEBUG>>>letter %c spotted ! \n",i+97);
            
            // if(strchr(wordToCompare,i+97) == NULL){
            //     if(diff >= threshold){
            //         continue;
            //    }
            //    diff++;
            // }


            word[level] = i+97;
            res = levensteinInDictionnary(tree->letter[i],word,level+1,wordToCompare,threshold,diff);
            word[level] = '\0';

        }
    }
    return res;

}
// Prompt a word and add it to the dictionnary
void addWordMenu(dictionnary* dictionnary){
    node* tree = dictionnary->tree;
    char wordToInsert[MAXNBLETTERINWORD];    
    while(userInput("Veuillez entrer le mot à insérer dans le dictionnaire\n>",wordToInsert,MAXNBLETTERINWORD) != 0);
    
    if(addWord(tree,wordToInsert)){
        printf("%s has been successfully added to the dictionnary\n",wordToInsert );
        dictionnary->nbWord++;
    }else{
        printf("%s already exist in dictionnary\n",wordToInsert);
    }
}
// Prompt a word and search it in the dictionnary
void searchWordMenu(dictionnary* dictionnary){
    node* tree = dictionnary->tree;
    char wordToSearch[MAXNBLETTERINWORD];

    while(userInput("Veuillez entrer le mot à chercher dans le dictionnaire\n>",wordToSearch,MAXNBLETTERINWORD) != 0);

    if(searchWord(tree,wordToSearch)){
        printf("Le mot \'%s\' EST BIEN CONTENU dans le dictionnaire %s\n",wordToSearch,dictionnary->name );
    }else{
        printf("Le mot \'%s\' N'EST PAS CONTENU dans le dictionnaire %s\n",wordToSearch,dictionnary->name );
    }
}
// -------------------------- Programm functions's menu  --------------------------

// Prompt user for a name and description and add a new dictionnnary to the library
void addDicMenu(dictionnary** library,int numberOfDic,dictionnary** dicInUse){
    int i;
    char dicName[255] = "";
    char dicDesc[255] = "";
 
    char* pdicName = dicName;

    askForDicInfo(dicName,dicDesc);

    addDicAndUse(library,numberOfDic,dicName,dicDesc,dicInUse);
}
// Ask for dic to erase and call eraseDic
void eraseDicMenu(dictionnary* library,int numberOfDic,dictionnary** dicInUse){
    int numOfDicToDel=0;
    char* input = malloc(sizeof(char)*255);
    printLibrary(library,numberOfDic);

    while((numOfDicToDel = numericUserInput("Quel dictionnaire voulez vous supprimer ?\n>",input,4,1,(short)numberOfDic)) == -1);

    // eraseDic(library,numOfDicToDel);
}
// Prompt a file path and call loadDictionnaryFromFile passing it the dicInUse
void buildDicWithFileMenu(dictionnary** library,int* numberOfDic,dictionnary** dicInUse){
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
    
    unsigned long int startMeasuringTime = getTime();
    unsigned long int finishMeasuringTime;
    if(loadDictionnaryFromFile(pathToDicFile,*dicInUse) == -1){
        printf("Le fichier dictionnaire \'%s\' n'éxiste pas\n",pathToDicFile );
    }else{
        printf("\n");
    }
    finishMeasuringTime = getTime();
    printf("DEBUG>>>Dictionnary import time = %ld milliseconds\n",finishMeasuringTime-startMeasuringTime );
}
// Print the library and ask user to choose a dictionnary
// The choosen dictionnary will be pointed by dicInUse
void chooseDicMenu(dictionnary* library,int numberOfDic,dictionnary** dicInUse){
    int numOfDicToUse;
    int i;
    *dicInUse = library; // using first dictionnary of library
    char* input = malloc(sizeof(int));

    printLibrary(library,numberOfDic);
    while((numOfDicToUse = numericUserInput("Veuillez entrer le numéro du dictionnaire que vous voulez utiliser ?\n>",input,4,1,(short)numberOfDic)) == -1);
    
    *dicInUse += numOfDicToUse-1; // using the dictionnary n° numOfDicToUse of library
}
// -------------------------- Dictionnary manipulation functions --------------------------
void addDicAndUse(dictionnary** library,int numberOfDic,char name[255],char desc[255],dictionnary** dicCreated){

    if(numberOfDic){ // if numberOfDic=0, the first dictionnary is already allocated by init()
        *library = realloc(*library,(numberOfDic+1)*sizeof(dictionnary));
        memset(*library+numberOfDic,0,sizeof(dictionnary)); // Setting new space to 0
    }
    *dicCreated = *library;

    (*dicCreated)+=numberOfDic;    

    strcpy((*dicCreated)->name,name);
    strcpy((*dicCreated)->description,desc);
    (*dicCreated)->nbWord=0;
    // (*dicCreated)->tree = mmap(0, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED,MAP_ANONYMOUS fd, 0);

    (*dicCreated)->tree = calloc(sizeof(node),1);
    (*dicCreated)->tree->endOfWord = -1;
}
void eraseDic(dictionnary* library,int numberOfDicToDel){
    // dictionnnary* dicToDel = library;
    // dicToDel+=numberOfDicToDel;
}
// Read the file passed as 1st parameter and enter each line as a word in dicInUse
int loadDictionnaryFromFile(char pathToDicFile[255],dictionnary* dicInUse){   
    FILE * inputFile;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    inputFile = fopen(pathToDicFile, "r");
    if (inputFile == NULL){
        return EXIT_FAILURE;
    }
    while ((read = getline(&line, &len, inputFile)) != -1) {

        line[strlen(line)-1] = '\0';
        if(DEBUG){
            printf("Retrieved line %s of length %zu :\n",line, read-1);
        }
        // If line has a special char ignore the line
        if(strspn(line,"abcdefghijklmnopqrstuvwxyz") != 0){
            printf("trying to add word >%s<\n",line);
            addWord(dicInUse->tree,line);
            dicInUse->nbWord++;
            if(DEBUG){
            printf("word >%s< has been inserted in dictionnary >%s<\n",line,dicInUse->name );
            }
        }else{
            printf("line %s ignored\n",line );
        }


    }
    fclose(inputFile);
    if (line){
        free(line);
    }
    return EXIT_SUCCESS;
}
void askForDicInfo(char* dicName,char* dicDesc){

    while(userInput("Choisissez un nom de dictionnaire\n>",dicName,255) != 0);

    while(userInput("Vous pouvez donner une description\n>",dicDesc,255) > 1);

}
// -------------------------- Utils functions's  --------------------------

// Function used to prompt something to user
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
// call userInput
// return value entered by user, if invalid return -1
// lowLimit = numerical values under it won't be accepted
// highLimit = numerical values upper it won't be accepted
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
void printMenu(dictionnary* dicInUse){
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
void printLibrary(dictionnary* library, int numberOfDic){
    dictionnary* dictionnary = library;
    printf("Bibliothèque :\n");
   	printf("---------------------------------------\n");
    int count=0;
    int i;
	for (i = 0; i < numberOfDic; ++i){
        printf("Dictionnaire n°%d : %s\n",count+1,dictionnary->name);
        if(dictionnary->description[0] != '\n'){
            printf("desc : >%s<\n",dictionnary->description );
        }
        printf("Nombre de mots contenu dans le dictionnaire : %d\n",dictionnary->nbWord );
        dictionnary++;
        count++;
        printf("---------------------------------------\n");
    }
}
// Return 1 if dictionnary contain a dictionnary
int isDictionnaryInUse(dictionnary* dictionnary){
    if(dictionnary->tree->endOfWord == -1){
        return 1;
    }else{
        return 0;
    }
}
// Return 0 if dictionnary is empty, else return 1
int isDictionnaryInMemory(dictionnary* dictionnary){
    if(dictionnary->tree == NULL){
        return 0;
    }else{
        return 1;
    }
}
unsigned long getTime(){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    unsigned long millisec;
    return millisec = (tv.tv_usec / 1000)+(tv.tv_sec * 1000) ;
}
// -------------------------- Programm Menu  --------------------------
void menu(dictionnary* library){
    int choice;
    char* input = malloc(sizeof(char)*255);
    int isDicInMem=0;
    int isDicInUse=0;
    int numberOfDic = 0;
    dictionnary* dicInUse = NULL;

    printMenu(dicInUse);
    
    while((choice = numericUserInput(">",input,255, 1, 8)) == -1);

    do{
        isDicInMem = isDictionnaryInMemory(library);
        if(isDicInMem){
            isDicInUse = isDictionnaryInUse(dicInUse);
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


                    printf("Dictionnary %s :\n", dicInUse->name);

                    startMeasuringTime = getTime();
                    getAllWordInDictionnary(dicInUse->tree,word,0);
                    finishMeasuringTime = getTime();
                    printf("%ld milliseconds to access all dictionnary's word\n",(finishMeasuringTime-startMeasuringTime) );
                    
                    printf("Searching for a word looking like 'titi' \n");
                    startMeasuringTime = getTime();
                    levensteinInDictionnary(dicInUse->tree,word,0,"titi",2,0);
                    finishMeasuringTime = getTime();
                    printf("nbNodeParcoured=%d\n",nbNodeParcoured );
                    printf("%ld milliseconds to access all dictionnary's word and compare the levenstein distance with 'titi'\n",(finishMeasuringTime-startMeasuringTime) );
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
// Function executed when programme is launched
dictionnary* init(){
    dictionnary* library = calloc(sizeof(dictionnary),1);
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



    dictionnary* library = calloc(sizeof(dictionnary),1);

    if(verbose){
    	printf("%d (expected 0)\n",isDictionnaryInMemory(library));    	
    }
    if(isDictionnaryInMemory(library)){
    	passed = 0 ;
    }

	strcpy(library->name , "test");
	strcpy(library->description , "desc");


    library->tree = calloc(sizeof(node),1);
    library->tree->endOfWord = -1; 

	// library->tree->letter[0] = malloc(sizeof(node));
    if(verbose){
    	printf("%d (expected 1)\n",isDictionnaryInMemory(library));
    }
    if(!isDictionnaryInMemory(library)){
    	passed = 0 ;
    }

    if(verbose){
        char word[25];
        printf("flag2\n");
   
        loadDictionnaryFromFile("testDicInFile.dic",library);
        // getAllWordInDictionnary(library->tree,word,0);
        levensteinInDictionnary(library->tree,word,0,"titi",2,0);
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