import java.io.BufferedWriter;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.Writer;
import java.util.Queue;

public class Thread0 extends Thread {

	int id;
	private Queue<Log> logs;//Fila da logs
	private boolean finish = true;// True enquanto threads produtoras ainda não acabaram
	private String nomeArquivo;//Nome do arquivo passado por argumento
	private Assento[] assentos;//Vetor de estado dos assentos

	//Construtor
	public Thread0(int id, Assento[] assentos, Queue<Log> logs, Integer threadsFinalizadas, String nomeArquivo) {
		this.id = id;
		this.assentos = assentos;
		this.logs = logs;
		this.nomeArquivo = nomeArquivo;
	}

	@Override
	public void run() {
		try {
			//Criando escritor de arquivo
			Writer buffWrite = new BufferedWriter(
					new OutputStreamWriter(new FileOutputStream(nomeArquivo + ".c"), "utf-8"));

			printInicio(buffWrite);
			consome(buffWrite);
			printFim(buffWrite);

			buffWrite.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}
	//Imprime o inicio necessário do arquivo
	private void printInicio(Writer buffWrite) throws IOException {
		buffWrite.append("#include \"aux.c\"\n#include <stdio.h>\n#include <stdlib.h>\n\nint main() {\n");
		buffWrite.append("v0 = malloc(sizeof(int)*"+assentos.length+");\n");
		buffWrite.append("int i;\nfor(i=0;i<"+assentos.length+";i++){v0[i] = 0;}\n");
		buffWrite.append("vPrincipal = v0;\n");
		buffWrite.append("TAM = "+assentos.length+";\n");
	}

	//Imprime fim do arquivo
	private void printFim(Writer buffWrite) throws IOException {
		buffWrite.append("\n return 0;\n}");
	}

	// Imprime Logs no arquivo desejado
	private void consome(Writer buffWrite) throws IOException {
		// Enquanto ainda tiver thread produtora trabalhando ou log nao lido
		int count = 0;
		while (finish || logs.size() > 0) {
			Log log = logs.poll(); // remove o primeiro da fila, se nao tiver
									// ninguem, retorna null
			if (log != null) {
				count++;
				imprimeLog(buffWrite, log, count);
			}
		}

	}

	// Imprime no arquivo o log formatado da forma que desejamos
	private void imprimeLog(Writer buffWrite, Log log, int count) throws IOException {

		System.out.print("int v" + count + "[] = ");
		buffWrite.append("int v" + count + "[] = ");
		Assento[] k = log.getEstado();
		System.out.print("{");
		buffWrite.append("{");
		for (int i = 0; i < k.length; i++) {
			if (i == k.length - 1) {

				System.out.print(k[i].getId());
				buffWrite.append(k[i].getId() + "");
			} else {
				System.out.print(k[i].getId() + " ,");
				buffWrite.append(k[i].getId() + " ,");

			}
		}

		System.out.println("};");
		buffWrite.append("};");

		System.out.print("op" + log.getFunc());
		buffWrite.append("op" + log.getFunc());// n da funcao

		System.out.print("(" + log.getId() + ", v" + count+", ");
		buffWrite.append("(" + log.getId() + ", v" + count+", ");

		System.out.print(log.getRetorno()+");\n");
		buffWrite.append(log.getRetorno()+");\n");

	}
	
	//Setter
	public void setFinish(boolean finish) {
		this.finish = finish;
	}
}
