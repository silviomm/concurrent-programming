
public class Assento {

	private int id = 0; // id da thread que esta ocupando o assento
	private boolean ocupado = false; // booleano indicando se o assento esta
										// ocupado ou nao
	//Construtor
	public Assento() {

	}
	//Gets and Sets
	public Assento(int id, boolean ocupado) {
		this.id = id;
		this.ocupado = ocupado;
	}

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public boolean isOcupado() {
		return ocupado;
	}

	public void setOcupado(boolean ocupado) {
		this.ocupado = ocupado;
	}

}
