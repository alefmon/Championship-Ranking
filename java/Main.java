package TP2_Aeds;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.util.Scanner;

public class Main {
	private static Scanner entrada;

	public static void main(String[] args) throws FileNotFoundException, UnsupportedEncodingException{
	//Validação da entrada.	
		if(args.length!=2){
			System.out.println("ENTRADA INVÁLIDA! 2 arquivos devem ser passados como argumento.");
			System.exit(0);
		}
	//Declaração de variáveis e objetos.	
		int i=0,j=0, pos1=0, pos2=0, posic1=0, posic2=0;
		Campeonato Camp= new Campeonato();
		ListaTimes listaCamp= new ListaTimes();
		String[][] arquivo= new String[100000][3];
		entrada = new Scanner(new File(args[0]));
		PrintWriter saida= new PrintWriter(args[1], "UTF-8");
		entrada.useDelimiter(",|\\n");
	//Verificar o conteúdo do arquivo de entrada e armazenar no vetor arquivo.	
		while(entrada.hasNext()){
			arquivo [i][j]=entrada.next();
			if(j==2 && arquivo[i][j].length()>63){
				System.out.println("ENTRADA INVÁLIDA! O nome do time deve ter no máximo 63 caracteres.");
				System.exit(0);
			}	
			if(j<2)
				j++;
			else{
				i++;
				j=0;
			}
		}
		entrada.close();
		i=0;
		j=0;
	//Verificar, a cada linha da entrada, o tipo de operação que deverá ser executada pelo programa.	
		while(arquivo[i][0]!=null){
			//Verificar se o nome do time é válido.
				if(arquivo[i][1].length()>63 || arquivo[i][2].length()>63){
					System.out.println("ENTRADA INVÁLIDA! O nome do time deve ter no máximo 63 caracteres.");
					System.exit(0);
				}
			//Caso a operação seja uma consulta ao ranking ou à pontuação.	
				if(arquivo[i][0].compareTo("CONSULTA")==0){
					Time Novo= new Time();
					Novo.nome= arquivo[i][2];
					posic1=listaCamp.consultaTime(Novo);
				//Verificar se o time solicitado já está na lista dos times do campeonato.	
					if(posic1==-1){
						Novo.ranking=Camp.times_jogaram+1;
						listaCamp.insereTime(Novo);
						posic1= listaCamp.numTimes;
					}
				//Consulta ao ranking do time.	
					if(arquivo[i][1].compareTo("RANKING")==0){
					//Se o time já jogou.	
						if(listaCamp.times[posic1].jogou){
							int pos=Camp.consultaRankingTime(listaCamp.times[posic1]);
							saida.println("RANKING,"+listaCamp.times[posic1].nome+","+ pos);
						}
					//Se o time não jogou ainda.	
						else
							saida.println("RANKING,"+listaCamp.times[posic1].nome+","+ listaCamp.times[posic1].ranking);
					}
				//Consulta à pontuação do time.	
					else if(arquivo[i][1].compareTo("PONTUACAO")==0){
						saida.println("PONTUACAO," + listaCamp.times[posic1].nome+ "," + listaCamp.times[posic1].pontuacao);
					}
				//Verificar se a consulta é válida ou não.	
					else{
						System.out.println("ENTRADA INVÁLIDA! Só é possível consultar RANKING ou PONTUACAO.");
						System.exit(0);
					}
				//Reordena a lista dos times em ordem alfabética.
					listaCamp.ordenaNome();
				}
				
			//Caso a linha do arquivo de entrada informe uma vitória do time A sobre o time B.	
				else if(arquivo[i][0].compareTo("VITORIA")==0){
				//Verificar o nome dos times que jogaram.
					Time timeA= new Time();
					timeA.nome=arquivo[i][1];
					Time timeB= new Time();
					timeB.nome= arquivo[i][2];
				//Consultar a posição dos times na lista.	
					posic1= listaCamp.consultaTime(timeA);
					posic2= listaCamp.consultaTime(timeB);
				//Caso o time A já esteja na lista dos times.		
					if(posic1!= -1){
						timeA.pontuacao= listaCamp.times[posic1].pontuacao;
						pos1= Camp.consultaRankingTime(timeA);
					}
				//Caso o time B já esteja na lista dos times.
					if(posic2!= -1){
						timeB.pontuacao= listaCamp.times[posic2].pontuacao;
						pos2= Camp.consultaRankingTime(timeB);
					}
				//Caso o time A ainda não tenha sido mencionado no arquivo de entrada.			
					if(posic1== -1){
						Camp.insereTime(timeA);
						listaCamp.insereTime(timeA);
						pos1= Camp.times_jogaram;
						posic1= listaCamp.numTimes;
					}
				//Caso o time B ainda não tenha sido mencionado no arquivo de entrada.		
					if(posic2== -1){
						Camp.insereTime(timeB);
						listaCamp.insereTime(timeB);
						pos2= Camp.times_jogaram;
						posic2= listaCamp.numTimes;
					}
				//Caso seja o primeiro jogo do time A.
					if(pos1== -1){
						Camp.insereTime(timeA);
						pos1= Camp.times_jogaram;
					}
				//Caso seja o primeiro jogo do time B.	
					if(pos2== -1){
						Camp.insereTime(timeB);
						pos2= Camp.times_jogaram;
					}
				//Modificar a pontuação dos times que jogaram.	
					Camp.times[pos1].modificaPontuacao(3);
				//Reordenar a lista em ordem alfabética e reordenar o ranking do campeonato.
					Camp.ordenaRanking();
					for(j=1; j<= Camp.times_jogaram; j++){
						Camp.times[j].ranking=j;
					}
					listaCamp.ordenaNome();
				}

			//Caso a linha do arquivo de entrada informe um EMPATE entre os times A e B.	
				else if(arquivo[i][0].compareTo("EMPATE")==0){
					//Verificar o nome dos times que jogaram.
					Time timeA= new Time();
					timeA.nome=arquivo[i][1];
					Time timeB= new Time();
					timeB.nome= arquivo[i][2];
				//Consultar a posição dos times na lista.	
					posic1= listaCamp.consultaTime(timeA);
					posic2= listaCamp.consultaTime(timeB);
				//Caso o time A já esteja na lista dos times.		
					if(posic1!= -1){
						timeA.pontuacao= listaCamp.times[posic1].pontuacao;
						pos1= Camp.consultaRankingTime(timeA);
					}
				//Caso o time B já esteja na lista dos times.
					if(posic2!= -1){
						timeB.pontuacao= listaCamp.times[posic2].pontuacao;
						pos2= Camp.consultaRankingTime(timeB);
					}
				//Caso o time A ainda não tenha sido mencionado no arquivo de entrada.			
					if(posic1== -1){
						Camp.insereTime(timeA);
						listaCamp.insereTime(timeA);
						pos1= Camp.times_jogaram;
						posic1= listaCamp.numTimes;
					}
				//Caso o time B ainda não tenha sido mencionado no arquivo de entrada.		
					if(posic2== -1){
						Camp.insereTime(timeB);
						listaCamp.insereTime(timeB);
						pos2= Camp.times_jogaram;
						posic2= listaCamp.numTimes;
					}
				//Caso seja o primeiro jogo do time A.
					if(pos1== -1){
						Camp.insereTime(timeA);
						pos1= Camp.times_jogaram;
					}
				//Caso seja o primeiro jogo do time B.	
					if(pos2== -1){
						Camp.insereTime(timeB);
						pos2= Camp.times_jogaram;
					}
				//Modificar a pontuação dos times que jogaram.	
					Camp.times[pos1].modificaPontuacao(1);
					Camp.times[pos2].modificaPontuacao(1);
				//Reordenar a lista em ordem alfabética e reordenar o ranking do campeonato.
					Camp.ordenaRanking();
					for(j=1; j<= Camp.times_jogaram; j++){
						Camp.times[j].ranking=j;
					}	
					listaCamp.ordenaNome();
				}
			//Verificar se a operação feita pelo usuário é válida ou não.	
				else{
					System.out.println("ENTRADA INVÁLIDA! O primeiro campo da linha deve ser CONSULTA, VITORIA ou EMPATE. Além disso, verifique se existem somente 3 campos por linha.");
					System.exit(0);
				}
				i++;
				pos1=0;
				posic1=0;
				pos2=0;
				posic2=0;
		}
	//Impressão da classificação final do campeonato.	
		Camp.imprime(saida);
		saida.close();
	}


}
