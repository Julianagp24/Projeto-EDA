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
    // Alocar memória para a nova antena
    ListaAntenas *nova = (ListaAntenas*)malloc(sizeof(ListaAntenas));
    // Verifica se a alocação foi bem sucedida
    if (!nova) {
        printf("Erro ao alocar memória!\n");
        return lista;
    } 
    // Inicializa a nova antena
    nova->antena.freq = freq;
    nova->antena.x = x;
    nova->antena.y = y; 
    // Insere a nova antena no início da lista
    nova->prox = lista;
    // Atualiza a lista de antenas
    return nova;
}

/*
    Remover uma antena pela coordenada
*/
ListaAntenas* removerAntena(ListaAntenas *lista, int x, int y) {
    // Verifica se a lista está vazia
    ListaAntenas *atual = lista, *anterior = NULL;
    // Percorre a lista para encontrar a antena a remover
    while (atual) {
        // Verifica se a antena atual é a que queremos remover
        if (atual->antena.x == x && atual->antena.y == y) {
            if (anterior)
                anterior->prox = atual->prox;
            else
                lista = atual->prox;
            // Libera a memória da antena removida
            free(atual);
            // Retorna a lista atualizada
            return lista;
        }
        // Avança para a próxima antena
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
    // Verifica se a lista de antenas está vazia
    LocalNefasto *nefasto = NULL;
    while (lista != NULL) { // ListaAntenas tem prox
        // Criar um novo LocalNefasto
        LocalNefasto *novo = (LocalNefasto*) malloc(sizeof(LocalNefasto));
        // Verifica se a alocação foi bem sucedida
        if (!novo) return nefasto;
        // Inicializa o novo local nefasto
        novo->x = lista->antena.x;
        novo->y = lista->antena.y;
        // Insere o novo local nefasto no início da lista
        novo->prox = nefasto;
        // Atualiza a lista de locais nefastos
        nefasto = novo; 
        // Avança para a próxima antena
        lista = lista->prox;
    }

    return nefasto;
}

/*
    Listar locais nefastos
*/
void listarLocaisNefastos(LocalNefasto *lista) {
    // Percorre a lista de locais nefastos e imprime as coordenadas
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
    // Verifica se o nome do ficheiro é válido
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
    // Verifica se o nome do ficheiro é válido
    FILE* fp;
    // Verifica se o ficheiro existe
    ListaAntenas* lista = NULL;
    ListaAntenas* aux;
    // Abre o ficheiro para leitura binária
    // Se o ficheiro não existir, retorna NULL
    if ((fp = fopen(nomeFicheiro, "rb")) == NULL) return NULL;

    // Lê as antenas do ficheiro até o fim
    Antena antenaTemp;
    while (fread(&antenaTemp, sizeof(Antena), 1, fp)) {
        // Aloca memória para a nova antena
        aux = (ListaAntenas*)malloc(sizeof(ListaAntenas));
        // Verifica se a alocação foi bem sucedida
        if (aux == NULL) {
            fclose(fp);
            return lista;  // Retorna o que já foi lido se der erro de memória
        }
        // Inicializa a nova antena
        aux->antena = antenaTemp;
        // Insere a nova antena no início da lista
        aux->prox = lista;  
        // Atualiza a lista de antenas
        lista = aux;
    }
    
    fclose(fp);
    
    // Retorna a lista de antenas lidas do ficheiro
    return lista;
}

#pragma endregion

#pragma region "Liberar lista"

/*
	Liberar lista
*/
void liberarLista(ListaAntenas* lista) {
    // Libera a memória alocada para a lista de antenas
    ListaAntenas* aux;
    // Percorre a lista e libera cada nó
    while (lista) {
        // Libera a memória do nó atual
        aux = lista;
        // Avança para o próximo nó
        lista = lista->prox;
        free(aux);
    }
}

#pragma endregion