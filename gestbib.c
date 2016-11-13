// Structs
typedef struct node{
    int endOfWord;
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

// Prototypes
// -------------------------- Inside Dictionnary functions --------------------------
void addWord(node* tree,char* wordToAdd);
int searchWord(node* tree,char* wordToSearch);
int supWord(node* tree,char* wordToSup);

void addWordMenu(dictionnary* dictionnary);
void searchWordMenu(dictionnary* dictionnary);
// -------------------------- Programm functions's menu  --------------------------
void buildDicWithFileMenu(dictionnary* dicInUse);
void chooseDicMenu(dictionnary* library,int numberOfDic,dictionnary** dicInUse);
void addDicMenu(dictionnary** library,int numberOfDic,dictionnary** dicInUse);
void eraseDicMenu(dictionnary* library,int numberOfDic,dictionnary** dicInUse);

// -------------------------- Dictionnary manipulation functions --------------------------
void eraseDic(dictionnary* library,int dicToDel);
// void addDic();
void askForDicInfo(char** dicName,char** description);

// -------------------------- Utils functions's  --------------------------
int loadDictionnaryFromFile(char pathToDicFile[255],dictionnary* dicInUse);
int fileExist (char *filename);

void printMenu();
void printLibrary(dictionnary* library, int numberOfDic);

int isDicInUse(dictionnary* dicInUse);
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
        // printf("flag wordToAdd[i]=%d | i=%d | corresponding to letter : %c | node* = %p\n",wordToAdd[i],i,wordToAdd[i],tree);
        if(!tree->letter[wordToAdd[i] - 97]){
            // printf("%p doesn't exist\n",tree->letter[wordToAdd[i] - 97] );
            // calloc same as malloc but initialise all bit at 0
            tree->letter[wordToAdd[i] - 97] = calloc(sizeof(node),1);
            // printf("allocating memory : %p\n", tree->letter[wordToAdd[i] - 97]);
        }
        // printf("passing from node* %p to node* %p\n",tree,tree->letter[wordToAdd[i] - 97] );
        tree = tree->letter[wordToAdd[i] - 97] ;
        i++;
    }
    tree->endOfWord = 1 ;
}
// Return 1 if word exist in tree, 0 if not
int searchWord(node* tree,char* wordToSearch){
    int i=0;
    while(wordToSearch[i] != '\0'){

        // printf("flag wordToSearch[i]=%d | i=%d | corresponding to letter : %c | node* = %p nextNode* = %p\n",wordToSearch[i],i,wordToSearch[i],tree,tree->letter[wordToSearch[i] - 97]);
        if(!tree->letter[wordToSearch[i] - 97]){
            return 0;
        }

        // printf("passing from node* >%p< to node* >%p<\n",tree,tree->letter[wordToSearch[i] - 97] );
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
            tree = &tree->letter[i];
            free(tree->letter[i]);
        }
        return 1;   
    }
}

// Prompt a word and add it to the dictionnary
void addWordMenu(dictionnary* dictionnary){
    node* tree = dictionnary->tree;
    char wordToInsert[255];
    printf("Veuillez entrer le mot à insérer dans le dictionnaire\n>");
    fgets(wordToInsert,254,stdin); // en attendant le flush()
    
    fgets(wordToInsert,254,stdin);

    wordToInsert[strlen(wordToInsert)-1] = '\0';

    printf("wordToInsert=>%s<\n",wordToInsert );

    addWord(tree,wordToInsert);
    dictionnary->nbWord++;
}
// Prompt a word and search it to the dictionnary
void searchWordMenu(dictionnary* dictionnary){
    node* tree = dictionnary->tree;
    char wordToSearch[255];
    printf("Veuillez entrer le mot à chercher dans le dictionnaire\n>");
    fgets(wordToSearch,254,stdin); // en attendant le flush()
    fgets(wordToSearch,254,stdin);

    wordToSearch[strlen(wordToSearch)-1] = '\0';

    printf("wordToSearch=>%s<\n",wordToSearch );

    if(searchWord(tree,wordToSearch)){
        printf("Le mot %s est bien contenu dans le dictionnaire\n",wordToSearch );
    }else{
        printf("Le mot %s n'est pas contenu dans le dictionnaire\n",wordToSearch );
    }
}

// -------------------------- Programm functions's menu  --------------------------

