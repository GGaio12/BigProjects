#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "listareserva.h"
#include "oficinafunc.h"

int main(){
     /*
      * Inicializações para o início do programa
      * ----------------------------------------
      * Inicializações necessárias para o funcionamento normal do programa.
      * 
      * Notas:
      *     - As variáveis de controlo foram incializadas como 'unsigned short int' de modo a ocupar menos espaço na memória.
      */
     
    const double HORAS_DE_TRABALHO[] = {8, 8.5, 9, 9.5, 10, 10.5, 11, 11.5, 12, 12.5, 13, 13.5, 14, 14.5, 15, 15.5, 16, 16.5, 17, 17.5, 18};
    const int N_HORAS_DE_TRABALHO = 21;
    char nome[30];
    double horas_disponiveis[N_HORAS_DE_TRABALHO], hora_escolhida;
    int escolha, cont, id, servico, dia, mes, ano, hora, minutos, escolha_hora, n_horas = 0;
    unsigned short int erro = 0, on = 1, done = 0, servico_ok = 0, data_ok, hora_ok, next_action = 0, mudar_dia = 1, fazer_prereserva = 0;
    Data data;
    
     /*
      * Leitura dos dados dos ficheiros
      * -------------------------------
      * Primeiro o Programa lê o ficheiro e cria uma lista de reservas consoante a informação do ficheiro
      * De seguida repete o processo para o ficheiro de lista de espera.
      * 
      * Notas:
      *     - Caso qualquer um dos dois ficheiros ou listas tenha valores inválidos e/ou não sejam encontrados,
      *     o Programa não é executado.
      */
    
    pLista reservas;
    reservas = cria_lista();
    FILE * f;
    f = fopen("Lista Reservas.txt", "r");
    if(f != NULL){
        if(reservas == NULL) erro = 1;
        else analisar_ficheiro(reservas, f, 'r');
        fclose(f);
    }
    else erro = 1;

    pLista prereservas;
    prereservas = cria_lista();
    f = fopen("Lista PreReservas.txt", "r");
    if(f != NULL){
        if(prereservas == NULL) erro = 1;
        else analisar_ficheiro(prereservas, f, 'p');
        fclose(f);
    }
    else erro = 1;

    if(erro){
        printf("Erro...\n");
        printf("\n<< ... A encerrar o programa ... >>\n");
        on = 0;
    }

    /*
     * Programa
     * --------
     */

    while(on){
         /*
          * Verificação e eliminação de datas inválidas
          * -------------------------------------------
          */

        verifica_data_listas(reservas, prereservas);

        f = fopen("Lista Reservas.txt", "w");
        atualizar_ficheiro(reservas, f, 'r');
        fclose(f);

        f = fopen("Lista PreReservas.txt", "w");
        atualizar_ficheiro(prereservas, f, 'p');
        fclose(f);

         /*
          * Menu Inicial
          * ------------
          * No Menu são apresentadas as opções básicas do utilizador para editar a sua agenda, sendo estas divididas por um 'switch'
          * o qual atua consoante o pretendido/escolhido pelo utilizador.
          * 
          * Notas:
          *     - Caso a escolha seja inválida, ou seja, o inserido não seja um número de uma escolha do menu, o programa apresenta
          *     erro e volta ao menu inicial para que o utilizador possa fazer uma nova escolha.
          */

        printf("\n\nO que pretende fazer?\n");
        printf("(Escreva o número correspondente ao que deseja)\n");
        printf("[1]->Reservar\n");
        printf("[2]->Pré Reservar\n");
        printf("[3]->Cancelar Reserva/Pré-Reserva\n");
        printf("[4]->Listar Reservas e Pré Reservas (Todas)\n");
        printf("[5]->Listar Reservas e Pré Reservas (Cliente Único)\n");
        printf("[6]->Fechar\n");
        ler_escolha(&escolha);
        printf("\n");
        switch(escolha)
        {
        case 1: /*  Reservar  */
            done = 0;
            while(!done){
                 /*
                  * Defeniçáo ID
                  * ------------
                  * Caso seja um cliente com um ID previamente atribuido, esses ID e nome associado são-lhe novamente atribuidos na nova reserva.
                  */
                
                escolha = 0;
                while((escolha != 1) && (escolha != 2)){
                    printf("Deseja registar uma reserva para um cliente novo ou para um cliente já existente?\n");
                    printf("[1]->Registar um novo cliente na lista\n");
                    printf("[2]->Registar uma nova entrada de um cliente já existente na lista\n");
                    ler_escolha(&escolha);
                    if(escolha == 1){
                        define_nome(nome, 30);
                        id = 0;
                    }
                    else if(escolha == 2){
                        done = pergunta_id(reservas, prereservas, &id, nome);
                    }
                    else mensagem_erro("Escolha inválida");
                }
                if(done == 1){
                    printf("A voltar ao menu inicial...\n");
                    break;
                }

                 /*
                  * Defenição do serviço
                  * --------------------
                  * Notas:
                  *     - Caso a escolha de serviço seja diferente de uma escolha válida (1 ou 2), é apresentado erro e é repetido
                  *     o processo até que a escolha seja válida.
                  */

                servico_ok = 0;
                while(!servico_ok){
                    define_servico(&servico);
                    if((servico != 1) && (servico != 2)) mensagem_erro("Escolha inválida");
                    else servico_ok = 1;
                }

                 /*
                  * Defenição da data e hora do serviço
                  * -----------------------------------
                  * A defenição da data é subdividada em 2 partes:
                  *  --> 'Defenição da data'
                  *  --> 'Defenição da hora'
                  * 
                  * Variaveis de controlo:
                  *   --> 'mudar_dia'        (Controla se a etapa está concluida)
                  *   --> 'data_ok'          (Controla se a data está definida)
                  *   --> 'hora_ok'          (Controla se a hora está definida)
                  *   --> 'next_action'      (Controla se a próxima ação está definida)
                  *   --> 'fazer_prereserva' (Controla se é necessário fazer uma pré reserva no próximo)
                  * 
                  * Variaveis de escolha:
                  *   --> 'hora_escolhida'   (Escolha da hora perante as horas disponíveis)
                  */

                mudar_dia = 1; 
                while(mudar_dia){
                    mudar_dia = 0;
                    data_ok = 0;
                    hora_ok = 0;
                    n_horas = 0;
                    fazer_prereserva = 0;
                    for(int i = 0; i < N_HORAS_DE_TRABALHO; i++) horas_disponiveis[i] = 0;

                     /*
                      * Defenição da data
                      * -----------------
                      * Após ser definida uma data válida passada pelo utilizador, é armazenada numa estrutura 'Data'.
                      */

                    while(!data_ok){
                        if(define_data(&dia, &mes, &ano)) data_ok = 1;
                        else mensagem_erro("Data inválida");
                    }
                    data.dia = dia;
                    data.mes = mes;
                    data.ano = ano;

                     /*
                      * Defenição da hora
                      * -----------------
                      * Apresenta todas as possíveis horas para a data escolhida tendo em conta o serviço escolhido.
                      * A hora escolhida é guardada na variável: 'hora_escolhida'
                      * 
                      * Notas:
                      *     - Caso não haja horas disponiveis, é apresentada uma escolha para utilizador onde este pode escolher entre:
                      *     1. Fazer uma pré-reserva;    2. Escolher um novo dia;    3. Voltar ao menu incial.
                      */
                    
                    while(!hora_ok){
                         /*
                          * Verificação das horas disponiveis
                          * ---------------------------------
                          * Notas:
                          *     - Caso a lista de reservas ainda esteja vazia, as horas disponiveis são todas as horas possíveis.
                          *     - Caso ocorra algum erro enquanto se determina as horas disponiveis, é apresentado erro e volta ao menu inicial.
                          */

                        if(vazia_l(reservas)){
                            for(int i = 0; i < (N_HORAS_DE_TRABALHO - servico); i++) horas_disponiveis[i] = HORAS_DE_TRABALHO[i];
                        }
                        else{
                            erro = !determinar_horas_disponiveis(reservas, data, servico, horas_disponiveis);
                            if(erro){
                                mensagem_erro("= NULL");
                                done = 1;
                                break;
                            }
                        }

                         /*
                          * Definição da hora escolhida
                          * ---------------------------
                          * Determina uma hora específica, escolhida pelo utilizador, de acordo com as horas disponiveis.
                          * 
                          * Notas:
                          *     - (i)   Caso haja horas disponiveis, são apresentadas todas as horas disponiveis e
                          *     determinada a hora escolhida pelo utilizador.
                          *     - (ii)  Caso não haja horas disponiveis é questionado se o utilizador pretende fazer
                          *     uma pré-reserva, escolher um dia diferente ou voltar ao menu inicial.
                          */
                        
                        for(int i = 0; i < (N_HORAS_DE_TRABALHO - servico); i++){
                            if(horas_disponiveis[i] >= 8) n_horas += 1;
                            else break;
                        }

                        /*  (i)  */
                        if(n_horas != 0){
                            while(!hora_ok){
                                printf("\nHoras disponiveis para dia %d/%d/%d:\n", data.dia, data.mes, data.ano);
                                for(int i = 0; i < n_horas; i++){
                                    double_hora_to_ints(horas_disponiveis[i], &hora, &minutos);
                                    printf("[%d]->%.2d:%.2d\n", i + 1, hora, minutos);
                                }
                                printf("Por favor, indique o número correspondente à hora que pretende reservar o seu serviço.\n");
                                ler_escolha(&escolha);
                                if((escolha > 0) && (escolha <= n_horas)){
                                    hora_escolhida = horas_disponiveis[escolha - 1];
                                    data.hora = hora_escolhida;
                                    hora_ok = 1;
                                    escolha = 0;
                                    printf("\n");
                                }
                                else mensagem_erro("Escolha inválida");
                            }
                        }

                        /*  (ii)  */
                        else{
                            hora_ok = 1;
                            next_action = 0;
                            while(!next_action){
                                printf("\nInfelizmente não existem horas disponiveis para o serviço que pretende.\n");
                                printf("Gostaria de:\n");
                                printf("[1]->Entrar numa lista de espera para uma hora especifica\n");
                                printf("[2]->Escolher um dia diferente\n");
                                printf("[3]->Voltar ao menu inicial\n");
                                ler_escolha(&escolha);
                                printf("\n");
                                switch (escolha)
                                {
                                case 1: /*  Pré-reserva  */
                                    hora_escolhida = 0;
                                    while(hora_escolhida == 0){
                                        for(int i = 0; i < (N_HORAS_DE_TRABALHO - servico); i++){
                                            double_hora_to_ints(HORAS_DE_TRABALHO[i], &hora, &minutos);
                                            printf("[%d]->%.2d:%.2d\n", i + 1, hora, minutos);
                                        }
                                        printf("Por favor, indique o número correspondente à hora que pretende pré reservar o seu serviço.\n");
                                        printf("(A pré reserva apenas se realizará no caso da hora escolhida ficar disponivel)\n");
                                        ler_escolha(&escolha);
                                        if((escolha > 0) && (escolha <= N_HORAS_DE_TRABALHO)){
                                            hora_escolhida = HORAS_DE_TRABALHO[escolha - 1];
                                            data.hora = hora_escolhida;
                                            escolha = 1;
                                            printf("\n");
                                        }
                                        else mensagem_erro("Escolha inválida");
                                    }
                                    fazer_prereserva = 1;
                                    done = 1;
                                    break;

                                case 2: /*  Escolher um dia diferente  */
                                    mudar_dia = 1;
                                    printf("\n");
                                    break;

                                case 3: /*  Voltar ao menu inicial  */
                                    done = 1;
                                    printf("\n");
                                    break;
                                        
                                default: /*  Erro: Escolha inválida  */
                                    mensagem_erro("Escolha inválida");
                                    break;
                                }
                                if(escolha == 1 || escolha == 2 || escolha == 3) next_action = 1;
                            }
                        }
                    } 
                }
                if(erro) break;
                
                 /*
                  * Listagem do Cliente
                  * -------------------
                  * Caso tudo esteja definido, cria um cliente com os dados obtidos e pede confirmação.
                  * (i)  Caso esteja tudo correto, o programa insere o novo cliente na lista correta e atualiza o respetivo ficheiro.
                  * (ii) Caso o utilizador decida não prosseguir com a reserva, é questionado ao mesmo se pretende voltar a preencher os dados ou se quer voltar ao menu inicial.
                  */

                if(data_ok && hora_ok && escolha != 3){
                    Cliente * cliente = cria_cliente(nome, data, servico, id);
                    if(cliente != NULL){
                        escolha = 0;
                        while((escolha != 1) && (escolha != 2)){
                            printf("\nPor favor verifique se está tudo correto.\n");
                            imprime_cliente(*cliente);
                            printf("Pretende continuar?\n");
                            printf("[1]->Sim\n");
                            printf("[2]->Não\n");
                            ler_escolha(&escolha);
                            /*  (i)  */
                            if(escolha == 1){
                                if(fazer_prereserva == 1){
                                    f = fopen("Lista PreReservas.txt", "w");
                                    if(f != NULL){
                                        insere_cliente_l(prereservas, *cliente, 'p');
                                        atualizar_ficheiro(prereservas, f, 'p');
                                        fclose(f);
                                    }
                                    else{
                                        printf("Erro...\nf = NULL\n");
                                        printf("A voltar ao menu inicial...\n");
                                    }
                                }
                                else{
                                    f = fopen("Lista Reservas.txt", "w");
                                    if(f != NULL){
                                        insere_cliente_l(reservas, *cliente, 'r');
                                        atualizar_ficheiro(reservas, f, 'r');
                                        fclose(f);
                                    }
                                    else{
                                        printf("Erro...\nf = NULL\n");
                                        printf("A voltar ao menu inicial...\n");
                                    }
                                }
                                done = 1;
                            }
                            /*  (ii)  */
                            else if(escolha == 2){
                                escolha = 0;
                                while((escolha != 1) && (escolha != 2)){
                                    printf("\nPretende voltar a preencher ou voltar ao menu inicial?\n");
                                    printf("[1]->Voltar a preencher\n");
                                    printf("[2]->Voltar ao menu inicial\n");
                                    ler_escolha(&escolha);
                                    printf("\n");
                                    if(escolha == 2) done = 1;
                                    else if(escolha != 1) mensagem_erro("Escolha inválida");
                                }
                            }
                            else mensagem_erro("Escolha inválida");
                        }
                    }
                    else{
                        mensagem_erro("= NULL");
                        done = 1;
                    }
                }
            }
            break;

        case 2: /*  Pré Reservar  */
            done = 0;
            while(!done){
                 /*
                  * Defeniçáo ID
                  * ------------
                  * Caso seja um cliente com um ID previamente atribuido, esses ID e nome associado são-lhe novamente atribuidos na nova reserva.
                  */
                
                escolha = 0;
                while((escolha != 1) && (escolha != 2)){
                    printf("Deseja registar uma pré-reserva para um cliente novo ou para um cliente já existente?\n");
                    printf("[1]->Registar um novo cliente na lista\n");
                    printf("[2]->Registar uma nova entrada de um cliente já existente na lista\n");
                    ler_escolha(&escolha);
                    if(escolha == 1){
                        define_nome(nome, 30);
                        id = 0;
                    }
                    else if(escolha == 2){
                        done = pergunta_id(reservas, prereservas, &id, nome);
                    }
                    else mensagem_erro("Escolha inválida");
                }
                if(done == 1){
                    printf("A voltar ao menu inicial...\n");
                    break;
                }

                 /*
                  * Defenição do serviço
                  * --------------------
                  * Notas:
                  *     - Caso a escolha de serviço seja diferente de uma escolha válida (1 ou 2), é apresentado erro e é repetido
                  *     o processo até que a escolha seja válida.
                  */

                servico_ok = 0;
                while(!servico_ok){
                    define_servico(&servico);
                    if((servico != 1) && (servico != 2)) mensagem_erro("Escolha inválida");
                    else servico_ok = 1;
                }

                 /*
                  * Defenição da data e hora do serviço
                  * -----------------------------------
                  * A defenição da data é subdividada em 2 partes:
                  *  --> 'Defenição da data'
                  *  --> 'Defenição da hora'
                  * 
                  * Variaveis de controlo:
                  *   --> 'data_ok'          (Controla se a data está definida)
                  *   --> 'hora_ok'          (Controla se a hora está definida)
                  * 
                  * Variaveis de escolha:
                  *   --> 'hora_escolhida'   (Escolha da hora perante as horas disponíveis)
                  */

                data_ok = 0;
                hora_ok = 0;
                for(int i = 0; i < N_HORAS_DE_TRABALHO; i++) horas_disponiveis[i] = 0;

                 /*
                  * Defenição da data
                  * -----------------
                  * Após ser definida uma data válida passada pelo utilizador, é armazenada numa estrutura 'Data'.
                  */

                while(!data_ok){
                    if(define_data(&dia, &mes, &ano)) data_ok = 1;
                    else mensagem_erro("Data inválida");
                }
                data.dia = dia;
                data.mes = mes;
                data.ano = ano;

                 /*
                  * Definição da hora escolhida
                  * ---------------------------
                  * Determina uma hora específica, escolhida pelo utilizador, para fazer uma pré reserva.
                  */
                    
                while(!hora_ok){
                    for(int i = 0; i < (N_HORAS_DE_TRABALHO - servico); i++){
                        double_hora_to_ints(HORAS_DE_TRABALHO[i], &hora, &minutos);
                        printf("[%d]->%.2d:%.2d\n", i + 1, hora, minutos);
                    }
                    printf("Por favor, indique o número correspondente à hora que pretende pré reservar o seu serviço.\n");
                    printf("(A pré reserva apenas se realizará no caso da hora escolhida ficar disponivel)\n");
                    ler_escolha(&escolha);
                    if((escolha > 0) && (escolha <= (N_HORAS_DE_TRABALHO - servico))){
                        hora_escolhida = HORAS_DE_TRABALHO[escolha - 1];
                        data.hora = hora_escolhida;
                        hora_ok = 1;
                        printf("\n");
                    }
                    else mensagem_erro("Escolha inválida");
                }

                 /*
                  * Listagem do Cliente
                  * -------------------
                  * Caso tudo esteja definido, cria um cliente com os dados obtidos e pede confirmação.
                  * (i)  Caso esteja tudo correto, o programa insere o novo cliente na lista de pré reservas e atualiza o ficheiro.
                  * (ii) Caso o utilizador decida não prosseguir com a reserva, é questionado ao mesmo se pretende voltar a preencher os dados ou se quer voltar ao menu inicial.
                  */

                if(data_ok && hora_ok){
                    Cliente * cliente = cria_cliente(nome, data, servico, id);
                    if(cliente != NULL){
                        escolha = 0;
                        while((escolha != 1) && (escolha != 2)){
                            printf("\nPor favor verifique se está tudo correto.\n");
                            imprime_cliente(*cliente);
                            printf("Pretende continuar?\n");
                            printf("[1]->Sim\n");
                            printf("[2]->Não\n");
                            ler_escolha(&escolha);
                            /*  (i)  */
                            if(escolha == 1){
                                f = fopen("Lista PreReservas.txt", "w");
                                if(f != NULL){
                                    insere_cliente_l(prereservas, *cliente, 'p');
                                    atualizar_ficheiro(prereservas, f, 'p');
                                    fclose(f);
                                }
                                else{
                                    printf("Erro...\nf = NULL\n");
                                    printf("A voltar ao menu inicial...\n");
                                }
                                done = 1;
                            }
                            /*  (ii)  */
                            else if(escolha == 2){
                                escolha = 0;
                                while((escolha != 1) && (escolha != 2)){
                                    printf("\n\nPretende voltar a preencher ou voltar ao menu inicial?\n");
                                    printf("[1]->Voltar a preencher\n");
                                    printf("[2]->Voltar ao menu inicial\n");
                                    ler_escolha(&escolha);
                                    printf("\n");
                                    if(escolha == 2) done = 1;
                                    else if(escolha != 1) mensagem_erro("Escolha inválida");
                                }
                            }
                            else mensagem_erro("Escolha inválida");
                        }
                    }
                }
            }
            break;

        case 3: /*  Cancelar Reserva/Pré-Reserva  */
            escolha = 0;
            while(escolha != 1 && escolha != 2){
                printf("Pretende cancelar uma reserva ou uma pré-reserva?\n");
                printf("[1]->Reserva\n");
                printf("[2]->Pré-Reserva\n");
                ler_escolha(&escolha);
                printf("\n");
            }

            if(escolha == 1) erro = cancelar_reserva(reservas, prereservas);
            else if(escolha == 2) erro = cancelar_reserva(prereservas, prereservas);
            
            if(!erro){
                f = fopen("Lista Reservas.txt", "w");
                if(f != NULL){
                    atualizar_ficheiro(reservas, f, 'r');
                    fclose(f);
                }
                else{
                    mensagem_erro("Erro Ficheiro");
                    printf("\n<< ... A encerrar o programa ... >>\n");
                    done = 1;
                    break;
                }

                f = fopen("Lista PreReservas.txt", "w");
                if(f != NULL){
                    atualizar_ficheiro(prereservas, f, 'p');
                    fclose(f);
                }
                else{
                    mensagem_erro("Erro Ficheiro");
                    printf("\n<< ... A encerrar o programa ... >>\n");
                    done = 1;
                }
            }   
            else if(erro) printf("Erro...\nCliente não encontrado na lista.\n");
            break;

        case 4: /*  Listar Reservas/Pré-Reservas (Todas)  */
            escolha = 0;
            while(escolha != 1 && escolha != 2){
                printf("Pretende ver a lista de reservas ou pré-reservas?\n");
                printf("[1]->Reserva\n");
                printf("[2]->Pré-Reserva\n");
                ler_escolha(&escolha);
                printf("\n");
            }

            if(escolha == 1) imprime_lista(reservas, 'r');
            else if(escolha == 2) imprime_lista(prereservas, 'p');
            printf("\nClick 'Enter' para continuar...\n");
            fgets(nome, 2, stdin);
            break;

        case 5: /*  Listar Reservas/Pré-Reservas (Cliente Único)  */
            imprime_reservas_c(reservas, prereservas);
            printf("\nClick 'Enter' para continuar...\n");
            fgets(nome, 2, stdin);
            break;

        case 6: /*  Fechar  */
            printf("\n<< ... A encerrar o programa ... >>\n");
            on = 0;
            break;

        default: /*  No caso da escolha ser inválida  */
            mensagem_erro("Escolha inválida");
            break;
        }
    }

    reservas = destroi_lista(reservas);
    prereservas = destroi_lista(prereservas);
    return 0;
}
