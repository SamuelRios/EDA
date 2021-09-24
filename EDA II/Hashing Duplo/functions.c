#include <stdio.h>
#include <stdlib.h>

#include "types.h"

#define MAX(a, b) ((a > b) ? a : b)


int hash1(int key)
{
    return (key % MAXNUMREGS);
}

int hash2(int key)
{
    return (MAX((key / MAXNUMREGS) % MAXNUMREGS, 1));
}

void ini(void) {
    FILE *file;
    int cont = 0;

    if (!(file = fopen("archive.bin", "w+"))) {
        printf("Erro na criacao do arquivo.");
        exit(-1);
    }

    Record r;
    r.occupied = false;

    int i;
    for(i = 0; i < MAXNUMREGS; i++) {
        fwrite(&r, sizeof(Record), 1, file);
    }
    fclose(file); 
}

int checkNextPositions(Record* ro, FILE* file, int key, int pos, int jumps){
    for (int i = 1; i < MAXNUMREGS; i++) {
        pos += jumps;
        if (pos >= MAXNUMREGS){
            pos = pos - MAXNUMREGS;
        }
        fseek(file, pos * sizeof(Record), SEEK_SET);
        fread(ro, sizeof(Record), 1, file);
        if ((*ro).occupied) {
            if((*ro).data.key == key){
                printf("chave ja existente: %d\n", key);
                return -1;
            }
        } else {
            if((*ro).data.key != -1)
                break;
            else {
                int pos2 = pos;
                for(int j=i+1; j< MAXNUMREGS; i++){
                    pos2 += jumps;
                    if (pos2 >= MAXNUMREGS){
                        pos2 = pos2 - MAXNUMREGS;
                    }
                    fseek(file, pos2 * sizeof(Record), SEEK_SET);
                    fread(ro, sizeof(Record), 1, file);
                    if((*ro).occupied){
                        if((*ro).data.key == key){
                            printf("chave ja existente: %d\n", key);
                            return -1;
                        }
                    } else {
                        if((*ro).data.key != -1)
                            break;
                        else
                            return pos;
                    }
                }
                return pos;
            }
        }
    }
    return pos;
}

void writeRegister(FILE* file, int pos, Record* r){
    fseek(file, pos * sizeof(Record), SEEK_SET);
    if (fwrite(r, sizeof(Record), 1, file)) {
        printf("insercao com sucesso: %d\n", (*r).data.key);
    }
}

void insert(FILE *file){
    int key, pos, cont, jumps;
    Record r, ro;

    r.occupied = true;
    scanf("%d\n", &r.data.key); 
    scanf ("%[^\n]", r.data.name);
    scanf("%d", &r.data.age);
    key = r.data.key;
    pos = hash1(key);
    jumps = hash2(key);

    fseek(file, pos * sizeof(Record), SEEK_SET);
    fread(&ro, sizeof(Record), 1, file);
    if(ro.occupied){
        if(ro.data.key == key){
            printf("chave ja existente: %d\n", key);
        }else{
            pos = checkNextPositions(&ro, file, key, pos, jumps);
            if(pos != -1){
                if(!ro.occupied){
                    writeRegister(file, pos, &r);
                } else {
                    printf("insercao de chave sem sucesso - arquivo cheio: %d\n", key);
                }
            }
        }
    }else {
        if(ro.data.key == -1){
            pos = checkNextPositions(&ro, file, key, pos, jumps);
            if(pos != -1){
                pos = hash1(key);
                writeRegister(file, pos, &r);
            }
        } else {
            writeRegister(file, pos, &r);
        }
    }
}

Record* checkNextPositions2(Record* ro, FILE* file, int key, int* acessos){
    int pos = hash1(key);
    int jumps = hash2(key);
    for (int i = 1; i < MAXNUMREGS; i++) {
        pos += jumps;
        if (pos >= MAXNUMREGS){
            pos = pos - MAXNUMREGS;
        }
        fseek(file, pos * sizeof(Record), SEEK_SET);
        fread(ro, sizeof(Record), 1, file);
        (*acessos)++;
        if ((*ro).occupied) {
            if((*ro).data.key == key){
                return ro;
            }
        } else {
            if((*ro).data.key != -1)
                break;
        }
    }
    return NULL;
}

