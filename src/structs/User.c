#include "../structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

TUser *user(char *name, char *address, char *cpf) {
    TUser *user = (TUser *) malloc(sizeof(TUser));
    strcpy(user->name, name);
    strcpy(user->address, address);
    strcpy(user->cpf, cpf);
    return user;
}

void saveUsers(const char *filename, TUser *users, int count) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        exit(1);
    }
    fwrite(users, sizeof(TUser), count, file);
    fclose(file);
}

TUser *readUser(FILE *in) {
    TUser *user = (TUser *) malloc(sizeof(TUser));
    if (fread(user, sizeof(TUser), 1, in) <= 0) {
        free(user);
        return NULL;
    }
    return user;
}

void generateRandomUsers(TUser *users, int count) {
    for (int i = 0; i < count; i++) {
        generateRandomName(users[i].name);
        generateRandomAddress(users[i].address);
        generateRandomCPF(users[i].cpf);
    }
}

void printAllUsers(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        exit(1);
    }

    TUser user;
    while (fread(&user, sizeof(TUser), 1, file)) {
        printUser(&user);
    }

    fclose(file);
}

void deleteUser(const char *filename, const char *cpfToDelete) {
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

    TUser user;
    int found = 0;

    while (fread(&user, sizeof(TUser), 1, file)) {
        if (strcmp(user.cpf, cpfToDelete) != 0) {
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
        printf("Usuário com CPF %s foi deletado.\n", cpfToDelete);
    } else {
        remove("temp.dat");
        printf("Usuário com CPF %s não foi encontrado.\n", cpfToDelete);
    }
}

void generateUserBase(const char *filename, int numberOfUsers) {
    TUser *users = (TUser *) malloc(numberOfUsers * sizeof(TUser));
    if (users == NULL) {
        printf("Erro ao alocar memória para os usuários.\n");
        exit(1);
    }

    generateRandomUsers(users, numberOfUsers);
    saveUsers(filename, users, numberOfUsers);
    free(users);

    printf("%d usuários foram gerados e salvos em '%s'.\n", numberOfUsers, filename);
}

int sizeUser() {
    return sizeof(char) * 30
           + sizeof(char) * 30
           + sizeof(char) * 50
           + sizeof(char) * 12;
}

int number_of_users(FILE *file) {
    fseek(file, 0, SEEK_END);
    return ftell(file) / sizeUser();
}

TUser *userSequentialSearch(const char *filename, const char *targetCPF) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        return NULL;
    }

    TUser user;
    while (fread(&user, sizeof(TUser), 1, file)) {
        if (strcmp(user.cpf, targetCPF) == 0) {
            fclose(file);
            TUser *foundUser = (TUser *) malloc(sizeof(TUser));
            if (foundUser == NULL) {
                return NULL;
            }
            *foundUser = user;
            return foundUser;
        }
    }

    fclose(file);
    return NULL;
}



void updateUser(const char *filename, const char *targetCPF, TUser *updatedUser) {
    FILE *file = fopen(filename, "rb+");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    TUser user;
    long pos;
    int found = 0;

    while (fread(&user, sizeof(TUser), 1, file) == 1) {
        if (strcmp(user.cpf, targetCPF) == 0) {
            pos = ftell(file) - sizeof(TUser);
            found = 1;
            break;
        }
    }

    if (found) {
        fseek(file, pos, SEEK_SET);
        fwrite(updatedUser, sizeof(TUser), 1, file);
        printf("Usuário com CPF %s atualizado com sucesso.\n", targetCPF);
    } else {
        printf("Usuário com CPF %s não encontrado.\n", targetCPF);
    }

    fclose(file);
}

void printUser(TUser *user) {
    printf("\n*****************************************");
    printf("\nUSER\t%s\tCPF\t%s", user->name, user->cpf);
    printf("\nADDRESS:%s", user->address);
    printf("\n*****************************************");
}
