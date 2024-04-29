#include "server/howmanyProcess.h"
#include "protopeach.h"
#include <stdio.h>

void
howmanyProcess (int *sClient, char *name, struct fruit *fruits)
{
  int count;
  struct fruit *fruit;
  size_t line_pos = strcspn (name, "\n");
  name[line_pos] = '\0';
  fruit = findFruit (name, fruits);
  if (fruit == NULL)
  {
    howmanyResponceError (sClient, FRUITS_NOT_AVAILABLE);
    return;
  }
  count = getCountFruit (fruit);
  if (count == 0)
  {
    howmanyResponceError (sClient, NO_NUMBER_FRUITS_AVAILABLE);
  }
  howmanyResponce (sClient, count);
}
