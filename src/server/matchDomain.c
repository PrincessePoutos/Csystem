#include "server/matchDomain.h"
#include <pcre.h>
#include <stdio.h>
#include <string.h>

bool
matchDomain (char *domain)
{
  const char *pattern = "(?=^.{4,253}\\.?)(^((?!-)[a-zA-Z0-9-]{1,63}(?<!-)\\.)"
                        "+[a-zA-Z]{2,63}\\.?$)";

  pcre *re;
  const char *error;
  int erroffset;
  int rc;

  re = pcre_compile (pattern, 0, &error, &erroffset, NULL);
  if (re == NULL)
  {
    fprintf (stderr, "PCRE compilation failed at offset %d: %s\n", erroffset,
             error);
    return false; // Pattern compilation failed
  }

  rc = pcre_exec (re, NULL, domain, strlen (domain), 0, 0, NULL, 0);
  pcre_free (re);

  if (rc < 0)
  {
    return false; // String does not match the pattern
  }
  else
  {
    return true; // String matches the pattern
  }
}
