#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#define STR_LEN 20

int main() {
    int descriptors[2];
    if (pipe(descriptors) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid_t pid = fork();
    switch (pid) {
        case -1:
            perror("fork");
            close(descriptors[0]);
            close(descriptors[1]);
            exit(EXIT_FAILURE);
        case 0: //child process
            close(descriptors[1]); // closing the write end.
            char read_message[STR_LEN];

            if (read(descriptors[0], read_message, STR_LEN) == -1)
            {
                close(descriptors[0]);
                perror("read");
                exit(EXIT_FAILURE);
            }

            for (int i = 0; i < STR_LEN; i++)
            {
                printf("%c", toupper(read_message[i]));
            }
            printf("\n");
            close(descriptors[0]);
            break;
        default:                   // parent process
            close(descriptors[0]); // closing the read end.
            char* message = "KJGGsgksjgssLGwsg F";
            if (write(descriptors[1], message, STR_LEN) == -1)
            {
                perror("write");
                close(descriptors[1]);
                exit(EXIT_FAILURE);
            }
            close(descriptors[1]);

            if (waitpid(pid, NULL, 0) == -1)
            {
                perror("wait");
                exit(EXIT_FAILURE);
            }
    }
    exit(EXIT_SUCCESS);
}
