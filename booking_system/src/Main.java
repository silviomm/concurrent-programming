import java.util.ArrayList;
import java.util.List;
import java.util.Queue;
import java.util.Scanner;
import java.util.concurrent.ArrayBlockingQueue;

public class Main {

	public static void main(String[] args) throws InterruptedException {

		// Codigo para rodar no terminal pegando os argumentos
		// String nomeArquivo = args[0];
		// System.out.println("Nome do arquivo: => "+nomeArquivo);
		// int qntdAssentos = Integer.parseInt(args[1]);
		// System.out.println("Quantidade de Assentos => "+qntdAssentos);

		// Codigo para rodar no Eclipse
		Scanner in = new Scanner(System.in);
		int qntdAssentos = in.nextInt();
		String nomeArquivo = in.next();
		in.close();

		// Vetor de assentos
		Assento assentos[] = criaAssentos(qntdAssentos);

		// Fila com os logs da aplicação a serem impressos(max 10 elementos)
		Queue<Log> logs = new ArrayBlockingQueue<>(10);

		// quantas threads ja terminaram no programa
		Integer threadsFinalizadas = 0;

		// Lista de threads
		List<Thread> produtoras = new ArrayList<>();

		// Cria e Inicia as threads, retorna a thread consumidora
		Thread0 consumidora = criaThreads(produtoras, logs, assentos, threadsFinalizadas, nomeArquivo);

		// Espera pelas produtoras acabarem
		for (Thread k : produtoras) {
			k.join();
		}

		// Acabando, esperamos agora a thread0 acabar
		consumidora.setFinish(false);
		consumidora.join();

	}

	private static Thread0 criaThreads(List<Thread> threads, Queue<Log> logs, Assento[] assentos,
			Integer threadsFinalizadas, String nomeArquivo) {

		// Monitor
		Funcoes func = new Funcoes(logs);

		// Threads Produtoras
		Thread t1 = new Thread(new Thread1(func, 1, assentos));
		Thread t2 = new Thread(new Thread2(func, 2, assentos));
		Thread t3 = new Thread(new Thread3(func, 3, assentos));

		threads.add(t1);
		threads.add(t2);
		threads.add(t3);

		for (Thread thread : threads) {
			thread.start();
		}

		// Thread 0 Consumidora
		Thread0 t0 = new Thread0(0, assentos, logs, threadsFinalizadas, nomeArquivo);
		t0.start();

		return t0;
	}

	private static Assento[] criaAssentos(int qntdAssentos) {
		Assento[] assentos = new Assento[qntdAssentos];
		for (int i = 0; i < assentos.length; i++) {
			assentos[i] = new Assento();
//			assentos[i].setnAssento(i + 1);
		}
		return assentos;
	}

}
