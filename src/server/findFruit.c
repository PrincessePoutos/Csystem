#include "findFruit.h"

struct fruit *
findFruit (char *name, struct fruit *fruits)
{
  if (matchString (getNameFruit (fruits), name))
  {
    return fruits;
  }
  if (getNextFruit (fruits) == NULL)
  {
    return NULL;
  }
  return findFruit (name, getNextFruit (fruits));
}
