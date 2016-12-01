#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <math.h>

#include "utils.h"

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

    fgets(buff, sz, stdin);

    if(*buff == '\n'){
        return NO_INPUT;
    }
    // If it was too long, there'll be no newline. In that case, we flush
    // to end of line so that excess doesn't affect the next call.
    if (buff[strlen(buff)-1] != '\n') {
        extra = 0;
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = 1;
        return (extra == 1) ? TOO_LONG : OK;
    }
    // Otherwise remove newline and give string back to caller.
    buff[strlen(buff)-1] = '\0';
    return OK;
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