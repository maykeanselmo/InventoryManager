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
    order->value = 0.0;
    order->cod = rand();
    strcpy(order->date, date);
    order->numOfTypes = numOfTypes;




    // c_disorded_database( order->orderList, numOfTypes, numOfTypes-1);
    // acabou que tive que  reescrever a função, por causa de (order->value += p->value) , pra salvar o valor automaticamente, se n teria que percorrer o arquivo dnv 
    int vet[numOfTypes];
    TProd *p;
    for(int i = 0 ; i<numOfTypes ; i++){
        vet[i] = i+1;
    }
    mix_up(vet,numOfTypes,numOfTypes-1);
    printf("\nGenerating a order...\n");
    for(int i = 0 ; i < numOfTypes; i++){
        p = prod(vet[i], i*10,"PROD", "00/00/0000",10*i);
        order->value+= p->value;
        save(p,orderFile);
    }
    free(p);
    printf("\npedido gerado com sucesso");

    return order;
}

void orderPrint(TOrder *order){
    printf("\n*****************************************");
    printf("\nORDER %d\t\t%s",order->cod,order->date);
    printf("\nTYPES:%d\t TOTAL: %4.2f",order->numOfTypes,order->value);
    printf("\n*****************************************");

}

