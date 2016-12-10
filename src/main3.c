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

    do{
    	printMenu(dicInUse,3);
    } while((choice = numericUserInput(">",input,255, 1, 10)) == -1);

    do{
        isDicInMem = isDictionaryInMemory(library);

        switch(choice){
            case 1:
                addDicMenu(&library,numberOfDic,&dicInUse);
                numberOfDic++;
                do{
                	printMenu(dicInUse,3);
                } while((choice = numericUserInput(">",input,255, 1, 10)) == -1);

            break;
            case 2:
                if(isDicInMem){
                 	chooseDicMenu(library,numberOfDic,&dicInUse);
                }else{
                    printf("Veuillez d'abord créer ou charger un dictionnaire\n");                
                }                
                do{
                	printMenu(dicInUse,3);
                } while((choice = numericUserInput(">",input,255, 1, 10)) == -1);
           
            break;
            case 3:
                buildDicWithFileMenu(&library,&numberOfDic,&dicInUse);
                do{
                	printMenu(dicInUse,3);
                } while((choice = numericUserInput(">",input,255, 1, 10)) == -1);
          
            break;
            case 4:
                if(isDicInMem){
                    eraseDicMenu(library,numberOfDic,&dicInUse);
                }else{
                    printf("Veuillez d'abord créer un dictionnaire\n");                
                }
                do{
                	printMenu(dicInUse,3);
                } while((choice = numericUserInput(">",input,255, 1, 10)) == -1);
         
            break;
            case 5:
                if(dicInUse != NULL){
                    addWordMenu(dicInUse);
                }else{
                    printf("Veuillez d'abord charger un dictionnaire\n");
                }
                do{
                	printMenu(dicInUse,3);
                } while((choice = numericUserInput(">",input,255, 1, 10)) == -1);

                choice = input[0]-48;            
            break;
            case 6:
                if(dicInUse != NULL){
                    searchWordMenu(dicInUse);
                }else{
                    printf("Veuillez d'abord charger un dictionnaire\n");
                }
                do{
                	printMenu(dicInUse,3);
                } while((choice = numericUserInput(">",input,255, 1, 10)) == -1);
               
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
                do{
                	printMenu(dicInUse,3);
                } while((choice = numericUserInput(">",input,255, 1, 10)) == -1);
                break;
            case 8:
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
                    
                    nbNodeParcoured=0;
                    printf("Searching for a word looking like 'titi' \n");
                    startMeasuringTime = getTime();
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
                printMenu(dicInUse,3);
                do{
                	printMenu(dicInUse,3);
                } while((choice = numericUserInput(">",input,255, 1, 10)) == -1);            break;
            case 9:
                do{
                	printMenu(dicInUse,3);
                } while((choice = numericUserInput(">",input,255, 1, 10)) == -1);
            break;
            case 10:
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
