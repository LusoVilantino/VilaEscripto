﻿#include "linha.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int 
linha_contar_charactéres(char* linha) {
    int n = 0;

    for (int i = 0; linha[i] != '\0'; i++) { n = i; }

    return n;
}

int 
linha_contar_separador(char separador, char* linha) {
    int n = 1;

    for (int i = 0; linha[i] != '\0'; i++) {
        if (linha[i] == separador) {
            n = n + 1;
        }
    }

    return n;
}

bool linha_contém(char* comparador, char* linha) {
    int tamanho_comparador = 0;
    while (comparador[tamanho_comparador] != '\0') {
        tamanho_comparador++;
    }

    tamanho_comparador--;

    int n = 0;
    int n_comparador = 0;
    while (linha[n] != '\0') {
        if (linha[n] == comparador[n_comparador]) {
            printf(" (%d %c/%d %c - %d) ", n, linha[n], n_comparador, comparador[n_comparador], tamanho_comparador);
            if (n_comparador == tamanho_comparador) return 1;
            n_comparador++;
        }
        else {
            n_comparador = 0;
        }
        n++;
    }

    return 0;
}

char** 
linha_separar(char separador, char* linha) {
    int n = 0;
    int n2 = 0;
    int n3 = 0;

    char** matrizTratada = malloc(sizeof(char*));
    if (matrizTratada == NULL) return matrizTratada;

    char* linhaTratada = "";

    while (linha[n2]) {
        //printf("\n%c _ %s", linha[i], linha);
        if (linha[n2] != '\0') {
            if (linha[n2] == separador) {
                linhaTratada = "";

                n3 = 0;
                n2 = n2 + 1;

                n = n + 1;
                continue;
            }

            strncpy(&linhaTratada[n3], &linha[n2], sizeof(linha[n2]));
            linhaTratada[n3 + 1] = '\0';
            matrizTratada[n] = strdup(linhaTratada);

            if (matrizTratada[n] != NULL) {
                n2 = n2 + 1;
                n3 = n3 + 1;
            }
        }
    }
    //printf("\n0~%s\n1~%s", matrizTratada[0], matrizTratada[1]);
    //printf("\nlinha - %s", linhaTratada);

    return matrizTratada;
}

char* 
linha_aparar(char* linha) {
    int n = 0;

    while (linha[n] == ' ') { n = n + 1; }

    char* linhaTratada = "";
    int i = 0;
    while (linha[n] != '\0') {
        strncpy(&linhaTratada[i], &linha[n], sizeof(linha[n] - 1));

        linhaTratada[i + 1] = '\0';

        //printf("\n%d %d %c %c", i, n, linha[n], linhaTratada[i]);
        n = n + 1;
        i = i + 1;
    }

    int diferença = n - i;
    int índexReal = n - diferença;

    //printf("%d", índexReal);

    while (linhaTratada[índexReal - 1] == ' ' || linhaTratada[índexReal - 1] == '\n' || linhaTratada[índexReal - 1] == '\r' || linhaTratada[índexReal - 1] == '\t') {
        linhaTratada[índexReal - 1] = '\0';
        //printf("\n%d %c", índexReal, linhaTratada[índexReal - 1]);
        índexReal = índexReal - 1;
    }

    return strdup(linhaTratada);
}