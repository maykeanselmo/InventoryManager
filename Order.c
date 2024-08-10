#include "Product.h"
#include "Order.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdarg.h>

TOrder* order(int numOfTypes, char *date){
    FILE * orderFile;
    TOrder* order = (TOrder*) malloc(sizeof(TOrder));
    if ((orderFile = fopen("order.txt", "w+")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    order->orderList = orderFile;
    
    order->cod = rand();
    strcpy(order->date, date);
    order->numOfTypes = numOfTypes;


    c_disorded_database( order->orderList, numOfTypes, numOfTypes-1);
    printf("\npedido gerado com sucesso");

    return order;
}

void orderPrint(TOrder *order){
    printf("\n*****************************************");
    printf("\nORDER %d\t\t%s",order->cod,order->date);
    printf("\nTYPES:%d\t TOTAL: %4.2f",order->numOfTypes,order->value);
    printf("\n*****************************************");

}

