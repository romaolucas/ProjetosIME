/*
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__

  AO PREENCHER ESSE CABEÇALHO COM O MEU NOME E O MEU NÚMERO USP, 
  DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESSE PROGRAMA. 
  TODAS AS PARTES ORIGINAIS DESSE EXERCÍCIO PROGRAMA (EP) FORAM 
  DESENVOLVIDAS E IMPLEMENTADAS POR MIM SEGUINDO AS INSTRUÇÕES DESSE EP
  E QUE PORTANTO NÃO CONSTITUEM PLÁGIO. DECLARO TAMBÉM QUE SOU RESPONSÁVEL
  POR TODAS AS CÓPIAS DESSE PROGRAMA E QUE EU NÃO DISTRIBUI OU FACILITEI A
  SUA DISTRIBUIÇÃO. ESTOU CIENTE QUE OS CASOS DE PLÁGIO SÃO PUNIDOS COM 
  REPROVAÇÃO DIRETA NA DISCIPLINA.

  Nome: Lucas Romao Silva

  eval.c
  Pitao II

  Referências: Com exceção das rotinas fornecidas no esqueleto e em sala
  de aula, caso você tenha utilizado alguma refência, liste-as abaixo
  para que o seu programa não seja considerada plágio.
  Exemplo:
  - função mallocc retirada de: http://www.ime.usp.br/~pf/algoritmos/aulas/aloca.html

 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/

/*
  NAO EDITE OU MODIFIQUE NADA QUE ESTA ESCRITO NESTE ESQUELETO
*/

/*------------------------------------------------------------*/
/* interface para as funcoes deste modulo */
#include "eval.h" 

/*------------------------------------------------------------*/
#include <stdlib.h>  /* free(), atoi(), atof() */
#include <string.h>  /* strncmp(), strlen(), strncpy(), strcpy() */
#include <math.h>    /* pow() */

/*------------------------------------------------------------*/
#include "classes.h" /* tipo Classe */
#include "ts.h"      /* getValorTS() e setValorTS() */


/*------------------------------------------------------------
  Tabela com a preceedencia do operadores

  http://www.ime.usp.br/~pf/algoritmos/apend/precedence.html
*/
static const int precedencia[MAX_OPERADORES] =
{
    /* 4 operadores relacionais com 2 simbolos  */
     4   /* "==" */ /* da esquerda para a direita */
    ,4   /* "!=" */ /* da esquerda para a direita */
    ,5   /* ">=" */ /* da esquerda para a direita */
    ,5   /* "<=" */ /* da esquerda para a direita */
    
    /* 2 operadores relacionais com 1 simbolo */
    ,5  /* ">"  */ /* da esquerda para a direita */
    ,5  /* "<"  */ /* da esquerda para a direita */ 
    
    /* 7 operadores aritmeticos */
    ,8  /* "^" */ /* da direita para a esquerda */
    ,7  /* "%" */ /* da esquerda para a direita */
    ,7  /* "*" */ /* da esquerda para a direita */
    ,7  /* "/" */ /* da esquerda para a direita */
    ,6  /* "+" */ /* da esquerda para a direita */
    ,6  /* "-" */ /* da esquerda para a direita */
    ,8  /* "_" */ /* da direita para a esquerda */
    
    /* 3 operadores logicos  */
    ,3  /* "&&" */ /* da esquerda para a direita */ 
    ,2  /* "||" */ /* da esquerda para a direita */
    ,8  /* "!"  */ /* da direita para a esquerda */

     /* atribuicao */ 
    ,1  /* "=" */ /* da direita para a esquerda */ 
}; 


