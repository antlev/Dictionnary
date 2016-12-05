// Prototypes
//----------------------------------------------------------------------------------------
unsigned int getAllWordInDictionary(unsigned int tree,char* word,short level);

unsigned int levensteinInDictionary(unsigned int tree,short level,char* wordToCompare,short threshold,short diff,char* word,short* found);

int scanFile(char* pathTofile,unsigned int dictionary);