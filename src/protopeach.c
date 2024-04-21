#include "protopeach.h"
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

struct fruit
{
  char name[20];
  int count;
  struct fruit *nextFuit;
  struct fruit *prevFuit;
};

struct fruit *
createFirstFruit (char *fname, int fcount)
{
  struct fruit *res = (struct fruit *)calloc (1, sizeof (struct fruit));
  stpcpy (res->name, fname);
  res->count = fcount;
  return res;
}

struct fruit *
createFruit (char *name, int count, struct fruit *prevFruit)
{
  struct fruit *res = createFirstFruit (name, count);
  if (prevFruit->nextFuit == NULL)
  {
    prevFruit->nextFuit = res;
    res->prevFuit = prevFruit;
  }
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

struct fruit *
getNextFruit (struct fruit *fruit)
{
  return fruit->nextFuit;
}
struct fruit *
getPrevFruit (struct fruit *fruit)
{
  return fruit->prevFuit;
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
