#include "User.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>

TUser* user(char *name, char *adress, char *paymentMethod, char *cpf){
    TUser *user = (TUser*) malloc(sizeof(TUser));
    strcpy(user->name, name);
    strcpy(user->adress, adress);
    strcpy(user->paymentMethod, paymentMethod);
    strcpy(user->cpf, cpf);

    return user;
}

void printUser(TUser *user){
    printf("\n*****************************************");
    printf("\nUSER\t%s\tCPF\t%s",user->name,user->cpf);
    printf("\nADRESS:%s\t PAYMENTMETHOD: %s",user->adress,user->paymentMethod);
    printf("\n*****************************************");
}

int sizeUser(){
    return sizeof(char) * 30  
        + sizeof(char) * 30 
        + sizeof(char) * 20
        + sizeof(char) * 12; 
}

int qtdUserInFile(FILE* file){
    fseek(file, 0, SEEK_END);
    int tam = trunc(ftell(file) / sizeUser());
    return tam;
}

