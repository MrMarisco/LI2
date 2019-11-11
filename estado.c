//
// Created by pja on 28/02/2019.
//
#include <stdio.h>
#include "estado.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Imprime menu com comandos no ecrã
 */
void printaComandos ()
{
    printf ("N-New Game\n");
    printf ("L-Load Game\n");
    printf ("E-Save Game\n");
    printf ("J<L,C>-Play\n");
    printf ("S-Jogadas Válidas\n");
    printf ("H-Sugestion\n");
    printf ("U-Undo\n");
    printf ("A-Game vs Bot\n");
    printf ("B-Jogar Bot\n");
    printf ("P-Comandos\n");
    printf ("C-Campeonato\n");
    printf ("Q-Quit\n\n");
}

/**
 * @brief Troca o valor da peça
 * @param c Peça a trocar
 * @return Devolve peça trocada
 */
VALOR troca (VALOR c)
{
    if (c==VALOR_O) return VALOR_X;
    if (c==VALOR_X) return VALOR_O;
}

/**
 * @brief Imprime o tabuleiro de um estado
 * @param e Estado a ser imprimido
 */
void printa(ESTADO e)
{
    char c = ' ',atual;
    int x=0,o=0;
    if (e.peca==VALOR_X) atual='X';else atual='O';
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            switch (e.grelha[i][j]) {
                case VALOR_O: {
                    c = 'O';
                    o++;
                    break;
                }
                case VALOR_X: {
                    c = 'X';
                    x++;
                    break;
                }
                case VAZIA: {
                    c = '-';
                    break;
                }
            }
            printf("%c ", c);

        }
        printf("\n");
    }
    printf ("    Joga %c\n",atual);
    printf ("    MODO %c\n",e.modo);
    printf(" 'X'=%d 'O'=%d\n",x,o);
}

/**
 * @brief Verifica se um número existe num array
 * @param i Número
 * @param v Array
 * @return Devolve 1 se existe e 0 se nao existe
 */
int existe (int i,int v [8])
{
    int j;
    for (j=0;j<8;j++) 
        {
         if  (v[j]==i) return 1; 
        }
    return 0;
}

/**
 * @brief Verifica se uma certa posição pertence ao tabuleiro 8x8
 * @param i Primeira coordenada
 * @param j Segunda coordenada
 * @return Devolve 1 se existe e 0 se nao existe
 */
int dentro (int i,int j)
{
 if (i<8&&i>=0&&j<8&&j>=0) return 1;
 return 0;
}

/**
 * @brief coloca 2 nas posições do array se naquela direção existe uma peça do mesmo tipo e peças opostas entre elas.
 * @param i Primeira Coordenada
 * @param j Segunda Ordenada
 * @param a Array das posições a volta
 * @param e Estado
 */
void dispersa (int i,int j,int a [8],ESTADO e)
{
    int l=i,c=j;
    VALOR v;
    v=e.peca;
    
    i=l-1;
    for (i;a[0]==1&&dentro(i,j);i--) {if (e.grelha[i][j]==VAZIA) a[0]=0;
                       if (e.grelha[i][j]==v) a[0]=2;}
    i=l-1;j=c+1;
    for (;a[1]==1&&dentro(i,j);i--,j++) {if (e.grelha[i][j]==VAZIA) a[1]=0;
                       if (e.grelha[i][j]==v) a[1]=2;}
    i=l;j=c+1;
    for (;a[2]==1&&dentro(i,j);j++) {if (e.grelha[i][j]==VAZIA) a[2]=0;
                       if (e.grelha[i][j]==v) a[2]=2;}
    i=l+1;j=c+1;
    for (;a[3]==1&&dentro(i,j);i++,j++) {if (e.grelha[i][j]==VAZIA) a[3]=0;
                       if (e.grelha[i][j]==v) a[3]=2;}
    i=l+1;j=c;
    for (;a[4]==1&&dentro(i,j);i++) {if (e.grelha[i][j]==VAZIA) a[4]=0;
                       if (e.grelha[i][j]==v) a[4]=2;}
    i=l+1;j=c-1;
    for (;a[5]==1&&dentro(i,j);i++,j--) {if (e.grelha[i][j]==VAZIA) a[5]=0;
                       if (e.grelha[i][j]==v) a[5]=2;}
    i=l;j=c-1;
    for (;a[6]==1&&dentro(i,j);j--) {if (e.grelha[i][j]==VAZIA) a[6]=0;
                       if (e.grelha[i][j]==v) a[6]=2;}
    i=l-1;j=c-1;
    for (;a[7]==1&&dentro(i,j);i--,j--) {if (e.grelha[i][j]==VAZIA) a[7]=0;
                       if (e.grelha[i][j]==v) a[7]=2;}
}

