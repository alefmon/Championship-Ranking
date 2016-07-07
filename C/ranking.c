#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "TAD_time.h"

int main(int argc, char const *argv[]){

//Validação da entrada.
	if(argc!=3){
		printf("ENTRADA INVÁLIDA! 2 Arquivos devem ser passados como argumento.\n");
		exit(0);
	}
//Variáveis.
	int i=0, j=0, k=0, num_linhas=0, quant_times=0, quant_times_jogaram=0;
	char *consulta="CONSULTA", *vitoria="VITORIA", *empate="EMPATE";
	char *info;
//Arquivos passados como argumento.
	FILE *ent, *saida;
	ent= fopen(argv[1], "r");
	saida= fopen(argv[2], "w");
//Verificar o número de linhas do arquivo de entrada.
	char linha[1000];
	while(fgets(linha,1000,ent)!= NULL){		
		num_linhas++;
	}
	fclose(ent);
	ent= fopen(argv[1], "r");
//Vetor que receberá as informações do arquivo de entrada.
	entrada* vetor;
	vetor= (entrada*) malloc(num_linhas*sizeof(entrada));
	for(j=0; j<num_linhas; j++){
		for(k=0; k<64; k++){
			vetor[j].elemento1[k]=0;
			vetor[j].elemento2[k]=0;
			vetor[j].elemento3[k]=0;
		}	
	}	
//Alocar as linhas da entrada em um vetor.	
	verifica_entrada(ent, vetor);
//Criar dois vetores de times, que contém o nome de todos, a pontuaçao e a classificação. Um será ordenado por ordem alfabética e o outro pela pontuação.
	time *campeonato, *times_camp;
	campeonato= (time*) malloc((2*num_linhas+1)*sizeof(time));
	times_camp= (time*) malloc((2*num_linhas+1)*sizeof(time));
//Inicilaizar os vetores.	
	for(j=0; j<(2*num_linhas+1); j++){
		for(k=0; k<64; k++){
			campeonato[j].nome[k]=0;
			times_camp[j].nome[k]=0;
		}
		campeonato[j].ranking=0;
		times_camp[j].ranking=0;
		campeonato[j].pontuacao=0;
		times_camp[j].pontuacao=0;
		campeonato[j].flag_jogou=0;
		times_camp[j].flag_jogou=0;
	}
//Verificar o conteúdo da entrada, organizar o campeonato e efetuar as operações solicitadas pelo usuário.	
	while(i< num_linhas){
			info= vetor[i].elemento1;
			//Caso a linha contenha uma requisição de consulta.	
				if(strcmp(info, consulta)==0){
					operacao_consulta(saida, vetor, campeonato, times_camp, &i, &quant_times, &quant_times_jogaram);
				}
			//Caso a linha contenha uma informação de vitória em alguma partida.
				else if(strcmp(info, vitoria)==0){
					armazena_vitoria(vetor, campeonato, times_camp, &i, &quant_times, &quant_times_jogaram);
				}
			//Caso a linha contenha uma informação de empate em alguma partida.
				else if(strcmp(info, empate)==0){
					armazena_empate(vetor, campeonato, times_camp, &i, &quant_times, &quant_times_jogaram);
				}
			//Validação da entrada.
				else{
					printf("ENTRADA INVÁLIDA! O primeiro campo da linha deve ser CONSULTA, VITORIA ou EMPATE.\n");
					exit(0);
				}	
				i++;	
	} 
//Impressão do ranking final do campeonato no arquivo de saída.
	for(i=1; i<= quant_times_jogaram; i++){
			fprintf(saida, "%d,%s,%d\n", i,campeonato[i].nome,campeonato[i].pontuacao);
	}
	free(vetor);
	free(campeonato);
	free(times_camp);
	fclose(ent);
	fclose(saida);
	return 0;
}