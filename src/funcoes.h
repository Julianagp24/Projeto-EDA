/**
 * @file funcoes.h
 * @author Juliana Pereira (31540@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 2025-03-28
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef FUNCOES_H
#define FUNCOES_H

#include "dados.h"

typedef struct ListaAntenas {
    Antena antena;
    struct ListaAntenas *prox;
} ListaAntenas;

typedef struct LocalNefasto {
    int x, y;
    struct LocalNefasto *prox;
} LocalNefasto;

/*
    Funções para manipulação de antenas
*/
ListaAntenas* inserirAntena(ListaAntenas *lista, char freq, int x, int y);
ListaAntenas* removerAntena(ListaAntenas *lista, int x, int y);
void listarAntenas(ListaAntenas *lista);
void liberarLista(ListaAntenas *lista);

/*
    Funções para manipulação de locais nefastos
*/
LocalNefasto* deduzirLocaisNefastos(ListaAntenas *lista);
void listarLocaisNefastos(LocalNefasto *lista);
Antena* carregarAntenasDeFicheiro(const char *nomeFicheiro);

/*
    Função para salvar antenas em binário
*/
void salvarAntenasBinario(ListaAntenas *lista, const char *Antena);

#endif