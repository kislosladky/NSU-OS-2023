#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    int status;
    if (argc < 2)
    {
        fprintf(STDERR_FILENO, "No command passed\n");
        exit(EXIT_FAILURE);
    }
    switch (pid = fork())
    {
    case -1:
        perror("Fork is failed");
        exit(EXIT_FAILURE);
    case 0:
        execvp(argv[1], argv + 1);
        perror("Exec is failed");
        exit(EXIT_FAILURE);
    default:
        if (waitpid(pid, &status, 0) == -1)
        {
            perror("Waitpid is failed");
            exit(EXIT_FAILURE);
        }
        else
        {
            printf("\nThe code is %d\n", status);
        }
    }
    exit(EXIT_SUCCESS);
}
