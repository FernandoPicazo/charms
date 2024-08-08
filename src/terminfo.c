#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/ioctl.h>
#include"charm.h"

int parse_env_integer(const char* integerString, long int *result);
int get_term_dimensions(struct chterm *term);

/**
 * Starting with the terminfo API
 * 
**/
int evaluate_term(struct chterm *term){
    const char* termtype = getenv("TERM");
    printf("%s\n", termtype);
    term->termtype = termtype;
    get_term_dimensions(term);
    return 0;
}

int get_term_dimensions(struct chterm *term){
    const char* rows = getenv("LINES");
    printf("%s rows\n", rows);

    long int ret;
    int status;
    if(rows != NULL){
        status = parse_env_integer(rows, &ret);
        if (status == 0){
            term->rows = (unsigned int) ret;
        }else{
            return -1;
        }
    }    

    status = 0;
    const char* columns = getenv("COLUMNS"); 
    printf("%s columns\n", columns);
    if (columns != NULL){
        status = parse_env_integer(columns, &ret);
        if (status == 0){
            term->columns = (unsigned int) ret;
        }else {
            return -1;
        }
    }
    
    //This terminal does not export dimension info
    if (rows == NULL || columns == NULL){
        printf("Falling back to ioctl");
        struct winsize wsize;
        ioctl(term->fd, TIOCGWINSZ, &wsize); 
        printf("Got rows: %d\n", wsize.ws_col);
        printf("Got columns: %d\n", wsize.ws_col);

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
