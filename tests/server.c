#include "fff.h"
#include "protopeach.h"
#include "server/socket.h"
#include <criterion/criterion.h>

DEFINE_FFF_GLOBALS;

char fname[10] = "peach";
Test (server, nameFruid)
{
  struct fruit *f = createFruit (fname, 3);

  cr_assert_str_eq (getNameFruit (f), "peach");

  delFruit (f);
}

Test (server, conuntFruit)
{
  struct fruit *f = createFruit (fname, 9);

  cr_assert_eq (getCountFruit (f), 9);

  delFruit (f);
}

Test (server, countFruitOtherValue)
{
  struct fruit *f = createFruit (fname, 4);

  cr_assert_eq (getCountFruit (f), 4);

  delFruit (f);
}

Test (server, addCount)
{
  struct fruit *f = createFruit (fname, 4);
  addCount (f, 2);
  cr_assert_eq (getCountFruit (f), 4 + 2);

  delFruit (f);
}

Test (server, addCountOtherValue)
{
  struct fruit *f = createFruit (fname, 4);
  addCount (f, 4);
  cr_assert_eq (getCountFruit (f), 4 + 4);

  delFruit (f);
}

Test (server, addCountNull)
{
  struct fruit *f = createFruit (fname, 4);
  addCount (f, 0);
  cr_assert_eq (getCountFruit (f), 4);

  delFruit (f);
}

Test (server, subCount)
{
  struct fruit *f = createFruit (fname, 4);
  subCount (f, 1);
  cr_assert_eq (getCountFruit (f), 4 - 1);

  delFruit (f);
}

Test (server, subCountOtherValue)
{
  struct fruit *f = createFruit (fname, 6);
  subCount (f, 4);
  cr_assert_eq (getCountFruit (f), 6 - 4);

  delFruit (f);
}

Test (server, subCountNull)
{
  struct fruit *f = createFruit (fname, 6);
  subCount (f, 0);
  cr_assert_eq (getCountFruit (f), 6);

  delFruit (f);
}

Test (server, subCountGrNumber)
{
  struct fruit *f = createFruit (fname, 6);
  cr_assert_eq (subCount (f, 10), -1);

  delFruit (f);
}

Test (server, subCountGrNumberNotChangeCounter)
{
  struct fruit *f = createFruit (fname, 6);
  subCount (f, 10);

  cr_assert_eq (getCountFruit (f), 6);

  delFruit (f);
}

Test (server, subCountNagativeNumber)
{
  struct fruit *f = createFruit (fname, 6);
  subCount (f, -10);

  cr_assert_eq (getCountFruit (f), 6);

  delFruit (f);
}
