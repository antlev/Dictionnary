#include <stdio.h>
#include <stdlib.h>

#include "../headers/gestbib.h"

int main(int argc,char *argv[]){

	// char* input = malloc(sizeof(char)*255);
	// while(userInput("Entrer le chemin du fichier à scanner\n>",input,255) != 0);

    menu(init());

    return 0;
}
