#ifndef socket_H
#define socket_H
#include <arpa/inet.h>
#include <sys/socket.h>

void openSocketServer (struct sockaddr_in serv_addr, int *sockfd);
void closeSocket (int *sockfd);
int acceptClientConnetion (int *sockfd);
void receiveDataFromClient (int s, char *buffer, int bufferSize);
void sendDataToClient (int s, const char *buffer, int bufferSize);

#endif /* end of include guard: socket_H */
