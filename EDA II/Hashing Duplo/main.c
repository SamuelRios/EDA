#include<stdio.h>
#include<stdlib.h>
#include <sys/stat.h>
 
#include "functions.c"

int checkIfFileExists(const char* filename) {
    struct stat buffer;
    int exist = stat(filename,&buffer);
    if(exist == 0)
        return 1;
    else  
        return 0;
}


int main() {

    FILE *f;
    char op;

    int successfulAccessSum = 0;
    int unsuccessfulAccessSum = 0;
    int successfulQueries = 0;
    int unsuccessfulQueries = 0;

    if(!checkIfFileExists("archive.bin"))
    {
      //printf("file does not exists\n");
      ini();
    }
      //printf("file exists\n");


    do {
    
    f = fopen("archive.bin","r+");
    if(!f) {
        printf("Erro na abertura do arquivo!\n");
        exit(-1);
    }

    scanf("%c", &op);

    switch(op) {
        case 'e':
          op = 'e';
        break;
        case 'i':
            insert(f);
        break;
        case 'c':
          if(consult(f, &successfulAccessSum, &unsuccessfulAccessSum))
            successfulQueries++;
          else
            unsuccessfulQueries++;
        break;
        case 'r':
          delete(f);
        break;
        case 'p':
          read(f);
        break;
        case 'm':
          media(
            successfulAccessSum,
            successfulQueries,
            unsuccessfulAccessSum, 
            unsuccessfulQueries
          );
        break;
      }

      fclose(f);
    } while(op != 'e');

    
}