struct fruit;

struct fruit *createFirstFruit (char *name, int count);
void createFruit (char *name, int count, struct fruit *headFruit);
void delFruit (struct fruit *);

char *getNameFruit (struct fruit *fruit);
int getCountFruit (struct fruit *fruit);
struct fruit *getNextFruit (struct fruit *fruit);
struct fruit *getPrevFruit (struct fruit *fruit);

void addCount (struct fruit *fruit, int addNumber);
int subCount (struct fruit *fruit, int subNumber);
