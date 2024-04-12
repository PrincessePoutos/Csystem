#include "server/server.h"
#include "protopeach.h"
#include "server/socket.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void
initFruits (void)
{
  char *name = calloc (1, sizeof (char) * 20);

  strcpy (name, "peach");
  peach = createFruit (name, 0);

  strcpy (name, "mango");
  mango = createFruit (name, 0);

  strcpy (name, "kiwi");
  kiwi = createFruit (name, 0);

  strcpy (name, "watermelon");
  watermelon = createFruit (name, 0);

  strcpy (name, "tomato");
  tomato = createFruit (name, 0);

  strcpy (name, "ananas");
  ananas = createFruit (name, 0);

  free (name);
  return;
}

bool
matchDomain (char *domain)
{
  return true;
}

void
heloResponse (int *sClient, enum HeloResponse heloResponseChoise)
{
  char *buffer = calloc (1, sizeof (char) * BUFFER_SIZE);
  char *errorCode = malloc (sizeof (char) * 3);
  strcpy (buffer, "HELO");
  switch (heloResponseChoise)
  {
  case OK:
    strcat (buffer, " OK");
    break;
  case NOK:
    strcat (buffer, " NOK ");
    sprintf (errorCode, "%d", SERVER_REFUSE_HELO);
    strcat (buffer, errorCode);
    break;
  default:
    break;
  }
  free (errorCode);
  sendDataToClient (*sClient, buffer, strlen (buffer));
  free (buffer);
}

int
main (int argc, char *argv[])
{
  int *s, *sClient;
  char *buffer;
  bool run;
  struct state state;
  struct sockaddr_in servAddr;
  servAddr.sin_family = AF_INET;
  servAddr.sin_port = htons (9001);
  servAddr.sin_addr.s_addr = INADDR_ANY;

  s = malloc (sizeof (int));
  openSocketServer (servAddr, s);

  initFruits ();

  sClient = malloc (sizeof (int));
  *sClient = acceptClientConnetion (s);
  buffer = calloc (1, sizeof (char) * BUFFER_SIZE);
  run = true;
  state.helo = false;

  while (run)
  {
    memset (buffer, '\0', BUFFER_SIZE);
    receiveDataFromClient (*sClient, buffer, sizeof (buffer));
    if (buffer[0] == 'q')
    {
      run = false;
      continue;
    }
    if (buffer[0] == 'h' && buffer[1] == 'e' && buffer[2] == 'l'
        && buffer[3] == 'o' && buffer[4] == ' ' && matchDomain (buffer + 5)
        && !state.helo)
    {
      printf ("%s", buffer);
      heloResponse (sClient, OK);
      state.helo = true;
    }
    else if (buffer[0] == 'h' && buffer[1] == 'e' && buffer[2] == 'l'
             && buffer[3] == 'o' && buffer[4] == ' '
             && matchDomain (buffer + 5) && state.helo)
    {
      printf ("%s", buffer);
      heloResponse (sClient, NOK);
      run = false;
      continue;
    }
    else
    {
      printf ("%s", buffer);
      heloResponse (sClient, NOK);
      run = false;
      continue;
    }
  }
  close (*sClient);
  free (sClient);
  free (buffer);

  close (*s);
  free (s);
  return 0;
}
