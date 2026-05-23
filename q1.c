#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Elemento {
    int numero;
    struct Elemento *proximo;
} Elemento;

// inserir elemento no topo da pilha
void push(Elemento *base, int numero) {
    Elemento *elemento_temporario = base;

    while (elemento_temporario->proximo != NULL) {
        elemento_temporario = elemento_temporario->proximo;
    }

    elemento_temporario->proximo = malloc(sizeof(Elemento));
    elemento_temporario = elemento_temporario->proximo;
    elemento_temporario->proximo = NULL;
    elemento_temporario->numero = numero;
}

// retirar elemento do topo da pilha
void pop() {}

// exibe elemento do topo
void elemento_topo() {}

// verifica se a pilha esta vazia
bool verifica_vazio(Elemento *base) {
    if (base->proximo == NULL) {
        return true;
    } else {
        return false;
    }
}

// limpa pilha
void limpar() {}

void visualizar_pilha_inteira(Elemento *base) {
    Elemento *elemento_temporario = base;

    while (elemento_temporario->proximo != NULL) {
        elemento_temporario = elemento_temporario->proximo;
        printf("%d\n", elemento_temporario->numero);
    }
}

int main(void) {
    // declara base da pilha
    Elemento base = {0};
    base.proximo = NULL;
    
    verifica_vazio(&base);

    push(&base, 4);
    push(&base, 2);
    push(&base, 6);

    verifica_vazio(&base);
    
    return 0;
}
