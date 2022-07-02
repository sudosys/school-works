#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <poll.h>
#include <unistd.h>

#define LIMIT 500
#define TRUE 1
#define FALSE 0

int main() {

    FILE* more_than_300KB_pipeline;
    FILE* more_than_5mins_pipeline;
    FILE* pids_pipeline;
    char more_than_300KB[LIMIT];
    char more_than_5mins[LIMIT];
    char pids[LIMIT];
    int proc_index = 1;
    int user_choice = 0;
    int is_killed = FALSE;
    const char* ram_usage_proc_names_cmd = "ps ux | awk 'NR > 1 {if($6>300) print $11}'";
    const char* cpu_time_proc_names_cmd = "ps ux | awk '{split($10,a,\":\"); if(a[2]>5) print $11}'";
    const char* proc_ids_cmd = "ps ux | awk 'NR > 1 {if($6>300) print $2}' && ps ux | awk '{split($10,a,\":\"); if(a[2]>5) print $2}'";
    struct pollfd stdin_poll = { STDIN_FILENO, POLLIN | POLLPRI };
    char* proc_name;
    char kill_cmd[15] = "kill -9 ";

    while (TRUE) {

        if (is_killed == 1) { break; }

        more_than_300KB_pipeline = popen(ram_usage_proc_names_cmd, "r");
        more_than_5mins_pipeline = popen(cpu_time_proc_names_cmd, "r");
        pids_pipeline = popen(proc_ids_cmd, "r");

        printf("Using more than 300KB:\n");

        while (fgets(more_than_300KB, sizeof(more_than_300KB), more_than_300KB_pipeline) != NULL) {

            proc_name = strrchr(more_than_300KB, '/');

            if (proc_name != NULL) { printf("%d - %s", proc_index, proc_name+1); }
            
            proc_index++;

        }

        printf("\nRunning more than 5 minutes:\n");

        while (fgets(more_than_5mins, sizeof(more_than_5mins), more_than_5mins_pipeline) != NULL) {
            
            proc_name = strrchr(more_than_5mins, '/');

            if (proc_name != NULL) { printf("%d - %s", proc_index, proc_name+1); }

            proc_index++;

        }

        printf("Enter a number to kill, or wait for the next refresh ->");

        fflush(stdout);

        if (poll(&stdin_poll, 1, 5000)) { 
            scanf("%d", &user_choice);
        } else {
            system("clear");
            proc_index = 1;
            continue;
        }

        proc_index = 1;

        while (fgets(pids, sizeof(pids), pids_pipeline) != NULL) {

            if (proc_index == user_choice) { 

                system(strcat(kill_cmd,pids));

                is_killed = TRUE;

                break;
            
            }

            proc_index++;

        }

    }

    pclose(more_than_300KB_pipeline);
    pclose(more_than_5mins_pipeline);
    pclose(pids_pipeline);

    return 0;

}
