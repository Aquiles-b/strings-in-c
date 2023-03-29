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
        if (string[i] > 96 )
            string[i] = string[i] - 32;
    }
}

/*Coloca entre [] qualquer caracter não alfanumérico.*/
void encapsula_caracteres(char *string)
{

}

int main()
{
    char *string = ler_string();
    aumenta_caps(string);

    printf ("%s\n", string);

    free(string);

    return 0;
}
