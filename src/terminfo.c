#include<stdio.h>
#include<stdlib.h>
#include"charm.h"


/**
 * Starting with the terminfo API
 * 
**/
int evaluate_term(){
    const char* termtype = getenv("TERM");
    printf("%s\n", termtype);
    return 0;
}
