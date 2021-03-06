#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <math.h>

#include "../headers/utils.h"

#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2
// -------------------------- Utils functions's  --------------------------
// @return the time of the day in milliseconds
unsigned long getTime(){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    unsigned long millisec;
    return millisec = (tv.tv_usec / 1000)+(tv.tv_sec * 1000) ;
}
// @return the time of the day in milliseconds
unsigned long getTimeMicro(){
    struct timeval tv;
    gettimeofday(&tv,NULL);
    unsigned long microsec;
    return microsec = tv.tv_sec * 1000000 + tv.tv_usec ;
}
// Function used to prompt something to user
// @param prmpt : store the message to print on screen
// @param buff : store the user input
// @param sz : maximum size of input 
// @return 0 if input is ok
// @return 1 if input is empty
// @return 2 if input is too long
int userInput (char *prmpt, char *buff, size_t sz) {
    int ch, extra;

    // Get line with buffer overrun protection.
    if (prmpt != NULL) {
        printf ("%s", prmpt);
        fflush (stdout);
    }

    if(fgets(buff, sz, stdin) == NULL){
        return 1;
    }
    if(*buff == '\n'){
        return 1;
    }
    // If it was too long, there'll be no newline. In that case, we flush
    // to end of line so that excess doesn't affect the next call.
    if (buff[strlen(buff)-1] != '\n') {
        extra = 0;
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = 1;
        return (extra == 1) ? 2 : 0;
    }
    // Otherwise remove newline and give string back to caller.
    buff[strlen(buff)-1] = '\0';
    return 0;
}
// Function used to prompt numeric value to user (call userInput)
// @param prmpt : store the message to print on screen
// @param buff : store the user input
// @param sz : maximum size of input 
// @param lowLimit : numerical values under it won't be accepted
// @param highLimit : numerical values upper it won't be accepted
// @return 0 if input is ok
// @return 1 if input is empty
// @return 2 if input is too long
// @return -1 if input is out of bound
int numericUserInput(char* prmpt, char* buff, size_t sz,short lowLimit,short highLimit){

    if( userInput(prmpt,buff,sz) == 0 ){
        short nbDigit=0;
        short i=0,j=0;

        while( buff[i]-48 >= 0 && buff[i]-48 <= 9 ){
            nbDigit++;   
            i++;
        }
        int returnValue = 0;
        for(i=nbDigit-1;i>=0;i--){
            returnValue+=(buff[i]-48)*pow(10,j);
            j++;
        }
        if(returnValue >= lowLimit && returnValue <= highLimit){
            return returnValue;
        }else{
            return -1;
        }
    }else{
        return -1;
    }
}
// What does the function is obvious
void printMenu(dictionary* dicInUse,short main){
    if(dicInUse->name){
        printf("---------- Vous utilisez maintenant le dictionnaire %s ----------\n",dicInUse->name);
    }
    if(main == 1){
        printf("1) Cr�er un fichier dictionnaire\n");
        printf("2) Utiliser un dictionnaire existant\n");
        printf("3) Fabriquer un dictionnaire � partir d'un fichier texte\n");
        printf("4) D�ruire un fichier dictionnaire\n");
        printf("5) Ins�rer un mot dans un dictionnaire\n");
        printf("6) Rechercher un mot dans un dictionnaire\n");
        printf("7) Faire une recherche regex\n");
        printf("8) Quitter l'application\n");    
    }else if(main == 2){
        printf("1) Tester la diff�rence de deux mots\n");
        printf("2) Quitter l'application\n");    
    }else{
        printf("******************** Traitement dictionnaire ********************\n");
        printf("1) Cr�er un dictionnaire\n");
        printf("2) Utiliser un dictionnaire existant\n");
        printf("3) Fabriquer un dictionnaire � partir d'un fichier texte\n");
        printf("4) D�ruire un fichier dictionnaire\n");
        printf("5) Ins�rer un mot dans un dictionnaire\n");
        printf("6) Rechercher un mot dans un dictionnaire\n");
        printf("7) Effectuer une recherche avanc�e dans le dictionnaire\n");
        printf("******************** Traitement de fichier ********************\n");
        printf("8) Affiche les mots du fichier non contenu dans le dictionnaire\n");
        printf("9) Proposer une correction des mots non contenu dans le dictiionnaire d'un fichier\n");
        printf("10) Corriger un fichier\n");
        printf("11) Quitter l'application\n");   
    }
}
// Concatenate 2 strings
// param s1 : string 1
// param s2 : string 2
char* concat(const char *s1, const char *s2){
    char *result = malloc(strlen(s1)+strlen(s2)+1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}