#include <stdio.h>
#include <stdlib.h>

#include "../headers/gestbib.h"

int main(int argc,char *argv[]){

            case 8:
                if(dicInUse != NULL){
                    printf("test\n");

                    scanFile("src/test",dicInUse->tree);

                    short* found= malloc(sizeof(short));

                    unsigned long int startMeasuringTime=0;
                    unsigned long int finishMeasuringTime=0;

                    printf("---------- TEST ----------\n");
                    char* word = calloc(sizeof(char)*256,1);
                    printf("Dictionary %s :\n", dicInUse->name);

                    nbNodeParcoured=0;
                    startMeasuringTime = getTime();
                    getAllWordInDictionary(dicInUse->tree,word,0);
                    finishMeasuringTime = getTime();
                    if(DEBUG){
                        printf("%ld milliseconds to access all dictionary's word\n",(finishMeasuringTime-startMeasuringTime) );
                        printf("Nombre  de noeuds parcouru = %ld\n",nbNodeParcoured );
                    }
                    
                    nbNodeParcoured=0;
                    printf("Searching for a word looking like 'titi' \n");
                    startMeasuringTime = getTime();
                    levensteinInDictionary(dicInUse->tree,0,"titi",2,0,word,found);
                    finishMeasuringTime = getTime();

                    if(!*found){
                        printf("no word seems to look like titi \n");
                    }
                    if(DEBUG){
                        printf("nbNodeParcoured=%ld\n",nbNodeParcoured );
                        printf("%ld milliseconds to access all dictionary's word and compare the levenstein distance with 'titi'\n",(finishMeasuringTime-startMeasuringTime) );
                    }
                }else{
                    printf("Veuillez d'abord charger un dictionnaire\n");
                }
                printMenu(dicInUse);
                while((choice = numericUserInput(">",input,256, 1, 8)) == -1);
            break;

	// char* input = malloc(sizeof(char)*255);
	// while(userInput("Entrer le chemin du fichier à scanner\n>",input,255) != 0);

    menu(init());

    return 0;
}
