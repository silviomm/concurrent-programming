
public class V {

	private int[] a;
	private int[] b;
	private int[] c;
	public int tam;
	private int nthreads;

	public V(int tam, int nthreads) {
		this.tam = tam;
		this.nthreads = nthreads;
		this.a = new int[tam];
		this.b = new int[tam];
		this.c = new int[tam];
		inicializaVetores();
	}

	public int[] getA() {
		return a;
	}

	public int[] getB() {
		return b;
	}

	private void inicializaVetores() {
		System.out.println("Init");
		for (int i = 0; i < tam; i++) {
			a[i] = b[i] = i;
		}
	}

	public void setC(int i, int n){
		c[i] = n;
	}
	
	public int[] getC() {
		return c;
	}

	public int getNthreads() {
		return nthreads;
	}

}
