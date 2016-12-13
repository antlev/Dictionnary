#include <stdio.h>
#include <stdlib.h>
#include "../headers/gestbib.h"
#include "../headers/utils.h"
#include <sys/mman.h>

extern node* map;
extern long int mmapVirtualMem;

int main(int argc,char *argv[]){

	dictionary* library = init();
    short choice;
    char* input = malloc(sizeof(char)*2);
    char* again = malloc(sizeof(char)*2);
    short numberOfDic = 0;
    dictionary* dicInUse = NULL;
    do{
        do{
            printMenu(dicInUse,1);
        }while((choice = numericUserInput(">",input,2, 1, 7)) == -1);
        switch(choice){
            case 1:
                do{
                    addDicMenu(&library,numberOfDic,&dicInUse);
                    numberOfDic++;
                    while(userInput("Voulez vous ajouter un nouveau dictionnaire ? (O/N)\n>",again,2) != 0);
                }while(*again == 'o' || *again == 'O');
            break;
            case 2:
                if(dicInUse != NULL){
                 	chooseDicMenu(library,numberOfDic,&dicInUse);
                }else{
                    printf("Veuillez d'abord créer ou charger un dictionnaire\n");                
                }                
            break;
            case 3:
                do{
                    buildDicWithFileMenu(&library,&numberOfDic,&dicInUse);
                    while(userInput("Voulez vous charger un autre fichier ? (O/N)\n>",again,2) != 0);
                }while(*again == 'o' || *again == 'O');
            break;
            case 4:
                if(dicInUse != NULL){
                    do{
                        eraseDicMenu(library,numberOfDic,&dicInUse);
                        while(userInput("Voulez vous supprimer un autre dictionnaire ? (O/N)\n>",again,2) != 0);
                    }while(*again == 'o' || *again == 'O');
                }else{
                    printf("Veuillez d'abord créer un dictionnaire\n");                
                }
            break;
            case 5:
                if(dicInUse != NULL){
                    do{
                        addWordMenu(dicInUse);
                        while(userInput("Voulez vous ajouter un autre mot ? (O/N)\n>",again,2) != 0);
                    }while(*again == 'o' || *again == 'O');
                }else{
                    printf("Veuillez d'abord charger un dictionnaire\n");
                }
                
            break;
            case 6:
                if(dicInUse != NULL){
                    do{
                        searchWordMenu(dicInUse);
                        while(userInput("Voulez vous rechercher un autre mot ? (O/N)\n>",again,2) != 0);
                    }while(*again == 'o' || *again == 'O');
                }else{
                    printf("Veuillez d'abord charger un dictionnaire\n");
                }
            break;
            case 7:
                printf("Au-revoir\n");
                free(again);
                free(input);
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
