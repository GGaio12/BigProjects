#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "listareserva.h"

 /*
  * Definição de constantes
  * -----------------------
  */

const double HORAS_DE_TRABALHO[] = {8, 8.5, 9, 9.5, 10, 10.5, 11, 11.5, 12, 12.5, 13, 13.5, 14, 14.5, 15, 15.5, 16, 16.5, 17, 17.5, 18};
const int N_HORAS_DE_TRABALHO = 21;

 /* 
  * Manipulação de Listas (básico)
  * ------------------------------
  */

/* Cria uma lista de clientes */
/* Return: Ponteiro para o inicio da lista */
pLista cria_lista(){
    pLista aux;
    Cliente c1 = {"", 0, {0, 0, 0, 0}, 0};
    aux = (pLista) malloc(sizeof (noLista));
    if(aux != NULL){
        aux->cliente = c1;
        aux->prox = NULL;
    }
    return aux;
}

/* Destroi uma lista de clientes */
/* Return: NULL */
pLista destroi_lista(pLista lista){
    pLista temp_ptr;
    while(!vazia_l (lista)){
        temp_ptr = lista;
        lista = lista->prox;
        free (temp_ptr);
    }
    free(lista);
    return NULL;
}

/* Verifica se uma lista está vazia ou não */
/* Return 1-> A lista está vazia ; Return 0-> A lista não está vazia */
int vazia_l(pLista lista){
    if(lista->prox == NULL) return 1;
    else return 0;
}

/* Imprime uma lista de clientes com as suas informações */
/* Nota: */
/* mode == 'r' -> imprime a 'lista' como lista de reservas */
/* mode == 'p' -> imprime a 'lista' como lista de pré-reservas */
void imprime_lista(pLista lista, int mode){
    pLista aux = lista->prox;
    int horas, minutos;
    if(mode == 'r') printf("<----------/ LISTA DE RESERVAS /---------->\n");
    else if(mode == 'p') printf("<----------/ LISTA DE PRÉ-RESERVAS /---------->\n");
    while(aux){
        printf("\n");
        printf(" Nome   --> %s\n", aux->cliente.nome);
        printf("  ID    --> %d\n", aux->cliente.id);
        printf(" Data   --> %.2d/%.2d/%.4d\n", aux->cliente.data.dia, aux->cliente.data.mes, aux->cliente.data.ano);
        double_hora_to_ints(aux->cliente.data.hora, &horas, &minutos);
        printf(" Hora   --> %.2d:%.2d\n", horas, minutos);
        if(aux->cliente.servico == 1) printf("Serviço --> Limpeza\n");
        else if(aux->cliente.servico == 2) printf("Serviço --> Manutenção\n");
        printf("\n");
        printf("---------------------------\n");
        aux = aux->prox;
    }
    printf("----------/ FIM /----------\n");
}

/* Insere um cliente numa lista de reservas ou pré-reservas (consoante o 'mode') */
void insere_cliente_l(pLista lista, Cliente cliente, int mode){
    pLista no, ant, inutil;
    no = (pLista) malloc(sizeof (noLista));
    if(no != NULL){
        no->cliente = cliente;
        procura_cliente_l(lista, cliente, &ant, &inutil, 1, mode);
        no->prox = ant->prox;
        ant->prox = no;
    }
}


 /* 
  * Manipulação de Listas (avançado)
  * --------------------------------
  */

