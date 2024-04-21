struct fruit;

struct fruit *createFirstFruit (char *name, int count);
struct fruit *createFruit (char *name, int count, struct fruit *prevFruit);
void delFruit (struct fruit *);

char *getNameFruit (struct fruit *fruit);
int getCountFruit (struct fruit *fruit);
struct fruit *getNextFruit (struct fruit *fruit);
struct fruit *getPrevFruit (struct fruit *fruit);

void addCount (struct fruit *fruit, int addNumber);
int subCount (struct fruit *fruit, int subNumber);
