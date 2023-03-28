#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void imprime_contrario(){
    char string[100];

    fgets(string, 99, stdin);
    string[strcspn (string, "\n")] = '\0';

    int tam = strlen(string); 

    for (int i = tam; i >= 0; i--) {
        printf ("%c", string[i]);
    }
    printf ("\n");
}

void tamanho_string(){
    char string[100];
    int i;

    fgets(string, 99, stdin);
    string[strcspn(string, "\n")] = '\0';

    for (i = 0; string[i] != '\0'; i++) {
        
    }

    int tam = i;
    printf ("%d\n", tam);
}

void aumenta_caps(){
    char string[100];

    fgets(string, 99, stdin);
    string[strcspn(string, "\n")] = '\0';

    for (int i = 0; string[i] != '\0'; i++) {
        string[i] = string[i] - 32;
    }
    printf ("%s\n", string);
}

void encapsula_caracteres(){
    char *string = malloc(sizeof(char)*64);
    fgets(string, 64, stdin);
    string[strcspn(string, "\n")] = '\0';
}

int main(){
    encapsula_caracteres();

    return 0;
}
