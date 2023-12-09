#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

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
            int read_fd = descriptors[0];
            char ch;
            while (read(read_fd, &ch, 1)) {
                printf("%c", toupper(ch));
            }
            printf("\n");
            close(read_fd);
            break;
        default:                   // parent process
            close(descriptors[0]); // closing the read end.
            int write_fd = descriptors[1];
            char* message = "KJGGsgksjgssLGwsg F\0";
            for (char* pointer = message; *pointer != '\0'; pointer++)
            {
                if(write(write_fd, pointer, 1) == 0) {
                    perror("write");
                    close(write_fd);
                    exit(EXIT_FAILURE);
                }
            }
            close(write_fd);

            if (waitpid(pid, NULL, 0) == -1)
            {
                perror("wait");
                exit(EXIT_FAILURE);
            }
    }
    exit(EXIT_SUCCESS);
}
