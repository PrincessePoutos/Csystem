#include "server/changeFruitProcess.h"
#include "protopeach.h"

void
changeFruitProcess (int *sClient, char *buffer, struct fruit *fruits)
{
  char *newName, *copyBuffer, *name;
  struct fruit *fruit;
  copyBuffer = strdup (buffer);
  newName = copyBuffer;
  name = strsep (&newName, " ");
  if (name == NULL || newName == NULL)
  {
    unknownResponse (sClient);
    free (copyBuffer);
    return;
  }
  fruit = findFruit (name, fruits);
  if (fruit == NULL)
  {
    changeFruitResponceError (sClient, FRUITS_NOT_AVAILABLE);
    free (copyBuffer);
    return;
  }
  setNameFruit (fruit, newName);
  changeFruitResponce (sClient, getNameFruit (fruit));
  free (copyBuffer);
}