/* Imprime as reservas e pré-reservas de um cliente específico */
void imprime_reservas_c(pLista lista_r, pLista lista_p){
    int escolha, id;
    unsigned short int id_ok = 0;
    char id_str[15];
    char * last_nome = (char *) malloc(30 * sizeof(char));
    pLista aux;
    

    printf("Insira o ID do cliente.\n");
    printf("ID: ");
    ler_str(id_str, 15);
    id = str_to_int(id_str);

    for(int i = 0; i < 2; i++){
        /*  Verifica lista 1 (lista de reservas)  */
        if(i == 0) aux = lista_r->prox;
        /*  Caso não seja encontrado na lista 1  */
        /*  Verifica lista 2 (lista de pré-reservas)  */
        else if((i == 1) && (!id_ok)) aux = lista_p->prox;

        /* Percorre a lista até ao último cliente ou até o cliente ser encontrado */
        while((aux) && (!id_ok)){
            /* Caso o ID seja igual ao procurado e o nome não tenha sido "descartado" */
            if((aux->cliente.id == id) && (strcmp(aux->cliente.nome, last_nome) != 0)){
                escolha = 0;
                while(escolha != 1 && escolha != 2){
                    printf("\nO cliente a que se refere é: %s?\n", aux->cliente.nome);
                    printf("[1]->Sim\n");
                    printf("[2]->Não\n");
                    ler_escolha(&escolha);
                    printf("\n");
                }
                if(escolha == 1){
                    id_ok = 1;
                    free(last_nome);
                    break;
                }
                else if(escolha == 2) strcpy(last_nome, aux->cliente.nome);
            }
            aux = aux->prox;
        }
    }
    
    /* Caso o cliente não tenha sido encontrado volta ao menu inicial */
    if(!id_ok) printf("Erro...\nCliente não encontrado...\n\nA voltar ao menu inicial");
    /* Caso contrário, imprime todas as ocorrências do cliente nas duas listas com a data e hora do serviço agendado */
    else{
        int horas, minutos;
        printf("--> Cliente: %s\n", aux->cliente.nome);
        for(int i = 0; i < 2; i++){
            if(i == 0){
                printf("<----------/ LISTA DE RESERVAS /---------->\n");
                aux = lista_r->prox;
            }
            else if(i == 1){
                printf("<----------/ LISTA DE PRÉ-RESERVAS /---------->\n");
                aux = lista_p->prox;
            }
            while(aux){
                if(aux->cliente.id == id){
                    double_hora_to_ints(aux->cliente.data.hora, &horas, &minutos);
                    printf("\n");
                    printf(" Data   --> %d/%d/%d\n", aux->cliente.data.dia, aux->cliente.data.mes, aux->cliente.data.ano);
                    printf(" Hora   --> %.2d:%.2d\n", horas, minutos);
                    if(aux->cliente.servico == 1) printf("Serviço --> Lavagem\n");
                    else if(aux->cliente.servico == 2) printf("Serviço --> Manutenção\n");
                    printf("\n");
                    printf("---------------------------\n");
                }
                aux = aux->prox;
            }
        }
        printf("----------/ FIM /----------\n");
    }
}

/* Cancela uma reserva específica, procurando por ID passado pelo utilizador */
int cancelar_reserva(pLista lista, pLista lista2){
    char id_str[15];
    int id, escolha = 0;
    unsigned short int ok = 0;
    pLista aux, ant, ant2, primeiro;
    aux = (pLista) malloc(sizeof(noLista));
    aux = lista->prox;
    ant = lista;

    printf("Insira o ID da pessoa que deseja cancelar a reserva.\n");
    printf("ID: ");
    ler_str(id_str, 15);
    id = str_to_int(id_str);

    while(aux){
        if(aux->cliente.id == id){
            while((escolha != 1) && (escolha != 2)){
                printf("\n\n");
                imprime_cliente(aux->cliente);
                printf("É esta reserva que pretende cancelar?\n");
                printf("[1]->Sim\n");
                printf("[2]->Não\n");
                ler_escolha(&escolha);
                if(escolha == 1 || escolha == 2) break;
                else mensagem_erro("Escolha inválida");
            }
            if(escolha == 1){
                procura_cliente_l(lista2, aux->cliente, &ant2, &primeiro, 1, 0);
                if(primeiro != NULL){
                    if(ant != lista){
                        if((aux->prox != NULL)){
                            if((compara_data(aux->prox->cliente.data, aux->cliente.data) == 1) || (((aux->prox->cliente.data.hora) - (ant->cliente.data.hora + tempo_servico(ant->cliente.servico))) >= tempo_servico(primeiro->cliente.servico)) && ((primeiro->cliente.data.hora + tempo_servico(primeiro->cliente.servico)) <= aux->prox->cliente.data.hora)) ok = 1;
                        }
                        else ok = 1;
                    }
                    else if(aux->prox != NULL){
                        if((compara_data(aux->prox->cliente.data, aux->cliente.data) == 1) || ((primeiro->cliente.data.hora + tempo_servico(primeiro->cliente.servico)) <= aux->prox->cliente.data.hora)) ok = 1;
                    }
                    else ok = 1;
                }
                
                if(ok == 1){
                    aux->cliente = primeiro->cliente;
                    ant2->prox = primeiro->prox;
                    free(primeiro);
                }
                else{
                    ant->prox = aux->prox;
                    free(aux);
                }
                return 0;
            }
        }
        aux = aux->prox;
        ant = ant->prox;
    }
    return 1;
}


 /* 
  * Identificação de Clientes
  * -------------------------
  */

