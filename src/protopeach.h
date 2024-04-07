struct fruit
{
  char name[10];
  int count;
};

struct fruit *createFruit (char name[10], int count);
void delFruit (struct fruit *);

char *getNameFruit (struct fruit *fruit);
int getCountFruit (struct fruit *fruit);

void addCount (struct fruit *fruit, int addNumber);
int subCount (struct fruit *fruit, int subNumber);
