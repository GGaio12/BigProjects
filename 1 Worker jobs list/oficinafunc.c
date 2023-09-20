#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "oficinafunc.h"

 /* 
  * Criação de um cliente
  * ---------------------
  */

/* Cria um cliente de forma dinâmica e devolve um ponteiro do mesmo */
/* Notas: */
/* Se id == 0 cria um id random novo */
/* Return NULL caso falhe na alocação de memória */
Cliente * cria_cliente(char nome[], Data data, int servico, int id){
    Cliente * cliente;
    srand(time(0));
    int random = rand();
    cliente = (Cliente *) malloc(sizeof (Cliente));
    if(cliente != NULL){
        strcpy(cliente->nome, nome);
        cliente->data = data;
        if(id == 0) cliente->id = random;
        else cliente->id = id;
        cliente->servico = servico;
    }
    return cliente;
}

/* Questiona o nome ao utilizador no tamanho máximo de 'tamanho', guardando o nome em 'nome' */
void define_nome(char nome[], int tamanho){
    printf("\nNome do Cliente: ");
    ler_str(nome, tamanho);
    printf("\n");
}

/* Questiona o serviço ao utilizador, guardando o respetivo valor em 'servico' */
/* Return 1--> Lavagem ; Return 2--> Manutenção */
void define_servico(int * servico){
    printf("Serviço desejado:\n");
    printf("[1]->Lavagem\n[2]->Manutenção\n");
    ler_escolha(servico);
    printf("\n");
}

/* Questiona a data do serviço ao utilizador (verificando a sua validade) e atribui os respectivos valores às variáveis. */
/* Return 1-> data válida ; Return 0-> data inválida */
int define_data(int * dia, int * mes, int * ano){
    char dia_str[4], mes_str[4], ano_str[5];
    printf("Data da Reserva:\n");
    printf("Dia: ");
    ler_str(dia_str, 4);

    printf("Mês: ");
    ler_str(mes_str, 4);

    printf("Ano: ");
    ler_str(ano_str, 5);

    if(data_str_to_int(dia_str, mes_str, ano_str, dia, mes, ano) && valida_data((*dia), (*mes), (*ano))) return 1;
    else return 0;
}


 /*
  * Impressão de resultados
  * ----------------------
  */

/* Imprime na consola todas as informações sobre o cliente passado */
void imprime_cliente(Cliente cliente){
    int horas, minutos;
    double_hora_to_ints(cliente.data.hora, &horas, &minutos);
    printf(" Nome   --> %s\n", cliente.nome);
    printf("  ID    --> %d\n", cliente.id);
    printf(" Data   --> %.2d/%.2d/%.4d\n", cliente.data.dia, cliente.data.mes, cliente.data.ano);
    printf(" Hora   --> %.2d:%.2d\n", horas, minutos);
    if(cliente.servico == 1) printf("Serviço --> Lavagem\n");
    else if(cliente.servico == 2) printf("Serviço --> Manutenção\n");
}

/* Imprime na consola uma mensagem de erro especifica */
/* "Escolha inválida" ; "Falha ao ler" ; "= NULL" ; "Data inválida" ; "Erro Ficheiro" */
void mensagem_erro(char erro[]){
    if(strcmp(erro, "Escolha inválida") == 0) printf("\nErro... Valor de opção inválido...\nPor favor ensira um número para uma opção válido.\n\n");
    else if(strcmp(erro, "Falha ao ler") == 0) printf("\nErro... Falha ao ler com a função fgets()\n\n");
    else if(strcmp(erro, "= NULL") == 0) printf("\nErro... Incapacidade de alocação...\nA voltar para o menu inicial...\n\n");
    else if(strcmp(erro, "Data inválida") == 0) printf("\nErro... Data inválida ou muito longínqua...\nPor favor insira uma data válida para prosseguir\n\n");
    else if(strcmp(erro, "Erro Ficheiro") == 0) printf("\nErro... Algo inesperado ocorreu ao tentar analizar o ficheiro...\n\n");
}


 /*
  * Interação com datas
  * -------------------
  */

/* Compara duas datas */
/* Return 0-> Iguais ; Return 1-> d1 Maior(futura) ; Return 2-> d2 Maior(futura) */
int compara_data(Data d1, Data d2){
    if(d1.ano > d2.ano) return 1;
    else if(d1.ano < d2.ano) return 2;
        else if(d1.mes > d2.mes) return 1;
        else if(d1.mes < d2.mes) return 2;
            else if(d1.dia > d2.dia) return 1;
            else if(d1.dia < d2.dia) return 2;
                else return 0;
}

/* Compara duas horas */
/* Return 0-> Iguais ; Return 1-> hora1 Maior(futura) ; Return 2-> hora2 Maior(futura) */
int compara_hora(double hora1, double hora2){
    if(hora1 > hora2) return 1;
    else if (hora1 < hora2) return 2;
        else return 0;
}

/* Verifica se um ano é bissexto */
/* Return 1-> É bissexto ; Return 0-> Não é bissexto */
int ano_bissexto(int ano){
    if(((ano % 400) == 0) || (((ano % 4) == 0) && ((ano % 100) != 0))) return 1; //É bissexto se for divisível por 400 ou se for divisível por 4, mas não por 100
    else return 0; //Todos os demais não são bissextos
}

