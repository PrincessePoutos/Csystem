#include "server/server.h"
#include "protopeach.h"
#include "server/socket.h"
#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int
matchString (char *s1, char *s2)
{
  return ((*s1 == 0 && *s2 == 0)                 ? (1)
          : (*s1 != 0 && *s2 == 0)               ? (0)
          : (*s1 == 0 && *s2 != 0 && *s2 != '*') ? (0)
          : (*s1 == 0 && *s2 != 0 && *s2 == '*') ? (matchString (s1, s2 + 1))
          : (*s1 != 0 && *s2 != 0 && *s2 == '*')
              ? (matchString (s1, s2 + 1) || matchString (s1 + 1, s2))
          : (*s1 != 0 && *s2 != 0 && *s2 != '*')
              ? (*s1 != *s2) ? (0) : (matchString (s1 + 1, s2 + 1))
              : (matchString (s1 + 1, s2 + 1)));
}

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

void
unknownResponse (int *sClient)
{
  char *buffer = calloc (1, sizeof (char) * 3);
  sprintf (buffer, "%02d", UNKNOWN);
  sendDataToClient (*sClient, buffer, 3);
}

int
main (int argc, char *argv[])
{
  int *s, *sClient;
  char *buffer, *copyBuffer;
  char *rest, *token;
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
#define HELO_MAGIC "helo"
    copyBuffer = strdup (buffer);
    rest = copyBuffer;
    token = strsep (&rest, " ");
    if (!state.helo && matchString (token, (char *)HELO_MAGIC)
        && matchDomain (rest))
    {
      printf ("%s", buffer);
      heloResponse (sClient, OK);
      state.helo = true;
    }
    else if (state.helo && matchString (token, (char *)HELO_MAGIC)
             && matchDomain (rest))
    {
      printf ("%s", buffer);
      heloResponse (sClient, NOK);
      run = false;
      free (copyBuffer);
      continue;
    }
#define SEND_MAGIC "sendfruit"
    else if (state.helo && matchString (token, (char *)SEND_MAGIC))
    {
      printf ("%s,%s", token, rest);
    }
    else
    {
      printf ("%s", buffer);
      unknownResponse (sClient);
      run = false;
      free (copyBuffer);
      continue;
    }
    free (copyBuffer);
  }
  free (buffer);

  close (*sClient);
  free (sClient);

  close (*s);
  free (s);
  return 0;
}
