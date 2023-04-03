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

void encapsula(char *string, size_t ind){
    char aux1, aux2;

    aux1 = string[ind+1];
    for (size_t i = ind; i < strlen(string); ++i) {
        string[i+1] = string[i];
        aux2 = string[i+2];
        string[i+2] = aux1;
        aux1 = aux2;
    }
}

/*Coloca entre [] qualquer caracter não alfanumérico.*/
void encapsula_caracteres(char *string)
{
    for (size_t i = 0; i < strlen(string); i++){
        if (string[i] > 122 || string[i] < 65 || (string[i] < 97 && string[i] > 90))
            encapsula(string, i);
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
