#ifndef MAINPROCESS_H
#define MAINPROCESS_H

#include "protopeach.h"
#include "server/changeFruitProcess.h"
#include "server/howmanyProcess.h"
#include "server/matchDomain.h"
#include "server/matchString.h"
#include "server/recvFruitProcess.h"
#include "server/responce.h"
#include "server/sendFuitProcess.h"
#include "server/socket.h"
#include "server/state.h"
#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void mainProcess (struct state *state, int *sClient, char *buffer, bool *run,
                  struct fruit *fruits);

#endif /* end of include guard: MAINPROCESS_H */
