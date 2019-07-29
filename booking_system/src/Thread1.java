public class Thread1 implements Runnable {

	int id;
	private Assento[] assentos; // vetor de assentos compartilhado entre as
								// threads
	private Funcoes func;//Cópia do monitor

	//Construtor
	public Thread1(Funcoes func, int id, Assento[] assentos) {
		this.func = func;
		this.id = id;
		this.assentos = assentos;
	}

	@Override
	public void run() {

		func.visualizaAssentos(assentos, id);
		func.alocaAssentoLivre(assentos, id);
		func.visualizaAssentos(assentos, id);

	}
}
