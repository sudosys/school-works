#include <stdlib.h>

int main() {

    system("gedit &");

    system("sleep 3");

    system("kill -9 `ps x | grep -v grep | grep gedit | awk '{print $1}'`");

    return 0;
}