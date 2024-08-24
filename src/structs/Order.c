#include "../structs.h"
#include <stdlib.h>
#include <string.h>


void orderPrint(TOrder *order) {
    printf("\n*****************************************\n");
    printf("ORDER %d             %s\n", order->cod, order->date);
    printf("TYPES:%d         PAYMENTMETHOD: %s\n", order->numOfTypes, order->paymentMethod);
    printf("\nTOTAL: %.2f\n", order->value);
    printf("*****************************************\n");

    TProdNode *current = order->products;
    while (current != NULL) {
        printf("Product ID: %d, Name: %s, Quantity: %d, Price: %.2f\n",
               current->product->cod, current->product->name,
               current->product->qtd, current->product->value);
        current = current->next;
    }
    printf("*****************************************\n");
}


TOrder *readOrder(FILE *in) {
    TOrder *order = (TOrder*) malloc(sizeof(TOrder));

    fread(&order->cod, sizeof(int), 1, in);
    fread(&order->numOfTypes, sizeof(int), 1, in);
    fread(order->date, sizeof(char), sizeof(order->date), in);
    fread(order->paymentMethod, sizeof(char), sizeof(order->paymentMethod), in);
    fread(&order->value, sizeof(double), 1, in);

    order->products = NULL; 

    return order;
}

TOrder *readOrderWithProd(FILE *in) {
    TOrder *order = readOrder(in);
    if (order == NULL) {
        return NULL; 
    }
    
    TProdNode *currentNode;
    TProdNode *headNode;

    for (int i = 0; i<order->numOfTypes ; i++){
        TProd *product = (TProd*)malloc(sizeof(TProd));
        if(product == NULL){
            freeProductList(headNode);
            free(order);
        }

        fread(product,sizeof(TProd),1,in);
        TProdNode *newNode = criaNo(product);
        if(newNode == NULL){
            freeProductList(newNode);
            free(order);
            return NULL;
        }
        if (headNode == NULL){
            headNode = newNode;
        }else{
            currentNode->next = newNode;
        }
        order->products = headNode;
    }
    return order;
}




TOrder* createOrderWithRandomProducts(int numOfTypes, const char* date) {
    TOrder *order = (TOrder *) malloc(sizeof(TOrder));
    if (order == NULL) {
        printf("Erro ao alocar memória para o pedido.\n");
        return NULL;
    }

    order->cod = rand();
    order->numOfTypes = numOfTypes;
    strcpy(order->date, date);
    order->value = 0.0;
    generateRandomPaymentMethod(order->paymentMethod);

    order->products = NULL;
    TProdNode *lastnode = NULL;
    for (int i = 0; i < numOfTypes; i++) {
        TProd *product = createRandomProduct();
        TProdNode *newNode = (TProdNode *)malloc(sizeof(TProdNode));
        if(newNode == NULL){
            freeProductList(newNode);
            free(product);
            free(order);
            return NULL;
        }
        newNode->product = product;
        newNode->next = NULL;
        if(order->products == NULL){
            order->products = newNode;
        }else {
            lastnode->next = newNode;
        }
        lastnode = newNode;
        order->value += product->value * product->qtd;
    }
    printf("\norder %d created successfully...", order->cod);
    return order;
}

int qtdOrderInFile(FILE *file){
    fseek(file, 0, SEEK_END);
    rewind(file);
    return (int)(ftell(file) / sizeof(TOrder));
}

