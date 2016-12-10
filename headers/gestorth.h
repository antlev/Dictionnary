// Prototypes
//----------------------------------------------------------------------------------------
unsigned int getAllWordInDictionary(unsigned int tree,char* word,short level);

unsigned int levensteinInDictionary(unsigned int tree,short level,char* wordToCompare,short threshold,short diff,char* word,short* found);

int scanFile(char* pathTofile,unsigned int dictionary);

int printWordNotInDic(char* pathTofile,unsigned int dictionary,short proposeCorrection);

int proposeCorrection(char* pathTofile,unsigned int dictionary);

unsigned int printCloseWordInDic(unsigned int tree,short level,char* wordToCompare,short maxThreshold,short diff,char* word,short* found);

unsigned int returnClosestWordinDic(unsigned int tree,short level,char* wordToCompare,short diff,char* word,short* found,char* closestWord);