#include "../structs.h"
#include <stdlib.h>
#include <string.h>


int generateRandomProductCode() {
    return rand() % 1000;
}
void generateRandomPaymentMethod(char* paymentMethod) {
    const char* methods[] = {"Credit Card", "Debit Card", "PayPal", "Cash"};
    strcpy(paymentMethod, methods[rand() % 4]);
}

void generateRandomDueDate(char* due_date) {
    sprintf(due_date, "%02d/%02d/%04d", rand() % 31 + 1, rand() % 12 + 1, rand() % 5 + 2023);
}


TProd* createRandomProduct() {
    TProd* product = (TProd*)malloc(sizeof(TProd));
    product->cod = generateRandomProductCode();
    product->qtd = rand() % 100 + 1;
    snprintf(product->name, sizeof(product->name), "Product%d", product->cod); // Nome do produto
    generateRandomDueDate(product->due_date); // Gera data de validade aleatória
    product->value = (double)(rand() % 1000) / 10; // Valor aleatório de 0 a 99.9

    return product;
}
void freeOrder(TOrder* order) {
    for (int i = 0; i < order->numOfTypes; i++) {
        free(order->products[i]);
    }
    free(order);
}