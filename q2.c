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

void desenhar_pacote(int tamanho, int espaco) {
    for (int i = 0; i < espaco; ++i) printf("    ");
    printf(",,,,,,,,,,,,,,,,\n");

    for (int i = 0; i < espaco; ++i) printf("    ");
    printf("|   pacote     |\n");

    for (int i = 0; i < espaco; ++i) printf("    ");
    if (tamanho > 9) printf("|  %d   bytes  |\n", tamanho);
    else printf("|   %d bytes    |\n", tamanho);

    for (int i = 0; i < espaco; ++i) printf("    ");
    printf(",,,,,,,,,,,,,,,,\n");
}

void desenhar_seta_cima(int espaco) {
    for (int i = 0; i < espaco; ++i) printf("    ");
    printf("        ^\n");

    for (int i = 0; i < espaco; ++i) printf("    ");
    printf("        |\n");
}

void desenhar_seta_baixo(int espaco) {
    for (int i = 0; i < espaco; ++i) printf("    ");
    printf("        |\n");

    for (int i = 0; i < espaco; ++i) printf("    ");
    printf("        v\n");
}

// simulação da transmiçao de arquivos
void transmitir_arquivo(Pacote *destino, Pacote *origem, int arquivo) {
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
			inserir_pacote(origem, TAMANHO_MAXIMO_PACOTE); 
		} else if (resto > 0 && i == quantidade_pacotes) { // caso exista um resto menor que a tamanho do canal, adiciona na fila
			inserir_pacote(origem, resto);
		}
		
	}
    
    int *espaco = malloc(quantidade_pacotes + 1);
    int pacote_da_vez = quantidade_pacotes;
    while (1) {
        system("clear");
        // exibição da simulação de transmissao
        Pacote *pacote_temporario = origem->proximo;
        for (int i = 1; i < quantidade_pacotes+1; i++) {
            if (espaco[i] == 0) {
                if (i == 1) printf("       null\n");
                desenhar_seta_cima(espaco[i]);
            }
            desenhar_pacote(pacote_temporario->tamanho, espaco[i]);

            if (espaco[i] == 10) {
                desenhar_seta_baixo(espaco[i]);
                if (i >= quantidade_pacotes && espaco[i] == 10) {
                    for (int j = 0; j < espaco[i]; ++j) printf("    ");
                    printf("       null\n");
                }
            } else {
                printf("\n\n");
            }

            if (pacote_temporario->proximo) {
                pacote_temporario = pacote_temporario->proximo;
            }
            if (i == pacote_da_vez) {
                espaco[i]++;
            }
            if (espaco[pacote_da_vez] == 10) {
                pacote_da_vez--;
            }
        }
        sleep(1);
    }
    free(espaco);
}


int main(void) {
	// primeiro pacote da fila
    Pacote origem = {.proximo = NULL};
    Pacote destino = {.proximo = NULL};

	// variavel para o tamanho do arquivo
    int tamanho_arquivo = 0;

	// recebe o tamanho do arquivo do usuario
	printf("insira o tamanho do arquivo: ");
	scanf("%d", &tamanho_arquivo);

	// faz a simulação da transmissao
	transmitir_arquivo(&destino, &origem, tamanho_arquivo);

	// demonstra a finalização de transmissao
	printf("\ntransmissão concluida!!\n");
	return 0;
}
