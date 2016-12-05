// Prototypes
//----------------------------------------------------------------------------------------
unsigned int getAllWordInDictionary(unsigned int tree,char* word,short level);

unsigned int levensteinInDictionary(unsigned int tree,char* word,short level,char* wordToCompare,short threshold,short diff);

int scanFile(char* pathTofile,unsigned int dictionary);