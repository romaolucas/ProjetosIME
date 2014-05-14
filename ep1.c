/***************************************************************/
/**                                                           **/
/**   Lucas Romao Silva         Numero USP: 8536214           **/
/**   Exercicio-Programa 1                                    **/
/**                                                           **/
/***************************************************************/

#include <stdio.h>  /* scanf, printf,  ... */
#include <stdlib.h> /* srand, rand,    ... */


/*Algumas observacoes: 
1 - esse Exercicio-Programa consome muita memoria ao tentar resolver matrizes muito grandes, dado que gera matrizes de (n*n)*(n*n), porem, ele calcula de modo relativamente rapido se o tabuleiro dado tem solucao ou nao
2 - nao procurei tratar a opcao que o usuario digita, ou seja, ele ira dar problema caso voce insira algo diferente de s ou l na primeira opcao
3 - o meu metodo para encontrar a melhor solucao foi baseado no pdf disponivel no link: http://people.math.sfu.ca/~jtmulhol/math302/notes/24-Lights-Out.pdf e numa serie de 3 videos onde a primeira parte esta disponivel no link: http://www.youtube.com/watch?v=oCHCD_-nhg4
4 - o tabuleiro comeca a ficar torto conforme n aumenta muito, logo fica dificil de visualizar
*/

/*---------------------------------------------------------------*/
/* 
 * 0. C O N S T A N T E S 
 */

#define MAX 128

/*tamanho maximo do nome do arquivo*/

#define FNMAX 200

#define ACORDADO '#'
#define DORMINDO ' '
#define TAPINHA  'T'

#define TRUE 1
#define FALSE 0



/*Prototipos das funcoes*/

/* PARTE I */

void leiaTurtledorm(int *n, int tdorm[][MAX]);

void mostreTurtledorm(int n, int tdorm[][MAX], char c);

void atualizeTurtledorm(int n, int tdorm[][MAX], int lin, int col);

int  todosDormindo(int n, int tdorm[][MAX]);

int  graveTurtledorm(int n, int tdorm[][MAX]);

/* PARTE II */

void sorteieTurtledorm(int *n, int tdorm[][MAX]);

/* PARTE III */

void resolvaTurtledorm(int n, int tdorm[][MAX]);

/*  Funcoes auxiliares*/

int RandomInteger( int low, int high);

void geraMatriztapinha(int n, int mtapinha[][MAX*MAX+1]);

void geraMatriznula(int n, int nula[][MAX]);

void imprimeMatriz(int n, int M[][MAX*MAX+1]);

void escalonaMatriztapinha(int n, int mtapinha[][MAX*MAX+1]);

int  contaTapinhas(int n, int v[MAX*MAX]); 

/*---------------------------------------------------------------*/
/* 
 *  M A I N 
 */

int main(int argc, char *argv[]){

    int n, tdorm[MAX][MAX];

    int x, y, qtmovimento;
    
    char opcao, opcao2;

    qtmovimento = 0;
		
    printf("(s)ortear ou (l)er um turtledorm: ");
    scanf("%c", &opcao);

    if(opcao == 'l')

       leiaTurtledorm(&n, tdorm);

    else

       sorteieTurtledorm(&n, tdorm);
     
      mostreTurtledorm(n, tdorm, ACORDADO);

		/*enquanto houverem turtles despertos o laço de repeticao continuara executando, pode-se sair dele antes caso o usuario desista do jogo*/		

     while(!todosDormindo(n, tdorm)){
 
       
       printf("Digite:\n");
       printf("a - para ajuda\n");
       printf("d - para desistir\n");
       printf("g - para gravar o turtledorm\n");
       printf("linha coluna de onde se deseja dar um tapinha\nOpcao: ");

       /*ele tentara ler dois inteiros, se nao conseguir, ira executar a opcao correspondente*/
       
       if(scanf("%d %d", &x, &y) == 0){

           scanf("%c", &opcao2);

           switch(opcao2){
 
             case 'a':
                resolvaTurtledorm(n, tdorm);
                break;

             case 'd':
                printf("Voce falhou com a sua missao como guardiao apos %d movimentos. Boa sorte da proxima vez!\n", qtmovimento);
                return 0;

             case 'g':
                graveTurtledorm(n, tdorm);
                break;

            }
           
                 
        }
        else{
			  qtmovimento++;
           atualizeTurtledorm(n, tdorm, x-1, y-1);

			}
        
        printf("Numero de movimentos: %d\n\n", qtmovimento);  
        mostreTurtledorm(n, tdorm, ACORDADO);


    }

 
    printf("Estao todos dormindo, bom trabalho!\n");
    return 0;
}

