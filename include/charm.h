#ifndef CHARMS_H
#define CHARMS_H

struct chterm{
    int fd;
    const char* termtype;
    unsigned int rows;
    unsigned int columns;
};

struct chcell{
       
};

int init_term(struct chterm* term);
int evaluate_term(struct chterm *term);
#endif
