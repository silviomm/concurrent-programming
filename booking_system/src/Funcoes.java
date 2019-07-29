import java.util.Queue;

//	Monitor que contem todas as funções do sistema que serão executadas por threads produtoras

public class Funcoes {

	Queue<Log> logs;//Fila do qual utilizamos de estrutura para buffer das threads Produtoras e Consumidora
	//Na fila serão armazenados os logs das operações
	
	//Construtor
	public Funcoes(Queue<Log> logs) {
		this.logs = logs;
	}

	//Adiciona na fila de logs
	private void adiciona(int op, int id, int ret, Assento[] assentos) {//Recebe: Número da operanção,
	//id da thread que a fez, retorno da operação e vetor de estado dos assentos pós operação 
		boolean adicionado = false;
		while (!adicionado) {
			//funcao offer retorna true se conseguiu adicionar na fila, else: false
			//Semelhante a fazer a thread esperar quando o buffer tiver cheio
			adicionado = logs.offer(new Log(op, id, ret, assentos));
		}
	}
	//Operação que vizualiza o estado dos assentos
	public void visualizaAssentos(Assento[] assentos, int id) {
		// sessao crítica é apenas a parte do log.
		synchronized (this) {
			adiciona(1, id, 0, assentos.clone());
		}
	}
	
	public synchronized int alocaAssentoLivre(Assento[] assentos, int id) {
		for (int i = 0; i < assentos.length; i++) {//Percorre o vetor de assentos
			if (!assentos[i].isOcupado()) {//Se achar um assento que esteja livre
				
				assentos[i].setId(id);//coloca id da thread no assento
				assentos[i].setOcupado(true);//ocupa assento

				adiciona(2, id, 1, assentos.clone());//Adiciona log de execução à fila, com retorno 1
				return 1;//conseguiu alocar um assento
			}
		}
		//Se não existir um assento livre
		adiciona(2, id, 0, assentos.clone());//Adiciona log de execução à fila, com retorno 0 
		return 0;//não conseguiu alocar assento(todos assentos ocupados)
	}

	public synchronized int alocaAssentoDado(Assento[] assentos, Assento assento, int id) {
		if (assento.isOcupado()) {//Se assento dado esta ocupado
			adiciona(3, id, 0, assentos.clone());//Adiciona log de execução à fila, com retorno 0
			return 0;//não conseguiu alocar assento
		} else {//Se assento esta livre
			assento.setId(id);//Coloca id da thread no assento
			assento.setOcupado(true);//Ocupa assento
			adiciona(3, id, 1, assentos.clone());//Adiciona log de execução à fila, com retorno 1
			return 1;//conseguiu alocar assento
		}

	}

	public synchronized int liberaAssento(Assento[] assentos, Assento assento, int id) {
		if (assento.getId() == id) {//Se o id do assento for o mesmo da thread que quer liberalo
			assento.setOcupado(false);//Desocupa assento
			assento.setId(0);//Coloca 0 no lugar do id da thread
			adiciona(4, id, 1, assentos.clone());//Adiciona log de execução à fila, com retorno 1
			return 1;//conseguiu liberar assento
		}
		adiciona(4, id, 0, assentos.clone());//Adiciona log de execução à fila, com retorno 0
		return 0;//não conseguiu liberar assento(thread não foi quem alocou assento)
	}
}
