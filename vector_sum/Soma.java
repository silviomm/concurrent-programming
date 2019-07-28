
public class Soma implements Runnable{

	private V v;
	private int id;

	public Soma(V v, int id) {
		this.v = v;
		this.id = id;
	}
	
	@Override
	public void run() {
		int k = id;
		while(k < v.tam){
			v.setC(k, v.getA()[k]+v.getB()[k]);
			k = k+v.getNthreads();
		}
	}

}
