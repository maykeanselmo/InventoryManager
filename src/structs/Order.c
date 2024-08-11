#include "../structs.h"
#include <stdlib.h>
#include <string.h>

TOrder *readOrder(FILE *in);

TOrder* createOrderWithRandomProducts(int numOfTypes, const char* date) {
    TOrder *order = (TOrder *) malloc(sizeof(TOrder));
    order->cod = rand();
    order->numOfTypes = numOfTypes;
    strcpy(order->date, date);
    order->value = 0.0;
    generateRandomPaymentMethod(order->paymentMethod);

    for (int i = 0; i < numOfTypes; i++) {
        TProd *product = createRandomProduct();
        order->products[i] = product;
        order->value += product->value * product->qtd;
    }
    return  order;
}

void printAllOrders(const char* filename) {
    FILE *file = fopen(filename, "rb"); // Abre o arquivo para leitura binária
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    TOrder order;
    while (fread(&order, sizeof(TOrder), 1, file) == 1) { // Lê os pedidos um por um
        orderPrint(&order);

        for (int i = 0; i < order.numOfTypes; i++) {
            TProd* product = order.products[i];
            printf("  Product Code: %d, Name: %s, Quantity: %lu, Value: %.2f, Due Date: %s\n",
                   product->cod, product->name, product->qtd, product->value, product->due_date);
        }
        printf("\n*****************************************");
    }

    fclose(file);
}
void createMultipleOrdersWithRandomProducts(TUser* user, int orderCount) {
    char namefile[sizeof(user->name) + 9];
    strcpy(namefile, user->name);
    strcat(namefile, "order.txt");

    FILE* orderFile = fopen(namefile, "wb");
    if (orderFile == NULL) {
        printf("Erro ao abrir o arquivo para gravação.\n");
        return;
    }

    for (int i = 0; i < orderCount; i++) {
        int numOfTypes = rand() % 5 + 1;
        char date[11];
        sprintf(date, "%02d/%02d/%04d", rand() % 31 + 1, rand() % 12 + 1, rand() % 5 + 2023);

        TOrder* order = createOrderWithRandomProducts(numOfTypes, date);

        fwrite(order, sizeof(TOrder), 1, orderFile);

        printf("Ordem %d: Código: %d, Data: %s, Valor: %.2f, Número de Tipos: %d\n",
               i + 1, order->cod, order->date, order->value, order->numOfTypes);

        for (int j = 0; j < order->numOfTypes; j++) {
            free(order->products[j]);
        }
        free(order);
    }

    fclose(orderFile);
}

void deleteOrder(TUser *user, int orderCode) {

    char filename[sizeof(user->name) + 9];
    strcpy(filename, user->name);
    strcat(filename, "order.txt");

    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    FILE *tempFile = fopen("temp.dat", "wb");
    if (tempFile == NULL) {
        printf("Erro ao abrir o arquivo temporário para escrita.\n");
        fclose(file);
        return;
    }

    TOrder order;
    int found = 0;

    while (fread(&order, sizeof(TOrder ), 1, file)) {
        if (order.cod != orderCode) {
            fwrite(&user, sizeof(TUser), 1, tempFile);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove(filename);
        rename("temp.dat", filename);
        printf("Order de codigo %d foi deletado.\n", orderCode);
    } else {
        // Se o CPF não foi encontrado, remova o arquivo temporário
        remove("temp.dat");
        printf("Order de codigo %d  não foi encontrado.\n", orderCode);
    }
}


void orderPrint(TOrder *order){
    printf("\n*****************************************");
    printf("\nORDER %d\t\t%s",order->cod,order->date);
    printf("\nTYPES:%d\t PAYMENTMETHOD: %s TOTAL: %4.2f",order->numOfTypes,order->paymentMethod,order->value);
    printf("\n*****************************************");

}
