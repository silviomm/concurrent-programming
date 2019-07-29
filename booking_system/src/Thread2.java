import java.util.Random;

//import java.util.List;

public class Thread2 implements Runnable {

	private Assento[] assentos;//Vetor de estado dos assentos
	private int id;//id da thread
	private Funcoes func;//cópia do monitor
	
	//Construtor
	public Thread2(Funcoes func, int id, Assento[] assentos) {
		this.func = func;
		this.id = id;
		this.assentos = assentos;
	}

	@Override
	public void run() {

		func.visualizaAssentos(assentos, id);
		func.alocaAssentoDado(assentos, assentos[aleatorio()], id);
		func.visualizaAssentos(assentos, id);

	}
	
	public int aleatorio(){
		Random generator = new Random();
		int n = generator.nextInt(assentos.length-1);
		return n;
	}
}
