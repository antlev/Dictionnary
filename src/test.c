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