#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    pid_t pid = fork();
    int child_exit_status;
    switch (pid)
    {
    case -1:
        perror("fork");
        exit(EXIT_FAILURE);
        break;
    case 0: //child
        printf("Child process\n");
        execlp("cat", "cat", "1.txt", (char *)NULL);
        perror("exelp");
        exit(EXIT_FAILURE);
        break;
    default:
        if (wait(&child_exit_status) == -1) {
            perror("wait");
            exit(EXIT_FAILURE);
        }
        if (child_exit_status != 0)
        {
            printf("The program called by exec is failed\n");
            exit(EXIT_FAILURE);
        }

        printf("Child process ended\n");
        break;
    }
    exit(EXIT_SUCCESS);
}
