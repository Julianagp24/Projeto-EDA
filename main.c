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
#include "dados.h"
#include "funcoes.h" 

int main() {
    ListaAntenas* lista = NULL;  // Lista de antenas
    LocalNefasto* locais = NULL; // Lista de locais nefastos
    int opcao, x, y;
    char freq;
    lista = carregarAntenasDeFicheiro("antenas.txt");

    do {
        printf("\nGestão de Antenas \n");
        printf("1. Adicionar Antena\n");
        printf("2. Remover Antena\n");
        printf("3. Listar Antenas\n");
        printf("4. Deduzir Locais Nefastos\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite a frequência (char) e as coordenadas (x y): ");
                scanf(" %c %d %d", &freq, &x, &y);
                lista = inserirAntena(lista, freq, x, y);
                break;
            case 2:
                printf("Digite as coordenadas da antena a remover (x y): ");
                scanf("%d %d", &x, &y);
                lista = removerAntena(lista, x, y);
                break;
            case 3:
                listarAntenas(lista);
                break;
            case 4:
                locais = deduzirLocaisNefastos(lista);
                listarLocaisNefastos(locais);
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 5);
    
    return 0;
}
