#include <stdio.h>
#include <stdlib.h>

#include "../headers/gestbib.h"
#include "../headers/utils.h"
#include <sys/mman.h>


#ifndef DEBUG
    #define DEBUG (0)
#endif

extern node* map;
extern long int mmapVirtualMem;
// Threshold is the maximum distance between 2 words to accept as a similar word
static const short THRESHOLD = 2;

int main(int argc,char *argv[]){

	dictionary* library = init();

    int choice;
    char* input = malloc(sizeof(char)*255);
    int isDicInMem=0;
    int numberOfDic = 0;
    dictionary* dicInUse = NULL;

    printMenu(dicInUse);
    
    while((choice = numericUserInput(">",input,255, 1, 8)) == -1);

    do{
        isDicInMem = isDictionaryInMemory(library);

        switch(choice){
            case 1:
                addDicMenu(&library,numberOfDic,&dicInUse);
                numberOfDic++;
                printMenu(dicInUse);
                while((choice = numericUserInput(">",input,255, 1, 8)) == -1);

            break;
            case 2:
                if(isDicInMem){
                 	chooseDicMenu(library,numberOfDic,&dicInUse);
                }else{
                    printf("Veuillez d'abord créer ou charger un dictionnaire\n");                
                }                
                printMenu(dicInUse);
                while((choice = numericUserInput(">",input,255, 1, 8)) == -1);
           
            break;
            case 3:
                buildDicWithFileMenu(&library,&numberOfDic,&dicInUse);
                printMenu(dicInUse);
                while((choice = numericUserInput(">",input,255, 1, 8)) == -1);
          
            break;
            case 4:
                if(isDicInMem){
                    eraseDicMenu(library,numberOfDic,&dicInUse);
                }else{
                    printf("Veuillez d'abord créer un dictionnaire\n");                
                }
                printMenu(dicInUse);
                while((choice = numericUserInput(">",input,255, 1, 8)) == -1);
         
            break;
            case 5:
                if(dicInUse != NULL){
                    addWordMenu(dicInUse);
                }else{
                    printf("Veuillez d'abord charger un dictionnaire\n");
                }
                printMenu(dicInUse);
                while((choice = numericUserInput(">",input,255, 1, 8)) == -1);

                choice = input[0]-48;            
            break;
            case 6:
                if(dicInUse != NULL){
                    searchWordMenu(dicInUse);
                }else{
                    printf("Veuillez d'abord charger un dictionnaire\n");
                }
                printMenu(dicInUse);
                while((choice = numericUserInput(">",input,255, 1, 8)) == -1);
               
            break;
            case 7:
                printf("Au-revoir\n");
                free(library);
                munmap(map,mmapVirtualMem);
                exit(0);
            break;
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

            default:
            break;
        }
    } while(1);
    exit(0);
}
