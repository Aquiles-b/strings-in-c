#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TAM 64

/*Le uma string da entrada padrão e retorna um ponteiro para ela.*/
char *ler_string()
{
    char *string = malloc(sizeof(char)*TAM);
    fgets(string, TAM, stdin);
    string[strcspn(string, "\n")] = '\0';

    return string;
}

/*Imprime a string do final pro comeco.*/
void imprime_contrario(char *string)
{
    int tam = strlen(string); 

    for (int i = tam; i >= 0; i--) {
        printf ("%c", string[i]);
    }
    printf ("\n");
}

/*Retorna o tamanho da string.*/
int tamanho_string(char *string)
{
    int i;

    for (i = 0; string[i] != '\0'; i++);
    
    return i;
}

/*Modifica todos os caracteres da string para caixa alta.*/
void aumenta_caps(char *string)
{
    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] > 96 && string[i] < 123)
            string[i] = string[i] - 32;
    }
}

/*Modifica todos os caracteres da string para caixa baixa.*/
void diminuiu_caps(char *string)
{
    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] < 91 && string[i] > 64 )
            string[i] = string[i] + 32;
    }
}

/* Colocar o elemente em ind entre [] */
void encapsula(char *string, size_t ind){
    char aux;
    size_t tam = strlen(string);
    string[tam+1] = '[';
    string[tam+2] = ']';

    while (tam != ind-1){
        aux = string[tam];
        string[tam] = string[tam+1];
        if(tam == ind)
            string[tam+1] = aux;
        else{
        string[tam+1] = string[tam+2];
        string[tam+2] = aux;
        }
        tam--;
    }
}

/*Retorna 1 se for alfanumerico e zero cc.*/
int ehAlfanumerico(char item)
{
    return ((item >= 48 && item <= 57) || (item >= 65 && item <= 90) ||
            (item >= 97 && item <= 122) || item == ' ');
}

/*Coloca entre [] qualquer caracter não alfanumérico.*/
void encapsula_caracteres(char *string)
{
    char item;
    for (size_t i = 0; i < strlen(string); i++){
        item = string[i];
        if (!ehAlfanumerico(item)){
            encapsula(string, i);
            i += 2;
        }
    }
}

/*Le linhas consecutivas do stdin, para quando a linhas for nula e
 * retorna vetor de ponteiros para as linhas.*/
char** ler_linhas()
{
    int i = -1;
    char** linhas = malloc(sizeof(char*)*TAM);

    do{
        i++;
        linhas[i] = ler_string();
    }while(strlen(linhas[i]) != 0);

    return linhas;
}

int particiona(char** linhas, int a, int b)
{
    int meio = a-1;
    char* aux;
    for (int i = a; i <= b; i++)
        if (strcmp(linhas[i], linhas[b]) <= 0){
            meio++;
            aux = linhas[meio];
            linhas[meio] = linhas[i];
            linhas[i] = aux;
        }

    return meio;
}

void auxQuickSort(char** linhas, int a, int b)
{
    if (a >= b)
        return;
    int meio = particiona(linhas, a, b);
    auxQuickSort(linhas, a, meio - 1);
    auxQuickSort(linhas, meio + 1, b);
}

int tam_texto(char** linhas)
{
    int tam = 0;
    while(strlen(linhas[tam]) != 0)
        tam++;

    return tam;
}

void ordena_texto(char** linhas)
{
    auxQuickSort(linhas, 0, tam_texto(linhas)-1);
}

void imprime_linhas(char** linhas)
{
    int tam = tam_texto(linhas);
    int i = 0;
    while(i < tam){
        puts(linhas[i]);
        i++;
    }
}

void destroi_texto(char** linhas)
{
    int tam = tam_texto(linhas);
    for(int i = 0; i < tam; i++){
        free(linhas[i]);
        linhas[i] = NULL;
    }
    free(linhas);
}

void imprime_linhas_ordem_alfabetica(char** linhas)
{
    char** linhas_ordenadas;
    memcpy(linhas_ordenadas, linhas, TAM);

    ordena_texto(linhas_ordenadas);
    imprime_linhas(linhas);
    imprime_linhas(linhas_ordenadas);
    imprime_linhas(linhas);
}

int main()
{
    char** linhas = ler_linhas();
    imprime_linhas_ordem_alfabetica(linhas);

    destroi_texto(linhas);

    return 0;
}