/**
 * @brief Coloca 1 nas diferentes posições do array se a mesma pertence ao tabuleiro e contém uma peça adversária
 * @param i Primeira coordenada
 * @param j Segunda coordenada
 * @param a Array das posições em volta
 * @param e Estado
 */
void array (int i,int j,int a [8],ESTADO e)
{
    VALOR v,o;
    v=e.peca;
    o=troca (v);
    if (dentro (i-1,j) && e.grelha[i-1][j]==o) a[0]=1;
    if (dentro (i-1,j+1) && e.grelha[i-1][j+1]==o) a[1]=1;
    if (dentro (i,j+1) && e.grelha[i][j+1]==o) a[2]=1;
    if (dentro (i+1,j+1) && e.grelha[i+1][j+1]==o) a[3]=1;
    if (dentro (i+1,j) && e.grelha[i+1][j]==o) a[4]=1;
    if (dentro (i+1,j-1) && e.grelha[i+1][j-1]==o) a[5]=1;
    if (dentro (i,j-1) && e.grelha[i][j-1]==o) a[6]=1;
    if (dentro (i-1,j-1) && e.grelha[i-1][j-1]==o) a[7]=1;
}

/**
 * @brief Verifica se uma jogada é possivel num certo estado
 * @param i Primeira coordenada
 * @param j Segunda coordenada
 * @param e Estado
 * @return Devolve 1 se é possivel e 0 se nao é possivel.
 */
int epossivel (int i,int j,ESTADO e)
{   
    int u;
    int a [8]= {0,0,0,0,0,0,0,0};
    array (i,j,a,e);
    dispersa (i,j,a,e);
    if (existe (2,a) && e.grelha[i][j]==VAZIA ) return 1;
    return 0;
}

/**
 * @brief Imprime tabuleiro com '+' nas posições onde a jogada é possível
 * @param e Estado
 */
void printaPossiveis (ESTADO e)
{
    char c = ' ',atual;
    int x=0,o=0;
    if (e.peca==VALOR_X) atual='X';else atual='O';
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (epossivel (i,j,e))  printf("+ ");
            else {
            switch (e.grelha[i][j]) 
            {
                case VALOR_O: {
                    c = 'O';
                    o++;
                    break;
                }
                case VALOR_X: {
                    c = 'X';
                    x++;
                    break;
                }
                case VAZIA: {
                    c = '-';
                    break;
                }
            }
            printf("%c ", c);
                }
        }
        printf("\n");
    }
    printf ("    Joga %c\n",atual);
    printf ("    MODO %c\n",e.modo);
    printf(" 'X'=%d 'O'=%d\n",x,o);
    for (int i = 0; i < 8; i++) 
   {
        for (int j = 0; j < 8; j++) 
            if (epossivel (i,j,e))  printf("(%d,%d) ",i+1,j+1);
   }
   printf("\n");
}

/**
 * @brief Altera o Tabuleiro de acordo com a jogada feita nas coordenadas (i,j).
 * @param i Primeira coordenada
 * @param j Segunda coordenada
 * @param a Array das posições a volta
 * @param e Estado
 * @return Devolve o estado resultante.
 */
