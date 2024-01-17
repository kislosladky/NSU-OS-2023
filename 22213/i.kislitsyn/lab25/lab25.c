#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <wait.h>

#define BUFF_LEN 30

int main()
{
    int fd[2];
    int status;
    pid_t pid;
    char buffer[BUFF_LEN];

    if (pipe(fd) == -1)
    {
        perror("Pipe creation failure");
        exit(EXIT_FAILURE);
    }

    switch (pid = fork())
    {
    case -1:
        perror("Fork failure");
        close(fd[0]);
        close(fd[1]);
        exit(EXIT_FAILURE);
    case 0:  
        close(fd[1]);

        do
        {
            if ((status = read(fd[0], buffer, BUFF_LEN)) == -1)
            {
                perror("Read failure");
                close(fd[0]);
                exit(EXIT_FAILURE);
            }

            for (int i = 0; i < status; i++)
            {
                buffer[i] = toupper(buffer[i]);
            }

            if ((write(0, buffer, status)) == -1)
            {
                perror("Write failure");
                close(fd[0]);
                exit(EXIT_FAILURE);
            }

        } while (status > 0);

        close(fd[0]);
        break;
    default:
        close(fd[0]);
        int file;
        int red;

        if ((file = open("input.txt", O_RDONLY)) < 0)
        {
            perror("Open error");
            exit(EXIT_FAILURE);
        }

        while ((red = read(file, buffer, BUFF_LEN)) > 0)
        {
            if ((status = write(fd[1], buffer, red)) == -1)
            {
                perror("Write failure");
                close(fd[1]);
                exit(EXIT_FAILURE);
            }
        }
        if (red == -1)
        {
            perror("read from file error");
            exit(EXIT_FAILURE);
        }

        close(fd[1]);

        if (waitpid(pid, 0, 0) == -1) {
            perror("Wait error");
            close(fd[1]);
            exit(EXIT_FAILURE);
        }
    }

    exit(EXIT_SUCCESS);
}