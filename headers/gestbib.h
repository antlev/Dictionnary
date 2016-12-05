// Structs
//----------------------------------------------------------------------------------------
typedef struct __attribute__((__packed__)) node{
    short endOfWord;
    unsigned int letter[26];
}node;

typedef struct dictionary{
    char name[255];
    char description[255];
    unsigned int nbWord;
    unsigned int tree;
}dictionary;

// Prototypes
//----------------------------------------------------------------------------------------
// -------------------------- Inside Dictionary functions --------------------------
int addWord(unsigned int tree,char* wordToAdd);
int searchWord(unsigned int tree,char* wordToSearch);
// int supWord(unsigned int tree,char* wordToSup);
int sanitiseWordForDictionary(char* word);
// unsigned int getAllWordInDictionary(unsigned int tree,char* word,short level);
// unsigned int levensteinInDictionary(unsigned int tree,char* word,short level,char* wordToCompare,short threshold,short diff);
// -------------------------- User Interface --------------------------
void addWordMenu(dictionary* dictionary);
void searchWordMenu(dictionary* dictionary);
void buildDicWithFileMenu(dictionary** library,int* numberOfDic,dictionary** dicInUse);
void chooseDicMenu(dictionary* library,int numberOfDic,dictionary** dicInUse);
void addDicMenu(dictionary** library,int numberOfDic,dictionary** dicInUse);
void eraseDicMenu(dictionary* library,int numberOfDic,dictionary** dicInUse);
// -------------------------- Dictionary manipulation functions --------------------------
void eraseDic(dictionary* library,int dicToDel);
void addDicAndUse(dictionary** library,int numberOfDic,char name[255],char desc[255],dictionary** dicCreated);
// -------------------------- Utils functions's  --------------------------
int loadDictionaryFromFile(char pathToDicFile[255],dictionary* dicInUse);
void printMenu(dictionary* dicInUse);
void printLibrary(dictionary* library, int numberOfDic);
int isDictionaryInUse(dictionary* dictionary);
int isDictionaryInMemory(dictionary* dictionary);
void menu(dictionary* library);
dictionary* init();
// -------------------------- Test function  --------------------------
void test(int verbose);