#include <stdio.h>
#include "estado.h"


int main()
{
    ESTADO e = {0};
    HIST *h=NULL;
    int dificuldade =0;
    printaComandos ();
        // estado inicial do tabuleiro. Inicio do jogo!
        e.grelha[3][4] = VALOR_X;
        e.grelha[4][3] = VALOR_X;
        e.grelha[3][3] = VALOR_O;
        e.grelha[4][4] = VALOR_O;
        e.peca = VALOR_X;
        e.modo ='0';
    printf("\n");
    printa(e);
    printf("\n");
    joga (e,&h,dificuldade);
    return 0;
}