#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

// const int EXIT_FAILURE=-1;
// const int EXIT_SUCCESS=1;
const int MAXNBLETTERINWORD=20;

int main(int argc,char *argv[]){
	int randomNbLetterInWord;
	int i,j;
	char fileName[255];
	int noWordToInsert;
	
	int OFFSET='a';
	int NBLETTERINSCOPE=((165-'!')+1);

	printf("quel range de lettre voulez vous générer ?\n");

	int range;
    scanf("%d",&range);


    if(range == 0){
		OFFSET=97;
		NBLETTERINSCOPE=122;
    }else if(range == 1){
		OFFSET=65;
		NBLETTERINSCOPE=90;
    }else if(range == 2){
		OFFSET=65;
		NBLETTERINSCOPE=122;
    }else if(range == 3){
		OFFSET=48;
		NBLETTERINSCOPE=90;
	}else if(range == 4){
		OFFSET=33;
		NBLETTERINSCOPE=255;
	}     
	printf("choose file name\n>");
    // fgets(fileName,254,stdin); // en attendant le flush() 
    fgets(fileName,254,stdin);
    fileName[strlen(fileName)-1] = '\0'; 

    printf("Entrez un nombre de mots\n>");

    scanf("%d",&noWordToInsert);

    FILE *file = fopen(fileName, "ab+");
    srand(time(NULL)); // for random chararacter genreration
    for(i=0;i<noWordToInsert;i++){
		randomNbLetterInWord = (rand()%MAXNBLETTERINWORD)+1;    //returns a pseudo-random integer between 0 and RAND_MAX
		for (j = 0; j < randomNbLetterInWord; ++j)
		{	    
			fputc( (rand()%NBLETTERINSCOPE)+OFFSET, file );
		}
		fputc('\n',file);
    }
    fclose(file);


    return 0;
}
