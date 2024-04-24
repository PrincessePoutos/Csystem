#include "server/server.h"
#include "protopeach.h"
#include "server/changeFruitProcess.h"
#include "server/clear.h"
#include "server/howmanyProcess.h"
#include "server/init.h"
#include "server/matchString.h"
#include "server/recvFruitProcess.h"
#include "server/responce.h"
#include "server/sendFuitProcess.h"
#include "server/socket.h"
#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

bool
matchDomain (char *domain)
{
  return true;
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
  struct fruit *fruits;
  servAddr.sin_family = AF_INET;
  servAddr.sin_port = htons (9001);
  servAddr.sin_addr.s_addr = INADDR_ANY;

  s = malloc (sizeof (int));
  openSocketServer (servAddr, s);

  fruits = initFruits ();

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
      sendFuitProcess (sClient, rest, fruits);
    }
#define RECV_MAGIC "recvfruit"
    else if (state.helo && matchString (token, (char *)RECV_MAGIC))
    {
      recvFruitProcess (sClient, rest, fruits);
    }
#define CHANGE_MAGIC "chngfruit"
    else if (state.helo && matchString (token, (char *)CHANGE_MAGIC))
    {
      changeFruitProcess (sClient, rest, fruits);
    }
#define HOWMANY_MAGIC "howmany"
    else if (state.helo && matchString (token, (char *)HOWMANY_MAGIC))
    {
      howmanyProcess (sClient, rest, fruits);
    }
    else if (state.helo)
    {
      printf ("%s", buffer);
      unknownResponse (sClient);
      run = false;
      free (copyBuffer);
      continue;
    }
    else
    {
      printf ("%s", buffer);
      heloResponse (sClient, NOK);
      run = false;
      free (copyBuffer);
      continue;
    }
    free (copyBuffer);
  }
  free (buffer);
  clearFruits (fruits);
  close (*sClient);
  free (sClient);

  close (*s);
  free (s);
  return 0;
}
