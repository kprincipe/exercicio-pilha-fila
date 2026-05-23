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
void pop(Elemento *base) {
	Elemento *elemento_temporario = base;
	Elemento *elemento_anterior;
	
	while (elemento_temporario->proximo != NULL) {
		elemento_anterior = elemento_temporario;
		elemento_temporario = elemento_temporario->proximo;
	}

	elemento_anterior->proximo = NULL;
	free(elemento_temporario);

}

// exibe elemento do topo
void elemento_topo(Elemento *base) {
	Elemento *elemento_temporario = base;
	
	while(elemento_temporario->proximo != NULL) {
		elemento_temporario = elemento_temporario->proximo;
	}

	printf("\nelemento do topo: %d\n", elemento_temporario->numero);
}

// verifica se a pilha esta vazia
bool verifica_vazio(Elemento *base) {
    if (base->proximo == NULL) {
        return true;
    } else {
        return false;
    }
}

// limpa pilha
void limpar(Elemento *base) {
	

}

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

    push(&base, 4);
    push(&base, 2);
    push(&base, 6);
  
	elemento_topo(&base);

    return 0;
}
