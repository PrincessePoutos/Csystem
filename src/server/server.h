#ifndef server_H
#define server_H

#include <regex.h>
#include <stdbool.h>
#define BUFFER_SIZE 1024
struct state
{
  bool helo;
};

bool matchDomain (char *domain);

#endif /* end of include guard: server_H */
