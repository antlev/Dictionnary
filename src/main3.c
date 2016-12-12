#include <stdio.h>
#include <stdlib.h>

#include "../headers/gestbib.h"
#include "../headers/gestrech.h"
#include "../headers/gestorth.h"
#include "../headers/utils.h"
#include <sys/mman.h>


extern node* map;
extern long int mmapVirtualMem;
long nbNodeParcoured;
// Threshold is the maximum distance between 2 words to accept as a similar word
static const short THRESHOLD = 2;

int main(int argc,char *argv[]){

	dictionary* library = init();

    int choice;
    char* input = malloc(sizeof(char)*255);
    int isDicInMem=0;
    int numberOfDic = 0;
    dictionary* dicInUse = NULL;

    short* found= malloc(sizeof(short));
    *found=0;
    unsigned long int startMeasuringTime=0;
    unsigned long int finishMeasuringTime=0;
    short nbMenu = 11;

    do{
        isDicInMem = isDictionaryInMemory(library);
	    do{
	    	printMenu(dicInUse,3);
	    } while((choice = numericUserInput(">",input,255, 1, nbMenu)) == -1);

        switch(choice){
            case 1:
                addDicMenu(&library,numberOfDic,&dicInUse);
                numberOfDic++;
            break;
            case 2:
                if(isDicInMem){
                 	chooseDicMenu(library,numberOfDic,&dicInUse);
                }else{
                    printf("Veuillez d'abord créer ou charger un dictionnaire\n");                
                }                
            break;
            case 3:
                buildDicWithFileMenu(&library,&numberOfDic,&dicInUse);
            break;
            case 4:
                if(isDicInMem){
                    eraseDicMenu(library,numberOfDic,&dicInUse);
                }else{
                    printf("Veuillez d'abord créer un dictionnaire\n");                
                }
            break;
            case 5:
                if(dicInUse != NULL){
                    addWordMenu(dicInUse);
                }else{
                    printf("Veuillez d'abord charger un dictionnaire\n");
                }
            break;
            case 6:
                if(dicInUse != NULL){
                    searchWordMenu(dicInUse);
                }else{
                    printf("Veuillez d'abord charger un dictionnaire\n");
                }
                  
            break;
            case 7:
	            if(dicInUse != NULL){
	                char* word = calloc(sizeof(char)*256,1);
	                char* wordToFind = calloc(sizeof(char)*256,1);
	 
	                while(userInput("Veuillez entrer le mot à rechercher dans le dictionnaire\n>",wordToFind,256) != 0);

                    printCloseWordInDic(dicInUse->tree,0,wordToFind,2,0,word,found);
	 
				}else{
					printf("Veuillez d'abord charger un dictionnaire\n");
				}
            break;
            case 8:
                if(dicInUse != NULL){
					char* pathTofile = calloc(sizeof(char)*256,1);

                    do{
                    	while(userInput("Veuillez entrer le fichier à corriger\n>",pathTofile,256) != 0);
					} while(printWordNotInDic(pathTofile,dicInUse->tree,0));

                }else{
                    printf("Veuillez d'abord charger un dictionnaire\n");
                }
           	break;
            case 9:
                if(dicInUse != NULL){
					char* pathTofile = calloc(sizeof(char)*256,1);
					
                    do{
                    	while(userInput("Veuillez entrer le fichier à corriger\n>",pathTofile,256) != 0);
					} while(printWordNotInDic(pathTofile,dicInUse->tree,1));

                }else{
                    printf("Veuillez d'abord charger un dictionnaire\n");
                }
                do{
                	printMenu(dicInUse,3);
                } while((choice = numericUserInput(">",input,255, 1, nbMenu)) == -1);            break;
            case 10:
                if(dicInUse != NULL){

                    char* pathToFile = calloc(sizeof(char)*256,1);
                    short* found= malloc(sizeof(short));
                    *found=0;
                    nbNodeParcoured=0;
                    
                    while(userInput("Veuillez entrer le chemin du fichier à corriger\n>",pathToFile,256) != 0);

                    proposeCorrection(pathToFile,dicInUse->tree);

                    if(DEBUG){
                        printf("%ld milliseconds to access all dictionary's word\n",(finishMeasuringTime-startMeasuringTime) );
                        printf("Nombre  de noeuds parcouru = %ld\n",nbNodeParcoured );
                    }

                }else{
                    printf("Veuillez d'abord charger un dictionnaire\n");
                }
                printMenu(dicInUse,3);
               break;
            case 11:
                printf("Au-revoir\n");
                free(library);
                munmap(map,mmapVirtualMem);
                exit(0);
            break;
            default:
            break;
        }
    } while(1);
    exit(0);
}
