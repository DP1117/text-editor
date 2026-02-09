#include <stdlib.h>
#include <termios.h>
#include <unistd.h> 

struct termios orig_termios;

void disableRawMode (void) {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode (void) {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);

    struct termios raw = orig_termios;
    
    // turns echo and canonical terminal attributes off
    raw.c_lflag &= ~(ECHO | ICANON);

    /* The TCSAFLUSH option specifies to set the terminal 
     * upon no more pending output to be written while also 
     * discarding any unread input
     */
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main (void) {
    // disables canonical and turns on raw
    enableRawMode();

    char c;
    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q');
    return 0;
}
