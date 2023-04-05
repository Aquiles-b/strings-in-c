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

/*Função interna do quickSort.*/
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

/*Função interna do quickSort.*/
void auxQuickSort(char** linhas, int a, int b)
{
    if (a >= b)
        return;
    int meio = particiona(linhas, a, b);
    auxQuickSort(linhas, a, meio - 1);
    auxQuickSort(linhas, meio + 1, b);
}

/*Retorna quantidade de linhas de um texto.*/
int tam_texto(char** linhas)
{
    int tam = 0;
    while(strlen(linhas[tam]) != 0)
        tam++;

    return tam;
}

/*Ordena usando quicksort de forma alfabetica.*/
void ordena_texto(char** linhas)
{
    auxQuickSort(linhas, 0, tam_texto(linhas)-1);
}

/*Imprime texto.*/
void imprime_linhas(char** linhas)
{
    int tam = tam_texto(linhas);
    int i = 0;
    while(i < tam){
        puts(linhas[i]);
        i++;
    }
}

/*Desaloca o texto.*/
void destroi_texto(char** linhas)
{
    int tam = tam_texto(linhas);
    for(int i = 0; i < tam; i++){
        free(linhas[i]);
        linhas[i] = NULL;
    }
    free(linhas);
}

/*Imprime as linhs do texto em ordem alfabetica.*/
void imprime_linhas_ordem_alfabetica(char** linhas)
{
    char** linhas_ordenadas = malloc(sizeof(char*)*TAM);
    memcpy(linhas_ordenadas, linhas, TAM);

    ordena_texto(linhas_ordenadas);
    imprime_linhas(linhas_ordenadas);
    free(linhas_ordenadas);
}

/*Desloca os caracteres de um string a partir do indice @i substituindo o 
 * @i por @i+1.*/
void desloca_caracteres_esquerda(char* string, size_t i)
{
    while(string[i] != '\0'){
        string[i] = string[i+1];
        i++;
    }
}

/*remove todos os caracteres nao alfanumericos de uma string.*/
void remove_caracteres_nao_alfanumericos(char* string)
{
    size_t i = 0;
    while(string[i] != '\0'){
        if (!ehAlfanumerico(string[i])){
            desloca_caracteres_esquerda(string, i);
            i--;
        }
        i++;
    }
}

/*Remove caracteres repetidos em sequencia.*/
void remove_caracter_repetido(char* string)
{
    size_t i = 0;
    while(string[i] != '\0'){
        if (string[i] == string[i+1]){
            desloca_caracteres_esquerda(string, i);
            i--;
        }
        i++;
    }
}

/*Tenta achar a string @agulha dentro da string @palheiro.*/
short compara_sequencia(char* agulha, char* palheiro, size_t j)
{
    size_t i, tam, comparador;
    comparador = 0;
    i = 0;
    tam = tamanho_string(agulha);
    while(agulha[i] != '\0'){
        if(agulha[i] == palheiro[j]){
            i++;
            j++;
            comparador++;
        }else
            return 0;
    }
    if (comparador == tam)
        return 1;

    return 0;
}

/*Retorn indice de onde começa a sequencia @agulha em palheiro
 * -1 caso nao exista e -2 caso alguma string seja nula.*/
int busca(char* agulha, char* palheiro)
{
    if (tamanho_string(agulha) == 0 || tamanho_string(palheiro) == 0)
        return -2;

    size_t j = 0;
    while(palheiro[j] != '\0'){
        if (agulha[0] == palheiro[j]){
            if(compara_sequencia(agulha, palheiro, j))
                return j;
        }
        j++;
    }

    return -1;
}

/*Remove caracteres especiais, deixa tudo em minusculo e retira os espaços.*/
void trata_string(char* string)
{
    size_t i = 0;
    diminuiu_caps(string);
    remove_caracteres_nao_alfanumericos(string);
    while(string[i] != '\0'){
        if(string[i] == ' '){
            desloca_caracteres_esquerda(string, i);
            i--;
        }
        i++;
    }
}

/*Inverte uma string.*/
void inverte_string(char* string)
{
    size_t i = 0;
    size_t tam = tamanho_string(string)-1;
    char aux;

    while(i < tam){
        aux = string[tam];
        string[tam] = string[i];
        string[i] = aux;
        i++;
        tam--;
    }
}

/*Retorna 1 se for palindromo e 0 c.c*/
short eh_palindromo(char* string)
{
    char* p_tratada = malloc(sizeof(char)*TAM);
    char* p_tratada_rev = malloc(sizeof(char)*TAM);
    memcpy(p_tratada, string, TAM);
    trata_string(p_tratada);

    memcpy(p_tratada_rev, p_tratada, TAM);
    inverte_string(p_tratada_rev);

    if(!strcmp(p_tratada, p_tratada_rev))
        return 1;

    return 0;
}

/*Mostra o indice das palavras da string que começa com uma letra ou
 * digito informado em @digt. se nada for informado pega pelo stdin.*/
void posPal(char* string, char* digt)
{
    int j = 0, ind_palavra = 0, vet[TAM];
    char* pt;
    if(!digt)
        scanf("%c", digt);

    pt = strtok(string, " ");
    while(pt){
        if(pt[0] == *digt){
            vet[j] = ind_palavra;
            j++;
        }
        pt = strtok(NULL, " ");
        ind_palavra++;
    }

    for(int i = 0; i < j; i++)
        printf ("%d ", vet[i]);

    printf ("\n");
}

int aux_busca_binaria(char vetor[], int a, int b, char valor, int* m)
{
    if (a > b)
        return -1;

    *m = (b + a) / 2;
    if (vetor[*m] == valor)
        return *m;
    if (valor > vetor[*m])
        return aux_busca_binaria(vetor, *m + 1, b, valor, m);
    return aux_busca_binaria(vetor, a, *m - 1, valor, m);
}

/*Se existir retorna o indice, caso contrario retorna -1.*/
int buscaBinaria(char vetor[], int tam, char valor, int* m)
{
    return aux_busca_binaria(vetor, 0, tam, valor, m);
}


short letra_nao_utilizada(char letra, char* vet, int* tam)
{
    int ind;
    int existe = buscaBinaria(vet, *tam, letra, &ind);

    if(existe == -1){
        for (int i = *tam; i >= ind; i--) 
            vet[i] = vet[i-1];

        tam++;
        vet[ind] = letra;

        return 1;
    }

    return 0;
}

void primPal(char* string)
{
    char* letras = malloc(sizeof(char)*TAM);
    char* pt;
    int tam = 0;

    pt = strtok(string, " ");
    while(pt){
        if(letra_nao_utilizada(pt[0], letras, &tam)){
            printf ("%c: ", pt[0]);
            posPal(string, &pt[0]);
        }
            pt = strtok(NULL, " ");
    }
}


int main()
{
    char* string = ler_string();

    primPal(string);

    free(string);

    return 0;
}