ESTADO alteraTabuleiro (int i,int j,int a [8],ESTADO e)
{
    int l=i,c=j;
    VALOR v,o;
    v=e.peca;
    o=troca (v);
    e.grelha [i][j]=v;
    i=l-1;
    for (;a[0]==2 && e.grelha[i][j]==o;i--) {
            e.grelha[i][j]=v;}
    i=l-1;j=c+1;
    for (;a[1]==2 && e.grelha[i][j]==o;i--,j++) {
            e.grelha[i][j]=v;}
    i=l;j=c+1;
    for (;a[2]==2 && e.grelha[i][j]==o;j++) {
            e.grelha[i][j]=v;}
    i=l+1;j=c+1;
    for (;a[3]==2 && e.grelha[i][j]==o;i++,j++) {
            e.grelha[i][j]=v;}
    i=l+1;j=c;
    for (;a[4]==2 && e.grelha[i][j]==o;i++) {
            e.grelha[i][j]=v;}
    i=l+1;j=c-1;
    for (;a[5]==2 && e.grelha[i][j]==o;i++,j--) {
            e.grelha[i][j]=v;}
    i=l;j=c-1;
    for (;a[6]==2 && e.grelha[i][j]==o;j--) {
            e.grelha[i][j]=v;}
    i=l-1;j=c-1;
    for (;a[7]==2 && e.grelha[i][j]==o;i--,j--) {
            e.grelha[i][j]=v;};
    return e;
}

ESTADO inserir (int i,int j,ESTADO e) 
{
    int a [8]={0,0,0,0,0,0,0,0};
        array (i,j,a,e);
        dispersa (i,j,a,e);
        e=alteraTabuleiro (i,j,a,e);
        e.peca=troca(e.peca);
    return e;
}

/**
 * @brief Imprime a pontuação de cada jogador e indica o vencedor no estado de jogo
 * @param e Estado
 * @return Devolve o carácter da peça do jogador que ganhou
 */
char score (ESTADO e)
{
    int i,j,x=0,o=0;
    for (i=0;i<8;i++)
    {
        for (j=0;j<8;j++)
            {
            if (e.grelha[i][j]==VALOR_X) x++;
            if (e.grelha[i][j]==VALOR_O) o++;
            }
    }
    printf("\n-Existem %d peças 'X'-\n",x);
    printf("-Existem %d peças 'O'-\n",o);
    if (x<o) {
        printf("-'O' ganhou por %d-\n\n", o - x);
        return 'O';
    }
    else
        if (x>o) {
            printf("-'X' ganhou por %d-\n\n", x - o);
            return 'X';
        }
        else {
            printf("-Está Empatado-\n\n");
            return '-';
        }
    }

/**
 * @brief Reseta o estado preenchendo apenas as posições centrais
 * @return Devolve o estado do início de jogo
 */
ESTADO new ()
{
    ESTADO e = {0};
    e.grelha[3][4] = VALOR_X;
    e.grelha[4][3] = VALOR_X;
    e.grelha[3][3] = VALOR_O;
    e.grelha[4][4] = VALOR_O;
    e.modo ='1';
    e.peca=VALOR_X;
    return e;
 }

/**
 * @brief Abre um ficheiro e lê o estado e a dificuldade do bot nele contido
 * @param dificuldade Dificuldade do bot
 * @param e Estado
 * @param h Histórico
 * @param comando Comando com o nome do ficheiro
 * @return Devolve o estado presente no ficheiro
 */
