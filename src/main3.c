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

int main(int argc,char *argv[]){

	dictionary* library = init();

    short choice;
    short numberOfDic = 0;
    short nbMenu = 11;
    short* found= malloc(sizeof(short));
    char* again = malloc(sizeof(char)*2);
    char* pathToFile = calloc(sizeof(char)*256,1);

    char* input = malloc(sizeof(char)*2);
    char* word = calloc(sizeof(char)*256,1);
    
    dictionary* dicInUse = NULL;
    *found=0;

    unsigned long int startMeasuringTime=0;
    unsigned long int finishMeasuringTime=0;

    do{ 
        do{
	       printMenu(dicInUse,3);
        } while((choice = numericUserInput(">",input,2, 1, nbMenu)) == -1);
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
	            if(dicInUse != NULL){
	                char* wordToFind = calloc(sizeof(char)*256,1);
                    short threshold = 2;
                    printf("******************** RECHERCHE AVANCEE ********************\n");
                    printf("Le seuil est de %d voulez vous le modifier ? (O/N)\n",threshold );
                    while(userInput(">",input,2) != 0);
                    if(*input == 'o' || *input == 'O'){
                        while((threshold = numericUserInput("Veuillez entrer un nouveau seuil\n>",input,255, 1, 10)) == -1);
                    }
                    do{
    	                while(userInput("Veuillez entrer le mot à rechercher dans le dictionnaire\n>",wordToFind,256) != 0);

                        printCloseWordInDic(dicInUse->tree,0,wordToFind,threshold,0,word,found);

                        if(!*found){
                            printf("Aucun mot dans le dictionnaire n'a une distance plus petite que %d\n",threshold );
                        }else{
                            printf("\n");
                        }
                        while(userInput("Voulez vous effectuer une nouvelle recherche avancée\n>",input,2) != 0);
                    }while(*input == 'o' || *input == 'O');
                    free(wordToFind);

	 
				}else{
					printf("Veuillez d'abord charger un dictionnaire\n");
				}
            break;
            case 8:
                if(dicInUse != NULL){
					
                    do{
                    	while(userInput("Veuillez entrer le fichier à corriger\n>",pathToFile,256) != 0);
                        printWordNotInDic(pathToFile,dicInUse,0);
                        while(userInput("Voulez vous re-afficher les mots non contenus dans le dictionnaire ?\n>",again,2) != 0);
                    } while(*again == 'o' || *again == 'O');
                    
                }else{
                    printf("Veuillez d'abord charger un dictionnaire\n");
                }
           	break;
            case 9:
                if(dicInUse != NULL){	
    				do{	
                    	while(userInput("Veuillez entrer le fichier à corriger\n>",pathToFile,256) != 0);
                        printWordNotInDic(pathToFile,dicInUse,1);
                        while(userInput("Voulez vous corriger un autre fichier ?\n>",again,2) != 0);
                    } while(*again == 'o' || *again == 'O');
                    
                }else{
                    printf("Veuillez d'abord charger un dictionnaire\n");
                }
            case 10:
                if(dicInUse != NULL){   
                    short* found= malloc(sizeof(short));
                    *found=0;
                    nbNodeParcoured=0;
                    do{
                        while(userInput("Veuillez entrer le chemin du fichier à corriger\n>",pathToFile,256) != 0);
                        proposeCorrection(pathToFile,dicInUse->tree);
                        while(userInput("Voulez vous corriger un autre fichier ?\n>",again,2) != 0);
                    } while(*again == 'o' || *again == 'O');
                    if(DEBUG){
                        printf("%ld milliseconds to access all dictionary's word\n",(finishMeasuringTime-startMeasuringTime) );
                        printf("Nombre  de noeuds parcouru = %ld\n",nbNodeParcoured );
                    }
                }else{
                    printf("Veuillez d'abord charger un dictionnaire\n");
                }
               break;
            case 11:
                printf("Au-revoir\n");
                free(pathToFile);
                free(word);
                free(again);
                free(found);
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
