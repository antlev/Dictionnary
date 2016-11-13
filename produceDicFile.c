#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// const int EXIT_FAILURE=-1;
// const int EXIT_SUCCESS=1;
const int NBWORDTOINSERT=100000000;
const int MAXNBLETTERINWORD=20;

int main(){
	int randomNbLetterInWord;
	int i,j;
	// char alphabet[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	char fileName[255];
    
	printf("choose file name\n>");
    // fgets(fileName,254,stdin); // en attendant le flush() 
    fgets(fileName,254,stdin);
    fileName[strlen(fileName)-1] = '\0'; 

    FILE *file = fopen(fileName, "ab+");
    srand(time(NULL)); // for random chararacter genreration
    for(i=0;i<NBWORDTOINSERT;i++){
		randomNbLetterInWord = (rand()%MAXNBLETTERINWORD)+1;    //returns a pseudo-random integer between 0 and RAND_MAX
		for (j = 0; j < randomNbLetterInWord; ++j)
		{	    
			fputc( (rand()%26)+97, file );
		}
		fputc('\n',file);
    }
    fclose(file);


    return 0;
}
