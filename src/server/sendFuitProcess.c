#include "server/sendFuitProcess.h"

void
sendFuitProcess (int *sClient, char *buffer, struct fruit *fruits)
{
  char *count, *copyBuffer, *name;
  struct fruit *fruit;
  copyBuffer = strdup (buffer);
  count = copyBuffer;
  name = strsep (&count, " ");
  if (name == NULL || count == NULL)
  {
    unknownResponse (sClient);
    return;
  }
  fruit = findFruit (name, fruits);
  if (fruit == NULL)
  {
    sendFruitResponceError (sClient, FRUITS_NOT_AVAILABLE);
    return;
  }
  if (!addCount (fruit, atoi (count)))
  {
    sendFruitResponce (sClient);
  }
  else
  {
    sendFruitResponceError (sClient, TOO_MUCH_FRUITS);
  }
}
