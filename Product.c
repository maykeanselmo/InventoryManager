#include "Product.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>


TProd *prod(int cod, int qtd, char *name, char *duedate, double value){
    TProd *prod = (TProd * ) malloc(sizeof(TProd));
    if (prod) memset(prod, 0, sizeof(TProd));
    prod->cod = cod;
    prod->qtd = qtd;
    strcpy(prod->name, name);
    strcpy(prod->due_date, duedate);
    prod->value = value;
    return prod;
}

// writes a product to the file at the current cursor position
void save(TProd *prod, FILE *out){
    fwrite(&prod->cod, sizeof(int), 1, out);
    fwrite(&prod->qtd, sizeof(int), 1, out);
    fwrite(prod->name, sizeof(char), sizeof(prod->name), out);
    fwrite(prod->due_date, sizeof(char), sizeof(prod->due_date), out);
    fwrite(&prod->value, sizeof(double),1,out);
}

TProd *read(FILE *in){
    TProd *prod = (TProd * ) malloc(sizeof(TProd));
    if (0 >= fread(&prod->cod, sizeof(int), 1, in)) {
        free(prod);
        return NULL;
    }
    fread(&prod->qtd, sizeof(int), 1, in);
    fread(prod->name, sizeof(char), sizeof(prod->name), in);
    fread(prod->due_date, sizeof(char), sizeof(prod->due_date), in);
    fread(&prod->value, sizeof(double), 1, in);
    return prod;
}

void printProd(TProd *prod){
    printf("\n---------------------------------------");
    printf("\nPRODUCT\t\t- %d -\n\t\t",prod->cod);
    printf("\nNAME:\t%s",prod->name);
    printf("\nVALUE:\t%4.2f",prod->value);
    printf("\nQUANTITY:\t%ld",prod->qtd);
    printf("\n---------------------------------------\n");
}

int size(){
    return sizeof(int) * 2  //cod
        + sizeof(char) * 30 //name
        + sizeof(char) * 11 //due_date
        + sizeof(double); //value
}

int number_of_products(FILE* arq){
    fseek(arq, 0, SEEK_END);
    int tam = trunc(ftell(arq) / size());
    return tam;
}

void c_ordenate_database(FILE *out, int tam){
    int vet[tam];
    TProd *p;
    for(int i = 0 ; i<tam ; i++){
        vet[i] = i+1;
    }
    printf("\nGenerating a ordenated database...\n");
    for(int i = 0 ; i < tam; i++){
        //rever como quantidade do produto é gerada! 
        p = prod(vet[i],i*10,"PROD", "00/00/0000",10*i);
        save(p,out);
    }
    free(p);
}

//date mixup
void mix_up(int *vet,int MAX,int exchanges){
    srand(time(NULL));
    for (int i = 0; i <= exchanges; i++) {
        int j = rand() % (MAX-1);
        int k = rand() % (MAX-1);
        int tmp = vet[j];
        vet[j] = vet[k];
        vet[k] = tmp;
    }
}

void c_disorded_database(FILE *out, int tam, int exchanges){
    int vet[tam];
    TProd *p;
    for(int i = 0 ; i<tam ; i++){
        vet[i] = i+1;
    }
    mix_up(vet,tam,exchanges);
    printf("\nGenerating a disorded database...\n");
    for(int i = 0 ; i < tam; i++){
        p = prod(vet[i], i*10,"PROD", "00/00/0000",10*i);
        save(p,out);
    }
    free(p);
}

void printBase(FILE *out){
printf("\nPrinting database...\n");
    rewind(out);
    TProd *p;
    while ((p = read(out)) != NULL)
        printProd(p);
    free(p);
}