/*---------------------------------------------------------------*/
/* 
 *  I M P L E M E N T A C A O   D A S   FU N C O E S   DA  
 *                       P A R T E   I 
 */

/*nessa funcao, estou supondo que o usuario ira digitar o nome dum arquivo que exista*/

void leiaTurtledorm(int *n, int tdorm[][MAX]){

      int i, j;
      char fname[FNMAX];
      FILE *arq;

      
      printf("Digite o nome de um arquivo: ");
      scanf("%s", fname);
      
      arq = fopen(fname, "r");

		/*pede ao usuario o nome de um arquivo valido ate isso acontecer*/
		if(arq == NULL)
			do{
				printf("Erro na leitura do arquivo '%s'\n Digite o nome de outro arquivo: ", fname);
				scanf("%s", fname);
				arq = fopen(fname, "r");
			}while(arq == NULL);

      fscanf(arq,"%d", n);

      for(i=0; i<*n; i++)
        for(j=0; j<*n; j++)
                   fscanf(arq, "%d", &tdorm[i][j]);
  

       fclose(arq);
}


void mostreTurtledorm(int n, int tdorm[][MAX], char c){

     int i, j, aux;

     for(i=0; i<=n; i++)
       for(j=0; j<=n; j++){

      		/*esses 3 primeiros ifs servem para desenhar a moldura do tabuleiro, o quarto e o quinto servem para desenhar as turtles despertas*/
            if(i==0 && j==0)
                  printf("     |");
            else 
              if(i==0)
                   printf("  %d  |", j);

               else
                 if(j==0)
                    printf("  %d  |", i);
                else
                  if(tdorm[i-1][j-1] == 0)
                    printf("  %c  |", DORMINDO);
                  else
							if(c == ACORDADO)
                    		printf("  %c  |", ACORDADO); 
							else
								printf("  %c  |", TAPINHA);

              if(j==n){

                 printf("\n");
                 
                 for(aux=0; aux<=n; aux++){

                     printf("-----");
                     
                     

                         printf("+");

                      if(aux == n)
        
                         printf("\n");

                  }

              }

             }
       
   
     

}


void atualizeTurtledorm( int n, int tdorm[][MAX], int lin, int col){

     /*verifica a partir da linha e da coluna, em quais posicoes deve-se dar um tapinha, como a matriz e binaria, um tapinha corresponde a somar um em determinada posicao da matriz e tirar o resto por 2*/

     if(col != 0)

           tdorm[lin][col-1] = (tdorm[lin][col-1] + 1) % 2;

      if(col != n-1)

           tdorm[lin][col+1] = (tdorm[lin][col+1] + 1) % 2;

      tdorm[lin][col] = (tdorm[lin][col] + 1) % 2;

      if(lin != n-1)         

          tdorm[lin+1][col] = (tdorm[lin+1][col] + 1) % 2;
       
      if(lin != 0)
         
          tdorm[lin-1][col] = (tdorm[lin-1][col] + 1) % 2;


}

int todosDormindo(int n, int tdorm[][MAX]){

    int i, j;

    for(i=0; i<n; i++)

      for(j=0; j<n; j++)

         if(tdorm[i][j])

           return FALSE;


  
     return TRUE;    

}


