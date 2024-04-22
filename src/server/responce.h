#ifndef responce_H
#define responce_H
#include "server/server.h"
#include "server/socket.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>
/*
00: unknown error
21: no more of this fruit
42: can't get the number of fruits
51: too much fruits, the server can't get more fruits
69: fruit not available
90: the server refused your helo
*/
enum Errorcodes
{
  UNKNOWN = 00,
  NO_NUMBER_FRUITS_AVAILABLE = 21,
  NUMBER_NOT_FOUND_OF_FRUITS = 42,
  TOO_MUCH_FRUITS = 51,
  FRUITS_NOT_AVAILABLE = 69,
  SERVER_REFUSE_HELO = 90,
};

enum response
{
  NOK = 0,
  OK = 1,
};

void heloResponse (int *sClient, enum response heloResponseChoise);
void unknownResponse (int *sClient);
void sendFruitResponceError (int *sClient, enum Errorcodes errorCode);
void sendFruitResponce (int *sClient);
#endif /* end of include guard: responce_H */
