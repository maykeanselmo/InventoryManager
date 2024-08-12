#include "../structs.h"
#include <stdlib.h>
#include <string.h>

// TOrder *readOrder(FILE *in);

void orderPrint(TOrder *order){
    printf("\n*****************************************");
    printf("\nORDER %d\t\t%s",order->cod,order->date);
    printf("\nTYPES:%d\t PAYMENTMETHOD: %s TOTAL: %4.2f",order->numOfTypes,order->paymentMethod,order->value);
    printf("\n*****************************************");

}

TOrder *readOrder(FILE *in) {
    TOrder *order = (TOrder*) malloc(sizeof(TOrder));
    if (0 >= fread(&order->cod, sizeof(int), 1, in)) {
        free(order);
        return NULL;
    }
    fread(order->date, sizeof(char), sizeof(order->date), in);
    fread(order->paymentMethod, sizeof(char), sizeof(order->paymentMethod), in);
    fread(&order->value, sizeof(double ), sizeof(order->value), in);
    return order;
}

TOrder * createOrder(int cod, int numOfTypes,char date[11],double value,char paymentMethod[20]){
    TOrder *order = (TOrder*) malloc(sizeof(TOrder));
    if (order == NULL) {
        return NULL;
    }
    order->cod = cod;
    order->numOfTypes = numOfTypes;
    strcpy(order->date, date);
    strcpy(order->paymentMethod, paymentMethod);
    order->value = value;

    return order;
}

TOrder *orderSequentialSearch(TUser *user, const char orderCode) {

    char filename[sizeof(user->name) + 10];
    strcpy(filename, user->name);
    strcat(filename, "order.dat");

    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        return NULL;
    }

    TOrder order;
    while (fread(&order, sizeof(TOrder ), 1, file)) {
        if (order.cod == orderCode) {
            fclose(file);
            TOrder *foundOrder = (TOrder *) malloc(sizeof(TOrder));
            if (foundOrder == NULL) {
                return NULL;
            }
            *foundOrder = order;
            return foundOrder;
        }
    }

    fclose(file);
    return NULL;
}

void printOneOrder(TUser *user, int order_code){
    TOrder *foundOrder;
    foundOrder = orderSequentialSearch(user, order_code);
    orderPrint(foundOrder);
    free(foundOrder);
}


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

void printOrders(FILE *out) {
    printf("\nImprimindo a base de dados...\n");
    // rewind(out);
    TOrder *order = (TOrder *) malloc(sizeof(TOrder));

    while ((order = readOrder(out)) != NULL) {
        printf("\na");
        orderPrint(order);
        free(order);
    }
}

int number_of_orders(FILE *file) {
    fseek(file, 0, SEEK_END);
    return ftell(file) / sizeUser();
}

int sizeOrder() {
    return sizeof(int) * 2        // cod + numOfTypes
           + sizeof(char) * 11    // date
           + sizeof(double)       // value
           + sizeof(char) * 20;   // paymentMethod
}

void printAllOrders(TUser *user) {

    char filename[sizeof(user->name) + 9];
    strcpy(filename, user->name);
    strcat(filename, "order.dat");
    TOrder *f;

    FILE *orderFile = fopen(filename, "rb");

    if (orderFile == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }
    for (int i = 1; i <= number_of_orders(filename); ++i) {
        fseek(filename, sizeOrder() * i, SEEK_SET);
        f = readOrder(filename);
        orderPrint(f);
    }


    fclose(orderFile);
}

void createMultipleOrdersWithRandomProducts(TUser* user, int orderCount) {
    char namefile[sizeof(user->name) + 9];
    strcpy(namefile, user->name);
    strcat(namefile, "order.dat");

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
    strcat(filename, "order.dat");

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


