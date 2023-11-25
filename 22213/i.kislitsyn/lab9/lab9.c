#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    pid_t pid = fork();
    
    switch (pid)
    {
    case -1:
        perror("fork");
        exit(EXIT_FAILURE);
        break;
    case 0:
        execlp("cat", "cat", "1.txt", (char*) NULL);
        break;
    default:
        if (wait(NULL) == -1) {
            perror("wait");
            exit(EXIT_FAILURE);
        }
        break;
    }
    printf("Child process ended\n");
    exit(EXIT_SUCCESS);
}
