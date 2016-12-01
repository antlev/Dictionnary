// Structs
typedef struct __attribute__((__packed__)) node{
    short endOfWord;
    struct node* letter[26];
}node;

typedef struct dictionary{
    char name[255];
    char description[255];
    int nbWord;
    node* tree;
}dictionary;


// Prototypes
// -------------------------- Inside Dictionary functions --------------------------
int addWord(node* tree,char* wordToAdd);
int searchWord(node* tree,char* wordToSearch);
int supWord(node* tree,char* wordToSup);
node* getAllWordInDictionary(node* tree,char* word,short level);
node* levensteinInDictionary(node* tree,char* word,short level,char* wordToCompare,short threshold,short diff);
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
int userInput(char *prmpt, char *buff, size_t sz);
int numericUserInput(char* prmpt, char* buff, size_t sz,short lowLimit,short highLimit);
unsigned long getTime();
void printMenu(dictionary* dicInUse);
void printLibrary(dictionary* library, int numberOfDic);
int isDictionaryInUse(dictionary* dictionary);
int isDictionaryInMemory(dictionary* dictionary);
void menu(dictionary* library);
dictionary* init();
// -------------------------- Test function  --------------------------
void test(int verbose);