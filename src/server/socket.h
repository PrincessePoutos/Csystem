#include <arpa/inet.h>
#include <sys/socket.h>

void openSocketServer (struct sockaddr_in serv_addr, int *sockfd);
void closeSocket (int *sockfd);
int acceptClientConnetion (int *sockfd);
void receiveDataFromClient (int s, char *buffer, int bufferSize);
void sendDataToClient (int s, const char *buffer, int bufferSize);
/*
00: unknown error
21: no more of this fruit
42: can't get the number of fruits
51: too much fruits, the server can't get more fruits
69: fruit not available
90: the server refused your helo
*/
enum Errorcodes
{
  UNKNOWN = 00,
  NO_NUMBER_FRUITS_AVAILABLE = 21,
  NUMBER_NOT_FOUND_OF_FRUITS = 42,
  TOO_MUCH_FRUITS = 51,
  FRUITS_NOT_AVAILABLE = 69,
  SERVER_REFUSE_HELO = 90,
};
