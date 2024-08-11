#include "Product.h"
#include "Order.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include <unistd.h>

TOrder *readOrder(FILE *in);

TOrder* order(TUser* user, int numOfTypes, char *date){
    // FILE * orderFile = user->orderFile;


    char namefile[sizeof(user->name) + 9];
    strcpy(namefile, user->name);
    strcat(namefile, "order.txt");

    TOrder* order = (TOrder*) malloc(sizeof(TOrder));
    if ((user->orderFile = fopen(namefile, "w+")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    // order->orderList = orderFile;
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
        order->value= p->value*p->qtd;
        save(p,user->orderFile);
    }
    free(p);

    printf("\npedido gerado com sucesso");

    return order;
}

TOrder *findOrderSequential(int cod, FILE *arq){
    clock_t ti,tf;

    TOrder *p = NULL;
    int i = 0;
    rewind(arq);
    ti = clock();
    while ((p = (TOrder*)readOrder(arq)) != NULL){
        i++;
        if (p->cod == cod){
            tf = clock();
            printf("\nTEMPO: %f\n",(double)(tf - ti) / CLOCKS_PER_SEC);
            printf("\nCOMPARACOES BUSCA SEQUENCIAL: %d\n",i);

            return p;
        }
        free(p);
    }
    return p;

}

void delete_record(FILE *order_file, int order_code) {

    FILE *temp_file = fopen("temp.bin", "wb");
    if (!temp_file) {
        perror("Erro ao criar arquivo temporário");
        return;
    }

    TOrder order;
    int found = 0;


    rewind(order_file);


    while (fread(&order, sizeof(TOrder), 1, order_file) == 1) {
        // Se o código não for igual ao código a ser deletado, escreva no arquivo temporário
        if (order.cod != order_code) {
            fwrite(&order, sizeof(TOrder), 1, temp_file);
        } else {
            found = 1;
        }
    }


    fclose(order_file);
    fclose(temp_file);


    if (found) {
        remove("orders.bin"); // Remove o arquivo original
        rename("temp.bin", "orders.bin"); // Renomeia o temporário para o nome do arquivo original
        printf("Registro com código %d deletado com sucesso.\n", order_code);
    } else {
        remove("temp.bin"); // Remove o arquivo temporário se não houve exclusão
        printf("Registro com código %d não encontrado.\n", order_code);
    }
}

TOrder *readOrder(FILE *in) {
    TOrder *prod = (TOrder * ) malloc(sizeof(TOrder ));
    if (0 >= fread(&prod->cod, sizeof(int), 1, in)) {
        free(prod);
        return NULL;
    }
    fread(&prod->cod, sizeof(int), 1, in);
    fread(prod->date, sizeof(char), sizeof(prod->date), in);
    fread(&prod->numOfTypes, sizeof(char), sizeof(prod->numOfTypes), in);
    fread(&prod->value, sizeof(double), 1, in);
    return prod;
}




void printOrders(FILE *out) {
    printf("\nImprimindo a base de dados...\n");

    rewind(out);
    TOrder *order;

    while ((order = readOrder(out)) != NULL) {
        orderPrint(order);
    }
    free(order);
}

void orderPrint(TOrder *order){
    printf("\n*****************************************");
    printf("\nORDER %d\t\t%s",order->cod,order->date);
    printf("\nTYPES:%d\t TOTAL: %4.2f",order->numOfTypes,order->value);
    printf("\n*****************************************");

}

