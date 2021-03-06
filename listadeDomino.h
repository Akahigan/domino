#ifndef LISTADEDOMINO_H
#define LISTADEDOMINO_H
#include <stdio.h>
#include <stdlib.h>



typedef struct tp_no_aux {
	struct tp_no_aux *ant;
	tp_pedra pedra;
	struct tp_no_aux *prox;
} tp_no;

typedef struct {
	tp_no *ini;
	tp_no *fim;
	 int tamanho;
} tp_listad;

tp_listad *inicializa_listad() {
	tp_listad *lista=(tp_listad*) malloc(sizeof(tp_listad) );
	lista->ini = NULL;
	lista->fim = NULL;
	 lista->tamanho = 0;
	return lista;
}

int lista_vazia(tp_listad *lista) {
	if (lista->ini == NULL) return 1;
	return 0;
}

tp_no *aloca() {
	tp_no* pt;
	pt = (tp_no*) malloc(sizeof(tp_no));
	return pt;
}

int insere_listad_no_fim (tp_listad *lista, tp_pedra e){
	tp_no *novo;
	novo = aloca();
	if (!novo) return 0;
	novo->pedra = e;
	if(lista_vazia(lista)) {
		novo->prox = NULL;
		novo->ant = NULL;
		lista->ini = lista->fim = novo;
	}
	else {
		novo->prox = NULL;
		novo->ant = lista->fim;
		lista->fim->prox = novo;
		lista->fim = novo;
	}
	lista->tamanho++;
	return 1;
}

void imprime_listad(tp_listad *lista, int ordem){
	tp_no *atu;
	
	switch (ordem) {
		case 1: atu= lista->ini;
			while (atu != NULL) {
				printf(" [%d | %d] ",atu->pedra.esquerda, atu->pedra.direita);
				atu = atu->prox;
			}
			break;
		case 2: atu = lista->fim;
			while(atu != NULL) {
				printf(" [%d | %d] ",atu->pedra.esquerda, atu->pedra.direita);
				atu = atu->ant;
			}
			break;
		default: printf("codigo invalido");
	}
	printf("\n");
}

int remove_listad (tp_listad *lista, tp_pedra e) {
	tp_no *atu = lista->ini;
	while( (atu != NULL) && (atu->pedra.direita != e.direita || atu->pedra.esquerda != e.esquerda) ){
		atu = atu->prox;
	}
	if(atu == NULL) return 0;
	if(lista->ini == lista->fim){
		lista->ini = lista->fim = NULL;
	}
	else{
		if(lista->ini == atu){
			lista->ini = atu->prox;
			atu->prox->ant = NULL;
		}
	else{
		if(lista->fim == atu){
			lista->fim = atu->ant;
			atu->ant->prox = NULL;
		}
		else{
			atu->prox->ant = atu->ant;
			atu->ant->prox = atu->prox;
		}
	  }
	}
	free(atu);
	lista->tamanho--;
	return 1;
}

tp_no * busca_lista (tp_listad *lista, tp_pedra e) {
	tp_no *atu;
	atu = lista->ini;
	while ( (atu != NULL) && (atu->pedra.direita != e.direita) && (atu->pedra.esquerda != e.esquerda) ){
		atu = atu->prox;
	}
	return atu;
}

tp_listad *destroi_listad (tp_listad *lista){
	tp_no *atu;
	atu = lista->ini;
	while (atu != NULL){
		lista->ini = atu->prox;
		free(atu);
		atu = lista->ini;
	}
	free(lista);
	return NULL;
}

#endif
