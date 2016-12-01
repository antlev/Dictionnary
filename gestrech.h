// Prototypes
//----------------------------------------------------------------------------------------
// Return the Damerau Levenshtein Distance between 2 strings.
// Distance correspond to number of deletion,insertion,substitution or transposition.
// @param str1 : string of first word to compare
// @param str2 : string of second word to compare
// @return levenstein distance as int
int DamerauLevenshteinDistance(char* str1, char* str2);

// Return the lowest val between val1,val2 and val3
int minimum3(int val1, int val2, int val3);

// Return the lowest val between val1 and val2
int minimum2(int val1, int val2);

// Print a bidemsionnal table using a simple table of int
// @param tab : pointer on table of int
// @param nbLine : number of line of bidimensionnal table
// @param nbCol : number of column of bidimensionnal table
void printTab(int* tab,int nbLine,int nbCol);

// Function used to manipulate a bidimensionnal table using a simple table
// @return value of int in table at line 'line' and column 'column' 
// @param tab : pointer on table of int
// @param nbLine : number of line of bidimensionnal table
// @param nbCol : number of column of bidimensionnal table
int* getTab(int* tab,int nbCol,int i,int j);

