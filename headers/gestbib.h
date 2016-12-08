#ifndef SETOFLETTERSACCEPTED
    #define SETOFLETTERSACCEPTED (0)
#endif
// Set of letters ; IS0-8859-1
// 0 : a (97) -> z (122)
// 1 : ! (33) -> ~ (126)
// 2 : ! (33) -> � (255)
#if (SETOFLETTERSACCEPTED == 0)
	#define OFFSETASCII ('a')
	#define NBLETTERACCEPTED (('z'-'a')+1)
#elif (SETOFLETTERSACCEPTED == 1)
	#define OFFSETASCII (33)
	#define NBLETTERACCEPTED ((126-33)+1)
#elif (SETOFLETTERSACCEPTED == 2)
	#define OFFSETASCII (33)
	#define NBLETTERACCEPTED ((255-33)+1)
#endif

static const short MAXNBLETTERINWORD = 30;

// Structs
//----------------------------------------------------------------------------------------
// Struct node that compose a tree in which we will store our words
typedef struct __attribute__((__packed__)) node{
    short endOfWord;
    unsigned int letter[NBLETTERACCEPTED];
}node;
// Struct dictionary that  allow to save a name, description, number of word and the root of the tree that save words in dictionary
typedef struct dictionary{
    char name[255];
    char description[255];
    unsigned int nbWord;
    unsigned int tree;
}dictionary;

// Prototypes
//----------------------------------------------------------------------------------------
// -------------------------- Tree manipulation functions --------------------------
// Add the 'wordToAdd' into dictionary
// @param tree : root of the dictionary
// @param wordToAdd : word to add in the dictionary
// @return 0 if the wordToAdd has been successfully added 
// @return 1 if wordToAdd is already in tree
// @return -1 if wordToAdd is empty
// @return -2 if wordToAdd is uncompatible with dictionnary
int addWord(unsigned int tree,char* wordToAdd);
// Search wordToSearch into the given tree
// @param tree : root of the dictionary
// @param wordToSearch : word to search in the dictionary
// @return 1 if wordToSearch exist in dictionary
// @return 0 if word doesn't exist in dictionnary
// @return -2 if wordToSearch is uncompatible with dictionnary
// @return -1 if wordToSearch is empty
int searchWord(unsigned int tree,char* wordToSearch);

// Suppress wordToSup into the given tree
// @param tree : root of the dictionary
// @param wordToSup : word to erase from the dictionary
// @return 1 if wordToSup has been found and suppresed, 0 if not
// int supWord(unsigned int tree,char* wordToSup);

// Sanitise word for dictionary
// @return 0 if word is compatible with dictionnary
// @return -1 if word is empty
// @return -2 if word is incompatible with dictionnary
// @param word : String containing word to sanitise
int sanitiseWordForDictionary(char* word);
// -------------------------- User Interface --------------------------
// Prompt a word and call addWord() to add it to the dictionary
// @param dictionary : pointer on dictionary in which we want to add a word
void addWordMenu(dictionary* dictionary);
// Prompt a word and call searchWord() to search it to the dictionary
// @param dictionary : pointer on dictionary in which we want to search a word
void searchWordMenu(dictionary* dictionary);
// Print the library and ask user to choose a dictionary
// The choosen dictionary will be pointed by dicInUse
// @param library : pointer on library
// @param numberOfDic : Total number of dictionary in memory
// @param dicInUse : pointer on dictionary in use
void chooseDicMenu(dictionary* library,int numberOfDic,dictionary** dicInUse);
// Prompt user for a name and description and add a new dictionnnary to the library
// @param library : pointer on library
// @param numberOfDic : Total number of dictionary in memory
// @param dicInUse : pointer on dictionary in usevoid buildDicWithFileMenu(dictionary** library,int* numberOfDic,dictionary** dicInUse);
void addDicMenu(dictionary** library,int numberOfDic,dictionary** dicInUse);
// Ask for dic to erase and call eraseDic
// @param library : pointer on library
// @param numberOfDic : Total number of dictionary in memory
// @param dicInUse : pointer on dictionary in use
void eraseDicMenu(dictionary* library,int numberOfDic,dictionary** dicInUse);
// -------------------------- Dictionary manipulation functions --------------------------
void eraseDic(dictionary* library,int dicToDel);
// Add a new dictionary with the name and description passed as parameters
// @param library : pointer on library
// @param numberOfDic : Total number of dictionary in memory
// @param name : name of dictionary to create
// @param desc : description of dictionary to create
// @param dicCreated : pointer on dictionary created
void addDicAndUse(dictionary** library,int numberOfDic,char name[255],char desc[255],dictionary** dicCreated);
// -------------------------- Utils functions's  --------------------------
// Read file and call addWord on each line
// @param pathToDicFile : path to dictionary file to load 
// @param dicInUse : pointer on dictionary in use
// @return -1 : failure on opening file
// @return 0 : success
int loadDictionaryFromFile(char pathToDicFile[255],dictionary* dicInUse);
// Print menu on screen
void printMenu(dictionary* dicInUse);
// Print all the dictionnaries contained in the library
// @param library : pointer on library (first dictionary)
// @param numberOfDic : number of dictionary in memory
void printLibrary(dictionary* library, int numberOfDic);
// Tell if a dictionnary exist in memory
// @param dicInUse : pointer on dicInUse
// @return 1 if library contain a dictionary
// @return 0 if library in use is empty
int isDictionaryInMemory(dictionary* dictionary);
// Program's menu
void menu(dictionary* library);
// Function executed when program is launched
dictionary* init();
// -------------------------- Test function  --------------------------
// Test function, can be verbose and print debug option 
// 0 -> no output except line telling if all tests passed or not
// 1 -> debug output
void test(int verbose);


