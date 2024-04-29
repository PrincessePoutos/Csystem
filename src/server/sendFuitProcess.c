#include "server/sendFuitProcess.h"

void
sendFuitProcess (int *sClient, char *buffer, struct fruit *fruits)
{
#ifdef ENABLE_ERASE
  int diffCount;
#endif /* ifdef ENABLE_ERASE */
  char *count, *copyBuffer, *name;
  struct fruit *fruit;
  copyBuffer = strdup (buffer);
  count = copyBuffer;
  name = strsep (&count, " ");
  if (name == NULL || count == NULL)
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
  diffCount = atoi (count) - getCountFruit (fruit);
  if (!addCount (fruit, diffCount))
#else
  if (!addCount (fruit, atoi (count)))
#endif /* ifdef ENABLE_ERASE */
  {
    sendFruitResponce (sClient);
  }
  else
  {
    sendFruitResponceError (sClient, TOO_MUCH_FRUITS);
  }
  free (copyBuffer);
}
