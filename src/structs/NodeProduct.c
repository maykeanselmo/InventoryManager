#include "../structs.h"
#include <stdio.h>
#include <stdlib.h>

TProdNode* criaNo(TProd *product){
    TProdNode* newNode = (TProdNode*)malloc(sizeof(TProdNode));
    newNode->product = product;
    newNode->next = NULL;

    return newNode;
}

void insertProduct(TProdNode **head, TProd *product){
    TProdNode* newNode = criaNo(product);

    if(head == NULL){
        *head = newNode;
    }else {
        TProdNode * temp = *head;
        while (temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void freeProductList(TProdNode *head) {
    TProdNode *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->product);
        free(temp);     
    }
}

