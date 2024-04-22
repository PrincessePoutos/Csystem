#include "protopeach.h"
#include <malloc.h>
#include <stdio.h>
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

void
createFruit (char *name, int count, struct fruit *headFruit)
{
  if (headFruit == NULL)
  {
    return;
  }
  while (headFruit->nextFuit != NULL)
  {
    headFruit = headFruit->nextFuit;
  }
  headFruit->nextFuit = createFirstFruit (name, count);
  headFruit->nextFuit->prevFuit = headFruit;
}

void
delFruit (struct fruit *f)
{
  if (f->prevFuit != NULL)
  {
    // reassign the nextFuit value of the previous fruit if there is a fruit
    // after
    if (f->prevFuit->nextFuit != NULL)
    {
      f->prevFuit->nextFuit = f->nextFuit;
    }
  }
  else
  {
    if (f->nextFuit != NULL)
    {
      f->nextFuit->prevFuit = NULL;
    }
  }

  if (f->nextFuit != NULL)
  {
    // reassign the prevFuit value of the following fruit if there is a
    // previous fruit
    if (f->nextFuit->prevFuit != NULL)
    {
      f->nextFuit->prevFuit = f->prevFuit;
    }
  }
  else
  {
    if (f->prevFuit != NULL)
    {
      f->prevFuit->nextFuit = NULL;
    }
  }
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
