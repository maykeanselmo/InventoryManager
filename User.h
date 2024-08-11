#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct User {
    FILE* orderFile; 
    char name[30];
    char adress[30];
    char cpf[12];
} TUser;
TUser *user(char *name, char *adress,  char *cpf);
void saveUsers(const char *filename, TUser *users, int count);
void generateRandomUsers(TUser *users, int count);
void printAllUsers(const char *filename);
void deleteUser(const char *filename, const char *cpfToDelete);
void generateUserBase(const char *filename, int numberOfUsers);
TUser *userSequentialSearch(const char *filename, const char *targetCPF);
void updateUser(const char *filename, const char *targetCPF, TUser *updatedUser);
void printUser(TUser *user);
int sizeUser();
int qtdUserInFile(FILE *file);
#endif