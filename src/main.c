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
    ListaAntenas *lista = NULL;
    LocalNefasto *locaisNefastos = NULL;
    int opcao;
    char freq;
    int x, y;

    do {
        printf("\n--- Menu ---\n");
        printf("1 - Inserir Antena\n");
        printf("2 - Remover Antena\n");
        printf("3 - Listar Antenas\n");
        printf("4 - Deduzir Locais Nefastos\n");
        printf("5 - Listar Locais Nefastos\n");
        printf("6 - Gravar Antenas em Binário\n");
        printf("7 - Ler Antenas do Binário\n");
        printf("8 - Carregar Antenas do Ficheiro de Texto\n");
        printf("9 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite a frequência e coordenadas (freq x y): ");
                scanf(" %c %d %d", &freq, &x, &y);
                lista = inserirAntena(lista, freq, x, y);
                break;
            case 2:
                printf("Digite as coordenadas para remover (x y): ");
                scanf("%d %d", &x, &y);
                lista = removerAntena(lista, x, y);
                break;
            case 3:
                listarAntenas(lista);
                break;
            case 4:
                locaisNefastos = deduzirLocaisNefastos(lista);
                printf("Locais nefastos deduzidos!\n");
                break;
            case 5:
                listarLocaisNefastos(locaisNefastos);
                break;
            case 6:
                if (gravarAntenasBinario(lista)) {
                    printf("Ficheiro binário 'antena.bin' gravado com sucesso.\n");
                } else {
                    printf("Erro ao gravar o ficheiro binário!\n");
                }
                break;
            case 7:
                lista = lerAntenasBinario("antena.bin");
                printf("Ficheiro binário lido com sucesso.\n");
                break;
            case 8:
                lista = (ListaAntenas*)carregarAntenasDeFicheiro("antenas.txt");
                printf("Ficheiro de texto carregado com sucesso.\n");
                break;
            case 9:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 9);

    liberarLista(lista);
    return 0;
}