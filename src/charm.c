#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<termios.h>
#include<unistd.h>
#include"charm.h"

int enterTerminalAltBuffer(int fd);
int leaveterminalAltBuffer(int fd);
int prepareTerminal(int fd, struct termios *data);
int restoreTerminal(int fd, struct termios *data);
int clearTerminal(int fd);
int writeCommand(char* command, int fd);
int open_term_fd();

int charm_initialize(struct chterm* term){
    
    int ttyFd = open_term_fd();
    if (ttyFd < 0) {
        perror("Unable to open file descriptor");
        exit(1);
    }

    printf("Valid tty detected\n");
    //Ensure no weirdness going on
    int ret;
    ret = isatty(ttyFd);
    if (ret != 1) {
       perror("Strange terminal type detected"); 
       exit(1);
    }

    term->fd = ttyFd;
    evaluate_term(term);

    struct termios termiosData;
    ret = tcgetattr(ttyFd, &termiosData);
    if ( ret != 0){
        perror("Unable to retrieve terminal data");
        exit(1);
    }
    struct termios preparedTermios;
    memcpy(&preparedTermios, &termiosData, sizeof(struct termios));
    memcpy(&(term->termiosData), &termiosData, sizeof(struct termios));
    prepareTerminal(ttyFd, &preparedTermios);
    return 0;
}

void charm_terminate(struct chterm *term){
    restoreTerminal(term->fd, &(term->termiosData));
    close(term->fd);

}


int open_term_fd(){
    char* tty = ttyname(STDIN_FILENO);
    if (tty == NULL) {
        perror("Unable to acquire current terminal file descriptor");
        exit(1);
    }
    printf("TTY Name %s\n", tty);
    
    int ttyFd = open(tty, O_RDWR);
    return ttyFd;
}

int prepareTerminal(int fd, struct termios *data){
    data->c_lflag = ECHO | ISIG | ICANON ;
    data->c_iflag = IXON | ICRNL | BRKINT | INPCK | ISTRIP;
    data->c_oflag = OPOST;
    tcsetattr(fd, TCSAFLUSH, data);
    enterTerminalAltBuffer(fd);
    clearTerminal(fd);
    
    return 0;
}

int restoreTerminal(int fd, struct termios *data){
    tcsetattr(fd, TCSAFLUSH, data);
    leaveterminalAltBuffer(fd);
    
    return 0;
}

int clearTerminal(int fd){
    int written;
    //write(fd, "\x1B[2J", strlen("\x1B[2J"));
    writeCommand("\x1B[2J", fd);
    return 0;
}

int enterTerminalAltBuffer(int fd){
    int written;
    write(fd, "\x1B[s", strlen("\x1B[s"));
    write(fd, "\x1B[?47h", strlen("\x1B[?47h"));
    write(fd, "\x1B[?1049h", strlen("\x1B[?1049h"));
    return 0;
}

int leaveterminalAltBuffer(int fd){
    int written;
    write(fd, "\x1B[?1049l", strlen("\x1B[?1049l"));
    write(fd, "\x1B[?47l", strlen("\x1B[?47l"));
    write(fd, "\x1B[u", strlen("\x1B[u"));
    return 0;
}

int writeCommand(char* command, int fd){
    const int MAX_LEN = 20;
    int length = strnlen(command, MAX_LEN);
    int ret = write(fd, command, length); 
    return 0;
}

int killTerm(){
    return 0;
}

int drawLine(){
    return 0;
}
