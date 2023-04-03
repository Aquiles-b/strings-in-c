#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Le uma string da entrada padrão e retorna um ponteiro para ela.*/
char *ler_string()
{
    char *string = malloc(sizeof(char)*64);
    fgets(string, 64, stdin);
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

int main()
{
    char *string = ler_string();

    encapsula_caracteres(string);
    printf ("%s\n", string);

    free(string);

    return 0;
}
