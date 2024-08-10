#ifndef ORDER_H_INCLUDED
#define ORDER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "Product.h"
#include "User.h"

typedef struct Orderlist
{
    TUser *user;
    int cod;
    int numOfTypes;
    char date[11];
    double value;
} TOrder;

//função vai criar um arquivo txt com o tamanho numOfTypes * tamProduto e vai retornar um código que é gerado de maneira aleatória
TOrder* order(TUser* user, int numOfTypes, char *date );
void orderPrint(TOrder *order);




#endif 
