#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "TAD_time.h"

void verifica_entrada(FILE* ent, entrada* vetor){
	int i=0, j=0, k=0, m=0, flag_embranco=0;
	char matriz [3][64];
	char x, linha[1000];	
	while(fgets(linha,1000,ent)!= NULL){
		//Apagar o conteúdo da matriz que irá conter os atributos da linha lida.
			for(j=0;j<3;j++){
				for(k=0;k<64;k++)
					matriz[j][k]=0;
			}	
			j=0, k=0, m=0;
		//Cada linha da matriz recebe um atributo.
			x=linha[j];
			while(x!='\n' && x!=EOF){
				if(x==','){
					if(m==0 || flag_embranco==0){
						printf("ENTRADA INVÁLIDA! Não podem haver campos em branco.\n");
						exit(0);
					}
					k++;
					m=0;
					flag_embranco=0;
				}
				else{
					matriz[k][m]=linha[j];
					m++;
					if(!isblank(linha[j]))
						flag_embranco=1;
					//Verificar se os nomes dos times tem 63 caracteres ou menos.
					if(m==64){
						printf("ENTRADA INVÁLIDA! O nome do time deve ter no máximo 63 caracteres.\n");
						exit(0);
					}
				}	
				j++;
				x=linha[j];
			}
		//Verificar se a entrada contém o número correto de campos por linha.
			if(k!=2){
				printf("ENTRADA INVÁLIDA! Cada linha deve conter 3 atributos.\n");
				exit(0);
			}
		//Alocação dos atributos.
			strcpy(vetor[i].elemento1,matriz[0]);			
			strcpy(vetor[i].elemento2,matriz[1]);
			strcpy(vetor[i].elemento3,matriz[2]);
			i++;
	}
}	

void operacao_consulta(FILE* saida, entrada *vetor, time* campeonato, time* times_camp, int *i, int* quant_times, int* quant_times_jogaram){
	
	char *rank="RANKING", *pont="PONTUACAO";
	int pos1=0, posic1=0;
	char *info2;
	time time_a;
//Verificar o time a ser consultado.
	strcpy(time_a.nome, vetor[*i].elemento3);
	posic1= consulta_time(time_a, times_camp, quant_times);
//Se o time for novo, inserir o time no vetor.	
	if(posic1== -1){
		insere_time(time_a, times_camp, quant_times);
		posic1= (*quant_times);
		times_camp[posic1].ranking= (*quant_times_jogaram)+1;
	}
//Verificar o tipo de consulta solicitada.
	info2= vetor[*i].elemento2;
//Caso a consulta seja ao ranking do time.
	if(strcmp(info2, rank)==0){
		//Se o time já jogou, verifica a posição no ranking pelo vetor ordenado por ranking.
			if(times_camp[posic1].flag_jogou==1){
				time_a.pontuacao= times_camp[posic1].pontuacao;
				pos1= verifica_ranking(time_a, campeonato, quant_times_jogaram);
				fprintf(saida, "RANKING,%s,%d\n", campeonato[pos1].nome, campeonato[pos1].ranking);
			}
		//Se o time não jogou ainda, seu ranking é N+1.
			else
				fprintf(saida, "RANKING,%s,%d\n", times_camp[posic1].nome, times_camp[posic1].ranking);
	}
//Caso a consulta seja à pontuação do time.	
	else if(strcmp(info2, pont)==0){
		fprintf(saida, "PONTUACAO,%s,%d\n", times_camp[posic1].nome, times_camp[posic1].pontuacao);
	}	
//Validação da entrada.	
	else{
		printf("ENTRADA INVÁLIDA! Se vai fazer consulta, o segundo campo da linha deve ser RANKING ou PONTUACAO.\n");
		exit(0);
	}
//Reordenar o vetor que contém os times em ordem alfabética.	
	ordena_nome(times_camp, *quant_times, campeonato);	
}

