#ifndef PRODUCT_H_INCLUDED
#define PRODUCT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>


typedef struct Produto
{
    int cod;
    unsigned long int qtd;
    char name[30];
    char due_date[11];
    double value;
} TProd;

// Create a product
TProd *prod(int cod, int qtd, char *name, char *duedate, double value);

// save a product in a file at the current cursor position
void save(TProd *prod, FILE *out);

// read a Product at the file "In"
TProd *readProd(FILE *in);

// print a product
void printProd(TProd *prod);

int sizeProd();
int number_of_products(FILE* arq);


void c_ordenate_database(FILE *out, int tam);

void mix_up(int *vet,int MAX,int exchanges);

void c_disorded_database(FILE *out, int tam, int exchanges);


void printBase(FILE *out);

TProd *findProdSequential(int cod, FILE *arq);

void editProduct(int cod, FILE *stock);
void processEditChoice(int choice, TProd *p);
void posSearchProcess(TProd* p);
void preRemoveProcess(TProd* p, FILE *stock);
TProd *searchAndPrintProd(TProd* p, FILE* stock);




#endif
