#ifndef FILEUTILS_H_INCLUDED
#define FILEUTILS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "../structs.h"
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>

void c_ordenate_database(FILE *out, int tam);
void mix_up(int *vet, int MAX, int exchanges);
void c_disorded_database(FILE *out, int tam, int exchanges);
void printBase(FILE *out);
TProd *buscaBinariaPorCod(FILE *arq, int cod, int inicio, int fim);
void inteleavingAndIC(FILE* stock);
void selecaoSubstE_ESCOLHEOMETODOMAYKE(FILE* stock);
double generateRandomValue();
bool checkIfFolderExist(const char *directory);
void treeWinner(TProd **func, FILE *file, int sizeInTreeOfWinners, int *auxTreeWinner);
TProd* readRegisterProduct(FILE *in);
void saveRegisterProduct(TProd *func, FILE *out);
void printSortedFile(const char *fileName);


#endif // FILEUTILS_H_INCLUDED