/*-------------------------------------------------------------
    itensParaValores(iniFilaItens)
    
    Recebe uma lista ligada com cabeca iniFilaItens representado uma 
    fila de itens lexicos e converte o campo util de cada celula 
    para um valor como descrito a seguir. 

    Nessa conversao, o campo 'util' de cada celula recebe um valor 
    da seguinte maneira.

       - se o campo 'classe' da celula indica que 'item' e um ponteiro 
         para um string que representa um float (FLOAT_STR), 
         o campo 'vFloat' deve recebe o valor desse float;

       - se o campo 'classe' da celula indica que 'item' e um ponteiro 
         para um operador, o campo 'prec' deve receber a precedencia
         desse operador.
 
         Para isto utilize o vetor 'precedencia'declarado antes 
         desta funcao. 

	 Nesta funcao voce pode utilizar qualquer funcao da biblioteca
         string do C, como, por exemplo, atof().

   Esta funcao _nao_ deve alocar celula alguma, no entanto ela
   deve dar free nas estruturas que deixarem de ser necessarias.

*/

void
itensParaValores(CelUtil *iniFilaItens)
{
	CelUtil *p;
	float x;
	/*nas linhas abaixo, as strings que representam float, serao convertidas para float
	caso contrario, atribuiremos o valor da precedencia do operador
	*/
	for(p = iniFilaItens->prox; p != NULL; p = p->prox){

		if(p->classe == FLOAT_STR){
			x = atof(p->pStr);
			free(p->pStr);
			p->vFloat = x;
			p->classe = FLOAT;

		}
		else if(p->classe != ABRE_PARENTESES && p->classe != FECHA_PARENTESES && p->classe != ID_STR)
			p->prec = precedencia[p->classe];

		
	}

}


/*-------------------------------------------------------------
  eval(iniPosfixa, mostrePilhaExecucao)
  
  Recebe uma lista ligada como cabeca iniPosfixa que representa
  uma expressao em notacao posfixa. 
  
  A funcao percorre a expressao calculando os valores resultantes.
  Para isto e utilizada uma pilha de execucao. 
  
  A pilha de execucao e representada atraves de uma lista ligada
  com cabeca em que cada elemento e do tipo CelUtil.
  
  Ao final a funcao retorna o endereco da celula no topo da 
  pilha de execucao.
  
  O parametro mostrePilhaExecucao indica se os valores
  na pilha devem ser exibidos depois de qualquer alteracao na
  pilha de execucao.
  
  Esta funcao, ou qualquer funcao chamada por ela,
  pode alocar __no maximo__ uma celula CelUtil para ser a 
  cabeca da pilha. Isto pode ser particularmente util
  para aqueles que desejarem escrever um interface e biblioteca 
  como stack.h e stack.c feitas na aula
  desta semana.  

  Esta funcao deve dar free nas estruturas que deixarem de ser necessarias.
*/

