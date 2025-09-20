// api/core/include/getch.h

#include <iostream>
#include <termios.h>
#include <unistd.h>

char getch() {
    // Custom getch() function, cause linux doesnt support it directly
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON; // Disable buffered I/O
    old.c_lflag &= ~ECHO;   // Disable echo
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
}