/* Verifica se uma data é válida, ou seja, se é uma data futura ou o próprio dia */
/* Return 1-> É válida ; Return 0-> É inválida */
int valida_data(int dia, int mes, int ano){
    time_t time_r;
    struct tm * timeinfo;
    time(&time_r);
    timeinfo = localtime(&time_r);
    int c_dia, c_mes, c_ano;
    c_dia = timeinfo->tm_mday;
    c_mes = timeinfo->tm_mon + 1; //Adição de +1, pois, na estrutura tm os meses são definidos de 0 a 11 e não 1 a 12
    c_ano = timeinfo->tm_year + 1900; //Adição  de +1900, pois, na estrutura tm os anos contam a partir de 1900

    //Verificação de datas demasiado longínquas ou não existentes
    if((ano > (c_ano + 2)) || (mes < 1) || (mes > 12) || (dia < 1) || (dia > 31)) return 0;

    if(ano < c_ano) return 0;
    if(ano > c_ano){
        if(mes == 2){
            if(ano_bissexto(ano) && (dia <= 29)) return 1;
            else if(!ano_bissexto(ano) && (dia <= 28)) return 1;
            else return 0;
        }
        else if((((mes % 2) == 0) && (mes < 7)) || (((mes % 2) == 1) && (mes > 7))){
            if(dia <= 30) return 1;
            else return 0;
        }
        else if((((mes % 2) == 1) && (mes <= 7)) || (((mes % 2) == 0) && (mes > 7))){
            if(dia <= 31) return 1;
            else return 0;
        }
    }
    else if(ano == c_ano){
        if(mes < c_mes) return 0;
        else if((mes == c_mes) && (dia < c_dia)) return 0;
        else{
            if(mes == 2){
                if(ano_bissexto(ano) && (dia <= 29)) return 1;
                else if(!ano_bissexto(ano) && (dia <= 28)) return 1;
                else return 0;
            }
            else if((((mes % 2) == 0) && (mes < 7)) || (((mes % 2) == 1) && (mes > 7))){
                if(dia <= 30) return 1;
                else return 0;
            }
            else if((((mes % 2) == 1) && (mes <= 7)) || (((mes % 2) == 0) && (mes > 7))){
                if(dia <= 31) return 1;
                else return 0;
            }
        }
    }
}


 /*
  * Manipulação de strings
  * ----------------------
  */

/* Lê uma string da consola de tamanho máximo 'tamanho' e armazena a string lida em 'str' */
void ler_str(char str[], int tamanho){
    if(fgets(str, tamanho, stdin) == NULL){
        mensagem_erro("Falha ao ler");
    }
    else{
        str[strcspn(str, "\n")] = '\0';
    }
}

/* Lê a escolha feita pelo utilizador através da consola armazenando o respetivo valor num inteiro 'escolha' */
void ler_escolha(int * escolha){
    char * escolha_str = (char *) malloc(4 * sizeof(char));
    printf("Escolha: ");
    ler_str(escolha_str, 3);
    *escolha = str_to_int(escolha_str);
    free(escolha_str);
}

/* Remove da string 'str' a primeira ocorrência do caracter 'c' */
void removeChar(char * str, char c){
    int i, j;
    unsigned short int done = 0;
    int len = strlen(str);
    for(i = j = 0; i < len; i++){
        if((str[i] != c) || done){
            str[j++] = str[i];
            done = 1;
        }
    }
    str[j] = '\0';
}


 /*
  * Conversão de variáveis
  * ----------------------
  */

/* Transforma uma string com números contidos, em um inteiro */
/* Return: O número inteiro respectivo contido na string */
int str_to_int(char str[]){
    int numb = 0;
    size_t size = strlen(str);
    for(int i = (size - 1); i >= 0; i--){
        if(str[i] >= '0' && str[i] <= '9'){
            int j = 0;
            for(int pow = 1; ((str[i+j] >= '0') && (str[i+j] <= '9') && (((-1)*j) < size)); j--){
                numb += pow * (str[i+j] - '0');
                pow *= 10;
            }
            break;
        }
    }
    return numb;
}

/* Transforma os valores de dia, mes e ano contidos em string em inteiros */
/* Return 1-> Valores válidos (!= 0) ; Return 0-> Valores inválidos */
int data_str_to_int(char dia_str[], char mes_str[], char ano_str[], int * dia, int * mes, int * ano){
    *dia = str_to_int(dia_str);
    *mes = str_to_int(mes_str);
    *ano = str_to_int(ano_str);
    if((*dia != 0) && (*mes != 0) && (*ano != 0)) return 1;
    else return 0;
}

/* Transforma o inteiro 'servico' no respectivo tempo que demora a ser executado */
/* Return 0.5-> Servico == 1 (Limpeza) ; Return 1.0-> Servico == 2 (Manutenção) */
double tempo_servico(int servico){
    double tempo = servico/2;
    if(tempo == 0) return 0.5;
    else if(tempo == 1) return 1.0;
}

/* Transforma um valor double, relativo a horas, em dois valores inteiros respectivamente de horas e minutos */
void double_hora_to_ints(double hora, int * horas, int * minutos){
    *horas = hora;
    if(((*horas) - hora) != 0) (*minutos) = 30;
    else (*minutos) = 0;
}
