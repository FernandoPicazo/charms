#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/ioctl.h>
#include"charm.h"

int parse_env_integer(const char* integerString, long int *result);
int get_terminal_dimensions(struct chterm *term);

/**
 * Starting with the terminfo API
 * 
**/
int evaluate_term(struct chterm *term){
    const char* termtype = getenv("TERM");
    printf("%s\n", termtype);
    term->termtype = termtype;
    get_terminal_dimensions(term);
    return 0;
}

int get_terminal_dimensions(struct chterm *term){
    const char* rows = getenv("LINES");

    long int ret;
    int status;
    if(rows != NULL){
        status = parse_env_integer(rows, &ret);
        if (status == 0){
            term->rows = (unsigned int) ret;
        }else{
            printf("Unable to parse row count from env variable");
        }
    }    

    status = 0;
    const char* columns = getenv("COLUMNS"); 
    if (columns != NULL){
        status = parse_env_integer(columns, &ret);
        if (status == 0){
            term->columns = (unsigned int) ret;
        }else {
            printf("Unable to parse columns count from env variable");
        }
    }

    if (rows != NULL && columns != NULL){
        printf("%s rows\n", rows);
        printf("%s columns\n", columns);
        return 0;
    }
    
    //This terminal does not export dimension info
    printf("Falling back to ioctl\n");
    struct winsize wsize;
    status = 0;
    status = ioctl(term->fd, TIOCGWINSZ, &wsize); 
    if (status == 0){
        printf("Got rows: %d\n", wsize.ws_row);
        printf("Got columns: %d\n", wsize.ws_col);
        term->columns = wsize.ws_col;
        term->rows = wsize.ws_row;
    }else{
        printf("Unable to determine terminal size via ioctl: %s\n", strerror(errno));
    }

    return 0;
}

int parse_env_integer(const char* integerString, long int *result){
    if (integerString == NULL){
        return -1;
    }
    char *endptr;
    long int parseResult = 0;
    errno = 0;
    parseResult = strtol("5", &endptr, 10);
    
    if (parseResult == 0){
        //likely no digits found
        if (integerString == endptr){
            return -1;
        }
        if (errno != 0){
            printf("Unable to parse errors %s\n", strerror(errno));
            return -1;
        }
    }
    *result = parseResult;
    return 0;
}
