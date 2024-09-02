#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

#define MSGSIZE 20

char *server_sock = "server.sock";

int main()
{
    int fd;
    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
    {
        perror("Failed with socket creation");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_un addr;
    char msg[MSGSIZE];
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, server_sock);

    if ((bind(fd, (struct sockaddr*)&addr, sizeof(addr))) < 0)
    {
        perror("Binding failure");
        exit(EXIT_FAILURE);
    }


    if (listen(fd, 1) < 0)
    {
        perror("Listening failure");
        unlink(server_sock);
        exit(EXIT_FAILURE);
    }
   

    int accepted;
    if ((accepted = accept(fd, NULL, NULL)) == -1)
    {
        perror("Accept failed");
        unlink(server_sock);
        exit(EXIT_FAILURE);
    }
    unlink(server_sock);


    int len;
    while ((len = read(accepted, msg, MSGSIZE)) > 0)
    {
        for (int i = 0; i < len; i++)
        {
            msg[i] = toupper(msg[i]);
        }

        if ((write(STDOUT_FILENO, msg, len)) == -1)
        {
            perror("Failed with writing");
            exit(EXIT_FAILURE);
        }
    }


    if (len == -1)
    {
        perror("Failed with reading");
        exit(EXIT_FAILURE);
    }

    printf("Connection is closed\n");
    exit(EXIT_SUCCESS);
}
