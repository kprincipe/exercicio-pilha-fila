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
int elemento_topo(Elemento *base) {
	Elemento *elemento_temporario = base;
	
	while(elemento_temporario->proximo != NULL) {
		elemento_temporario = elemento_temporario->proximo;
	}

	return elemento_temporario->numero;
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
    Elemento *proximo_elemento = base;
    int quantidade_de_elementos = 0;

    while (proximo_elemento->proximo != NULL) {
        proximo_elemento = proximo_elemento->proximo;
        quantidade_de_elementos++;
    }

    while (quantidade_de_elementos > 0) {
        pop(base);
        quantidade_de_elementos--;
    }
}

void visualizar_pilha_inteira(Elemento *base) {
    Elemento *elemento_temporario = base;

    while (elemento_temporario->proximo != NULL) {
        elemento_temporario = elemento_temporario->proximo;
        printf("%d\n", elemento_temporario->numero);
    }
}

Elemento inicializar_pilha() {
    return (Elemento) {
        .numero = 0,
        .proximo = NULL
    };
}

int soma(int primeiro_numero, int segundo_numero) {
    // declara base da pilha
    Elemento pilha_temporaria = inicializar_pilha();
    Elemento pilha_primeiro_numero = inicializar_pilha();
    Elemento pilha_segundo_numero = inicializar_pilha();
    Elemento pilha_resultado = inicializar_pilha();
    
    int temporario_cortado = primeiro_numero;
    int temporario_isolado;
    while (temporario_cortado > 0) {
        temporario_isolado = temporario_cortado % 10;
        temporario_cortado = (int)(temporario_cortado / 10);
        push(&pilha_temporaria, temporario_isolado);
    }

    while (!verifica_vazio(&pilha_temporaria)) {
        push(&pilha_primeiro_numero, elemento_topo(&pilha_temporaria));
        pop(&pilha_temporaria);
    }

    temporario_cortado = segundo_numero;
    while (temporario_cortado > 0) {
        temporario_isolado = temporario_cortado % 10;
        temporario_cortado = (int)(temporario_cortado / 10);
        push(&pilha_temporaria, temporario_isolado);
    }

    while (!verifica_vazio(&pilha_temporaria)) {
        push(&pilha_segundo_numero, elemento_topo(&pilha_temporaria));
        pop(&pilha_temporaria);
    }

    printf("pilha primeiro numero:\n");
    visualizar_pilha_inteira(&pilha_primeiro_numero);
    printf("pilha segundo numero:\n");
    visualizar_pilha_inteira(&pilha_segundo_numero);
    return 0;
}

int main(void) {
    int resultado = soma(592, 3784);
    //printf("%d\n", resultado);

    return 0;
}
