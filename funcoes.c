/**
 * @file funcoes.c
 * @author Juliana Pereira (31540@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 2025-03-28
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "Funcoes.h"

/*
    Inserir uma antena na lista
*/
ListaAntenas* inserirAntena(ListaAntenas *lista, char freq, int x, int y) {
    ListaAntenas *nova = (ListaAntenas*)malloc(sizeof(ListaAntenas));
    if (!nova) {
        printf("Erro ao alocar memória!\n");
        return lista;
    }
    nova->antena.freq = freq;
    nova->antena.x = x;
    nova->antena.y = y;
    nova->prox = lista;
    return nova;
}

/*
    Remover uma antena pela coordenada
*/
ListaAntenas* removerAntena(ListaAntenas *lista, int x, int y) {
    ListaAntenas *atual = lista, *anterior = NULL;
    while (atual) {
        if (atual->antena.x == x && atual->antena.y == y) {
            if (anterior)
                anterior->prox = atual->prox;
            else
                lista = atual->prox;
            free(atual);
            return lista;
        }
        anterior = atual;
        atual = atual->prox;
    }
    printf("Antena não encontrada!\n");
    return lista;
 }
 
/*
    Listar todas as antenas
*/
void listarAntenas(ListaAntenas *lista) {
    ListaAntenas *atual = lista;
    printf("Lista de Antenas:\n");
    while (atual) {
        printf("Frequência: %c | Coordenadas: (%d, %d)\n", atual->antena.freq, atual->antena.x, atual->antena.y);
        atual = atual->prox;
    }
}

/*
    Deduzir locais nefastos a partir das antenas
*/
LocalNefasto* deduzirLocaisNefastos(Antena *lista) {
    LocalNefasto *nefasta = NULL;
    while (lista) {
        if (lista->x % 2 == 0 && lista->y % 2 == 0) { // Exemplo de regra
            LocalNefasto *novo = (LocalNefasto*) malloc(sizeof(LocalNefasto));
            if (!novo) return nefasta;
            novo->x = lista->x;
            novo->y = lista->y;
            novo->prox = nefasta;
            nefasta = novo;
        }
        lista = lista->prox;
    }
    return nefasta;
}

/*
    Listar locais nefastos
*/
void listarLocaisNefastos(LocalNefasto *lista) {
    while (lista) {
        printf("Local Nefasto: (%d, %d)\n", lista->x, lista->y);
        lista = lista->prox;
    }
}
/*
    Carregar ficheiro
*/
Antena* carregarAntenasDeFicheiro(const char *nomeFicheiro) {
    FILE *file = fopen(nomeFicheiro, "r");
    if (!file) {
        printf("Erro ao abrir o ficheiro!\n");
        return NULL;
    }
    Antena *lista = NULL;
    char freq;
    int x, y;
    while (fscanf(file, " %c %d %d", &freq, &x, &y) == 3) {
        lista = inserirAntena(lista, freq, x, y);
    }
    fclose(file);
    return lista;
}