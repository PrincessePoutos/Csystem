#include "server/socket.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
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
closeSocketServer (int *sockfd)
{
  close (*sockfd);
}
