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
    case 0: //child
        printf("Child process\n");
        execlp("cat", "cat", "1.txt", (char *)NULL);
        perror("exelp");
        exit(EXIT_FAILURE);
        break;
    default:
        if (wait(NULL) == -1) {
            perror("wait");
            exit(EXIT_FAILURE);
        }
        printf("Child process ended\n");
        break;
    }
    exit(EXIT_SUCCESS);
}