ESTADO abrir (int dificuldade,ESTADO e,HIST ** h,char *comando)
{
    HIST **k=h;
    VALOR antpeca;
    int i=2,j;
    char atual,bot,nome[48],linha [20],chr,chr2;
    FILE * cena;
    while (comando[i]!='\0') {
        nome[i - 2] = comando[i];
        i++;
    }
    nome[i-2]='\0';
    cena=fopen (nome,"r");
    fgets(linha,20,cena);
    bot = linha[0];
    atual = linha[2];
    dificuldade=linha[4];
    if (bot=='M') e.modo='0'; else e.modo='1';
    if (atual=='X') e.peca=VALOR_X;
    else e.peca=VALOR_O;
    for(i = 0; i<8; i++) {
        for (j = 0; j<8; j++) {
            chr = fgetc(cena);
            e.grelha[i][j] = (chr=='X') ? (VALOR_X):((chr=='O') ? (VALOR_O):VAZIA);
            chr2=fgetc(cena);
        }
        if(chr2==' ') fgetc(cena);
    }
    antpeca=e.peca;
    while (fgetc(cena)!=EOF) {
        *k=malloc(sizeof(HIST));
        (*k)->past.peca=troca(antpeca);
        (*k)->past.modo=e.modo;
        for (i=0;i<8;i++)
        {
            fgets(linha, 32, cena);
            for (j=0;j<16;j++)
            {
                if (linha[j]!=' ')
                {
                    if (linha[j]=='O')
                        (*k)->past.grelha[i][j/2] = VALOR_O;
                    else
                    {
                        if (linha[j]=='X')
                            (*k)->past.grelha[i][j/2]=VALOR_X;
                        else (*k)->past.grelha[i][j/2]=VAZIA;
                    }
                }
            }
        }
        antpeca=(*k)->past.peca;
        k=&((*k)->apontador);
    }
    *k=NULL;
    fclose (cena);
    return e;
}

/**
 * @brief Converte o valor da peça num carácter
 * @param v Valor da peça
 * @return Devolve o carácter que corresponde à peça
 */
char caracter (VALOR v)
{
    char x;
    if (v==VALOR_X) x='X';else
    if (v==VALOR_O) x='O';
    else x='-';
    return x;
}

/**
 * @brief Abre um ficheiro e guarda o estado atual e a dificuldade do bot no mesmo
 * @param e Estado
 * @param h Histórico
 * @param dificuldade Dificuldade do bot
 * @param comando Comando com o nome do ficheiro
 */
void guarda (ESTADO e,HIST **h,int dificuldade,char *comando)
{       
        int i,j,coisa=0;
        FILE *cena;
        char nome[48],bot,atual;
        HIST k;
        if ((*h)==NULL) coisa=1;
        else k=**h;
        i=2;
        while (comando[i]!='\0') {
            nome[i-2]=comando[i];
            i++;
        }
        nome[i-2]='\0';
        cena=fopen (nome,"w");
        if (e.modo=='0') bot='M';
        else bot='A';
        if (e.peca==VALOR_X) atual='X';
        else atual='O';
        fprintf(cena,"%c %c %d\n",bot,atual,dificuldade);
        for (i=0;i<8;i++) {
            for (j=0;j<8;j++) {
            fprintf(cena,"%c ",caracter (e.grelha[i][j]));
                }
            fprintf(cena,"\n");
            }
        fprintf(cena,"\n");
        if (coisa!=1) {
            while (k.apontador != NULL) {
                for (i = 0; i < 8; i++) {
                    for (j = 0; j < 8; j++) {
                        fprintf(cena, "%c ", caracter(k.past.grelha[i][j]));
                    }
                    fprintf(cena, "\n");
                }
                fprintf(cena, "\n");
                k = *(k.apontador);
            }
        }
        fclose (cena);
}

/**
 * @brief Verifica se o ficheiro existe
 * @param comando Comando com o nome do ficheiro
 * @return Devolve 1 se existe e 0 se não existe
 */
int temgravado (char* comando)
{
    int i=2;
    char nome[48];
    while (comando[i]!='\0') {
        nome[i - 2] = comando[i];
        i++;
    }
    nome[i-2]='\0';
    FILE *file;
    if ((file=fopen (nome,"r")))
         {
            fclose (file);
            return 1;
         }
    return 0;
}
/**
 * @brief Verifica a existencia de jogadas válidas
 * @param e Estado
 * @return Devolve 0 se existe jogada para a peça atual,1 se não existe para a peça atual mas existe para a peça oposta,2 se não existe para a peça atual nem para a peça oposta.
 */