/* Procura por um cliente numa lista */
/* Notas: */
/* --> hora == 1, compara as horas ; hora == 0, não compara as horas */
/* --> mode == 'r', procura sabendo que é uma lista de reservas ; mode == 'p', procura sabendo que é uma lista de pré-reservas ; mode == 0, caso particular para cancelamento de reservas */
void procura_cliente_l(pLista lista, Cliente cliente, pLista *ant, pLista *actual, int hora, int mode){
    *ant = lista; *actual = lista->prox;
    while(((*actual) != NULL) && ((compara_data((*actual)->cliente.data, cliente.data) == 2) || ((hora == 1) && (compara_data((*actual)->cliente.data, cliente.data) == 0) && (compara_hora((*actual)->cliente.data.hora, cliente.data.hora) == 2)) || ((mode == 'p') && (hora == 1) && (compara_data((*actual)->cliente.data, cliente.data) == 0) && ((compara_hora((*actual)->cliente.data.hora, cliente.data.hora) == 0) || (compara_hora((*actual)->cliente.data.hora, cliente.data.hora) == 2))))){
        *ant = *actual;
        *actual = (*actual)->prox;
    }
    if(((hora == 1) && (mode == 'r')) && (*actual) != NULL && (*actual)->cliente.nome != cliente.nome) *actual = NULL;
    else if((hora == 0) && ((mode == 'p') || (mode == 0)) && (*actual) != NULL){
        if(compara_data((*actual)->cliente.data, cliente.data) != 0) *actual = NULL;
    }
}

/* Pergunta o ID do cliente e, caso este seja encontrado em alguma lista, é-lhe associado o respetivo 'id' e 'nome' */
/* Return 1-> id/nome não atribuídos (cliente não encontrado) ; Return 0-> id/nome atribuídos (pode ter sido encontrado ou não o cliente) */
int pergunta_id(pLista lista_r, pLista lista_p, int *id, char * nome){
    int escolha;
    char id_str[15];
    char * last_nome = (char *) malloc(30 * sizeof(char));
    pLista aux;

    printf("\nInsira o ID do cliente.\n");
    printf("ID: ");
    ler_str(id_str, 15);
    *id = str_to_int(id_str);

    /* Verificação do ID nas duas listas */
    /* Assim que o ID é identificado e verificado em uma das listas, return */
    for(int i = 0; i < 2; i++){
        if(i == 0) aux = lista_r->prox;
        else if(i == 1) aux = lista_p->prox;

        while(aux){
            if((aux->cliente.id == (*id)) && (strcmp(aux->cliente.nome, last_nome) != 0)){
                escolha = 0;
                while(escolha != 1 && escolha != 2){
                    printf("\nO cliente a que se refere é: %s?\n", aux->cliente.nome);
                    printf("[1]->Sim\n");
                    printf("[2]->Não\n");
                    ler_escolha(&escolha);
                    printf("\n");
                }
                if(escolha == 1){
                    strcpy(nome, aux->cliente.nome);
                    free(last_nome);
                    return 0;
                }
                else if(escolha == 2) strcpy(last_nome, aux->cliente.nome);
            }
            aux = aux->prox;
        }
    }

    /*  Caso não seja identificado ou validado em nenhuma das listas  */
    free(last_nome);
    escolha = 0;
    while(escolha != 1 && escolha != 2){
        printf("Cliente não encontrado, deseja criar um novo cliente?\n");
        printf("[1]->Sim\n");
        printf("[2]->Não\n");
        ler_escolha(&escolha);
        printf("\n");
    }
    if(escolha == 1){
        define_nome(nome, 30);
        (*id) = 0;
        return 0;
    }
    else if(escolha == 2) return 1;
    else{
        printf("Erro...\nA voltar ao mneu incial...\n\n");
        return 1;
    }
}


 /* 
  * Interação com Datas
  * -------------------
  */

