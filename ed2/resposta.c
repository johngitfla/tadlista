#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tadlista.h"

typedef struct {
    char cep[10];
    int numero;
    char nome[100];
} t_endereco1;

typedef struct {
    char cep[10];
    Lista enderecos;  
} t_endereco2;

char *strip(char *s){
    int ultimo = strlen(s) - 1;
    if(s[ultimo] == '\n')
        s[ultimo] = '\0';
    return s;  
}

Lista loadbdceps(char *nomearq) {
    FILE *arquivo = fopen(nomearq, "r");
    if (!arquivo) {
        return NULL;
    }

    Lista lista = new_lista();
    char linha[150];

    while (fgets(linha, sizeof(linha), arquivo)) {
        strip(linha);

        t_endereco1 *endereco = (t_endereco1 *)malloc(sizeof(t_endereco1));
        if (sscanf(linha, "%[^,],%d,%[^\n]", endereco->cep, &endereco->numero, endereco->nome) == 3) {
            appendLista(lista, endereco);
        } 
    }

    fclose(arquivo);
    return lista;
}

t_endereco2 *busca_ou_cria_cep(Lista lista, char *cep) {
    for (int i = 0; i < lenLista(lista); i++) {
        t_endereco2 *endereco2 = (t_endereco2 *)elemLista(lista, i);
        if (strcmp(endereco2->cep, cep) == 0) {
            return endereco2;
        }
    }
    t_endereco2 *novo = (t_endereco2 *)malloc(sizeof(t_endereco2));
    strcpy(novo->cep, cep);
    novo->enderecos = new_lista();
    appendLista(lista, novo);
    return novo;
}

Lista converte(Lista lst1) {
    Lista lista2 = new_lista();

    for (int i = 0; i < lenLista(lst1); i++) {
        t_endereco1 *endereco = (t_endereco1 *)elemLista(lst1, i);
        t_endereco2 *endereco2 = busca_ou_cria_cep(lista2, endereco->cep);
        appendLista(endereco2->enderecos, endereco);
    }

    return lista2;
}

void print_enderecos_2(Lista lst) {
    for (int i = 0; i < lenLista(lst); i++) {
        t_endereco2 *endereco2 = (t_endereco2 *)elemLista(lst, i);
        printf("%s\n", endereco2->cep);
        for (int j = 0; j < lenLista(endereco2->enderecos); j++) {
            t_endereco1 *endereco = (t_endereco1 *)elemLista(endereco2->enderecos, j);
            printf("  %s, %d, %s\n", endereco->cep, endereco->numero, endereco->nome);
        }
        printf("\n");
    }
}

int main() {
    Lista enderecos1 = loadbdceps("bdceps.txt");
    
    if (!enderecos1) { 
        printf("Erro ao abrir o arquivo bdceps.txt\n");
        return 1;
    }
    
    Lista enderecos2 = converte(enderecos1);
    print_enderecos_2(enderecos2);
    

    

    for (int i = 0; i < lenLista(enderecos2); i++) {
        t_endereco2 *endereco2 = (t_endereco2 *)elemLista(enderecos2, i);
        for (int j = 0; j < lenLista(endereco2->enderecos); j++) {
            free(elemLista(endereco2->enderecos, j));
        }

    }

    return 0;
}
