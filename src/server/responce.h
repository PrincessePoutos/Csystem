#ifndef responce_H
#define responce_H
#include "server/server.h"
#include "server/socket.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>

void heloResponse (int *sClient, enum response heloResponseChoise);
void unknownResponse (int *sClient);
void sendFruitResponceError (int *sClient, enum Errorcodes errorCode);
void sendFruitResponce (int *sClient);
#endif /* end of include guard: responce_H */