/* Verifica as horas disponíveis, sabendo o serviço desejado, na 'data' e armazena-as no vetor 'horas_disponiveis[]' */
/* Return 1-> 0 Erros ; Return 0-> Erros na allocação de memória */
int determinar_horas_disponiveis(pLista lista, Data data, int servico, double horas_disponiveis[]){
    pLista * primeiro;
    primeiro = (pLista *) malloc(sizeof(pLista));
    if(primeiro != NULL){
        /* A variável 'primeiro' é um ponteiro para o primeiro cliente com uma data igual ou mais tardia que a data indicada */
        procura_data(lista, data, primeiro);
        
        /* Caso o dia esteja vazio */
        if(((*primeiro) == NULL) || (compara_data((*primeiro)->cliente.data, data) == 1)){
            for(int i = 0; i < (N_HORAS_DE_TRABALHO - servico); i++) horas_disponiveis[i] = HORAS_DE_TRABALHO[i]; //menos o serviço que é os valores que não fazem parte das horas disponiveis ex: se for limpeza o ultimo é 17,5 se for manutenção o ultimo é 17
        }
        /* Caso contrário */
        else{
            double duracao = 0, hora_fim_ant = 0;
            int count = 0, j = 0;

            /* Algoritmo para determinar quantos clientes tem ao longo do dia */
            pLista * aux;
            aux = (pLista *) malloc(sizeof(pLista));
            if(aux != NULL){
                *aux = (*primeiro);
                while(((*aux) != NULL) && (compara_data((*aux)->cliente.data, data) == 0)){
                    count += 1;
                    *aux = (*aux)->prox;
                }
            }
            else return 0;
            free(aux);

            /* Algoritmo para identificar as horas disponíveis no dia e armazenar no vetor passado por referência */
            while(count >= 0){
                if(((*primeiro)->cliente.data.hora != hora_fim_ant) && (count > 0)){
                    for(int i = 0; i < N_HORAS_DE_TRABALHO - servico; i++){
                        if((HORAS_DE_TRABALHO[i] >= hora_fim_ant) && ((HORAS_DE_TRABALHO[i] + tempo_servico(servico)) <= (*primeiro)->cliente.data.hora)){
                            horas_disponiveis[j] = HORAS_DE_TRABALHO[i];
                            j++;
                        }
                        else if((HORAS_DE_TRABALHO[i] + servico) > (*primeiro)->cliente.data.hora) break;
                    }
                }
                else if(count == 0){
                    for(int i = 0; i < (N_HORAS_DE_TRABALHO - servico); i++){
                        if(HORAS_DE_TRABALHO[i] >= hora_fim_ant){
                            horas_disponiveis[j] = HORAS_DE_TRABALHO[i];
                            j++;
                        }
                    }
                }

                count--;
                duracao = tempo_servico((*primeiro)->cliente.servico);
                hora_fim_ant = (*primeiro)->cliente.data.hora + duracao;
                if(count != 0) (*primeiro) = (*primeiro)->prox;
            }
        }
    }
    else return 0;
    free(primeiro);
    return 1;
}

/* Procura por um cliente com uma data >= à 'data', armazenando o ponteiro em 'primeiro' */
void procura_data(pLista lista, Data data, pLista * primeiro){
    *primeiro = lista->prox;
    while(((*primeiro) != NULL) && (compara_data((*primeiro)->cliente.data, data) == 2)) *primeiro = (*primeiro)->prox;
}

