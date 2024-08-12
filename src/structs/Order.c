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

// void printAllOrders(TUser* user) {
//     // Cria o nome do arquivo a partir do nome do usuário
//     char namefile[sizeof(user->name) + 10]; // sizeof(user->name) + 9 for "order.dat" + 1 for null terminator
//     strcpy(namefile, user->name);
//     strcat(namefile, "order.dat");

//     // Abre o arquivo para leitura binária
//     FILE *file = fopen(namefile, "rb");
//     if (file == NULL) {
//         printf("Erro ao abrir o arquivo %s para leitura.\n", namefile);
//         return;
//     }

//     printf("\nImprimindo todos os pedidos para o usuário %s...\n", user->name);

//     // Reposiciona o ponteiro do arquivo para o início
//     rewind(file);

//     // Lê e imprime todos os pedidos
//     TOrder order;
//     while (fread(&order, sizeof(TOrder), 1, file) == 1) {
//         orderPrint(&order);

//         // Imprime os produtos associados ao pedido
//         for (int i = 0; i < order.numOfTypes; i++) {
//             TProd* product = order.products[i];
//             printf("  Código do Produto: %d, Nome: %s, Quantidade: %lu, Valor: %.2f, Data de Validade: %s\n",
//                    product->cod, product->name, product->qtd, product->value, product->due_date);
//         }
//         printf("\n*****************************************\n");
//     }

//     // Fecha o arquivo
//     fclose(file);
// }


// void printAllOrders(TUser* user) {

//     printf("\na");
//     char namefile[sizeof(user->name) + 9];
//     strcpy(namefile, user->name);
//     strcat(namefile, "order.dat");
//     FILE *file = fopen(namefile, "rb"); // Abre o arquivo para leitura binária


//       printf("\nImprimindo a base de dados...\n");

//     rewind(file);
//     TOrder* o = (TOrder*)malloc(sizeof(TOrder));

//     while ((o = readOrder(file)) != NULL)
//         orderPrint(o);

//     free(o);



   

//     fclose(file);
//     }

void printAllOrders(TUser* user) {
    printf("\na");
    
    // Usando strlen em vez de sizeof
    char namefile[strlen(user->name) + 10]; // +10 para "order.dat" e '\0'
    
    strcpy(namefile, user->name);
    strcat(namefile, "order.dat");
    
    FILE *file = fopen(namefile, "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", namefile);
        return;
    }

    printf("\nImprimindo a base de dados...\n");

    // Rewind é desnecessário aqui

    TOrder* o = (TOrder*)malloc(sizeof(TOrder));

    while ((o = readOrder(file)) != NULL) {
        orderPrint(o);
    }

    free(o);
    fclose(file);
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


