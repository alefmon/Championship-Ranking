package TP2_Aeds;

//A classe Time representa uma equipe.
public class Time {
	String nome;
	int ranking;
	int pontuacao;
	boolean jogou;
	
//O método modifica a pontuação da equipe.	
	void modificaPontuacao(int valor){
		pontuacao+=valor;
		jogou=true;
	}	
	
}
