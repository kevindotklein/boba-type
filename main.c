#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

#include "colors.h"

#define FPS 30

int curpos = 0;

void clear_term(void) {
    printf("\e[1;1H\e[2J");
}

void term_mode(int mode){
  static struct termios origt, newt;

  if(mode == 1){
    tcgetattr(STDIN_FILENO, &origt);
    newt = origt;
    newt.c_lflag &= ~(ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  }else{
    tcsetattr(STDIN_FILENO, TCSANOW, &origt);
  }
  
}

int main(void) {
    char input;
    fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);
    term_mode(1);
    while(1){
        printf(RED "%d\n" RESET, curpos);
        scanf(" %c", &input);
        printf(GRN "%c" RESET, input);
        
        if(input){
            curpos++;
            input = 0;
        }
        
        clear_term();
        usleep(1200 * 1200/FPS);
    }

    return 0;
}
