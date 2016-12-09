#include <stdio.h>
#include <stdlib.h>
#include "../headers/gestbib.h"
#include "../headers/utils.h"
#include <sys/mman.h>

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

    do{
        isDicInMem = isDictionaryInMemory(library);
        do{
    	    printMenu(dicInUse,1);
        } while((choice = numericUserInput(">",input,255, 1, 7)) == -1);

        switch(choice){
            case 1:
                addDicMenu(&library,numberOfDic,&dicInUse);
                numberOfDic++;
                do{
                	printMenu(dicInUse,1);
                } while((choice = numericUserInput(">",input,255, 1, 7)) == -1);

            break;
            case 2:
                if(isDicInMem){
                 	chooseDicMenu(library,numberOfDic,&dicInUse);
                }else{
                    printf("Veuillez d'abord créer ou charger un dictionnaire\n");                
                }                
                do{
                	printMenu(dicInUse,1);
                } while((choice = numericUserInput(">",input,255, 1, 7)) == -1);
           
            break;
            case 3:
                buildDicWithFileMenu(&library,&numberOfDic,&dicInUse);
                do{
                	printMenu(dicInUse,1);
                } while((choice = numericUserInput(">",input,255, 1, 7)) == -1);
          
            break;
            case 4:
                if(isDicInMem){
                    eraseDicMenu(library,numberOfDic,&dicInUse);
                }else{
                    printf("Veuillez d'abord créer un dictionnaire\n");                
                }
                do{
                	printMenu(dicInUse,1);
                } while((choice = numericUserInput(">",input,255, 1, 7)) == -1);
         
            break;
            case 5:
                if(dicInUse != NULL){
                    addWordMenu(dicInUse);
                }else{
                    printf("Veuillez d'abord charger un dictionnaire\n");
                }
                do{
                	printMenu(dicInUse,1);
                } while((choice = numericUserInput(">",input,255, 1, 7)) == -1);

                choice = input[0]-48;            
            break;
            case 6:
                if(dicInUse != NULL){
                    searchWordMenu(dicInUse);
                }else{
                    printf("Veuillez d'abord charger un dictionnaire\n");
                }
                do{
                	printMenu(dicInUse,1);
                } while((choice = numericUserInput(">",input,255, 1, 7)) == -1);
               
            break;
            case 7:
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
