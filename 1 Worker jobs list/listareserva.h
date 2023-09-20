#ifndef LISTARESERVA_H
#define LISTARESERVA_H

#include "oficinafunc.h"

 /*
  * Definição de constantes e estruturas
  * ------------------------------------
  */

typedef struct noLista {
    Cliente cliente;
    struct noLista * prox;
} noLista;

typedef noLista * pLista;

 /*
  * Defenição de Funções
  * --------------------
  * Divididas em 5 (cinco) categorias:
  *     --> Manipulação de Listas (básico)
  *     --> Manipulação de Listas (avançado)
  *     --> Identificação de Clientes
  *     --> Interação com Datas
  *     --> Leitura/Escrita em Ficheiros
  */

/*  Manipulação de Listas (básico)  */

pLista cria_lista();
pLista destroi_lista(pLista lista);
int vazia_l(pLista lista);
void imprime_lista(pLista lista, int mode);
void insere_cliente_l(pLista lista, Cliente cliente, int mode);


/*  Manipulação de Listas (avançado)  */

void imprime_reservas_c(pLista lista_r, pLista lista_p);
int cancelar_reserva(pLista lista, pLista lista2);


/*  Identificação de Clientes  */

void procura_cliente_l(pLista lista, Cliente cliente, pLista *ant, pLista *actual, int hora, int mode);
int pergunta_id(pLista lista_r, pLista lista_p, int *id, char * nome);


/*  Interação com Datas  */

int determinar_horas_disponiveis(pLista lista, Data data, int servico, double horas_disponiveis[]);
void procura_data(pLista lista, Data data, pLista * primeiro);
void verifica_data_listas(pLista lista_r, pLista lista_p);


/*  Leitura/Escrita em Ficheiros  */

void analisar_ficheiro(pLista lista, FILE * f, int mode);
void atualizar_ficheiro(pLista lista, FILE * f, int mode);

#endif
