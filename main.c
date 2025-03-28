/**
 * @file main.c
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
 
int main() {
    ListaAntenas *lista = NULL;
    int opcao, x, y;
    char freq;
     
    do {
        printf("\nMenu:\n");
        printf("1 - Inserir antena\n");
        printf("2 - Remover antena\n");
        printf("3 - Listar antenas\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
         
        switch (opcao) {
            case 1:
                printf("Frequência da antena (A-Z): ");
                scanf(" %c", &freq);
                printf("Coordenadas (x y): ");
                scanf("%d %d", &x, &y);
                lista = inserirAntena(lista, freq, x, y);
                break;
            case 2:
                printf("Coordenadas da antena a remover (x y): ");
                scanf("%d %d", &x, &y);
                lista = removerAntena(lista, x, y);
                break;
            case 3:
                listarAntenas(lista);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
     
    liberarLista(lista);
    return 0;
}