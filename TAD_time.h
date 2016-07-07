#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#ifndef RANK_H
#define RANK_H

//Tipo de dados criado para representar cada linha do arquivo de entrada.
typedef struct{
	char elemento1[64];
	char elemento2[64];
	char elemento3[64];
}entrada;

//Tipo de dados usado para representar um time.
typedef struct{
	char nome[64];
	int ranking;
	int pontuacao;
	int flag_jogou;
}time;

//A função verifica o arquivo de entrada e aloca cada linha do arquivo em uma posição do vetor.
void verifica_entrada(FILE* ent, entrada* vetor);

//A função realiza a consulta do ranking ou da pontuação do time solicitado. Depois, ela imprime no arquivo de saída o resultado da consulta.
void operacao_consulta(FILE* saida, entrada *vetor, time* campeonato, time* times_camp, int* i, int* quant_times, int* quant_times_jogaram);

//A função modifica a classificação do campeonato, caso tenha sido informado uma vitória no resultado da partida. 
void armazena_vitoria(entrada* vetor, time* campeonato, time* times_camp, int *i, int* quant_times, int* quant_times_jogaram);

//A função modifica a classificação do campeonato, caso tenha sido informado um empate no resultado da partida. 
void armazena_empate(entrada* vetor, time* campeonato, time* times_camp, int *i, int* quant_times, int* quant_times_jogaram);

//Adiciona o time no campeonato, caso ele não tenha sido incluído anteriormente, e retorna a posicao do time no vetor.
void insere_time(time time_novo, time* vetor, int* quant_times);

//A função utiliza a Pesquisa Binária para verificar a posição de um time no vetor ordenado por ordem alfabética.
int consulta_time(time time_procurado, time* times_camp, int* quant_times);

//A função utiliza a Pesquisa Binária para verificar a posição de um time no vetor ordenado pelo ranking.
int verifica_ranking(time time_procurado, time* campeonato, int* quant_times);

//A função altera a pontuação dos dois times que jogaram, de acordo com o resultado do jogo.
void modifica_pontuacao(time* vetor, int posicao1, int pont_a, int posicao2, int pont_b);

//A função utiliza o algoritmo da Inserção para ordenar o vetor de acordo com a pontuação de cada time.
void ordena_ranking(time* campeonato, int quant_times);

//A função utiliza o algoritmo da Inserção para ordenar o vetor por ordem alfabética dos times.
void ordena_nome(time* camp_times, int quant_times, time* campeonato);

#endif
