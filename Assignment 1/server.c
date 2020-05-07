// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 80
#define NOBODY -2

int setupSocket()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR,
                   &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t *)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    return new_socket;
}

int main(int argc, char const *argv[])
{
    // int newSocket = setupSocket();
    // if (argc > 1)
    // {
    //     // if (argv[2] == "CHILD_PROCESS")
    //     // {

    //     char buffer[1024] = {0};

    //     int valread, i;
    //     int new_socket;
    //     sscanf(argv[1], "%d", &new_socket);
    //     printf("\n New Socket %d \n", new_socket);
    //     // printf("Argc: %d \n", argc);
    //     // printf("Argv length %d \n", sizeof(argv));
    //     // for (i = 0; i < sizeof(argv); i++)
    //     // {
    //     //     printf("i th val %d", i);
    //     //     printf(": %s \n", argv[i]);
    //     // }

    //     // printf("In Child, Socket: %d", new_socket);
    //     valread = read(new_socket, buffer, 1024);
    //     printf("%s\n", buffer);
    //     send(new_socket, hello, strlen(hello), 0);

    //     printf("Hello message sent %d \n", getuid());
    //     return 0;
    //     // }
    // }
    // else
    // {
    int newSocket = setupSocket();
    printf("SocketId: %d \n", newSocket);
    printf("Before Forked\n");
    int newProcess = fork();
    if (newProcess == 0)
    {
        printf("After Fork\n");
        setuid(NOBODY);
        int valread;
        char *hello = "Hello from server vishal";
        char buffer[1024] = {0};
        // char soct_fd[11], process_type[15];
        // sprintf(soct_fd, "%d", newSocket);
        // sprintf(process_type, "%s", "CHILD_PROCESS");
        // printf("Socket descriptor: %s \n", soct_fd);
        // printf("child process arg: %s \n", process_type);
        // sprintf(msg_fd,"%d",fd);
        // char *args[] = {argv[0], soct_fd, NULL};
        valread = read(newSocket, buffer, 1024);
        printf("%s\n", buffer);
        send(newSocket, hello, strlen(hello), 0);
        printf("Hello message sent\n");
        // return 0;
    }
    return 0;
}
