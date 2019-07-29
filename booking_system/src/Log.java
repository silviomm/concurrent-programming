
public class Log {
	private int func;
	private int id;
	private int retorno;
	private Assento[] estado;

	public Log(int func, int id, int retorno, Assento[] estado) {
		this.func = func;
		this.id = id;
		this.retorno = retorno;
		this.estado = new Assento[estado.length];
		for (int i = 0; i < estado.length; i++) {
			this.estado[i] = new Assento(estado[i].getId(), estado[i].isOcupado());
		}
	}

	public int getRetorno() {
		return retorno;
	}

	public int getId() {
		return id;
	}

	public int getFunc() {
		return func;
	}

	public Assento[] getEstado() {
		return estado;
	}

	public void imprimeEstado() {

	}

}
