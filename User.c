#include "UserUtils.h"
#include "User.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>

TUser *user(char *name, char *adress,char *cpf) {
    TUser *user = (TUser *) malloc(sizeof(TUser));
    strcpy(user->name, name);
    strcpy(user->adress, adress);
    strcpy(user->cpf, cpf);

    return user;
}

void saveUsers(const char *filename, TUser *users, int count) {
    FILE *file = fopen(filename, "wb"); // Abre o arquivo para escrita em binário
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        exit(1);
    }
    fwrite(users, sizeof(TUser), count, file); // Grava todos os usuários no arquivo
    fclose(file); // Fecha o arquivo
}

// Função para gerar múltiplos usuários aleatórios
void generateRandomUsers(TUser *users, int count) {
    for (int i = 0; i < count; i++) {
        generateRandomName(users[i].name);
        generateRandomAddress(users[i].adress);
        generateRandomCPF(users[i].cpf);
    }
}



void printAllUsers(const char *filename) {
    FILE *file = fopen(filename, "rb"); // Abre o arquivo para leitura binária
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        exit(1);
    }

    TUser user;
    while (fread(&user, sizeof(TUser), 1, file)) {
        printUser(&user); // Usa a função existente para imprimir as informações do usuário
    }

    fclose(file); // Fecha o arquivo
}

void deleteUser(const char *filename, const char *cpfToDelete) {
    FILE *file = fopen(filename, "rb"); // Abre o arquivo para leitura binária
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    FILE *tempFile = fopen("temp.dat", "wb"); // Abre um arquivo temporário para escrita binária
    if (tempFile == NULL) {
        printf("Erro ao abrir o arquivo temporário para escrita.\n");
        fclose(file);
        return;
    }

    TUser user;
    int found = 0;

    while (fread(&user, sizeof(TUser), 1, file)) {
        if (strcmp(user.cpf, cpfToDelete) != 0) {
            // Se o CPF não é o que queremos deletar, escreva no arquivo temporário
            fwrite(&user, sizeof(TUser), 1, tempFile);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        // Remove o arquivo original e renomeia o arquivo temporário
        remove(filename);
        rename("temp.dat", filename);
        printf("Usuário com CPF %s foi deletado.\n", cpfToDelete);
    } else {
        // Se o CPF não foi encontrado, remova o arquivo temporário
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

TUser *userSequentialSearch(const char *filename, const char *targetCPF) {
    FILE *file = fopen(filename, "rb"); // Abre o arquivo em modo de leitura binária
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    TUser user;
    while (fread(&user, sizeof(TUser), 1, file) == 1) { // Lê usuários um por um
        if (strcmp(user.cpf, targetCPF) == 0) { // Compara o CPF
            fclose(file); // Fecha o arquivo antes de retornar
            TUser *foundUser = (TUser *) malloc(sizeof(TUser)); // Aloca memória para o usuário encontrado
            *foundUser = user; // Copia os dados do usuário encontrado
            return foundUser; // Retorna o usuário encontrado
        }
    }

    fclose(file); // Fecha o arquivo se o usuário não for encontrado
    return NULL; // Retorna NULL se o usuário não for encontrado
}

void updateUser(const char *filename, const char *targetCPF, TUser *updatedUser) {
    FILE *file = fopen(filename, "rb+"); // Abre o arquivo em modo de leitura e escrita binária
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    TUser user;
    long pos;
    int found = 0;

    // Busca o usuário no arquivo
    while (fread(&user, sizeof(TUser), 1, file) == 1) {
        if (strcmp(user.cpf, targetCPF) == 0) { // Compara o CPF
            pos = ftell(file) - sizeof(TUser); // Guarda a posição do usuário encontrado
            found = 1;
            break; // Sai do loop se o usuário for encontrado
        }
    }

    if (found) {
        // Atualiza os dados do usuário
        fseek(file, pos, SEEK_SET); // Move o ponteiro para a posição do usuário encontrado
        fwrite(updatedUser, sizeof(TUser), 1, file); // Escreve os dados atualizados no arquivo
        printf("\nUsuário com CPF %s atualizado com sucesso.\n", targetCPF);
    } else {
        printf("\nUsuário com CPF %s não encontrado.\n", targetCPF);
    }

    fclose(file); // Fecha o arquivo
}

void printUser(TUser *user) {
    printf("\n*****************************************");
    printf("\nUSER\t%s\tCPF\t%s", user->name, user->cpf);
    printf("\nADRESS:%s\t ", user->adress);
    printf("\n*****************************************");
}

int sizeUser() {
    return sizeof(char) * 30
           + sizeof(char) * 30
           + sizeof(char) * 20
           + sizeof(char) * 12;
}

int qtdUserInFile(FILE *file) {
    fseek(file, 0, SEEK_END);
    int tam = trunc(ftell(file) / sizeUser());
    return tam;
}

