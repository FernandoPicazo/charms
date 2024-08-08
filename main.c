#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<termios.h>
#include<unistd.h>
#include"charm.h"

int main(int argc, char* argv[]){
    printf("Hello World\n");
    
    struct chterm term;
    evaluate_term(&term);
    return 0;
}
