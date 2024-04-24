#include "server/recvFruitProcess.h"
#include "protopeach.h"
#include <stdio.h>

void
recvFruitProcess (int *sClient, char *buffer, struct fruit *fruits)
{
  char *charCount, *copyBuffer, *name;
  struct fruit *fruit;
#ifdef ENABLE_ERASE
  int count;
  size_t line_pos;
#endif /* ifdef ENABLE_ERASE */
  copyBuffer = strdup (buffer);
  charCount = copyBuffer;
  name = strsep (&charCount, " ");
#ifdef ENABLE_ERASE
  line_pos = strcspn (name, "\n");
  name[line_pos] = '\0';
  if (name == NULL || charCount != NULL)
#else
  if (name == NULL || charCount == NULL)
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
  count = getCountFruit (fruit);
  if (!subCount (fruit, count))
  {
    recvFruitResponce (sClient, count);
  }
#else
  if (!subCount (fruit, atoi (charCount)))
  {
    recvFruitResponce (sClient, atoi (charCount));
  }
#endif /* ifdef ENABLE_ERASE */
  else
  {
    recvFruitResponceError (sClient, TOO_MUCH_FRUITS);
  }
  free (copyBuffer);
}
