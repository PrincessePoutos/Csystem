#include "protopeach.h"
#include <malloc.h>
#include <string.h>

struct fruit *
createFruit (char fname[10])
{
  struct fruit *res = (struct fruit *)malloc (sizeof (struct fruit));
  strcpy (res->name, fname);
  return res;
}

void
delFruit (struct fruit *f)
{
  free (f);
}

char *
getNameFruit (struct fruit *fruit)
{
  return fruit->name;
}
