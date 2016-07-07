package TP2_Aeds;

import java.io.PrintWriter;

//A classe Campeonato representa o campeonato, o seu ranking e os times que participam deste.
public class Campeonato {
	int numTimesMax;
	Time[] times= new Time[100000];
	int times_jogaram;
	
//O método insere um novo time ao final do ranking.	
	void insereTime(Time novo){
		++times_jogaram;
		times[times_jogaram]= novo; 
		times[times_jogaram].nome= novo.nome;
	}
	
//O método ordena o campeonato pela pontuação dos times, ou seja, organiza o ranking.	
	void ordenaRanking(){
		int i=0, j=0, k=0;
		Time aux= new Time();
		for(i=2; i<=times_jogaram; i++){
			aux= times[i];
			j=i-1;
			times[0]= aux;
			while(aux.pontuacao >= times[j].pontuacao && j>0 && k!=1){
				if(aux.pontuacao==times[j].pontuacao && aux.nome.compareTo(times[j].nome)<0){
					times[j+1]= times[j];
					j--;
				}
				else if(aux.pontuacao > times[j].pontuacao){
					times[j+1]= times[j];
					j--;
				}
				else
					k=1;
			}
			times[j+1]= aux;
			k=0;
		}
	}
	
//O método realiza uma pesquisa binária e verifica a posição do time buscado no ranking.	
	int consultaRankingTime(Time time_procurado){
		int i=0, j=0, Esq=0, Dir=0;
		if(times_jogaram==0)
			return (-1);
		else{
			Esq=1;
			Dir= times_jogaram;
			i= (Esq + Dir)/2;
			while(time_procurado.pontuacao != times[i].pontuacao && Esq<=Dir){
				if(time_procurado.pontuacao < times[i].pontuacao)
					Esq= i+1;
				else
					Dir=i -1;
				i=(Esq + Dir)/2;
			}
		//Caso encontre algum time com a mesma pontuação, verificar todos os times com essa pontuação.
			while(time_procurado.pontuacao == times[i-1].pontuacao && i>1){
					i--;
			}	
			j=i;
		//Caso encontre o time procurado, retorna sua posição no vetor, ou seja, retorna seu ranking no campeonato.
			while(time_procurado.pontuacao == times[i].pontuacao && j<=times_jogaram){
				if(time_procurado.nome.compareTo(times[j].nome)==0){
					return j;
				}	
				j++;
			}
		//Se não encontrar o time procurado, retorna -1.
			return (-1);
		}
	}
	
//O método imprime a classificação do campeonato.	
	void imprime(PrintWriter saida){
		int i=1;
		while(i<=times_jogaram){
			saida.println(i+","+times[i].nome + ","+ times[i].pontuacao);
			i++;
		}
	}
	
	
	
	
}