// Prompt user for a name and description and add a new dictionnnary to the library
void addDicMenu(dictionnary** library,int numberOfDic,dictionnary** dicInUse){
    printf("enter in addDicMenu\n");
    int i;
    char dicName[255] = "";
    char description[255] = "";
    // char* dicName;
    // char* description;

    printf("numberOfDic >%d<\n",numberOfDic );
    printf("*library >%p<\n",*library );

    if(numberOfDic){
        *library = realloc(*library,(numberOfDic+1)*sizeof(dictionnary));
        memset(*library+numberOfDic,0,sizeof(dictionnary));
    }
    *dicInUse = *library;

    // check input is under 256 char
    printf("Veuillez donner un nom au dictionnaire\n>");

    fgets(dicName,254,stdin); // en attendant de flush
    fgets(dicName,254,stdin);
    dicName[strlen(dicName)-1] = '\0';

    printf("dicName=>%s<\n",dicName );
    printf("Vous pouvez donner une description\n>");
    // TODO check user input
    fgets(description,254,stdin);
    description[strlen(description)-1] = '\0';
    
    printf("desc=>%s<\n",description );
    // //TODO
    // askForDicInfo(&dicName,&description);

    printf("*dicInUse->tree = %p\n",(*dicInUse)->tree);
    (*dicInUse)+=numberOfDic;    

    printf("titi\n");
    strcpy((*dicInUse)->name,dicName);
    strcpy((*dicInUse)->description,description);
    (*dicInUse)->nbWord=0;

    (*dicInUse)->tree = calloc(sizeof(node),1);
    (*dicInUse)->tree->endOfWord = -1;
    // insertDicInLibrary((*dicInUse));
    printf("Vous utilisez maintenant le dictionnaire %s |\n",(*dicInUse)->name);
}
// Ask for dic to erase and call eraseDic
void eraseDicMenu(dictionnary* library,int numberOfDic,dictionnary** dicInUse){
    int dicToDel=0;
    printLibrary(library,numberOfDic);
    printf("Quel dicionnaire voulez vous supprimer ?\n");

    do{
        scanf("%d",&dicToDel);
    } while(dicToDel > numberOfDic || dicToDel <= 0);
    // eraseDic(library,dicToDel);

}

// Prompt a file path and call loadDictionnaryFromFile passing it the dicInUse
void buildDicWithFileMenu(dictionnary* dicInUse){
    char pathToDicFile[255];
    printf("Veuillez entrer le chemin du fichier dictionnaire\n>");
    
    fgets(pathToDicFile,254,stdin); // en attendant le flush()
    fgets(pathToDicFile,254,stdin);
    pathToDicFile[strlen(pathToDicFile)-1] = '\0';   

    loadDictionnaryFromFile(pathToDicFile,dicInUse);
    printf("\n");
}

// Print the library and ask user to choose a dictionnary
// The choosen dictionnary will be pointed by dicInUse
void chooseDicMenu(dictionnary* library,int numberOfDic,dictionnary** dicInUse){
    int dicToUse=0;
    int i;
    *dicInUse = library;

    printf("Dictionnaire en mémoire:\n");
    printLibrary(library,numberOfDic);
    printf("*dicInUse = %p\n",*dicInUse );
    printf("Veuillez entrer le numéro du dictionnaire que vous voulez utiliser ?\n");
    do{
        scanf("%d",&dicToUse);
    } while(dicToUse > numberOfDic || dicToUse <= 0);

    *dicInUse += dicToUse-1;

    printf("Vous utilisez maintenant le dictionnaire %s\n",(*dicInUse)->name );
}
// -------------------------- Dictionnary manipulation functions --------------------------
// void addDic(){
// }
// void useDic(dictionnary* library,int numberOfDicToUse,dictionnary** dicInUse){
//     int i;
//     *dicInUse = library;
//     for (i = 0; i < numberOfDicToUse; ++i){
//         *dicInUse++;
//     }
// }
void eraseDic(dictionnary* library,int numberOfDicToDel){

    dictionnnary* dicToDel = library;
    dicToDel+=numberOfDicToDel;
    

}