int naoHaJogadasValidas (ESTADO e)
{
    int conta=0,conta2=0,resultado=0;
    int i,j;
    for (int i = 0; i < 8; i++) 
   {
        for (int j = 0; j < 8; j++) 
            if (epossivel (i,j,e)) conta+=1;
    }
    if (conta==0) 
    {
    e.peca=troca (e.peca);
    for (int i = 0; i < 8; i++) 
   {
        for (int j = 0; j < 8; j++) 
            if (epossivel (i,j,e)) conta2+=1;
    }
   
   if (conta2==0) resultado=2;
   else resultado=1;
    }
   return resultado;
}

/**
 * @brief Imprime tabuleiro com a sugestão de jogada
 * @param x Primeira coordenada
 * @param y Segunda coordenada
 * @param e Estado
 */
void printaSugestao (int x,int y,ESTADO e)
{
    char c = ' ',atual;
    if (e.peca==VALOR_X) atual='X';else atual='O';
    int a=0,b=0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (i==x&&j==y) printf("? "); else
        {
            switch (e.grelha[i][j]) 
            {
                case VALOR_O: {
                    c = 'O';
                    b++;
                    break;
                }
                case VALOR_X: {
                    c = 'X';
                    a++;
                    break;
                }
                case VAZIA: {
                    c = '-';
                    break;
                }
            }
            printf("%c ", c);
        }
        }
        printf("\n");
    }
    printf ("    Joga %c\n",atual);
    printf("X'=%d 'O'=%d\n",a,b);
}

/**
 * @brief Conta a diferença de peças entre v e a peça oposta
 * @param v Valor da peça
 * @param e Estado
 * @return Devolve a diferença entre as duas peças
 */
int conta (VALOR v,ESTADO e)
{
    int i,j,x=0,o=0,res=0;
    for (i=0;i<8;i++){
        for (j=0;j<8;j++){ 
            if (e.grelha[i][j]==VALOR_X) x+=1;
            else if (e.grelha[i][j]==VALOR_O) o+=1;
        }
        }
        if (v==VALOR_X) res=x-o; else res=o-x;
    return res;
}

/**
 * @brief Calcula o indice do maximo ou minimo de um array.
 * @param s Apontador para um array de inteiros
 * @param n Numero de inteiros pertencentes ao array
 * @param maxOUmin Inteiro,1 se quiser calcular o indice do maximo do array,0 o minimo. 
 * @return Devolve o indice do maximo ou minimo de um array.
 */
int maxMin (int s [],int n,int maxOUmin)
{
	int j=s[0],i,res=0;
	for (i=0;i<n;i++)
	{
		if (maxOUmin==0 && s[i]<j) {res=i;j=s[i];} else
		if (maxOUmin==1 && s[i]>j) {res=i;j=s[i];}
	}
	return res;
}

/**
 * @brief Na arvore do algoritmo MaxMin,devolve o inteiro representante daquele ramo.
 * @param v Peca com qual o bot quer jogar. 
 * @param e Estado atual.
 * @param n profundidade da arvore representante do algoritmo MinMax, será 0 nas folhas da arvore.
 * @param maxOUmin simular a vez do bot a jogar deve-se maximizar (1),contrário minimizar (0).
 * @return Devolve o inteiro representante do ramo da arvore MinMax.
 */
int auxbotsugestao (VALOR v,ESTADO e,int n,int maxOUmin) 
{	
    int i,j,indice=0,res,array [15];                        
	JOGADA jog [15];                                    
	ESTADO salva;										
	if (n==0) res=conta(v,e);else 
		{
	for (i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            if (epossivel(i,j,e)&&indice<15) {  
                jog[indice].x=i;				
                jog[indice].y=j;
                indice++;
            }
        }
    }
    
    if (naoHaJogadasValidas (e)==1) {e.peca=troca(e.peca);res=auxbotsugestao(v,e,n-1,1-maxOUmin);} else 
    if (naoHaJogadasValidas (e)==2 && conta (v,e)>0) res=100; else
    if ((naoHaJogadasValidas (e)==2 && conta (v,e)<0)) res=conta (v,e);else
    {
        for (i=0;i<indice;i++)									
    	{
    		salva=inserir(jog[i].x,jog[i].y,e);                
    		array[i]=auxbotsugestao (v,salva,n-1,1-maxOUmin);  
    	}
        res= array [maxMin (array,indice,maxOUmin)]; 
    }
        }
    return res;
}