/* Verifica se alguma data é inválida (passada) nas duas listas, caso haja alguma, é retirada da lista */
void verifica_data_listas(pLista lista_r, pLista lista_p){
    pLista aux, ant, temp_ptr;

    for(int i = 0; i < 2; i++){
        /* Varifica lista reservas */
        if(i == 0){
            ant = lista_r;
            aux = lista_r->prox;
        }
        /* Varifica lista pré-reservas */
        else if(i == 1){
            ant = lista_p;
            aux = lista_p->prox;
        }

        if(aux != NULL){
            while(!valida_data(aux->cliente.data.dia, aux->cliente.data.mes, aux->cliente.data.ano)){
                ant->prox = aux->prox;
                temp_ptr = (pLista) malloc(sizeof(noLista));
                temp_ptr = aux;
                aux = aux->prox;
                free(temp_ptr);
            }
        }
    }
}


 /* 
  * Leitura/Escrita em Ficheiros
  * ----------------------------
  */

/* Analisa um ficheiro de texto e armazena a informação na 'lista' (consoante o 'mode') */
void analisar_ficheiro(pLista lista, FILE * f, int mode){
    Cliente * c;
    Data fulldata;
    char token[40], nome[30], ID[15], data[14], hora[8], servico[4];
    char *space, *str;
    int dia, mes, ano, servico_int;
    double horas;
    unsigned short int count = 0;

    while(fgets(token, 40, f) != NULL){
        space = strtok(token, "-->");
        str = strtok(NULL, "-->");
        if(strstr(space, "Nome") != NULL){
            strcpy(nome, str);
            removeChar(nome, ' ');
            nome[strcspn(nome, "\n")] = 0;
            count++;
        }
        else if(strstr(space, "ID") != NULL){
            strcpy(ID, str);
            count++;
        }
        else if(strstr(space, "Data") != NULL){
            strcpy(data, str);
            dia = str_to_int(strtok(data, "/"));
            mes = str_to_int(strtok(NULL, "/"));
            ano = str_to_int(strtok(NULL, "/"));
            count++;
        }
        else if(strstr(space, "Hora") != NULL){
            strcpy(hora, str);
            horas = str_to_int(strtok(hora, ":"));
            if(str_to_int(strtok(NULL, ":")) == 30) horas += 0.5;
            count++;
        }
        else if(strstr(space, "Serviço") != NULL){
            strcpy(servico, str);
            if(strstr(servico, "Limpeza") != NULL) servico_int = 1;
            else servico_int = 2;
            count++;
        }

        if(count == 5){
            fulldata.dia = dia;
            fulldata.mes = mes;
            fulldata.ano = ano;
            fulldata.hora = horas;
            c = cria_cliente(nome, fulldata, servico_int, str_to_int(ID));
            insere_cliente_l(lista, *c, mode);
            count = 0;
        }
    }
}

/* Reescreve o ficheiro com a informação atual da 'lista' (consoante o 'mode') */
void atualizar_ficheiro(pLista lista, FILE * f, int mode){
    pLista aux;
    aux = lista->prox;
    int horas, minutos;
    if(mode == 'r') fprintf(f, "<----------/ LISTA DE RESERVAS /---------->\n");
    else if(mode == 'p') fprintf(f, "<----------/ LISTA DE PRÉ-RESERVAS /---------->\n");
    while(aux != NULL){
        double_hora_to_ints(aux->cliente.data.hora, &horas, &minutos);
        fprintf(f, "\n");
        fprintf(f, " Nome   --> %s\n", aux->cliente.nome);
        fprintf(f, "  ID    --> %d\n", aux->cliente.id);
        fprintf(f, " Data   --> %.2d/%.2d/%d\n", aux->cliente.data.dia, aux->cliente.data.mes, aux->cliente.data.ano);
        fprintf(f, " Hora   --> %.2d:%.2d\n", horas, minutos);
        if(aux->cliente.servico == 1) fprintf(f, "Serviço --> Limpeza\n");
        else if(aux->cliente.servico == 2) fprintf(f, "Serviço --> Manutenção\n");
        fprintf(f, "\n");
        fprintf(f, "---------------------------\n");
        aux = aux->prox;
    }
    fprintf(f, "----------/ FIM /----------\n");
}
