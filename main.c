#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "client.h"
SOCKET sock;

void client(const char *address, const char *port, const char *name)
{

    USER_NAME = name;
    sock = init_connection(address, port);
    char buffer[BUF_SIZE];
	
    fd_set rdfs;
    write_server(sock, name);
    while(1)
    {
        FD_ZERO(&rdfs);
        FD_SET(STDIN_FILENO, &rdfs);
        FD_SET(sock, &rdfs);
        if(select(sock + 1, &rdfs, NULL, NULL, NULL) == -1)
        {
            perror("select()");
            exit(errno);
        }
        if(FD_ISSET(STDIN_FILENO, &rdfs))
        {
            fgets(buffer, BUF_SIZE - 1, stdin);
            {
                char *p = NULL;
                p = strstr(buffer, "\n");
                if(p != NULL)
                {
                    *p = 0;
                }
                else
                {
                    buffer[BUF_SIZE - 1] = 0;
                }
            }
            execute_command(sock, buffer);
        }
        else if(FD_ISSET(sock, &rdfs))
        {
            int n = read_server(sock, buffer);
            if(n == 0)
            {
                printf("\r\t[!] Server Disconnected!\n");
                break;
            }
            printf("\r\t");
            puts(buffer);
            render_user_input();
        }
    }
    end_connection(sock);
}

int init_connection(const char *address, const char *port)
{
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN sin = { 0 };
    struct hostent *hostinfo;
    if(sock == INVALID_SOCKET)
    {
        perror("socket()");
        exit(errno);
    }
    hostinfo = gethostbyname(address);

    if (hostinfo == NULL)
    {
        fprintf (stderr, "Unknown host %s.\n", address);
        exit(EXIT_FAILURE);
    }

    sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr;
    sin.sin_port = htons((uint16_t) *port);
    sin.sin_family = AF_INET;

    print_startup_info(address, port);

    if(connect(sock,(SOCKADDR *) &sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
    {
        perror("connect()");
        exit(errno);
    }

    return sock;
}

void print_startup_info(const char *address, const char *port){
    printf("[+] Hello %s.\n", USER_NAME);
    printf("[+] We are trying connecting you to the server at %s:%s....\n", address, port);
}

void render_user_input() {
    printf("\r\t%s\t> ", USER_NAME);
    fflush(stdout);
}

void execute_command(int sock, const char *command) {
    if (strncmp(command, ":help", strlen(":help")) == 0) {
        print_help();
    } else {
        write_server(sock, command);
    }
}

void print_help() {
    printf("\r\n[HELP] TCP Client\n");
    printf("Usage: client <address> <port> <username>...\n");
    printf("Options:\n");
    printf("\t:help\t\tDisplay this information.\n");
    printf("\t:who\t\tAsks the server for a list of connected users.\n");
    printf("\t:quit\t\tLeaves the server.\n\n");
    printf("Author: Osman KHODER.\n");
    printf("Email: osman.khoder@isae.edu.lb\n");
    printf("Version: 1.2.\n\n\n");
    render_user_input();
}

void end_connection(int sock)
{
    closesocket(sock);
}

int read_server(SOCKET sock, char *buffer)
{
    int n = 0;
    if((n = (int) recv(sock, buffer, BUF_SIZE - 1, 0)) < 0)
    {
        perror("recv()");
        exit(errno);
    }
    buffer[n] = '\0';
    return n;
}

void write_server(SOCKET sock, const char *buffer)
{
    if(send(sock, buffer, strlen(buffer), 0) < 0)
    {
        perror("send()");
        exit(errno);
    } else {
        render_user_input();
    }
}

int main(int argc, char **argv)
{
    if(argc < 3)
    {
        printf("Usage : %s <address> <port> <username>...\n", argv[0]);
        return EXIT_FAILURE;
    }
    client(argv[1], argv[2], argv[3]);
    return EXIT_SUCCESS;
}