/**
 * @brief Calcula a melhor jogada para o bot realizar segundo o algoritmo MinMax.
 * @param e Estado no qual se quer realizar a jogada.
 * @param profundidade ,ou seja,quantas jogadas no futuro se quer simular.
 * @return Devolve a Jogada sugerida.
 */
JOGADA botsugestao (ESTADO e,int profundidade) 
{   
    int i,j,indice=0,array[15];
    ESTADO salva;
    VALOR v;
    v=e.peca;
    JOGADA jog [15],jogada;
    int flag=0;
    if (epossivel(0,0,e)) {jogada.x=0;jogada.y=0;}else
    if (epossivel(0,7,e)) {jogada.x=0;jogada.y=7;}else
    if (epossivel(7,0,e)) {jogada.x=7;jogada.y=0;}else
    if (epossivel(7,7,e)) {jogada.x=7;jogada.y=7;}else
    {
    for (i=0;i<8;i++)   	
    {						
        for(j=0;j<8;j++)	
        {
            
            if (epossivel(i,j,e)&&indice<15&&flag==0) {
                jog[indice].x=i;
                jog[indice].y=j;
                indice++;
            }
        }
    }                                                            
    for (i=0;i<indice;i++)                  
    	{
    		salva=inserir(jog[i].x,jog[i].y,e);
    		array[i]=auxbotsugestao (v,salva,profundidade,0); 
    	}
    indice=maxMin (array,indice,1);
    jogada=jog[indice];
    }
    return jogada;
}


/**
 * @brief Efetua todos os comandos
 * @param e Estado
 * @param h Histórico
 * @param dificuldade Dificuldade do bot
 */