void armazena_vitoria(entrada* vetor, time* campeonato, time* times_camp, int *i, int* quant_times, int* quant_times_jogaram){

	int j=0, pos1=0, pos2=0, posic1=0, posic2=0;
	time time_a, time_b;
//Verificar os times que jogaram.
	strcpy(time_a.nome, vetor[*i].elemento2);
	strcpy(time_b.nome, vetor[*i].elemento3);
	posic1= consulta_time(time_a, times_camp, quant_times);
	posic2= consulta_time(time_b, times_camp, quant_times);	
	if(posic1!=-1){
		time_a.pontuacao= times_camp[posic1].pontuacao;
		pos1= verifica_ranking(time_a, campeonato, quant_times_jogaram);
	}
	if(posic2!=-1){
		time_b.pontuacao= times_camp[posic2].pontuacao;
		pos2= verifica_ranking(time_b, campeonato, quant_times_jogaram);
	}
//Caso o time vencedor tenha feito sua primeira partida no campeonato e não tenha sido citado anteriormente na entrada, ele será inserido na competição e no vetor para consulta.	
	if(posic1== -1){
		insere_time(time_a, campeonato, quant_times_jogaram);
		insere_time(time_a, times_camp, quant_times);
		pos1= (*quant_times_jogaram);
		posic1= (*quant_times);
	}
//Caso o time perdedor tenha feito sua primeira partida no campeonato e não tenha sido citado anteriormente na entrada, ele será inserido na competição e no vetor para consulta.	
	if(posic2== -1){
		insere_time(time_b, campeonato, quant_times_jogaram);
		insere_time(time_b, times_camp, quant_times);
		pos2= (*quant_times_jogaram);
		posic2= (*quant_times);
	}	
//Caso o time vencedor tenha feito sua primeira partida no campeonato, mas já tenha sido citado anteriormente na entrada, ele será inserido na competição apenas.		
	if(pos1== -1){
		insere_time(time_a, campeonato, quant_times_jogaram);
		pos1= (*quant_times_jogaram);
	}	
//Caso o time perdedor tenha feito sua primeira partida no campeonato, mas já tenha sido citado anteriormente na entrada, ele será inserido na competição apenas.			
	if(pos2== -1){
		insere_time(time_b, campeonato, quant_times_jogaram);
		pos2= (*quant_times_jogaram);
	}		
//Modificar a pontuação dos times que jogaram.			
	modifica_pontuacao(times_camp, posic1, 3, posic2, 0);
	modifica_pontuacao(campeonato, pos1, 3, pos2, 0);
//Reordenar a classificação do campeonato.	
	ordena_ranking(campeonato, *quant_times_jogaram);
	for(j=1; j<= *quant_times_jogaram; j++){
		campeonato[j].ranking=j;
	}
//Reordenar o vetor que contém os times em ordem alfabética.	
	ordena_nome(times_camp, *quant_times, campeonato);
	

}

void armazena_empate(entrada* vetor, time* campeonato, time* times_camp, int *i, int* quant_times, int* quant_times_jogaram){

	int j=0, pos1=0, pos2=0, posic1=0, posic2=0;
	time time_a, time_b;
//Verificar os times que jogaram.
	strcpy(time_a.nome, vetor[*i].elemento2);
	strcpy(time_b.nome, vetor[*i].elemento3);
	posic1= consulta_time(time_a, times_camp, quant_times);
	posic2= consulta_time(time_b, times_camp, quant_times);	
	if(posic1!=-1){
		time_a.pontuacao= times_camp[posic1].pontuacao;
		pos1= verifica_ranking(time_a, campeonato, quant_times_jogaram);
	}
	if(posic2!=-1){
		time_b.pontuacao= times_camp[posic2].pontuacao;
		pos2= verifica_ranking(time_b, campeonato, quant_times_jogaram);
	}
//Caso o time 1 tenha feito sua primeira partida no campeonato e não tenha sido citado anteriormente na entrada, ele será inserido na competição e no vetor para consulta.	
	if(posic1== -1){
		insere_time(time_a, campeonato, quant_times_jogaram);
		insere_time(time_a, times_camp, quant_times);
		pos1= (*quant_times_jogaram);
		posic1= (*quant_times);
	}
//Caso o time 2 tenha feito sua primeira partida no campeonato e não tenha sido citado anteriormente na entrada, ele será inserido na competição e no vetor para consulta.	
	if(posic2== -1){
		insere_time(time_b, campeonato, quant_times_jogaram);
		insere_time(time_b, times_camp, quant_times);
		pos2= (*quant_times_jogaram);
		posic2= (*quant_times);
	}	
//Caso o time 1 tenha feito sua primeira partida no campeonato, mas já tenha sido citado anteriormente na entrada, ele será inserido na competição apenas.		
	if(pos1== -1){
		insere_time(time_a, campeonato, quant_times_jogaram);
		pos1= (*quant_times_jogaram);
	}	
//Caso o time 2 tenha feito sua primeira partida no campeonato, mas já tenha sido citado anteriormente na entrada, ele será inserido na competição apenas.			
	if(pos2== -1){
		insere_time(time_b, campeonato, quant_times_jogaram);
		pos2= (*quant_times_jogaram);
	}		
//Modificar a pontuação dos times que jogaram.			
	modifica_pontuacao(times_camp, posic1, 1, posic2, 1);
	modifica_pontuacao(campeonato, pos1, 1, pos2, 1);
//Reordenar a classificação do campeonato.	
	ordena_ranking(campeonato, *quant_times_jogaram);
	for(j=1; j<= *quant_times_jogaram; j++){
		campeonato[j].ranking=j;
	}
//Reordenar o vetor que contém os times em ordem alfabética.	
	ordena_nome(times_camp, *quant_times, campeonato);

}

