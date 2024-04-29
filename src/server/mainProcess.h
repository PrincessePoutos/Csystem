#ifndef MAINPROCESS_H
#define MAINPROCESS_H

#include "matchString.h"
#include "protopeach.h"
#include "server/changeFruitProcess.h"
#include "server/howmanyProcess.h"
#include "server/matchDomain.h"
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

void mainProcess (int *sClient, struct fruit *fruits);

#endif /* end of include guard: MAINPROCESS_H */
