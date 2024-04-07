#include "protopeach.h"
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

struct fruit
{
  char name[10];
  int count;
};

struct fruit *
createFruit (char fname[10], int fcount)
{
  struct fruit *res = (struct fruit *)malloc (sizeof (struct fruit));
  stpcpy (res->name, fname);
  res->count = fcount;
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

int
getCountFruit (struct fruit *fruit)
{
  return fruit->count;
}

void
addCount (struct fruit *fruit, int addNumber)
{
  fruit->count += addNumber;
}

int
subCount (struct fruit *fruit, int subNumber)
{
  fruit->count -= subNumber;
  if (fruit->count < 0 || subNumber < 0)
  {
    fruit->count += subNumber;
    return -1;
  }
  return 0;
}
