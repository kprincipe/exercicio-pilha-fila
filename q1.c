#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Elemento {
    int numero;
    struct Elemento *proximo;
} Elemento;

// inserir elemento no topo da pilha
void push(Elemento *base, int numero) {
    // atribui ao elemento temporario o endereco da base da pilha
    Elemento *elemento_temporario = base;

    // percorre a pilha ate o final
    while (elemento_temporario->proximo != NULL) {
        elemento_temporario = elemento_temporario->proximo;
    }
	
    // aloca proximo elemento da pilha
    elemento_temporario->proximo = malloc(sizeof(Elemento));
    // atribui ao elemento temporario o endereco do ultimo elemento alocado
    elemento_temporario = elemento_temporario->proximo;
    // atribui nulo ao fim da pilha, indicando fim da lista
    elemento_temporario->proximo = NULL;
    // armazena numero no novo elemento
    elemento_temporario->numero = numero;
}

// retirar elemento do topo da pilha
void pop(Elemento *base) {
    // atribui ao elemento temporario o endereco da base da pilha
	Elemento *elemento_temporario = base;
    // auxiliar para guardar elemento anterior
	Elemento *elemento_anterior;
	
    // percorre pilha ate o fim e salva elemento anterior ao atual em auxiliar
	while (elemento_temporario->proximo != NULL) {
		elemento_anterior = elemento_temporario;
		elemento_temporario = elemento_temporario->proximo;
	}
    
    // atribui nulo ao topo da pilha
	elemento_anterior->proximo = NULL;
    // desaloca elemento do topo da lista
	free(elemento_temporario);
}

// exibe elemento do topo
int elemento_topo(Elemento *base) {
    // atribui ao elemento temporario o endereco da base da pilha
	Elemento *elemento_temporario = base;
	
    // percorre a pilha ate o final
	while(elemento_temporario->proximo != NULL) {
		elemento_temporario = elemento_temporario->proximo;
	}
    
    // retorna elemento do topo da lista
	return elemento_temporario->numero;
}

// verifica se a pilha esta vazia
bool verifica_vazio(Elemento *base) {
    // verifica se a pilha nao possui elementos e retirba verdadeiro caso nao
    if (base->proximo == NULL) {
        return true;
    } else { // caso a lista tenha elementos, retornar falso
        return false;
    }
}

// limpa pilha
void limpar(Elemento *base) {
    // atribui ao elemento temporario o endereco da base da pilha
    Elemento *proximo_elemento = base;

    int quantidade_de_elementos = 0;

    // percorre pilha ate o fim e soma um em quantidade_de_elementos para contagem de elementos
    while (proximo_elemento->proximo != NULL) {
        proximo_elemento = proximo_elemento->proximo;
        quantidade_de_elementos++;
    }

    // enquanto a quantidade_de_elementos for maior que 0, exclui o topo da pilha
    while (quantidade_de_elementos > 0) {
		pop(base);
        // decrementa elemento que acabou de ser removido da quantidade total
        quantidade_de_elementos--;
    }
}

Elemento inicializar_pilha() {
    // define valores iniciais para uma pilha recem criada
    return (Elemento) {
        .numero = 0,
        .proximo = NULL
    };
}

void separador_algarismos (Elemento *pilha, int numero) {
	
	Elemento pilha_temporaria = inicializar_pilha();

	// temporario que recebe o resto
    int temporario_cortado = numero;

	// temporario que recebe o algarismo para ser enviado a pilha temporaria
    int temporario_isolado;

    // separa algarismos e insere na pilha temporaria
    while (temporario_cortado > 0) {
        // temporario_isolado recebe o resto do temporario_cortado, o ultimo algarismo
        temporario_isolado = temporario_cortado % 10;

        // temporario_cortado exclui o ultimo algarismo para proxima iteracao
        temporario_cortado = (int)(temporario_cortado / 10);

        // adiciona o ultimo algarismo na pilha temporaria
        push(&pilha_temporaria, temporario_isolado);
    }

	// exibe a pilha do numero 
	printf("\npilha do numero %d", numero);
    
	// inverte ordem dos algarismos da base para o topo enquanto houver elementos na pilha7
	while (!verifica_vazio(&pilha_temporaria)) {
        push(pilha, elemento_topo(&pilha_temporaria));

		// exibe o elemento que está sendo adicionado na pilha
		printf("\n\t%d", elemento_topo(pilha));
		pop(&pilha_temporaria);

    }

	// aponta para o elemento que está no topo da pilha
	printf(" <- topo!!\n");

}

int soma(int primeiro_numero, int segundo_numero) {
    // declara base da pilha
    Elemento pilha_primeiro_numero = inicializar_pilha();
    Elemento pilha_segundo_numero = inicializar_pilha();
    Elemento pilha_resultado = inicializar_pilha();
	
	// função pra separar e reorganizar a ordem do primeiro número na pilha
	separador_algarismos(&pilha_primeiro_numero, primeiro_numero);

	// função pra separar e reorganizar a ordem do segundo número na pilha
	separador_algarismos(&pilha_segundo_numero, segundo_numero);

   	// soma dos numeros
	int temporaria_n1, temporaria_n2, resultado, sobe_um = 0;

	// enquanto as pilhas não estiverem vazias, os elementos da mesma posição irão se somas
	while(!verifica_vazio(&pilha_primeiro_numero) || !verifica_vazio(&pilha_segundo_numero)) {
		temporaria_n1 = elemento_topo(&pilha_primeiro_numero);
		temporaria_n2 = elemento_topo(&pilha_segundo_numero);
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

		} else { // caso o resultado seja menor que 9 e sobe um esteja zerado

			// o resultado é adicionado a pilha
			push(&pilha_resultado, resultado);

            // como o resultado e menor que 9, sobe_um e zerado
            sobe_um = 0;
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
	
	// fora do loop, verifica se existe sobe_um para ser adicionado
	// no final do resultado
	if (sobe_um > 0) {
		push(&pilha_resultado, sobe_um);
	}

    // zera variavel auxiliar de resultado
    resultado = 0;

    // converte algarismos da pilha para um inteiro
    while (!verifica_vazio(&pilha_resultado)) {
        // vai se adicionando o algarismo a cada classe numerica
        resultado = (resultado * 10) + elemento_topo(&pilha_resultado);
        pop(&pilha_resultado);
    }

    // retorna resultado final
    return resultado;
}

int main(void) {
	int n1, n2;

    // recebe numeros do usuario
	printf("insira o primeiro numero: ");
	scanf("%d", &n1);

	printf("insira o segundo numero: ");
	scanf("%d",&n2);

    // realiza operacao de soma
    int resultado = soma(n1, n2);

    // saida de resultado
    printf("\nresultado da soma: %d\n", resultado);

    return 0;
}
