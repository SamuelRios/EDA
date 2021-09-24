#include<stdbool.h>

#define MAXNUMREGS 11
#define MAXSIZENAME 21

typedef struct {
    int key;
    char name[MAXSIZENAME];
    int age;
} UserData;

typedef struct {
    bool occupied;
    UserData data;
} Record;
