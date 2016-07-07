package TP2_Aeds;

//A classe representa a lista dos times que são mencionados no arquivo de entrada.
public class ListaTimes {
	int numTimes;
	Time[] times= new Time[100000];

//O método insere um novo time no final da lista.	
	void insereTime(Time novo){
		++numTimes;
		times[numTimes]= novo; 
		times[numTimes].nome= novo.nome;
	}
//O método ordena a lista, em ordem alfabética.
	void ordenaNome(){
		int j=0, k=0;
		Time aux= new Time();
		for(k=2; k<=numTimes; k++){
			aux=times[k];
			j=k-1;
			times[0]= aux;
			while (aux.nome.compareTo(times[j].nome)<0 && j>0){
				times[j+1]= times[j];
				j--;
			}
			times[j+1]= aux;
		}
	}	
//O método realiza uma pesquisa binária para verificar a posição de um time na lista.	
	int consultaTime(Time time_procurado){
		int i=0, Esq=0, Dir=0;
		if(numTimes==0)
			return (-1);
	//Caso exista algum time no vetor, fazer pesquisa binária e verificar sua posição na lista.	
		else{
			Esq =1;
			Dir= numTimes;
			i= (Esq+Dir)/2;
			while(time_procurado.nome.compareTo(times[i].nome)!=0 && Esq<=Dir){
				if(time_procurado.nome.compareTo(times[i].nome)>0)
					Esq= i+1;
				else
					Dir= i-1;
				i= (Esq+Dir)/2;
			}
	
		//Caso encontre o time procurado, retornar sua posição na lista em ordem alfabética.	
			if (time_procurado.nome.compareTo(times[i].nome)==0)
				return i;
		//Se não encontrar o time procurado, retorna -1.	
			return (-1);
		}
	}
	
}
