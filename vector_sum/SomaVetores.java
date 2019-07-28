import java.util.Scanner;

public class SomaVetores {

	private static int nthreads;
	private static int tam;
	

	public static void main(String[] args) throws InterruptedException {
		
		Scanner in = new Scanner(System.in);
		
		System.out.println("Tamanho do vetor...");
		tam = in.nextInt();
		System.out.println("Numero de threads...");
		nthreads = in.nextInt();
		
		Thread[] threads = new Thread[nthreads];

		V v = new V(tam, nthreads);

		criaThreads(threads, v);

		startaThreads(threads);

		esperaTerminar(threads);

//		System.out.print("A: ");
//		imprime(v.getA());
//		System.out.print("B: ");
//		imprime(v.getB());
//		System.out.print("C: ");
//		imprime(v.getC());
	}

	private static void imprime(int[] v) {
		System.out.print("[");
		for (int i = 0; i < tam; i++) {
			if(i != tam-1)
				System.out.print(v[i]+",");
			else
				System.out.print(v[i]);
		}
		System.out.println("]");
	}

	private static void esperaTerminar(Thread[] threads) throws InterruptedException {
		for (int i = 0; i < threads.length; i++) {
			System.out.println("Esperando thread: " + i);
			threads[i].join();
		}
	}

	private static void startaThreads(Thread[] threads) {
		for (int i = 0; i < threads.length; i++) {
			System.out.println("Rodando a thread: "+i);
			threads[i].start();
		}
	}

	private static void criaThreads(Thread[] threads, V v) {
		for (int i = 0; i < threads.length; i++) {
			System.out.println("Criando a thread: " + i);
			threads[i] = new Thread(new Soma(v, i));
		}
	}

}
