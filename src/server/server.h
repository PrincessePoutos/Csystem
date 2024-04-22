#ifndef server_H
#define server_H

#include <regex.h>
#include <stdbool.h>
#define BUFFER_SIZE 1024
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

struct state
{
  bool helo;
};

bool matchDomain (char *domain);
void heloResponse (int *sClient, enum response heloResponseChoise);
struct fruit *initFruits (void);
void unknownResponse (int *sClient);
void sendFruitResponceError (int *sClient, enum Errorcodes errorCode);
void sendFruitResponce (int *sClient);
void sendFuitProcess (int *sClient, char *buffer, struct fruit *fruits);

#endif /* end of include guard: server_H */
