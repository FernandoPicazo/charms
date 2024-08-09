#ifndef CHARMS_H
#define CHARMS_H
#include<termios.h>
struct chterm{
    int fd;
    const char* termtype;
    unsigned int rows;
    unsigned int columns;
    struct termios termiosData;
};

struct chcell{
       
};

int charm_initialize(struct chterm* term);
void charm_terminate(struct chterm* term);
int evaluate_term(struct chterm *term);
#endif