int graveTurtledorm(int n, int tdorm[][MAX]){

    int i, j;

    char file[FNMAX];

    FILE *arq;

    printf("Digite o nome de um arquivo: ");
    scanf("%s", file);

    arq = fopen(file, "w");

    if(!arq){
			printf("Erro na criacao do arquivo");
        return EXIT_FAILURE;

	}

    fprintf(arq, "%d\n", n);

    for(i=0; i < n; i++){

      for(j=0; j < n; j++)

         fprintf(arq, "%d ", tdorm[i][j]);

      fprintf(arq, "\n");

    }

    fclose(arq);

    return EXIT_SUCCESS;
}

/*---------------------------------------------------------------*/
/* 
 *  I M P L E M E N T A C A O   D A S   FU N C O E S   DA  
 *                       P A R T E   I I
 */

void sorteieTurtledorm(int *n, int tdorm[][MAX]){

     int semente, low, high, nTapinhas;

     int lin, col, cont;

     char dificuldade;

     printf("Digite o tamanho do Turtledorm: ");
     scanf("%d", n);
    
     geraMatriznula(*n, tdorm);
 

     low = high = 0;

     printf("Selecione a dificuldade: (f)acil, (m)edio, (d)ificil: ");
     scanf(" %c", &dificuldade);

     printf("Digite uma semente para inicializar: ");
     scanf("%d", &semente);

     srand(semente);

		/*gera a quantidade minima e maxima de tapinhas a serem dados conforme informado na especificacao do ep*/
     switch(dificuldade){

		    case 'f':

		     low = (int)((0.05)*(*n)*(*n));
		     high = (int)((0.20)*(*n)*(*n));
		     break;
	 
		    case 'm':
		    
		      low = (int)((0.25)*(*n)*(*n));
		      high = (int)((0.50)*(*n)*(*n));
		      break;

		    case 'd':

		     low = (int)((0.55)*(*n)*(*n));
		     high = (int)((0.85)*(*n)*(*n));
		     break;
     } 

    nTapinhas = RandomInteger(low, high);

    printf("N de tapinhas: %d\n", nTapinhas);
   
    /*monta o Turtledorm aplicando os nTapinhas nos lugares sorteados em lin e col*/
    for(cont = 0; cont < nTapinhas; cont++){

		     lin = RandomInteger(0, *n-1);
		     col = RandomInteger(0, *n-1);
	 
		     atualizeTurtledorm(*n, tdorm, lin, col);
   
    }
   
   /*conta os turtles despertos*/
	for(lin = 0, cont = 0 ; lin < *n; lin++)
 		for(col = 0; col < *n; col++)
 			if(tdorm[lin][col])
				cont ++;
			
	 
	printf("Ha %d turtles despertos\n", cont);

}

/*---------------------------------------------------------------*/
/* 
 *  I M P L E M E N T A C A O   D A S   FU N C O E S   DA  
 *                       P A R T E   I I I
 */

