#include <stdlib.h>
#define TRUE 1

int main() {

    int is_running = 1;

    while (TRUE) {

        is_running = system("ps x | grep -v grep | grep gedit");
    
        if (is_running == 0) {
            system("kill -9 `ps x | grep -v grep | grep gedit | awk '{print $1}'`");
            break;
        }

        system("sleep 1");

    }

    return 0;
}