// Read the file passed as 1st parameter and enter each line as a word in dicInUse
int loadDictionnaryFromFile(char pathToDicFile[255],dictionnary* dicInUse){
   
    FILE * inputFile;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    inputFile = fopen(pathToDicFile, "r");
    if (inputFile == NULL)
        return EXIT_FAILURE;

    while ((read = getline(&line, &len, inputFile)) != -1) {
        printf("Retrieved line of length %zu :\n", read);
        printf("%s", line);
        line[strlen(line)-1] = '\0';
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
void askForDicInfo(char** dicName,char** description){
    printf("Choisissez un nom de dictionnaire\n");
    // check input is under 256 char

    fgets(*dicName,254,stdin); // en attendant de flush
    fgets(*dicName,254,stdin);
    *dicName[strlen(*dicName)-1] = '\0';

    printf("*dicName=>%s<\n",*dicName );
    printf("Vous pouvez donner une description\n");
    // TODO check user input
    fgets(*description,254,stdin);
    *description[strlen(*description)-1] = '\0';
    
    printf("desc=>%s<\n",*description );

}
// -------------------------- Utils functions's  --------------------------

// TO TEST return 1 if file exist else return 0
int fileExist (char *filename)
{
    FILE *file;
    if((fopen(filename,"r"))!=NULL){
        fclose(file);
        return 1;
    }else{
        return 0;
    }
}
// What does the function is obvious
void printMenu(){
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

        printf("pointeur dictionnary n°%d >%p<\n",count+1,dictionnary);
        if(dictionnary->description){
            printf("desc : >%s<\n",dictionnary->description );
        }
        printf("Nombre de mots contenu dans le dictionnaire : %d\n",dictionnary->nbWord );
        dictionnary++;
        count++;
        printf("---------------------------------------\n");
    }

}
// Return 0 if dicInUse point on NULL, else return 1
int isDicInUse(dictionnary* dicInUse){
    if(dicInUse == NULL){
        return 0;
    }else{
        return 1;
    }
}
// Return 1 if dictionnary contain a dictionnary
int isDictionnaryInUse(dictionnary* dictionnary){
    printf("entering isDictionnaryInUse -> dictionnary >%p< dictionnary->name=%s\n",dictionnary,dictionnary->name );
    if(dictionnary->tree->endOfWord == -1){
        return 1;
    }else{
        return 0;
    }
}

// Return 0 if dictionnary is empty, else return 1
int isDictionnaryInMemory(dictionnary* dictionnary){
    printf("entering isDictionnaryInMemory -> dictionnary >%p< dictionnary->name=%s\n",dictionnary,dictionnary->name );
    if(dictionnary->tree == NULL){
        return 0;
    }else{
        return 1;
    }
}

// -------------------------- Programm Menu  --------------------------
void menu(dictionnary* library){
    int choice;
    int isDicInMem=0;
    int isDicInUse=0;
    int numberOfDic = 0;
    dictionnary* dicInUse = NULL;

    printMenu();
    scanf("%d",&choice);
    do{
        isDicInMem = isDictionnaryInMemory(library);
        printf("isDicInMem = %d\n",isDicInMem);
        if(isDicInMem){
	        isDicInUse = isDictionnaryInUse(dicInUse);
        	printf("isDicInUse = %d\n",isDicInUse);
        }

        printf("flag isDicInMem=%d\n",isDicInMem );
        switch(choice){
            case 1:
            	printf("flaggggg library = %p\n",library );
                addDicMenu(&library,numberOfDic,&dicInUse);
                numberOfDic++;
                printMenu();
                scanf("%d",&choice);
            break;
            case 2:
                if(isDicInMem){
                 	chooseDicMenu(library,numberOfDic,&dicInUse);
                }else{
                    printf("Veuillez d'abord créer ou charger un dictionnaire\n");                
                }                
                printMenu();
                scanf("%d",&choice);
            break;
            case 3:
                buildDicWithFileMenu(dicInUse);
                printMenu();
                scanf("%d",&choice);
            break;
            case 4:
                if(isDicInMem){
                    eraseDicMenu(library,numberOfDic,&dicInUse);
                }else{
                    printf("Veuillez d'abord créer un dictionnaire\n");                
                }
                printMenu();
                scanf("%d",&choice);
            break;
            case 5:
                if(dicInUse != NULL){
                    addWordMenu(dicInUse);
                }else{
                    printf("Veuillez d'abord charger un dictionnaire\n");
                }
                printMenu();
                scanf("%d",&choice);
            break;
            case 6:
                if(dicInUse != NULL){
                    searchWordMenu(dicInUse);
                }else{
                    printf("Veuillez d'abord charger un dictionnaire\n");
                }
                printMenu();
                scanf("%d",&choice);
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


    if(passed){
        printf("All tests passed.\n");
    }else{
        printf("Some tests didn't passed\n");
    }
}