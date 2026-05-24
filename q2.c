/*
 *  Autores:
 *  	Beatriz Barauna
 *  	Kinan Principe
 *	
 *	Data: 
 *		24/05/2026
 *
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define TAMANHO_MAXIMO_PACOTE 64

// estrutura do pacote
typedef struct Pacote {
    int tamanho; // tamanho do pacote em bytes
    struct Pacote *proximo;
} Pacote;

// insere elemento ao final da fila
void inserir_pacote(Pacote *base, int tamanho) {
	// pacote temporario para começar a fila
	Pacote *pacote_temporario = base;
    
	// enquanto o proximo elemento apontado não for nulo
    while (pacote_temporario->proximo != NULL) {
        pacote_temporario = pacote_temporario->proximo;
    }
	
	// aloca o proximo espaço da fila
    pacote_temporario->proximo = malloc(sizeof(Pacote));

	// aponta pro espaço que acabou de ser alocado
    pacote_temporario = pacote_temporario->proximo;
	
	// define o tamanho que será transmitido
    pacote_temporario->tamanho = tamanho;

	// aponta o para o final da fila
    pacote_temporario->proximo = NULL;
}

// remove elemento do comeco da fila
void remover_elemento(Pacote *base) {
	// fila temporaria que se refere ao começo da fila
    Pacote *primerio_pacote = base->proximo;

	// o espaço no começo da fila apontará para o segundo elemento, o que vem depois do primeiro
    base->proximo = primerio_pacote->proximo;

	// libera o espaço do primeiro da fila que acabou de ser desvinculado da base
    free(primerio_pacote);
}

// desenho para representar o carregamento de pacotes
void desenho(int tam) { 
	// temporizador para simular o tempo de carregamento
	int temporizador = 0;

	// se estiver carregando o tamanho máximo da transmissão, demora 2 segundos
	if (tam == TAMANHO_MAXIMO_PACOTE)
		temporizador = 2;

	// se não, demora 1 segundo
	else 
		temporizador = 1;
	
	// desenho que é exibido para simular o carregamento
	for (int i = 0; i < 3; i++) {
		printf("=======");		
		
		// função para fazer a espera da simulação
		sleep(temporizador);
		fflush(stdout); // flush manual por conta do sleep
	}

}

// simulação da transmiçao de arquivos
void transmitir_arquivo(Pacote *base, int arquivo) {
	// conta a quantidade de pacotes, caso ele seja menor que o tamanho total, haverá apenas 1 pacote
	int quantidade_pacotes = 1;

	// resto da divisão de pacotes, caso o tamanho do arquivo não seja de base 2
	int resto = 0;

	// se o tamanho do arquivo for maior que o tamanho total da transmissao
    if (arquivo > TAMANHO_MAXIMO_PACOTE) {
		// divide o tamanho do arquivo pelo tamanho total do canal de transmissao
        quantidade_pacotes = arquivo / TAMANHO_MAXIMO_PACOTE;
		
		// caso o resto da divisao do arquivo pelo tamanho do canal seja maior que 0
        if (arquivo % TAMANHO_MAXIMO_PACOTE > 0) {
			// incrementa a quantidade de pacotes em 1
            quantidade_pacotes++;

			// guarda o resto
			resto = arquivo % TAMANHO_MAXIMO_PACOTE;
        }
    }
	
	// quantidade é iniciada em 1, para garantir que a transmissao aconteça mesmo que o tamanho do pacote 
	// seja maior que o tamanho do canal de transmissao
	for (int i = 1; i < quantidade_pacotes+1; i++) {
	
		// adiciona o tamanho maximo na transmissao de arquivo
		if (i < quantidade_pacotes) {
			inserir_pacote(base, TAMANHO_MAXIMO_PACOTE); 
		} else if (resto > 0 && i == quantidade_pacotes) { // caso exista um resto menor que a tamanho do canal, adiciona na fila
			inserir_pacote(base, resto);
		}
		
	}

	// auxiliar que irá fazer a soma da transmissao
	int conta = 0;
	
	// exibição da simulação de transmissao
	for (int i = 1; i < quantidade_pacotes+1; i++) {
		// exibe qual pacote está sendo transmitido e quantidade total
		printf("\nPacote %d/%d ", i, quantidade_pacotes);
		
		// mostra as bytes a serem transmitidas
		printf(" (%d bytes) \n| ", base->proximo->tamanho);

		// desenha a barra de progresso
		desenho(base->proximo->tamanho);			
		
		// incrementa o tamanho do primeiro elemento na fila
		conta += base->proximo->tamanho;

		// exibe o resultado da transmissao
		printf(" | recebido: %d bytes\n", conta);

		// verifica se existem elementos na fila para passar para o proximo elemento
		if (base->proximo != NULL) {
			remover_elemento(base);
		}
	}
}


int main(void) {
	// primeiro pacote da fila
    Pacote pacote = {.proximo = NULL};

	// variavel para o tamanho do arquivo
    int arquivo = 0;

	// recebe o tamanho do arquivo do usuario
	printf("insira o tamanho do arquivo: ");
	scanf("%d", &arquivo);

	// faz a simulação da transmissao
	transmitir_arquivo(&pacote, arquivo);

	// demonstra a finalização de transmissao
	printf("\ntransmissão concluida!!\n");
	return 0;
}
