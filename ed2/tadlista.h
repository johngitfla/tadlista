/* PRIVADO: NÃO PODE SER ALTERADO */
typedef void *t_dado; /*  NA APLICAÇÃO, PODE SER MENCIONADO MAS NÃO ALTERADO */

typedef struct tipo_no { /*  NA APLICAÇÃO, NÃO PODE SER MENCIONADO NEM ALTERADO */
  t_dado dado;
  struct tipo_no *anterior;
  struct tipo_no *proximo;
} * t_no;

typedef struct tipo_lista {
  t_no primeiro;
  t_no ultimo;
  int tamanho;
} * Lista; /*  NA APLICAÇÃO, PODE SER MENCIONADO MAS NÃO ALTERADO */

/*  NA APLICAÇÃO, DEVEM SER UTILIZADOS */
Lista new_lista();
int lenLista(Lista l);
Lista appendLista(Lista l, t_dado d);
t_dado elemLista(Lista l, int pos);
Lista insereLista(Lista l, t_dado dado, int pos);
t_dado removeLista(Lista l, int pos);