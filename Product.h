#ifndef PRODUCT_H_INCLUDED
#define PRODUCT_H_INCLUDED

#include <stdio.h>

typedef struct Produto
{
    int cod;
    char name[30];
    char due_date[11];
    double value;
} TProd;

// Create a product
TProd *prod(int cod, char *name, char *duedate, double value);

// save a product in a file at the current cursor position
void save(TProd *prod, FILE *out);

// read a Product at the file "In"
TProd *read(FILE *in);

// print a product
void print(TProd *prod);

int size();
int number_of_products(FILE* arq);


void c_ordenate_database(FILE *out, int tam);

void mix_up(int *vet,int MAX,int exchanges);

void c_disorded_database(FILE *out, int tam, int exchanges);


void printBase(FILE *out);


#endif