void resolvaTurtledorm(int n, int tdorm[][MAX]){

		  /*a variavel rank guarda a quantidade da linha de zeros da matriz escalonada reduzida*/
		  /*a variavel permutacao guarda as possiveis somas de quiet patterns a serem realizadas*/
		 /*a variavel index indica em qual coluna eu estou, quando index = 1, estou na penultima( ultima na matriz normal), quando index = 2, na antepenultima, etc*/

		  int lin, col, i, k, rank;
		  int menor, index, aux, aux2, compara;
        int permutacao;
        static int v[MAX*MAX] , menorv[MAX*MAX];
		  int msolucao[MAX][MAX];
		  int possivel = TRUE;
		  int linhazero = FALSE;
		  static int mtapinha[MAX*MAX][MAX*MAX+1];
	  
		  /*a matriz mtapinha corresponde a uma matriz onde cada linha corresponde a configuracao do turtledorm onde todas as tartarugas estao dormindo e um tapinha e dado em determinada posicao */  
 
		  rank = 0;
		  lin = col = 0;

		  geraMatriztapinha(n, mtapinha);
		 
        /*aqui e feita a matriz aumentada, isto e, a matriz de tapinhas, junto com a configuracao do tabuleiro*/
		  for(i = 0; i < n*n; i++){

		      mtapinha[i][n*n] = tdorm[lin][col];
		      col++;

		      if(col == n){
		         col = 0;
		         lin++;
	 
		      }         
		  }

		  escalonaMatriztapinha(n*n, mtapinha);

   		/*conta as linhas de zero*/
		  for(lin = 0; lin < n*n; lin++){
				for(col = 0; col < n*n; col++)
			 		if(mtapinha[lin][col])
	 					linhazero = FALSE;
			
					if(linhazero)
						rank++;
					linhazero = TRUE;

			}

			/*guarda a coluna solucao apos o escalonamento completo e armazena o numero de tapinhas dessa solucao*/
     		for(i = 0; i < n*n; i++)
				menorv[i] = mtapinha[i][n*n];

			menor = contaTapinhas(n*n, menorv);
			

         if(rank){
				/*verifica se o tabuleiro tem solucao, isto e, ve se o sistema correspondente e possivel, nos casos onde nao ha linhas de zero, essa verificacao e desnecessaria, um sistema e impossivel se na ultima coluna de alguma das linhas de zero ha um valor diferente de zero*/

				for(i =  n*n - 1;  i >= n*n - rank; i--) 
						if(mtapinha[i][n*n]){
							possivel = FALSE;
							break;
							}

				/*se for possivel, ele ira procurar pela melhor solucao*/

				if(possivel){
					permutacao = 1;

					/*o numero de permutacoes e dado por 2^n - 1 onde n e o numero de linhas de zeros da matriz aumentada em sua forma escalonada reduzida, nessas linhas abaixo, esse valor e calculado*/
               for(i = 0; i < rank; i++)
						permutacao *= 2;

					permutacao--;
					
					for(k = 1; k <= permutacao; k++){
						/*aqui sao feitas as somas possiveis, para isso, eu converto o valor de k para binario e onde ha 1s, significa que aquela coluna correspondente deve ser somada a coluna selecao, isto e, se k = 3 = 11 na base 2, temos que a primeira e a segunda coluna onde nao ha pivos devem ser somadas, se for k = 2, apenas a segunda, e por ai vai*/
						/*na hora de somar, ha apenas uma modificacao: onde deveria haver um pivo nessas colunas, e inserido o 1 na posicao do pivo, para entao fazer a soma*/

						aux = k;

						index = 0;

						/*inicializa a coluna de possivel solucao com o valor da ultima coluna da matriz aumentada*/
						for(i = 0; i < n*n; i++)
							v[i] = mtapinha[i][n*n];

						/*calcula a possivel solucao do sistema*/
		            while(aux){
		               
							aux2 = aux % 2;
							index++;

							if(aux2)

								for(i = 0; i < n*n; i++){
									if(i != (n*n - index))
										v[i] = (v[i] + mtapinha[i][n*n-index]) % 2;
									else
										v[i] = (v[i] + 1) % 2;
								
							}
						
		               
							aux /= 2;

		         	}

     					/*verifica a quantidade de tapinhas dados na solucao gerada, se for menor, atualiza as variaveis menor e menorv*/
						compara = contaTapinhas(n*n, v);
					
						if(compara < menor){
							menor = compara;
							for(i = 0; i < n*n; i++)
								menorv[i] = v[i];

						}
										

					}
						
			
		     }


		 }
		 /*se existir solucao para o sistema, ele informa a quantidade de tapinhas da melhor solucao, transforma o vetor menorv numa matriz solucao e a imprime na tela*/

		 if(possivel){

			 printf("Nº de tapinhas da melhor solucao: %d\n", menor); 

			 for(i = 0, lin = 0, col = 0, aux = 1; i < n*n; i++){

					msolucao[lin][col] = menorv[i];
					col++;

					if(col == n){
						lin++;
						col = 0;
						aux++;
					
					}

			 }
			 

			 mostreTurtledorm(n, msolucao, TAPINHA);
			 printf("\n");
			}
			else
				printf("Nao ha solucoes para este tabuleiro, por favor, pressione 'd' para desistir deste jogo\n");

}

