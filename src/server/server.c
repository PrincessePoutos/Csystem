#include "server/server.h"

int
main (int argc, char *argv[])
{
  int *s, *sClient;
  char *buffer;
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
    mainProcess (&state, sClient, buffer, &run, fruits);
  }
  free (buffer);
  clearFruits (fruits);
  close (*sClient);
  free (sClient);

  close (*s);
  free (s);
  return 0;
}