void printAllOrders(TUser* user) {
    FILE *file = fopen(charUserOrderName(user->name), "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    printf("\nPrinting %s's orders...\n", user->name);
    
    TOrder order;
    while (fread(&order.cod, sizeof(int), 1, file) == 1) {
        fread(&order.numOfTypes, sizeof(int), 1, file);
        fread(order.date, sizeof(char), sizeof(order.date), file);
        fread(order.paymentMethod, sizeof(char), sizeof(order.paymentMethod), file);
        fread(&order.value, sizeof(double), 1, file);

        order.products = NULL;
        TProdNode *lastNode = NULL;

        if (order.numOfTypes > 0) {
            for (int i = 0; i < order.numOfTypes; i++) {
                TProd *product = (TProd *)malloc(sizeof(TProd));
                if (product == NULL) {
                    printf("Erro ao alocar memória para o produto.\n");
                    fclose(file);
                    return;
                }

                fread(product, sizeof(TProd), 1, file);

                TProdNode *newNode = (TProdNode *)malloc(sizeof(TProdNode));
                if (newNode == NULL) {
                    printf("Erro ao alocar memória para o nó da lista de produtos.\n");
                    free(product);
                    fclose(file);
                    return;
                }

                newNode->product = product;
                newNode->next = NULL;

                if (order.products == NULL) {
                    order.products = newNode;
                } else {
                    lastNode->next = newNode;
                }
                lastNode = newNode;
            }
        }

        orderPrint(&order);

        TProdNode *current = order.products;
        while (current != NULL) {
            TProdNode *toFree = current;
            current = current->next;
            free(toFree->product); 
            free(toFree);
        }
        order.products = NULL; 

    }

    fclose(file);
}
 

int orderSize(){
     return sizeof(int) * 2 
        + sizeof(char) * 11 
        + sizeof(char) * 20 
        + sizeof(double); 
}

void saveOrder(TOrder* order, const char *filename){
    FILE *orderfile = fopen(filename, "wb"); 
    if (orderfile == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fwrite(&order->cod, sizeof(int), 1, orderfile);
    fwrite(&order->numOfTypes, sizeof(int), 1, orderfile);
    fwrite(order->date, sizeof(char), sizeof(order->date), orderfile);
    fwrite(order->paymentMethod, sizeof(char), sizeof(order->paymentMethod), orderfile);
    fwrite(&order->value, sizeof(double),1,orderfile);
    
}
void saveOrderInUserFile(TOrder* order, TUser* user) {
    char *filename = charUserOrderName(user->name);
    FILE *userOrderfile = fopen(filename, "ab"); // "ab" para adicionar no final do arquivo
    if (userOrderfile == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fwrite(&order->cod, sizeof(int), 1, userOrderfile);
    fwrite(&order->numOfTypes, sizeof(int), 1, userOrderfile);
    fwrite(order->date, sizeof(char), sizeof(order->date), userOrderfile);
    fwrite(order->paymentMethod, sizeof(char), sizeof(order->paymentMethod), userOrderfile);
    fwrite(&order->value, sizeof(double), 1, userOrderfile);

    TProdNode *current = order->products;
    while (current != NULL) {
        fwrite(current->product, sizeof(TProd), 1, userOrderfile);
        current = current->next;
    }

    fclose(userOrderfile);
}




void createMultipleOrdersWithRandomProducts(TUser* user, int orderCount) {
    char namefile[strlen(user->name) + 10];
    strcpy(namefile, user->name);
    strcat(namefile, "order.dat");

    FILE* orderFile = fopen(namefile, "ab");
    if (orderFile == NULL) {
        printf("Erro ao abrir o arquivo para gravação.\n");
        return;
    }

    for (int i = 0; i < orderCount; i++) {
        int numOfTypes = rand() % 5 + 1;  
        char date[11];
        sprintf(date, "%02d/%02d/%04d", rand() % 31 + 1, rand() % 12 + 1, rand() % 5 + 2023);

        TOrder* order = createOrderWithRandomProducts(numOfTypes, date);
        if (order == NULL) {
            printf("Erro ao criar a ordem %d.\n", i + 1);
            continue; 
        }

        saveOrderInUserFile(order,user);
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

    while (fread(&order.cod, sizeof(int), 1, file) == 1) {
        fread(&order.numOfTypes, sizeof(int), 1, file);
        fread(order.date, sizeof(char), sizeof(order.date), file);
        fread(order.paymentMethod, sizeof(char), sizeof(order.paymentMethod), file);
        fread(&order.value, sizeof(double), 1, file);

        TProdNode *head = NULL;
        TProdNode *tail = NULL;
        for (int i = 0; i < order.numOfTypes; i++) {
            TProd *product = (TProd *)malloc(sizeof(TProd));
            if (product == NULL) {
                printf("Erro ao alocar memória para produto.\n");
                fclose(file);
                fclose(tempFile);
                return;
            }
            fread(product, sizeof(TProd), 1, file);

            TProdNode *node = (TProdNode *)malloc(sizeof(TProdNode));
            if (node == NULL) {
                printf("Erro ao alocar memória para nó da lista.\n");
                fclose(file);
                fclose(tempFile);
                return;
            }
            node->product = product;
            node->next = NULL;

            if (head == NULL) {
                head = node;
                tail = node;
            } else {
                tail->next = node;
                tail = node;
            }
        }

        if (order.cod != orderCode) {
            fwrite(&order.cod, sizeof(int), 1, tempFile);
            fwrite(&order.numOfTypes, sizeof(int), 1, tempFile);
            fwrite(order.date, sizeof(char), sizeof(order.date), tempFile);
            fwrite(order.paymentMethod, sizeof(char), sizeof(order.paymentMethod), tempFile);
            fwrite(&order.value, sizeof(double), 1, tempFile);

            TProdNode *current = head;
            while (current != NULL) {
                fwrite(current->product, sizeof(TProd), 1, tempFile);
                TProdNode *next = current->next;
                free(current->product);
                free(current);
                current = next;
            }
        } else {
            found = 1;
            TProdNode *current = head;
            while (current != NULL) {
                TProdNode *next = current->next;
                free(current->product);
                free(current);
                current = next;
            }
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove(filename);
        rename("temp.dat", filename);
        printf("Order de codigo %d foi deletado.\n", orderCode);
    } else {
        remove("temp.dat");
        printf("Order de codigo %d não foi encontrado.\n", orderCode);
    }
}

