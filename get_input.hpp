#ifndef GET_INPUT_H
#define GET_INPUT_H

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <chrono>
#include <thread>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <regex>
#include <cctype>
#include <iomanip>
#include <fcntl.h>
#include <cstdlib>
#include <limits>
using namespace std;




//Non-blocking input determines whether the player has input
int kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}



//Two ways to read player input through non-blocking input, 
//respectively for selection menus and inside the game
char Mygetchar() {
    char ch;
    struct termios oldt, newt;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    read(STDIN_FILENO, &ch, 1);
    tcsetattr(STDIN_FILENO, TCSADRAIN, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    return ch;
}

int getch() {
    int ch;
    struct termios t_old, t_new;
    tcgetattr(STDIN_FILENO, &t_old);
    t_new = t_old;
    t_new.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t_new);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &t_old);
    return ch;
}

#endif