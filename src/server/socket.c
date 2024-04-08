#include "server/socket.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

void
openSocketServer (struct sockaddr_in serv_addr, int *sockfd)
{

  *sockfd = socket (AF_INET, SOCK_STREAM, 0);
  if (*sockfd < 0)
  {
    perror ("impossible d'ouvrir le socket\n");
    exit (-1);
  }

  if (bind (*sockfd, (struct sockaddr *)&serv_addr, sizeof (serv_addr)) < 0)
  {
    perror ("impossible de faire le bind\n");
    exit (-1);
  }
}

void
closeSocket (int *sockfd)
{
  close (*sockfd);
}

int
acceptClientConnetion (int *sockfd)
{
  return accept (*sockfd, NULL, NULL);
}

void
receiveDataFromClient (int *s, char *buffer, int bufferSize)
{
  recv (*s, buffer, bufferSize, 0);
}
