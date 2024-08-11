#ifndef FILEUTILS_H_INCLUDED
#define FILEUTILS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

void c_ordenate_database(FILE *out, int tam);

void mix_up(int *vet, int MAX, int exchanges);

void c_disorded_database(FILE *out, int tam, int exchanges);

void printBase(FILE *out);
TProd *buscaBinariaPorCod(FILE *arq, int cod,int inicio, int fim);

void inteleavingAndIC(FILE* stock, void * strucure);

#endif 
