#include "../src/protopeach.h"
#include <criterion/criterion.h>
#include <criterion/internal/assert.h>

Test (server, nameFruid)
{
  char fname[10] = "peach";
  struct fruit *f = createFruit (fname, 3);

  cr_assert_str_eq (getNameFruit (f), "peach");

  delFruit (f);
}

Test (server, conuntFruit)
{
  char fname[10] = "peach";
  struct fruit *f = createFruit (fname, 9);

  cr_assert_eq (getCountFruit (f), 9);

  delFruit (f);
}

Test (server, countFruitOtherValue)
{
  char fname[10] = "peach";
  struct fruit *f = createFruit (fname, 4);

  cr_assert_eq (getCountFruit (f), 4);

  delFruit (f);
}

Test (server, addCount)
{
  char fname[10] = "peach";
  struct fruit *f = createFruit (fname, 4);
  addCount (f, 2);
  cr_assert_eq (getCountFruit (f), 4 + 2);

  delFruit (f);
}

Test (server, addCountOtherValue)
{
  char fname[10] = "peach";
  struct fruit *f = createFruit (fname, 4);
  addCount (f, 4);
  cr_assert_eq (getCountFruit (f), 4 + 4);

  delFruit (f);
}

Test (server, addCountNull)
{
  char fname[10] = "peach";
  struct fruit *f = createFruit (fname, 4);
  addCount (f, 0);
  cr_assert_eq (getCountFruit (f), 4);

  delFruit (f);
}

Test (server, subCount)
{
  char fname[10] = "peach";
  struct fruit *f = createFruit (fname, 4);
  subCount (f, 1);
  cr_assert_eq (getCountFruit (f), 4 - 1);

  delFruit (f);
}

Test (server, subCountOtherValue)
{
  char fname[10] = "peach";
  struct fruit *f = createFruit (fname, 6);
  subCount (f, 4);
  cr_assert_eq (getCountFruit (f), 6 - 4);

  delFruit (f);
}

Test (server, subCountNull)
{
  char fname[10] = "peach";
  struct fruit *f = createFruit (fname, 6);
  subCount (f, 0);
  cr_assert_eq (getCountFruit (f), 6);

  delFruit (f);
}

Test (server, subCountGrNumber)
{
  char fname[10] = "peach";
  struct fruit *f = createFruit (fname, 6);
  cr_assert_eq (subCount (f, 10), -1);

  delFruit (f);
}

Test (server, subCountGrNumberNotChangeCounter)
{
  char fname[10] = "peach";
  struct fruit *f = createFruit (fname, 6);
  subCount (f, 10);

  cr_assert_eq (getCountFruit (f), 6);

  delFruit (f);
}
