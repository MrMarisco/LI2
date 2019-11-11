//
// Created by pja on 27/02/2019.
//



#ifndef PROJ_ESTADO_H
#define PROJ_ESTADO_H



/**
estado.h
Definição do estado i.e. tabuleiro. Representação matricial do tabuleiro.
*/


// definição de valores possiveis no tabuleiro
typedef enum {VAZIA, VALOR_X, VALOR_O} VALOR;
typedef struct jogada {
	int x;
	int y;
}JOGADA;

/**
Estrutura que armazena o estado do jogo
*/
typedef struct estado {
    VALOR peca; // peça do jogador que vai jogar!
    VALOR grelha[8][8];
    char modo; // modo em que se está a jogar! 0-> manual, 1-> contra computador
} ESTADO;


typedef struct historico {
	ESTADO past;
	struct historico* apontador;
}HIST;



void printaComandos ();
void printa(ESTADO);
void joga (ESTADO,HIST**,int);



#endif //PROJ_ESTADO_H