bool consult(FILE* file, int* successfullAccessSum, int* unsuccessfullAccessSum){
    int acessos = 0;
    int key, pos;
    Record r;

    scanf("%d", &key);

    pos = hash1(key);
    fseek(file, pos * sizeof(Record), SEEK_SET);
    fread(&r, sizeof(Record), 1, file);
    acessos++;
     if(r.occupied){
        if(r.data.key == key){
            printf("chave: %d\n", key);
            printf("%s\n", r.data.name);
            printf("%d\n", r.data.age);
            *successfullAccessSum += acessos;
            return true;
        } else {
            Record* foundElement = checkNextPositions2(&r, file, key, &acessos);
            if(foundElement){
                printf("chave: %d\n", key);
                printf("%s\n", r.data.name);
                printf("%d\n", r.data.age);
                *successfullAccessSum += acessos;
                return true;
            } else {
                printf("chave nao encontrada: %d\n", key);
                *unsuccessfullAccessSum += acessos;
                return false;
            }
        }
    }else{
        if(r.data.key == -1){
            Record* foundElement = checkNextPositions2(&r, file, key, &acessos);
            if(foundElement){
                printf("chave: %d\n", key);
                printf("%s\n", r.data.name);
                printf("%d\n", r.data.age);
                
                *successfullAccessSum += acessos;
                return true;
            } else {
                printf("chave nao encontrada: %d\n", key);
                *unsuccessfullAccessSum += acessos;
                return false;
            }
        } else {
            printf("chave nao encontrada: %d\n", key);
            *unsuccessfullAccessSum += acessos;
            return false;
        }
    }
}

int checkNextPositions3(int key, FILE* file, Record* r){
    int pos = hash1(key);
    for (int i = 1; i < MAXNUMREGS; i++) {
            pos += hash2(key);
            if (pos >= MAXNUMREGS) {
                pos = pos - MAXNUMREGS;
            }

            fseek(file, pos * sizeof(Record), SEEK_SET);
            fread(r, sizeof(Record), 1, file);
            if((*r).occupied){
                if((*r).data.key == key){
                    return pos;
                }
            } else {
                if((*r).data.key != -1){
                    return -1;
                }
            }
        }
        return -1;
}

void removeRegister(Record* r, FILE* file, int key, int pos){
    (*r).occupied = false;
    (*r).data.key = -1;        
    fseek(file, pos * sizeof(Record), SEEK_SET);
    if (fwrite(r, sizeof(Record), 1, file)) {
        printf("chave removida com sucesso: %d\n", key);
    } 
}

void delete(FILE * file) {
    int key, pos;
    Record r;

    scanf("%d", &key);

    pos = hash1(key);
    fseek(file, pos * sizeof(Record), SEEK_SET);
    fread(&r, sizeof(Record), 1, file);
    if (r.occupied){
        if(r.data.key == key) {
            removeRegister(&r,file, key, pos);
            return;
        } else {
            pos = checkNextPositions3(key, file, &r);
            if(pos != -1){
                removeRegister(&r,file, key, pos);
                return;
            }
        }
    } else {
        if(r.data.key == -1){
            pos = checkNextPositions3(key, file, &r);
            if(pos != -1){
                removeRegister(&r,file, key, pos);
                return;
            }
        }
    }
    printf("chave nao encontrada: %d\n", key);
}

void read(FILE * file) {
    int i;
    Record r;

    for ( i=0; i< MAXNUMREGS; i++) {
        fread(&r, sizeof(Record), 1, file);
        if(r.occupied == true) {
            printf("%d: %d %s %d\n", i, r.data.key, r.data.name, r.data.age);
        }
        else if(r.occupied == false && r.data.key == -1) {
            printf("%d: *\n", i);
        }
        else {
            printf("%d: vazio\n", i);
        }  
    }

}

void media(int successfulAccessSum, int successfulQueries, int unsuccessfulAccessSum, int unsuccessfulQueries) {
    double media;
    if(successfulQueries != 0){
        media = successfulAccessSum / (double)successfulQueries;
        printf("%.1f\n", media);
    } else
        printf("0.0\n");
    if(unsuccessfulQueries != 0){
        media = unsuccessfulAccessSum / (double)unsuccessfulQueries;
        printf("%.1f\n", media);
    } else printf("0.0\n");
}