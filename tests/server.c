#include "../src/protopeach.h"
#include <criterion/criterion.h>
#include <criterion/internal/assert.h>

Test (server, fruitInit)
{
  struct fruit *f = createFruit ("peach");

  cr_assert_null (f);

  delFruit (f);
}

Test (server, nameFruid)
{
  struct fruit *f = createFruit ("peach");

  cr_assert_eq (getNameFruit (f), "peach");

  delFruit (f);
}
