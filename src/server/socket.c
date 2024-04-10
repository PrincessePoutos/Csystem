#include "server/socket.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
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
  int opt = 1;
  // Permettre la réutilisation de l'adresse du socket
  if (setsockopt (*sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                  sizeof (opt)))
  {
    perror ("setsockopt");
    exit (-1);
  }

  if (bind (*sockfd, (struct sockaddr *)&serv_addr, sizeof (serv_addr)) < 0)
  {
    perror ("impossible de faire le bind\n");
    exit (-1);
  }
  listen (*sockfd, 1);
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
receiveDataFromClient (int s, char *buffer, int bufferSize)
{
  char *tmpBuffer = calloc (1, sizeof (char) * bufferSize);

  if (tmpBuffer == NULL)
  {
    perror ("Erreur lors de l'allocation de mémoire pour tmpBuffer");
    return;
  }

  ssize_t bytesRead;
  do
  {
    bytesRead = recv (s, tmpBuffer, bufferSize, 0);
    if (bytesRead < 0)
    {
      perror ("Erreur lors de la réception des données du client");
      break;
    }

    strncat (buffer, tmpBuffer, bytesRead);

    if (strchr (buffer, '\n') != NULL)
    {
      break;
    }

    memset (tmpBuffer, '\0', bufferSize);
  } while (bytesRead > 0);

  free (tmpBuffer);
}

void
sendDataToClient (int s, const char *buffer, int bufferSize)
{
  send (s, buffer, bufferSize, 0);
}
