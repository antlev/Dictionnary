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
#include <time.h>

#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

// int const EXIT_FAILURE = -1;


// map = mmap(0, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED,MAP_ANONYMOUS fd, 0);

// Prototypes
// -------------------------- Inside Dictionnary functions --------------------------
void addWord(node* tree,char* wordToAdd);
int searchWord(node* tree,char* wordToSearch);
int supWord(node* tree,char* wordToSup);

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
clock_t getTime();

void printMenu(dictionnary* dicInUse);
void printLibrary(dictionnary* library, int numberOfDic);

int isDictionnaryInUse(dictionnary* dictionnary);
int isDictionnaryInMemory(dictionnary* dictionnary);

void menu(dictionnary* library);
dictionnary* init();
// -------------------------- Test function  --------------------------
void test(int verbose);

// -------------------------- Inside Dictionnary functions --------------------------

// Add the wordToAdd into the tree 'tree'
void addWord(node* tree,char* wordToAdd){
    int i=0;
    while(wordToAdd[i] != '\0'){
        if(!tree->letter[wordToAdd[i] - 97]){
            // calloc same as malloc but initialise all bit at 0
            tree->letter[wordToAdd[i] - 97] = calloc(sizeof(node),1);
        }
        tree = tree->letter[wordToAdd[i] - 97] ;
        i++;
    }
    tree->endOfWord = 1 ;
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
        }
        return 1;   
    }
}
// Prompt a word and add it to the dictionnary
void addWordMenu(dictionnary* dictionnary){
    node* tree = dictionnary->tree;
    char wordToInsert[30];
    
    while(userInput("Veuillez entrer le mot à insérer dans le dictionnaire\n>",wordToInsert,30) != 0);
    
    printf("wordToInsert >%s<\n",wordToInsert );

    addWord(tree,wordToInsert);
    dictionnary->nbWord++;
}
// Prompt a word and search it to the dictionnary
void searchWordMenu(dictionnary* dictionnary){
    node* tree = dictionnary->tree;
    char wordToSearch[255];

    while(userInput("Veuillez entrer le mot à chercher dans le dictionnaire\n>",wordToSearch,30) != 0);

    if(searchWord(tree,wordToSearch)){
        printf("Le mot %s est bien contenu dans le dictionnaire\n",wordToSearch );
    }else{
        printf("Le mot %s n'est pas contenu dans le dictionnaire\n",wordToSearch );
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
    int dicToDel=0;
    printLibrary(library,numberOfDic);

    printf("Quel dictionnaire voulez vous supprimer ?\n");
    do{
        scanf("%d%*c",&dicToDel);
    } while(dicToDel > numberOfDic || dicToDel <= 0);

    // eraseDic(library,dicToDel);
}
// Prompt a file path and call loadDictionnaryFromFile passing it the dicInUse
void buildDicWithFileMenu(dictionnary** library,int* numberOfDic,dictionnary** dicInUse){
    char pathToDicFile[255];
    char input[2];

    if(*numberOfDic == 0){
        while(userInput("Vous n'avez pas de dictionnaire en mémoire voulez vous en créer un ? (O/N)\n>",input,sizeof(char)*2) != 0);
        if(input[0] == 'O' || input[0] == 'o'){
            addDicMenu(library,*numberOfDic,dicInUse);
            (*numberOfDic)++;
        }else{
            return;
        }
    } else {
        do{
            while(userInput("Voulez vous (C)réer un nouveau dictionnaire ou (A)jouter le fichier à un dictionnaire existant ?\n>",input,sizeof(char)*2) != 0);
        }
        while(input[0] != 'a' && input[0] != 'A' && input[0] != 'c' && input[0] != 'C');

        if(input[0] == 'a' || input[0] == 'A'){
            chooseDicMenu(*library,*numberOfDic,dicInUse);
        }else{
            addDicMenu(library,*numberOfDic,dicInUse);
            (*numberOfDic)++;
        }
    }
    
    while(userInput("Veuillez entrer le chemin du fichier dictionnaire\n>",pathToDicFile,sizeof(char)*255) != 0);
    
    long int startMeasuringTime = getTime();
    long int finishMeasuringTime;
    if(loadDictionnaryFromFile(pathToDicFile,*dicInUse) == -1){
        printf("file \'%s\' does not exist\n",pathToDicFile );
    }else{
        printf("\n");
    }
    finishMeasuringTime = getTime();
    printf("Dictionnary import time = %ld\n",finishMeasuringTime-startMeasuringTime );
}
// Print the library and ask user to choose a dictionnary
// The choosen dictionnary will be pointed by dicInUse
void chooseDicMenu(dictionnary* library,int numberOfDic,dictionnary** dicInUse){
    int dicToUse=0;
    int i;
    *dicInUse = library;

    printLibrary(library,numberOfDic);
    printf("Veuillez entrer le numéro du dictionnaire que vous voulez utiliser ?\n>");
    do{
        scanf("%d%*c",&dicToUse);
    } while(dicToUse > numberOfDic || dicToUse <= 0);
    *dicInUse += dicToUse-1;
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
        printf("Retrieved line of length %zu :\n", read-1);
        line[strlen(line)-1] = '\0';

        printf(">%s<", line);

        addWord(dicInUse->tree,line);
        dicInUse->nbWord++;
        printf("word >%s< has been inserted in dictionnary >%s<\n",line,dicInUse->name );
    }
    fclose(inputFile);
    if (line){
        free(line);
    }
    return EXIT_SUCCESS;
}
void askForDicInfo(char* dicName,char* dicDesc){

    while(userInput("Choisissez un nom de dictionnaire\n>",dicName,255*sizeof(char)) != 0);

    while(userInput("Vous pouvez donner une description\n>",dicDesc,255*sizeof(char)) > 1);

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

    fgets (buff, sz, stdin);

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
    printf("7) Quitter l'application\n>");    
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
clock_t getTime(){
    clock_t uptime = clock() / (1000000 / 1000);
    return uptime;
}
// -------------------------- Programm Menu  --------------------------
void menu(dictionnary* library){
    int choice;
    int isDicInMem=0;
    int isDicInUse=0;
    int numberOfDic = 0;
    dictionnary* dicInUse = NULL;

    printMenu(dicInUse);
    scanf("%d%*c",&choice);
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
                scanf("%d%*c",&choice);
            break;
            case 2:
                if(isDicInMem){
                 	chooseDicMenu(library,numberOfDic,&dicInUse);
                }else{
                    printf("Veuillez d'abord créer ou charger un dictionnaire\n");                
                }                
                printMenu(dicInUse);
                scanf("%d%*c",&choice);
            break;
            case 3:
                buildDicWithFileMenu(&library,&numberOfDic,&dicInUse);
                printMenu(dicInUse);
                scanf("%d%*c",&choice);
            break;
            case 4:
                if(isDicInMem){
                    eraseDicMenu(library,numberOfDic,&dicInUse);
                }else{
                    printf("Veuillez d'abord créer un dictionnaire\n");                
                }
                printMenu(dicInUse);
                scanf("%d%*c",&choice);
            break;
            case 5:
                if(dicInUse != NULL){
                    addWordMenu(dicInUse);
                }else{
                    printf("Veuillez d'abord charger un dictionnaire\n");
                }
                printMenu(dicInUse);
                scanf("%d%*c",&choice);
            break;
            case 6:
                if(dicInUse != NULL){
                    searchWordMenu(dicInUse);
                }else{
                    printf("Veuillez d'abord charger un dictionnaire\n");
                }
                printMenu(dicInUse);
                scanf("%d%*c",&choice);
            break;
            case 7:
                printf("Au-revoir\n");
                free(library);
                exit(0);
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

	library->tree = malloc(sizeof(node));

	library->tree->letter[0] = malloc(sizeof(node));
    if(verbose){
    	printf("%d (expected 1)\n",isDictionnaryInMemory(library));
    }
    if(!isDictionnaryInMemory(library)){
    	passed = 0 ;
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