#ifndef CLIENT_H
#define CLIENT_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;
#define CRLF "\r\n"
#define BUF_SIZE 1024
const char *USER_NAME;
void client(const char *address, const char *port, const char *name);
int init_connection(const char *address, const char *port);
void end_connection(int sock);
void print_startup_info(const char *address, const char *port);
void execute_command(int sock, const char *command);
void render_user_input();
void print_help();
int read_server(SOCKET sock, char *buffer);
void write_server(SOCKET sock, const char *buffer);
#endif /* guard */