CelUtil *
eval (CelUtil *iniPosfixa, Bool mostrePilhaExecucao)
{
	CelUtil *p;
	CelUtil *q;
	CelUtil *topo;
	CelUtil *iniPilha;
	float aux;
	char* nome;

	iniPilha = mallocSafe( sizeof(CelUtil));
	iniPilha->prox = NULL;

	p = iniPosfixa->prox;

	/*no laco abaixo, serao realizadas as operacoes, ele funciona da seguinte maneira, se encontro um identificador ou um float, este e empilhado
	caso um operador seja encontrado, e desempilhado um elemento e verifica-se se este e um identificador ou um numero, se for um identificador,
	guarda-se o valor que este identificador contem na variavel aux, em seguida, a string no campo pNomeID e liberada, o valor de aux e colocado no campo vFloat da celula
	e muda-se o tipo dela para float, o mesmo processo e feito com a celula que esta atualmente no topo da minha lista, menos no caso de a operacao ser de atribuicao,
	neste caso, o valor a ser atribuido e guardado na celulaTS*/
	/*a minha funcao stackPop nao libera a memoria de imediato, ela simplesmente retorna a celula que esta no topo da lista e atualiza-o.
	A celula obtida fica na variavel q, essa, ao terminar de ser utilizada, e liberada*/
	/*A variavel q tambem e utilizada para inserir um elemento na lista*/

	while(p != NULL){

		if(p->classe == FLOAT || p->classe == ID_STR){
			q = p;
			p = p->prox;
			stackPush(iniPilha, q);

		}
		else if(p->classe == OPER_IGUAL){

			q = stackPop(iniPilha);

			if(q->classe == ID_STR){

				aux = getValorTS(q->pNomeID);
				free(q->pNomeID);
				q->vFloat = aux;
				q->classe = FLOAT;

			}

			topo = stackTop(iniPilha);
			
			if(topo->classe == ID_STR){
				
				aux = getValorTS(topo->pNomeID);
				free(topo->pNomeID);
				topo->vFloat = aux;
				topo->classe = FLOAT;

			}

			topo->vFloat = topo->vFloat == q->vFloat;

			freeValor(q);

			p = p->prox;

			}
		else if(p->classe == OPER_DIFERENTE){

			q = stackPop(iniPilha);

			if(q->classe == ID_STR){

				aux = getValorTS(q->pNomeID);
				free(q->pNomeID);
				q->vFloat = aux;
				q->classe = FLOAT;

			}

			topo = stackTop(iniPilha);

			if(topo->classe == ID_STR){
				
				aux = getValorTS(topo->pNomeID);
				free(topo->pNomeID);
				topo->vFloat = aux;
				topo->classe = FLOAT;

			}

			topo->vFloat = topo->vFloat != q->vFloat;

			freeValor(q);

			p = p->prox;
		}
		else if(p->classe == OPER_MAIOR_IGUAL){

			q = stackPop(iniPilha);

			if(q->classe == ID_STR){

				aux = getValorTS(q->pNomeID);
				free(q->pNomeID);
				q->vFloat = aux;
				q->classe = FLOAT;

			}

			topo = stackTop(iniPilha);

			if(topo->classe == ID_STR){ 
				aux = getValorTS(topo->pNomeID);
				free(topo->pNomeID);
				topo->vFloat = aux;
				topo->classe = FLOAT;
				
			}

			topo->vFloat = topo->vFloat >= q->vFloat;
			
			freeValor(q);

			p = p->prox;
		}
		else if(p->classe == OPER_MENOR_IGUAL){

			q = stackPop(iniPilha);

			if(q->classe == ID_STR){

				aux = getValorTS(q->pNomeID);
				free(q->pNomeID);
				q->vFloat = aux;
				q->classe = FLOAT;

			}

			topo = stackTop(iniPilha);

			if(topo->classe == ID_STR){ 
				aux = getValorTS(topo->pNomeID);
				free(topo->pNomeID);
				topo->vFloat = aux;
				topo->classe = FLOAT;

			}

			topo->vFloat = topo->vFloat <= q->vFloat;

			freeValor(q);

			p = p->prox;
		}
		else if(p->classe == OPER_MAIOR){

			q = stackPop(iniPilha);

			if(q->classe == ID_STR){

				aux = getValorTS(q->pNomeID);
				free(q->pNomeID);
				q->vFloat = aux;
				q->classe = FLOAT;

			}

			topo = stackTop(iniPilha);

			if(topo->classe == ID_STR){
				
				aux = getValorTS(topo->pNomeID);
				free(topo->pNomeID);
				topo->vFloat = aux;
				topo->classe = FLOAT;

				
			}

			topo->vFloat = topo->vFloat > q->vFloat;

			freeValor(q);

			p = p->prox;
		}
		else if(p->classe == OPER_MENOR){

			q = stackPop(iniPilha);

			if(q->classe == ID_STR){

				aux = getValorTS(q->pNomeID);
				free(q->pNomeID);
				q->vFloat = aux;
				q->classe = FLOAT;

			}

			topo = stackTop(iniPilha);

			if(topo->classe == ID_STR){ 
				
				aux = getValorTS(topo->pNomeID);
				free(topo->pNomeID);
				topo->vFloat = aux;
				topo->classe = FLOAT;

				
			}

			topo->vFloat = topo->vFloat < q->vFloat;

			freeValor(q);

			p = p->prox;
		}
		else if(p->classe == OPER_EXPONENCIACAO){

			q = stackPop(iniPilha);

			if(q->classe == ID_STR){

				aux = getValorTS(q->pNomeID);
				free(q->pNomeID);
				q->vFloat = aux;
				q->classe = FLOAT;

			}

			topo = stackTop(iniPilha);

			if(topo->classe == ID_STR){ 
				
				aux = getValorTS(topo->pNomeID);
				free(topo->pNomeID);
				topo->vFloat = aux;
				topo->classe = FLOAT;

				
			}

			topo->vFloat = pow(topo->vFloat, q->vFloat);

			freeValor(q);

			p = p->prox;
		}
		else if(p->classe == OPER_RESTO_DIVISAO){

			q = stackPop(iniPilha);

			if(q->classe == ID_STR){

				aux = getValorTS(q->pNomeID);
				free(q->pNomeID);
				q->vFloat = aux;
				q->classe = FLOAT;

			}

			topo = stackTop(iniPilha);

			if(topo->classe == ID_STR){ 
				
				aux = getValorTS(topo->pNomeID);
				free(topo->pNomeID);
				topo->vFloat = aux;
				topo->classe = FLOAT;


			}

			topo->vFloat = fmod(topo->vFloat, q->vFloat);

			freeValor(q);

			p = p->prox;
		}
		else if(p->classe == OPER_MULTIPLICACAO){

			q = stackPop(iniPilha);

			if(q->classe == ID_STR){

				aux = getValorTS(q->pNomeID);
				free(q->pNomeID);
				q->vFloat = aux;
				q->classe = FLOAT;

			}

			topo = stackTop(iniPilha);

			if(topo->classe == ID_STR){ 
				
				aux = getValorTS(topo->pNomeID);
				free(topo->pNomeID);
				topo->vFloat = aux;
				topo->classe = FLOAT;

				
			}

			topo->vFloat = topo->vFloat * q->vFloat;

			freeValor(q);

			p = p->prox;
		}
		else if(p->classe == OPER_DIVISAO){

			q = stackPop(iniPilha);

			if(q->classe == ID_STR){

				aux = getValorTS(q->pNomeID);
				free(q->pNomeID);
				q->vFloat = aux;
				q->classe = FLOAT;

			}

			topo = stackTop(iniPilha);

			if(topo->classe == ID_STR){ 
				
				aux = getValorTS(topo->pNomeID);
				free(topo->pNomeID);
				topo->vFloat = aux;
				topo->classe = FLOAT;

				
			}

			topo->vFloat = topo->vFloat / q->vFloat;

			freeValor(q);

			p = p->prox;
		}
		else if(p->classe == OPER_ADICAO){

			q = stackPop(iniPilha);

			if(q->classe == ID_STR){

				aux = getValorTS(q->pNomeID);
				free(q->pNomeID);
				q->vFloat = aux;
				q->classe = FLOAT;

			}

			topo = stackTop(iniPilha);

			if(topo->classe == ID_STR){ 
				
				aux = getValorTS(topo->pNomeID);
				free(topo->pNomeID);
				topo->vFloat = aux;
				topo->classe = FLOAT;

				
			}

			topo->vFloat = topo->vFloat + q->vFloat;
			freeValor(q);

			p = p->prox;
		}
		else if(p->classe == OPER_SUBTRACAO){

			q = stackPop(iniPilha);

			if(q->classe == ID_STR){

				aux = getValorTS(q->pNomeID);
				free(q->pNomeID);
				q->vFloat = aux;
				q->classe = FLOAT;

			}

			topo = stackTop(iniPilha);

			if(topo->classe == ID_STR){ 
				
				aux = getValorTS(topo->pNomeID);
				free(topo->pNomeID);
				topo->vFloat = aux;
				topo->classe = FLOAT;


			}

			topo->vFloat = topo->vFloat - q->vFloat;

			freeValor(q);

			p = p->prox;
		}
		else if(p->classe == OPER_MENOS_UNARIO){

			
			topo = stackTop(iniPilha);

			if(topo->classe == ID_STR){ 
				aux = getValorTS(topo->pNomeID);
				free(topo->pNomeID);
				topo->vFloat = aux;
				topo->classe = FLOAT;
				
			}

			topo->vFloat = topo->vFloat*(-1);

			p = p->prox;
		}
		else if(p->classe == OPER_LOGICO_AND){

			q = stackPop(iniPilha);

			if(q->classe == ID_STR){

				aux = getValorTS(q->pNomeID);
				free(q->pNomeID);
				q->vFloat = aux;
				q->classe = FLOAT;

			}

			topo = stackTop(iniPilha);

			if(topo->classe == ID_STR){ 
				
				aux = getValorTS(topo->pNomeID);
				free(topo->pNomeID);
				topo->vFloat = aux;
				topo->classe = FLOAT;

				
			}

			topo->vFloat = topo->vFloat && q->vFloat;

			freeValor(q);

			p = p->prox;
		}
		else if(p->classe == OPER_LOGICO_OR){

			q = stackPop(iniPilha);

			if(q->classe == ID_STR){

				aux = getValorTS(q->pNomeID);
				free(q->pNomeID);
				q->vFloat = aux;
				q->classe = FLOAT;

			}

			topo = stackTop(iniPilha);

			if(topo->classe == ID_STR){ 
				
				aux = getValorTS(topo->pNomeID);
				free(topo->pNomeID);
				topo->vFloat = aux;
				topo->classe = FLOAT;

				
			}

			topo->vFloat = topo->vFloat || q->vFloat;

			freeValor(q);

			p = p->prox;
		}
		else if(p->classe == OPER_LOGICO_NOT){

			topo = stackTop(iniPilha);

			if(topo->classe == ID_STR){ 
				
				aux = getValorTS(topo->pNomeID);
				free(topo->pNomeID);
				topo->vFloat = aux;
				topo->classe = FLOAT;

				
			}

			topo->vFloat =  !topo->vFloat;

			p = p->prox;
		}
		else if(p->classe == OPER_ATRIBUICAO){

			q = stackPop(iniPilha);

			if(q->classe == ID_STR){
				
				aux = getValorTS(q->pNomeID);
				free(q->pNomeID);
				q->vFloat = aux;
					q->classe = FLOAT;

			}

			topo = stackTop(iniPilha);
			
			if(topo->classe == ID_STR) setValorTS(topo->pNomeID, q->vFloat);


			freeValor(q);
					
			p = p->prox;
		}

		if(mostrePilhaExecucao) mostreListaUtil(iniPilha, PILHA);

	}
   /*nessa parte, pego o que esta no topo da pilha e verifico se e um identificador, caso seja,
	e guardado o valor que este contem, libera a string e muda o tipo para FLOAT*/

	 topo = stackTop(iniPilha);
	 if(topo->classe == ID_STR){
			
			nome = mallocSafe((strlen(topo->pNomeID)+1)*sizeof(char));
			strcpy(nome, topo->pNomeID );

			free(topo->pNomeID);

			topo->vFloat = getValorTS(nome);
			topo->classe = FLOAT;
		}

    return topo; 
}

/*recebe uma pilha e uma celula a ser inserida e a insere na pilha*/

void stackPush(CelUtil *iniPilha, CelUtil *nova){
		nova->prox = iniPilha->prox;
		iniPilha->prox = nova;
		
}

/*retorna o que esta no topo da pilha, ignore a mensagem de erro*/

CelUtil* stackTop(CelUtil *iniPilha){

		if(iniPilha->prox == NULL){

			fprintf(stderr, "You went full retard, nigger, and you never go full retard.\n");
			exit(-1);

		}
		/*se chegou aqui, a pilha nao esta vazia*/
		return iniPilha->prox;

}

/*atualiza o topo da pilha e retorna o topo antigo*/
CelUtil* stackPop(CelUtil *iniPilha){

		CelUtil *p;
		p = iniPilha->prox;
		
		iniPilha->prox = p->prox;

		return p;

}

/*libera tudo, menos o topo*/
void stackFree(CelUtil *iniPilha){

		CelUtil *morta;
		CelUtil *p = iniPilha->prox;
		p = p->prox;
		while(p != NULL){

			morta = p;
			p = p->prox;
			freeValor(morta);
			
		}

}
