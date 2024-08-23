#include <stdio.h>
#include <stdlib.h>
#include "tadlista.h"

// Função para criar uma nova lista
Lista new_lista() {
    Lista lista = (Lista)malloc(sizeof(struct tipo_lista));
    lista->primeiro = NULL;
    lista->ultimo = NULL;
    lista->tamanho = 0;
    return lista;
}

// Função para obter o tamanho da lista
int lenLista(Lista l) {
    return l->tamanho;
}

// Função para adicionar um dado ao final da lista
Lista appendLista(Lista l, t_dado d) {
    t_no novo_no = (t_no)malloc(sizeof(struct tipo_no));
    novo_no->dado = d;
    novo_no->anterior = l->ultimo;
    novo_no->proximo = NULL;
    
    if (l->ultimo) {
        l->ultimo->proximo = novo_no;
    } else {
        l->primeiro = novo_no;
    }
    
    l->ultimo = novo_no;
    l->tamanho++;
    return l;
}

// Função para acessar um elemento da lista
t_dado elemLista(Lista l, int pos) {
    if (pos < 0 || pos >= l->tamanho) return NULL;
    
    t_no atual = l->primeiro;
    for (int i = 0; i < pos; i++) {
        atual = atual->proximo;
    }
    return atual->dado;
}

// Função para inserir um dado na lista em uma posição específica
Lista insereLista(Lista l, t_dado dado, int pos) {
    if (pos < 0 || pos > l->tamanho) return l;
    
    t_no novo_no = (t_no)malloc(sizeof(struct tipo_no));
    novo_no->dado = dado;
    
    if (pos == 0) {
        novo_no->proximo = l->primeiro;
        novo_no->anterior = NULL;
        if (l->primeiro) {
            l->primeiro->anterior = novo_no;
        }
        l->primeiro = novo_no;
        if (l->tamanho == 0) {
            l->ultimo = novo_no;
        }
    } else {
        t_no atual = l->primeiro;
        for (int i = 0; i < pos - 1; i++) {
            atual = atual->proximo;
        }
        novo_no->proximo = atual->proximo;
        novo_no->anterior = atual;
        if (atual->proximo) {
            atual->proximo->anterior = novo_no;
        }
        atual->proximo = novo_no;
        if (novo_no->proximo == NULL) {
            l->ultimo = novo_no;
        }
    }
    
    l->tamanho++;
    return l;
}

// Função para remover um elemento da lista de uma posição específica
t_dado removeLista(Lista l, int pos) {
    if (pos < 0 || pos >= l->tamanho) return NULL;
    
    t_no atual = l->primeiro;
    for (int i = 0; i < pos; i++) {
        atual = atual->proximo;
    }
    
    if (atual->anterior) {
        atual->anterior->proximo = atual->proximo;
    } else {
        l->primeiro = atual->proximo;
    }
    
    if (atual->proximo) {
        atual->proximo->anterior = atual->anterior;
    } else {
        l->ultimo = atual->anterior;
    }
    
    t_dado dado = atual->dado;
    free(atual);
    l->tamanho--;
    return dado;
}