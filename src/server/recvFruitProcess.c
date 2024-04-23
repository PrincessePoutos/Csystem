#include "server/recvFruitProcess.h"
#include "protopeach.h"
#include <stdio.h>

void
recvFruitProcess (int *sClient, char *buffer, struct fruit *fruits)
{
  char *count, *copyBuffer, *name;
  struct fruit *fruit;
  copyBuffer = strdup (buffer);
  count = copyBuffer;
  name = strsep (&count, " ");
#ifdef ENABLE_ERASE
  if (name == NULL || count != NULL)
#else
  if (name == NULL || count == NULL)
#endif /* ifdef ENABLE_ERASE */
  {
    unknownResponse (sClient);
    free (copyBuffer);
    return;
  }
  fruit = findFruit (name, fruits);
  if (fruit == NULL)
  {
    sendFruitResponceError (sClient, FRUITS_NOT_AVAILABLE);
    free (copyBuffer);
    return;
  }
#ifdef ENABLE_ERASE
  if (!subCount (fruit, getCountFruit (fruit)))
  {
    recvFruitResponce (sClient, getCountFruit (fruit));
  }
#else
  if (!subCount (fruit, atoi (count)))
  {
    recvFruitResponce (sClient, atoi (count));
  }
#endif /* ifdef ENABLE_ERASE */
  else
  {
    recvFruitResponceError (sClient, TOO_MUCH_FRUITS);
  }
  free (copyBuffer);
}
