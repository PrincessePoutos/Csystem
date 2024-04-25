#include "server/server.h"

int
main (int argc, char *argv[])
{
  int *s, *sClient;
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

  mainProcess (sClient, fruits);

  clearFruits (fruits);
  close (*sClient);
  free (sClient);

  close (*s);
  free (s);
  return 0;
}
