#ifndef FILEUTILS_H_INCLUDED
#define FILEUTILS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

void c_ordenate_database(FILE *out, int tam);

void mix_up(int *vet, int MAX, int exchanges);

void c_disorded_database(FILE *out, int tam, int exchanges);

void printBase(FILE *out);

#endif 
