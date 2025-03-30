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
#include "funcoes.h"

#pragma region "Antenas"

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
    while (lista != NULL) {
        
        printf("Frequência: %c | Coordenadas: (%d, %d)\n", lista->antena.freq, lista->antena.x, lista->antena.y);
        lista = lista->prox;
    }
}

#pragma endregion

#pragma region "Nefastos"

/*
    Deduzir locais nefastos a partir das antenas
*/
LocalNefasto* deduzirLocaisNefastos(ListaAntenas *lista) {
    LocalNefasto *nefasta = NULL;
    while (lista != NULL) { // ListaAntenas tem prox
        // Criar um novo LocalNefasto
        LocalNefasto *novo = (LocalNefasto*) malloc(sizeof(LocalNefasto));
        if (!novo) return nefasta;
        novo->x = lista->antena.x;
        novo->y = lista->antena.y;
        novo->prox = nefasta;
        nefasta = novo;
        
        lista = lista->prox; // Correto!
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

#pragma endregion

#pragma region "Carregar e Gravar Antenas"

/*
    Carregar ficheiro
*/

Antena* carregarAntenasDeFicheiro(const char *nomeFicheiro) {
    FILE *fp = fopen(nomeFicheiro, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o ficheiro!\n");
        return NULL;
    }

    Antena *antenas = (Antena*)malloc(sizeof(Antena) * 100); // Alocar espaço para 100 antenas
    if (antenas == NULL) {
        fclose(fp);
        return NULL;
    }

    int i = 0;
    while (fscanf(fp, "%c %d %d", &antenas[i].freq, &antenas[i].x, &antenas[i].y) == 3) {
        i++;
    }

    fclose(fp);
    return antenas;
}

/*
    Gravar antenas em binário
*/
bool gravarAntenasBinario(ListaAntenas *lista) {
    FILE *fp;

    if (lista == NULL) return false;

    // Abrir o ficheiro para escrita binária
    fp = fopen("antena.bin", "wb");
    if (fp == NULL) return false;

    ListaAntenas *aux = lista;
    while (aux) {
        fwrite(&(aux->antena), sizeof(Antena), 1, fp);
        aux = aux->prox;
    }

    fclose(fp);
    return true;
}

/*
    Le o ficheiro Antenas.bin
*/
ListaAntenas* lerAntenasBinario(const char* nomeFicheiro) {
    FILE* fp;
    ListaAntenas* lista = NULL;
    ListaAntenas* aux;

    if ((fp = fopen(nomeFicheiro, "rb")) == NULL) return NULL;

    Antena antenaTemp;
    while (fread(&antenaTemp, sizeof(Antena), 1, fp)) {
        aux = (ListaAntenas*)malloc(sizeof(ListaAntenas));
        if (aux == NULL) {
            fclose(fp);
            return lista;  // Retorna o que já foi lido se der erro de memória
        }
        aux->antena = antenaTemp;
        aux->prox = lista;  // Insere no início da lista
        lista = aux;
    }
    
    fclose(fp);
    return lista;
}

#pragma endregion

#pragma region "Liberar lista"

/*
	Liberar lista
*/
void liberarLista(ListaAntenas* lista) {
    ListaAntenas* aux;
    while (lista) {
        aux = lista;
        lista = lista->prox;
        free(aux);
    }
}

#pragma endregion