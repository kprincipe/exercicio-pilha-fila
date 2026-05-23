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
    
	// temporario que recebe o resto
    int temporario_cortado = primeiro_numero;
	// temporario que recebe o algarismo para ser enviado a pilha temporaria
    int temporario_isolado;
    while (temporario_cortado > 0) {
        temporario_isolado = temporario_cortado % 10;
        temporario_cortado = (int)(temporario_cortado / 10);
        push(&pilha_temporaria, temporario_isolado);
    }

	// reoganização da pilha do primeiro numero
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

	// reorganização da pilha do segundo numero
    while (!verifica_vazio(&pilha_temporaria)) {
        push(&pilha_segundo_numero, elemento_topo(&pilha_temporaria));
        pop(&pilha_temporaria);
    }
	
	// visualização das pilhas
    printf("pilha primeiro numero:\n");
    visualizar_pilha_inteira(&pilha_primeiro_numero);
    printf("pilha segundo numero:\n");
    visualizar_pilha_inteira(&pilha_segundo_numero);

	// soma dos numeros
	int temporaria_n1, temporaria_n2, resultado, sobe_um = 0;

	// enquanto as pilhas não estiverem vazias, os elementos da mesma posição irão se somas
	while(!verifica_vazio(&pilha_primeiro_numero) || !verifica_vazio(&pilha_segundo_numero)) {
		temporaria_n1 = elemento_topo(&pilha_primeiro_numero);
		temporaria_n2 = elemento_topo(&pilha_segundo_numero);
		
		// verifica se a pilha está vazia para temporaria ser 0
		if (verifica_vazio(&pilha_primeiro_numero)) {
			temporaria_n1 = 0;
		}
		
		if (verifica_vazio(&pilha_segundo_numero)) {
			temporaria_n2 = 0;
		}
		
		// soma das temporárias mais o sobe um
		resultado = temporaria_n1 + temporaria_n2 + sobe_um;

		// caso o resultado seja maior que 9
		if (resultado > 9) {
			// pega o resto
			int temp = resultado % 10;
			// coloca o resto na pilha de resultados
			push(&pilha_resultado, temp);
			
			// define a dezena que vai subir na adição
			sobe_um = (int) (resultado / 10);
				
		} else if (resultado <= 9 && sobe_um == 0) { // caso o resultado seja menor que 9 e sobe um esteja zerado
			// o resultado é adicionado a pilha
			push(&pilha_resultado, resultado);
		}  else if (resultado <= 9 && sobe_um > 0) { // caso o resultado seja menor que 9 e o sobe um seja maior que 0 
			// TODO: arrumar pra caso seja maior que 9
			resultado += sobe_um; 
			push(&pilha_resultado, resultado);
		}


		// caso a pilha não esteja vazia
		if (!verifica_vazio(&pilha_primeiro_numero)) {
			// remove o elemento do topo da pilha
			pop(&pilha_primeiro_numero);
		}
		
		// caso a pilha não esteja vazia
		if (!verifica_vazio(&pilha_segundo_numero)) {
			// remove o elemento do topo da pilha
			pop(&pilha_segundo_numero);
		}
	
	}
	
	printf("pilha resultado:\n");
	visualizar_pilha_inteira(&pilha_resultado);
    return 0;
}

int main(void) {

	int n1, n2;

	printf("insira o primeiro numero: ");
	scanf("%d", &n1);

	printf("insira o segundo numero: ");
	scanf("%d",&n2);

    int resultado = soma(n1, n2);
    //printf("%d\n", resultado);

    return 0;
}
