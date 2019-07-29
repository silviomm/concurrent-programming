import java.util.Random;

public class Thread3 implements Runnable {

	private Assento[] assentos;//Vetor de estado dos assentos
	private int id;// id da thread
	private Funcoes func;//Cópia do monitor
	
	//Construtor
	public Thread3(Funcoes func, int id, Assento[] assentos) {
		this.func = func;
		this.id = id;
		this.assentos = assentos;
	}

	@Override
	public void run() {

		func.visualizaAssentos(assentos, id);
		func.alocaAssentoLivre(assentos, id);
		func.visualizaAssentos(assentos, id);
		func.liberaAssento(assentos, assentos[aleatorio()], id);
		func.visualizaAssentos(assentos, id);
	}
	
	//Gera um número de assento aleatório
	public int aleatorio(){
		Random generator = new Random();
		int n = generator.nextInt(assentos.length-1);
		return n;
	}

}
