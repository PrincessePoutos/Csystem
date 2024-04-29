#include "client/client.h"
#include "matchString.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define HISTORY_ENV_NAME "CNETWORKING_HISTORY"
#define DEFAULT_HISTORY_FILE ".Cnetworking_history"

void
initHistory (void)
{
  getVarEnv ((char *)HISTORY_ENV_NAME);
  getVarEnv ((char *)"HOME");
}

char *
getVarEnv (char *name)
{
  char **env_ptr = environ;
  char *varName, *value, *copyEnv;

  while (*env_ptr != NULL)
  {
    copyEnv = strdup (*env_ptr);
    value = copyEnv;
    varName = strsep (&value, "=");
    if (varName == NULL || value == NULL)
    {
      free (copyEnv);
      continue;
    }
    if (matchString (varName, name))
    {
      printf ("%s\n", *env_ptr);
    }
    env_ptr++;
    free (copyEnv);
  }
  return NULL;
}

int
main (int argc, char *argv[])
{
  char *input;
  initHistory ();

  using_history ();
  // read_history (HISTORY_FILE);

  while (1)
  {
    input = readline (">> ");

    if (input == NULL)
    {
      printf ("\nAu revoir !\n");
      break;
    }

    if (strlen (input) == 0)
    {
      continue;
    }

    add_history (input);
    // write_history (HISTORY_FILE);

    printf ("Commande saisie : %s\n", input);

    free (input);
  }

  return 0;
}
