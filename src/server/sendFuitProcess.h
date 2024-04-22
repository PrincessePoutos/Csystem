#ifndef sendFruitProcess_H
#define sendFruitProcess_H
#include "protopeach.h"
#include "server/findFruit.h"
#include "server/responce.h"
#include <string.h>

void sendFuitProcess (int *sClient, char *buffer, struct fruit *fruits);
#endif /* end of include guard: sendFruitProcess_H */