void jogaManual (ESTADO e,HIST **h,int dificuldade)
{
	HIST *pas,*caixa;
    int i,j;
    JOGADA jog;
    char comando [50];
    fgets (comando,50,stdin);
    while (toupper(comando[0])!='Q') {
        for (i=0;comando[i]!='\n';i++);
        comando[i]='\0';
        switch (toupper(comando[0])) {
            case ('A'): {
                while (*h!=NULL) {
                        caixa=(*h)->apontador;
                        free(*h);
                        *h=caixa;
                    }
                printf("Insere Dificuldade [0 a 7]:\n");
                e=new();
                e.modo='1';
                scanf ("%d",&dificuldade);
                e.peca=VALOR_X;
                if (comando[2] == 'X') {
                    jog = botsugestao(e,dificuldade);
                    e = inserir(jog.x, jog.y, e);
                }
                printf("\n");
                printa(e);
                printf("\n");
                break;
            }
            case ('B'): {
                pas = malloc(sizeof(HIST));
                pas->past = e;
                pas->apontador = *h;
                *h = pas;
                jog = botsugestao(e,0);
                printf("Posicao sugerida é (%d,%d)\n", jog.x+1, jog.y+1);
                e = inserir(jog.x, jog.y, e);
                printf("\n");
                printa(e);
                printf("\n");
                break;
            }
            case ('H'): {
                jog = botsugestao(e, 0);
                printaSugestao(jog.x, jog.y, e);
                break;
            }
            case ('E'): {
                guarda(e,h,dificuldade,comando);
                printf("\nSalvo\n\n");
                printa(e);
                break;
            }
            case ('L'): {
                if (temgravado(comando)) {
                    while (*h!=NULL) {
                        caixa=(*h)->apontador;
                        free(*h);
                        *h=caixa;
                    }
                    e = abrir(dificuldade,e,h,comando);
                } else printf("Nada Gravado\n");
                printa(e);
                break;
            }
            case ('N'): {
                while (*h!=NULL) {
                        caixa=(*h)->apontador;
                        free(*h);
                        *h=caixa;
                    }
                e = new();
                if (comando[2] == 'X')
                    e.peca = VALOR_X;
                else
                    e.peca = VALOR_O;
                printa(e);
                (*h) = NULL;
                break;
            }
            case ('P'): {
                printaComandos();
                printa(e);
                break;
            }
            case ('J'): {
                i = comando[2] - '0' - 1;
                j = comando[4] - '0' - 1;
                if (epossivel(i, j, e)) {
                    pas = malloc(sizeof(HIST));
                    pas->past = e;
                    pas->apontador = *h;
                    *h = pas;
                    e = inserir(i, j, e);
                } else { printf("\nJogada Inválida\n"); }
                printf("\n");
                printa(e);
                printf("\n");
                break;
            }
            case ('S'): {
                printf("\n");
                printaPossiveis(e);
                printf("\n");
                break;
            }
            case ('U'): {
                if ((*h) == NULL) {
                    printf("-Esta no Inicio-\n");
                    printa(e);
                }
                else {
                    e = (*h)->past;
                    pas = (*h)->apontador;
                    free(*h);
                    *h = pas;
                    printa(e);
                }
                break;
            }
            case ('C'): {
                *h=NULL;
                if (!temgravado(comando)) {
                    e = new();
                    printa(e);
                    goto fim;
                }
                else {
                    for(i=0;comando[i]!='\0';i++);
                    if (comando[i-2]=='g')
                        score(e);
                    else {
                        e = abrir(dificuldade, e,h, comando);
                    }
                }
                printf("Tabuleiro lido:\n");
                printa(e);
                joga:
                    jog = botsugestao(e, 5);
                    e = inserir(jog.x, jog.y, e);
                    printf("Posição jogada:\nLinha:%d\nColuna:%d\n",jog.x+1,jog.y+1);
                    printf("Tabuleiro após jogada:\n");
                    printa(e);
                    if (naoHaJogadasValidas(e)==1) {
                        printf("Não há jogadas válidas, passando à frente...");
                        e.peca=troca(e.peca);
                        goto joga;
                    }
                    else {
                        if (naoHaJogadasValidas(e) == 2) {
                            for (i = 0; comando[i] != '\0'; i++);
                            comando[i] = '.';
                            comando[i + 1] = 'g';
                            comando[i + 2] = score(e);
                            comando[i + 3] = '\0';
                        }
                        fim:
                        guarda(e, h, 3, comando);
                    }
                break;
            }
        }
    if (toupper (comando[0]) == 'J' || toupper (comando[0]) == 'B' ) 
        {   

            if (naoHaJogadasValidas(e)==0 && e .modo=='1'){
                    jog = botsugestao(e,dificuldade);
                    printf ("\nBot jogou em (%d,%d)\n",jog.x+1,jog.y+1);
                    e = inserir(jog.x, jog.y, e);
                    printa(e);
                    while (naoHaJogadasValidas(e)==1){
                        printf("Sem Jogadas Válidas, passando a frente\n");
                        e.peca = troca(e.peca);
                        jog = botsugestao(e,dificuldade);
                        printf ("\nBot jogou em (%d,%d)\n",jog.x+1,jog.y+1);
                        e = inserir(jog.x, jog.y, e);
                        printa(e);
                    }
            }
            if (naoHaJogadasValidas(e) == 1) {
                printf("Sem Jogadas Válidas, passando a frente\n");
                e.peca = troca(e.peca);
                printa(e);
            }else
                if (naoHaJogadasValidas(e) == 2) {
                score(e);
            }
        }
    fgets(comando,50,stdin);
    }
}

/**
 * @brief Chama a função jogaManual se estiver no modo manual
 * @param e Estado
 * @param h Historico
 * @param dificuldade Dificuldade do bot
 */
void joga (ESTADO e,HIST **h,int dificuldade)
{
    if (e.modo=='0') jogaManual (e,h,dificuldade);
}