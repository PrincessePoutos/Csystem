#include "server/server.h"
#include "fff.h"
#include "protopeach.h"
#include "server/socket.h"
#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>

DEFINE_FFF_GLOBALS;

char fname[10] = "peach";
Test (server, nameFruid)
{
  struct fruit *f = createFruit (fname, 3);

  cr_assert_str_eq (getNameFruit (f), "peach");

  delFruit (f);
}

Test (server, conuntFruit)
{
  struct fruit *f = createFruit (fname, 9);

  cr_assert_eq (getCountFruit (f), 9);

  delFruit (f);
}

Test (server, countFruitOtherValue)
{
  struct fruit *f = createFruit (fname, 4);

  cr_assert_eq (getCountFruit (f), 4);

  delFruit (f);
}

Test (server, addCount)
{
  struct fruit *f = createFruit (fname, 4);
  addCount (f, 2);
  cr_assert_eq (getCountFruit (f), 4 + 2);

  delFruit (f);
}

Test (server, addCountOtherValue)
{
  struct fruit *f = createFruit (fname, 4);
  addCount (f, 4);
  cr_assert_eq (getCountFruit (f), 4 + 4);

  delFruit (f);
}

Test (server, addCountNull)
{
  struct fruit *f = createFruit (fname, 4);
  addCount (f, 0);
  cr_assert_eq (getCountFruit (f), 4);

  delFruit (f);
}

Test (server, subCount)
{
  struct fruit *f = createFruit (fname, 4);
  subCount (f, 1);
  cr_assert_eq (getCountFruit (f), 4 - 1);

  delFruit (f);
}

Test (server, subCountOtherValue)
{
  struct fruit *f = createFruit (fname, 6);
  subCount (f, 4);
  cr_assert_eq (getCountFruit (f), 6 - 4);

  delFruit (f);
}

Test (server, subCountNull)
{
  struct fruit *f = createFruit (fname, 6);
  subCount (f, 0);
  cr_assert_eq (getCountFruit (f), 6);

  delFruit (f);
}

Test (server, subCountGrNumber)
{
  struct fruit *f = createFruit (fname, 6);
  cr_assert_eq (subCount (f, 10), -1);

  delFruit (f);
}

Test (server, subCountGrNumberNotChangeCounter)
{
  struct fruit *f = createFruit (fname, 6);
  subCount (f, 10);

  cr_assert_eq (getCountFruit (f), 6);

  delFruit (f);
}

Test (server, subCountNagativeNumber)
{
  struct fruit *f = createFruit (fname, 6);
  subCount (f, -10);

  cr_assert_eq (getCountFruit (f), 6);

  delFruit (f);
}

Test (serverSocker, initSocket)
{
  int *s = calloc (1, sizeof (int));
  struct sockaddr_in *addr = calloc (1, sizeof (struct sockaddr_in));

  openSocketServer (*addr, s);
  cr_assert_geq (s, 0);

  closeSocket (s);
  free (addr);
  free (s);
}

FAKE_VALUE_FUNC3 (int, accept, int, __SOCKADDR_ARG, socklen_t *);
Test (serverSocker, acceptConnection)
{
  int *s = calloc (1, sizeof (int));
  struct sockaddr_in *addr = calloc (1, sizeof (struct sockaddr));

  openSocketServer (*addr, s);

  int sClient = acceptClientConnetion (s);
  cr_assert_geq (sClient, 0);

  closeSocket (&sClient);
  closeSocket (s);
  free (addr);
  free (s);
}

Test (serverSocker, acceptConnectionTestCall)
{
  int *s = calloc (1, sizeof (int));
  struct sockaddr_in *addr = calloc (1, sizeof (struct sockaddr));

  openSocketServer (*addr, s);

  int sClient = acceptClientConnetion (s);
  cr_assert_geq (sClient, 0);
  cr_assert_eq (accept_fake.call_count, 1);

  closeSocket (&sClient);
  closeSocket (s);
  free (addr);
  free (s);
  RESET_FAKE (accept);
}

Test (serverSocker, receiveDataFromClient)
{
  int *s = calloc (1, sizeof (int));
  struct sockaddr_in *addr = calloc (1, sizeof (struct sockaddr));

  openSocketServer (*addr, s);

  int sClient = acceptClientConnetion (s);
  int bufferSize = 1024;
  char buffer[bufferSize];
  receiveDataFromClient (sClient, buffer, bufferSize);

  closeSocket (&sClient);
  closeSocket (s);
  free (addr);
  free (s);
  RESET_FAKE (accept);
}

Test (serverError, unknown) { cr_assert_eq (UNKNOWN, 0); }

Test (serverError, noNumberFruitsAvailable)
{
  cr_assert_eq (NO_NUMBER_FRUITS_AVAILABLE, 21);
}

Test (serverError, numberNotFoumdOfFruits)
{
  cr_assert_eq (NUMBER_NOT_FOUND_OF_FRUITS, 42);
}

Test (serverError, tooMuchFruits) { cr_assert_eq (TOO_MUCH_FRUITS, 51); }

Test (serverError, fruitsNotAvailable)
{
  cr_assert_eq (FRUITS_NOT_AVAILABLE, 69);
}

Test (serverError, serverRefuseHelo) { cr_assert_eq (SERVER_REFUSE_HELO, 90); }
