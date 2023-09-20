#ifndef OFICINAFUNC_H
#define OFICINAFUNC_H

 /*
  * Definição de constantes e estruturas
  * ------------------------------------
  */

typedef struct Data
{
    int dia;
    int mes;
    int ano;
    double hora;
} Data;


typedef struct Cliente
{
    char nome[30];
    int id;
    Data data;
    int servico;
} Cliente;


 /*
  * Defenição de Funções
  * --------------------
  * Divididas em 5 (cinco) categorias:
  *     --> Criação de um cliente
  *     --> Impressão de resultados
  *     --> Interação com datas
  *     --> Manipulação de strings
  *     --> Conversão de variáveis
  */

/*  Criação de um cliente  */

Cliente * cria_cliente(char nome[], Data data, int servico, int id);
void define_nome(char nome[], int tamanho);
void define_servico(int * servico);
int define_data(int * dia, int * mes, int * ano);


/*  Impressão de resultados  */

void imprime_cliente(Cliente cliente);
void mensagem_erro(char erro[]);


/*  Interação com datas  */

int compara_data(Data d1, Data d2);
int compara_hora(double hora1, double hora2);
int ano_bissexto(int ano);
int valida_data(int dia, int mes, int ano);


/*  Manipulação de strings  */

void ler_str(char str[], int tamanho);
void ler_escolha(int * escolha);
void removeChar(char * str, char c);


/*  Conversão de variáveis  */

int str_to_int(char str[]);
int data_str_to_int(char dia_str[], char mes_str[], char ano_str[], int * dia, int * mes, int * ano);
double tempo_servico(int servico);
void double_hora_to_ints(double hora, int * horas, int * minutos);

#endif
