#include "matchString.h"

int
matchString (char *s1, char *s2)
{
  return ((*s1 == 0 && *s2 == 0)                 ? (1)
          : (*s1 != 0 && *s2 == 0)               ? (0)
          : (*s1 == 0 && *s2 != 0 && *s2 != '*') ? (0)
          : (*s1 == 0 && *s2 != 0 && *s2 == '*') ? (matchString (s1, s2 + 1))
          : (*s1 != 0 && *s2 != 0 && *s2 == '*')
              ? (matchString (s1, s2 + 1) || matchString (s1 + 1, s2))
          : (*s1 != 0 && *s2 != 0 && *s2 != '*')
              ? (*s1 != *s2) ? (0) : (matchString (s1 + 1, s2 + 1))
              : (matchString (s1 + 1, s2 + 1)));
}
