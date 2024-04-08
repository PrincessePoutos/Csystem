#include "server/server.h"
#include "server/socket.h"
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

bool
matchDomain (char *domain)
{
  char pattern[] = "^((?!-)[A-Za-z0-9-]{1,63}(?<!-)\\.)+[A-Za-z]{2,6}$";
  regex_t regex;
  int reti = regcomp (&regex, pattern, REG_EXTENDED);
  if (reti)
  {
    perror ("Impossible de compiler le pattern regex\n");
    exit (-1);
  }

  reti = regexec (&regex, domain, 0, NULL, 0);
  return reti;
}

void
heloResponse (int *sClient, enum HeloResponse heloResponseChoise)
{
  char *buffer = calloc (1, sizeof (char) * BUFFER_SIZE);
  strcpy (buffer, "HELO");
  switch (heloResponseChoise)
  {
  case OK:
    strcat (buffer, " OK");
    break;
  case NOK:
  default:
    strcat (buffer, " NOK");
    break;
  }
  sendDataToClient (*sClient, buffer, sizeof (buffer));
}

int
main (int argc, char *argv[])
{
  struct sockaddr_in servAddr;
  servAddr.sin_family = AF_INET;
  servAddr.sin_port = htons (9001);
  servAddr.sin_addr.s_addr = INADDR_ANY;

  int *s = malloc (sizeof (int));
  openSocketServer (servAddr, s);

  int *sClient = malloc (sizeof (int));
  *sClient = acceptClientConnetion (s);
  char *buffer = calloc (1, sizeof (char) * BUFFER_SIZE);
  while (1)
  {
    receiveDataFromClient (*sClient, buffer, sizeof (buffer));
    if (buffer[0] == 'q')
    {
      break;
    }
    if (buffer[0] == 'h' && buffer[1] == 'e' && buffer[2] == 'l'
        && buffer[3] == 'o' && buffer[4] == ' ' && matchDomain (buffer + 4))
    {
      printf ("%s", buffer);
      heloResponse (sClient, OK);
    }
    else
    {
      printf ("%s", buffer);
      heloResponse (sClient, NOK);
    }
  }
  closeSocket (sClient);
  free (sClient);
  free (buffer);

  closeSocket (s);
  free (s);
  return 0;
}