/*---------------------------------------------------------------*/
/* 
 *  I M P L E M E N T A C A O   D A S   F U N C O E S   A U X I L I A R E S
 */

int RandomInteger( int low, int high){

    int k;
    double d;
    d = (double) rand( ) / ((double) RAND_MAX + 1);
    k = d * (high - low + 1);
    return low + k;

} 

/*gera uma matriz (n*n)x(n*n) onde cada linha corresponde a como o turtledorm com todos dormindo ficaria apos um tapinha em uma posicao, ou seja, uma linha 1 1 1 0 corresponde a um turtledorm 2x2 apos um tapinha na primeira posicao*/

void geraMatriztapinha(int n, int mtapinha[][MAX*MAX+1]){

     int i, j;

     int lin, col, x, y, nula[MAX][MAX];

     lin = 0;

        
     col = 0;

     geraMatriznula(n, nula);

	  /*vai gerando matrizes nulas e aplicando tapinhas nas posicoes i, j, depois, transforma essa nova matriz numa linha da matriz (n*n)*(n*n)*/
     for(i = 0; i < n; i++){
        for(j = 0; j < n; j++ , lin++){

         geraMatriznula(n, nula);
         atualizeTurtledorm(n, nula, i, j);

         for(x = 0; x < n; x++)
           for(y = 0; y < n; y++ , col++){

                mtapinha[lin][col] = nula[x][y];
                
                
           }
                   
         col = 0;
              
      }
       col = 0;
     }

        
     
}


void geraMatriznula(int n, int nula[][MAX]){

     int i, j;

     for(i=0; i<n; i++)
        for(j=0; j<n; j++)
         nula[i][j] = 0;

}

/*recebe a matriz de tapinhas gerada pela funcao geraMatriztapinha junto com uma coluna extra contendo a configuracao atual do tabuleiro e deixa ela na forma escalonada reduzida*/

void escalonaMatriztapinha(int n, int mtapinha[][MAX*MAX+1]){

     int i, lin, x, y, k, aux;
     
     
     i = 0;
     k = 0;


     while(i < n-1){

       /*elimina os numeros diferentes de zero abaixo do pivo*/
 
       for(lin= i + 1; lin < n; lin++)
        if(mtapinha[lin][k] == 1)
         for(x = 0; x <= n; x++)
           mtapinha[lin][x] = (mtapinha[lin][x] + mtapinha[i][x]) % 2;

      /*troca linhas, se necessario, de modo que sempre haja um pivo na posicao i*i, porem, caso haja linhas de zeros, nem toda posicao i*i tera pivo*/

        for(lin = i+2; lin < n; lin++)
         if(mtapinha[lin][k+1] == 1){

           for(x = 0; x <=n; x++){

             aux = mtapinha[i+1][x];
             mtapinha[i+1][x] = mtapinha[lin][x];
             mtapinha[lin][x] = aux;

           }
           break;
         
         }

        i++;
        k++;
        

     }

     /*elimina os 1s acima dos pivos da matriz para deixa-la da forma escalonada reduzida*/

     for(i = 1; mtapinha[i][i] != 0; i++){
        for(lin = i-1; lin >= 0; lin--)
          if(mtapinha[lin][i])
            for(y = 0; y <= n; y++)
               mtapinha[lin][y] = (mtapinha[lin][y] + mtapinha[i][y]) % 2;
              }


}

/*conta quantos 1s ha no vetor solucao*/
int  contaTapinhas(int n, int v[MAX*MAX]){

	int k, cont = 0;
   for(k = 0; k < n; k++)
		if(v[k])
			cont++;

	return cont;
}
