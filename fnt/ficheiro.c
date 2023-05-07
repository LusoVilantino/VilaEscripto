﻿#include "ficheiro.h"
#include "mapa.h"
#include "linha.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


ConteúdoFicheiro
ficheiro_lêr(char* ficheiroNome) {
    char** linhas = malloc(sizeof(char*));
    char* linhaActualDoFicheiro = malloc(sizeof(char));
    char charactéreActualDoFicheiro = '\0';
    FILE* ficheiroLido = fopen(ficheiroNome, "r");

    if (linhas == NULL) return (ConteúdoFicheiro) { 0 };

    int n = 0;
    int nl = 0;
    while ((charactéreActualDoFicheiro = fgetc(ficheiroLido)) != EOF) {
        if (charactéreActualDoFicheiro == '$') break;
        if (charactéreActualDoFicheiro == '#') {
            char comentário;
            while (comentário = fgetc(ficheiroLido))
            {
                if (comentário == '\n') break;
            }
            continue;
        }

        if (charactéreActualDoFicheiro == '\n') {
            linhas[nl] = malloc(sizeof(char*));
            linhas[nl] = strdup(linhaActualDoFicheiro);

            linhas = realloc(linhas, (nl + 1 * sizeof(linhas)) * sizeof(char**));

            linhaActualDoFicheiro = malloc(sizeof(char*));

            n = 0;
            nl = nl + 1;
            continue;
        }
        linhaActualDoFicheiro[n] = charactéreActualDoFicheiro;

        n = n + 1;

        //linhaActualDoFicheiro = realloc(linhaActualDoFicheiro, (n + 1 * sizeof(linhaActualDoFicheiro)) * sizeof(char*));
        linhaActualDoFicheiro = realloc(linhaActualDoFicheiro, n + 1 * sizeof(char*)); // n + 1 é necessário pela 'regra do múltiplo a índice 0'.
        linhaActualDoFicheiro[n + 1] = '\0';

        //if (charactéreActualDoFicheiro == '\n') {
        //    char** tempor = realloc(linhas, (nl + 1 * 2) * sizeof *linhas);
        //    if (tempor != NULL) {
        //        linhas = tempor;
        //        linhas[nl] = strdup(linhaActualDoFicheiro);

        //        free(linhaActualDoFicheiro);
        //        linhaActualDoFicheiro = malloc(sizeof(char));

        //        n = 0;
        //        nl = nl + 1;
        //        continue;
        //    }
        //}

        //char* tempor = realloc(linhaActualDoFicheiro, (n + 1 * 2) * sizeof *linhaActualDoFicheiro); // n + 1 é necessário pela 'regra do múltiplo a índice 0'.
        //if (tempor != NULL) {
        //    linhaActualDoFicheiro = tempor;

        //    linhaActualDoFicheiro[n] = charactéreActualDoFicheiro;
        //    //linhaActualDoFicheiro = realloc(linhaActualDoFicheiro, (n + 1 * sizeof(linhaActualDoFicheiro)) * sizeof(char*));
        //    n = n + 1;

        //    linhaActualDoFicheiro[n] = '\0';
        //}
        //printf("\n%c - %s", charactéreActualDoFicheiro, linhaActualDoFicheiro);
    }

    ConteúdoFicheiro cf;
    cf.quantidade_conteúdo = nl;
    cf.conteúdo = linhas;

    //printf("\n");

    free(linhaActualDoFicheiro);
    fclose(ficheiroLido);

    return cf;
}

Mapa* ficheiro_conteúdo_mapear(char separador, char* ficheiroCaminho) {
    ConteúdoFicheiro ficheiroConteúdo = ficheiro_lêr(ficheiroCaminho);

    Mapa* mapa = mapa_construir();

    printf("\n\n %s - %d \n\n", ficheiroCaminho, ficheiroConteúdo.quantidade_conteúdo);

    int n = 0;
    while (ficheiroConteúdo.conteúdo) {
        if (n != ficheiroConteúdo.quantidade_conteúdo) {
            char** linhaSeparada = linha_separar(separador, ficheiroConteúdo.conteúdo[n]);
            mapa_introduzir(&mapa, (Mapa) { linha_aparar(linhaSeparada[0]), linha_aparar(linhaSeparada[1]), n });
            printf("%s- %s- %d-\n", (char*)mapa[n].passe, (char*)mapa[n].valôr, mapa[n].i);

            //system("cls");
            //// Try some Set Graphics Rendition (SGR) terminal escape sequences
            //wprintf(L"\x1b[31mThis text has a red foreground using SGR.31.\r\n");
            //wprintf(L"\x1b[1mThis text has a bright (bold) red foreground using SGR.1 to affect the previous color setting.\r\n");
            //wprintf(L"\x1b[mThis text has returned to default colors using SGR.0 implicitly.\r\n");
            //wprintf(L"\x1b[34;46mThis text shows the foreground and background change at the same time.\r\n");
            //wprintf(L"\x1b[0mThis text has returned to default colors using SGR.0 explicitly.\r\n");
            //wprintf(L"\x1b[31;32;33;34;35;36;101;102;103;104;105;106;107mThis text attempts to apply many colors in the same command. Note the colors are applied from left to right so only the right-most option of foreground cyan (SGR.36) and background bright white (SGR.107) is effective.\r\n");
            //wprintf(L"\x1b[39mThis text has restored the foreground color only.\r\n");
            //wprintf(L"\x1b[49mThis text has restored the background color only.\r\n");
            n = n + 1;
        }
        else break;
    }

    return mapa;
}