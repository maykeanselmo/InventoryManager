#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct User {
    FILE* orderFile; 
    char name[30];
    char adress[30];
    char paymentMethod[20];
    char cpf[12];
} TUser;
TUser * user(char *name, char *adress, char *paymentMethod, char *cpf);
int sizeUser();
int qtdUserInFile(FILE* file);
void printUser(TUser *user);
void generateUserBase(const char *filename, int numberOfUsers);

#endif