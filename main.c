#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Product.c"

int main(){
    TProd *prodTest = (TProd *)malloc(sizeof(TProd));
    prodTest->cod = 123;
    prodTest->qtd = 1;
    strcpy(prodTest->name,"TESTPRODUCT");
    strcpy(prodTest->due_date,"27/02/0505");
    prodTest->value = 0.00;
    printProd(prodTest);
}