void insere_time(time time_novo, time* vetor, int* quant_times){
	int x=(*quant_times+1);
	//Adiciona o time novo no vetor.
	strcpy(vetor[x].nome, time_novo.nome);
	(*quant_times)++;
}


int consulta_time(time time_procurado, time* times_camp, int* quant_times){
	int i=0, Esq=0, Dir=0;
	if ((*quant_times) == 0) 
		return (-1);
//Caso exista algum time no vetor, fazer pesquisa binária e verificar sua posição no vetor ordenado por ordem alfabética.	
	else {
		Esq = 1; 
		Dir = (*quant_times); 
			i = (Esq + Dir) / 2;
		while (strcmp(time_procurado.nome, times_camp[i].nome)!=0 && Esq <= Dir){
			if (strcmp(time_procurado.nome, times_camp[i].nome)>0) 
				Esq = i + 1; 
			else 
				Dir = i - 1;
			i = (Esq + Dir) / 2;
		}
	//Caso encontre o time procurado, retornar sua posição no vetor.
		if (strcmp(time_procurado.nome, times_camp[i].nome)==0)
			return i;
	//Se não encontrar o time procurado, retorna -1.
		return (-1);	
	} 
}

int verifica_ranking(time time_procurado, time* campeonato, int* quant_times){
	int i=0, j=0, Esq=0, Dir=0;
	if ((*quant_times) == 0) 
		return (-1);
//Caso exista algum time no vetor, fazer pesquisa binária e verificar sua posição no vetor ordenado pela classificação.		
	else {
		Esq = 1; 
		Dir = (*quant_times); 
			i = (Esq + Dir) / 2;
		while (time_procurado.pontuacao != campeonato[i].pontuacao && Esq <= Dir){
			if (time_procurado.pontuacao < campeonato[i].pontuacao ) 
				Esq = i + 1; 
			else 
				Dir = i - 1;
			i = (Esq + Dir) / 2;
		}
	//Caso encontre algum time com a mesma pontuação procurada, verificar todos os times que têm essa pontuação.
		while (time_procurado.pontuacao == campeonato[i-1].pontuacao && i>1){
			i--;	
		}
		j=i;
	//Caso encontre o time procurado, retornar sua posição no vetor.	
		while(time_procurado.pontuacao == campeonato[j].pontuacao && j<=(*quant_times)){
			if(strcmp(time_procurado.nome, campeonato[j].nome)==0)
		 		return j;
		 	j++;
		}
	//Se não encontrar o time procurado, retorna -1.	
		return (-1);
	}
}

void ordena_ranking(time* campeonato, int quant_times_jogaram){
	int i=0, j=0, k=0;
	time x;
//Ordenar o vetor pela pontuação dos times, usando o algoritmo de INSERÇÃO.
	for(i=2; i<= quant_times_jogaram; i++){
		x= campeonato[i];
		j=i-1;
		campeonato[0]= x; /*sentinela*/
		//Verificar se o time está na posição correta.
		while (x.pontuacao >= campeonato[j].pontuacao && j>0 && k!=1){
			//Se a pontuação for a mesma , ordenar por ordem alfabética.
			if(x.pontuacao==campeonato[j].pontuacao && strcmp(x.nome, campeonato[j].nome)<0){
					campeonato[j+1]= campeonato[j];				
					j--;
			}
			//Se o time tiver mais pontos que o da posição anterior, troca os times de posição.
			else if(x.pontuacao > campeonato[j].pontuacao){
				campeonato[j+1]= campeonato[j];
				j--;
			}
			else
				k=1;
		}
		campeonato[j+1]= x;
		k=0;
	}
}

void ordena_nome(time* times_camp, int quant_times, time* campeonato){
	int k=0, j=0;
	time x;
//Ordenar o vetor pela ordem alfabética do nome dos times, usando o algoritmo de INSERÇÃO.
	for(k=2; k<= quant_times; k++){
		x= times_camp[k];
		j=k-1;
		times_camp[0]= x; /*sentinela*/
		//Verificar se o time está na posição correta. Caso não esteja, troca os times de posição.
		while (strcmp(x.nome, times_camp[j].nome)<0  && j>0){
			times_camp[j+1]= times_camp[j];
			j--;
		}
		times_camp[j+1]= x;
	}	
}

void modifica_pontuacao(time* vetor, int posicao1, int pont_a, int posicao2, int pont_b){

//Modifica a pontuação dos times.
	vetor[posicao1].pontuacao+= pont_a;
	vetor[posicao2].pontuacao+= pont_b;
//Altera a flag, que agora passa a informar ao programa que o time já jogou.	
	vetor[posicao1].flag_jogou=1;
	vetor[posicao2].flag_jogou=1;
}

