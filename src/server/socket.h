#include <arpa/inet.h>
#include <sys/socket.h>

void openSocketServer (struct sockaddr_in serv_addr, int *sockfd);
void closeSocketServer (int *sockfd);
int acceptClientConnetion (int *sockfd);
