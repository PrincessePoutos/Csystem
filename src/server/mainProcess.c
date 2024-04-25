#include "server/mainProcess.h"

void
mainProcess (struct state *state, int *sClient, char *buffer, bool *run,
             struct fruit *fruits)
{
  char *rest, *token, *copyBuffer;
  memset (buffer, '\0', BUFFER_SIZE);
  receiveDataFromClient (*sClient, buffer, sizeof (buffer));
  if (buffer[0] == 'q')
  {
    *run = false;
    return;
  }
#define HELO_MAGIC "helo"
  copyBuffer = strdup (buffer);
  rest = copyBuffer;
  token = strsep (&rest, " ");
  if (!state->helo && matchString (token, (char *)HELO_MAGIC)
      && matchDomain (rest))
  {
    printf ("%s", buffer);
    heloResponse (sClient, OK);
    state->helo = true;
  }
  else if (state->helo && matchString (token, (char *)HELO_MAGIC)
           && matchDomain (rest))
  {
    printf ("%s", buffer);
    heloResponse (sClient, NOK);
    *run = false;
    free (copyBuffer);
    return;
  }
#define SEND_MAGIC "sendfruit"
  else if (state->helo && matchString (token, (char *)SEND_MAGIC))
  {
    sendFuitProcess (sClient, rest, fruits);
  }
#define RECV_MAGIC "recvfruit"
  else if (state->helo && matchString (token, (char *)RECV_MAGIC))
  {
    recvFruitProcess (sClient, rest, fruits);
  }
#define CHANGE_MAGIC "chngfruit"
  else if (state->helo && matchString (token, (char *)CHANGE_MAGIC))
  {
    changeFruitProcess (sClient, rest, fruits);
  }
#define HOWMANY_MAGIC "howmany"
  else if (state->helo && matchString (token, (char *)HOWMANY_MAGIC))
  {
    howmanyProcess (sClient, rest, fruits);
  }
  else if (state->helo)
  {
    printf ("%s", buffer);
    unknownResponse (sClient);
    *run = false;
    free (copyBuffer);
    return;
  }
  else
  {
    printf ("%s", buffer);
    heloResponse (sClient, NOK);
    *run = false;
    free (copyBuffer);
    return;
  }
  free (copyBuffer);
}
