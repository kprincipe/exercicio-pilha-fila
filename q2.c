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
    Pacote *pacote_temporario = base;
    
    while (pacote_temporario->proximo != NULL) {
        pacote_temporario = pacote_temporario->proximo;
    }

    pacote_temporario->proximo = malloc(sizeof(Pacote));
    pacote_temporario = pacote_temporario->proximo;
    pacote_temporario->tamanho = tamanho;
    pacote_temporario->proximo = NULL;
}

// remove elemento do comeco da fila
void remover_elemento(Pacote *base) {
    Pacote *primerio_pacote = base->proximo;
    base->proximo = primerio_pacote->proximo;
    free(primerio_pacote);
}

void transmitir_arquivo(Pacote *base, int arquivo) {
    int quantidade_pacotes = 1;
    int resto = 0;

    if (arquivo > TAMANHO_MAXIMO_PACOTE) {
        quantidade_pacotes = arquivo / TAMANHO_MAXIMO_PACOTE;

        if (arquivo % TAMANHO_MAXIMO_PACOTE > 0) {
            quantidade_pacotes++;
        }
    }
}

int main(void) {
    Pacote pacote = {.proximo = NULL};

    int arquivo = 1024; // arquivo de 1024 bytes

    transmitir_arquivo(&pacote, arquivo);

    return 0;
}
