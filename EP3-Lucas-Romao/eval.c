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
  Pitao I

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

/*-----------------------------------------------------------*/
#include "stack.h"

/*------------------------------------------------------------*/
/* interface para as funcoes deste modulo */
#include "eval.h" 

/*------------------------------------------------------------*/
#include <stdlib.h>  /* atoi(), atof() */
#include <string.h>  /* strncmp(), strlen(), strncpy(), strcpy() */
#include <math.h>    /* pow() */

/*------------------------------------------------------------*/
#include "classes.h" /* tipo Classe */

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
		else
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
  
  Esta funcao _nao_ deve alocar celula alguma, no entanto ela
  deve dar free nas estruturas que deixarem de ser necessarias.

  CORRECAO em 28/SET: 
      Esta funcao, ou qualquer funcao chamada por ela,
      pode alocar __no maximo__ uma celula CelUtil para ser a 
      cabeca da pilha. Isto pode ser particularmente util
      para aqueles que desejarem escrever um interface e biblioteca 
      como stack.h e stack.c feitas na aula
      desta semana.  

*/

CelUtil *
eval (CelUtil *iniPosfixa, Bool mostrePilhaExecucao)
{
	Stack s;
	
	CelUtil *p;
		
	float aux, conta;

   /*faco um ponteiro apontar para o comeco da lista e inicializo uma pilha*/
	p = iniPosfixa->prox;
	/*o valor 42 e totalmente arbitrario e so estou passando-o pois a funcao stackInit recebe um inteiro*/
	s = stackInit(42);

	while(p != NULL){

		if(p->classe == FLOAT){
			stackPush(s, p->vFloat);
	
			if(mostrePilhaExecucao)
				stackDump(s);
			

			}

		/*nas linhas a seguir, serão realizadas as operações*/
		/*tenho os elementos empilhados e, conforme for necessario, vou desempilhando-os e efetuando a conta entre eles, depois, empilho o resultado da conta*/
		else{
				if(p->classe == OPER_IGUAL){
				
				aux = stackPop(s);
				conta = stackPop(s) == aux;
				stackPush(s, conta);
				if(mostrePilhaExecucao)
					stackDump(s);

			}
			else if(p->classe == OPER_DIFERENTE){
				aux = stackPop(s);
				conta = stackPop(s) != aux;
				stackPush(s, conta);
			
				if(mostrePilhaExecucao)
					stackDump(s);
				 
			}
			else if(p->classe == OPER_MAIOR_IGUAL){
				
				aux = stackPop(s);
				conta = stackPop(s) >= aux;
				stackPush(s, conta);
		
				if(mostrePilhaExecucao)
					stackDump(s);

			}
			else if(p->classe == OPER_MENOR_IGUAL){

				aux = stackPop(s);
				conta = stackPop(s) <= aux;
				stackPush(s, conta);
	
				if(mostrePilhaExecucao)
					stackDump(s);
			}

			else if(p->classe == OPER_MAIOR){

			
				aux = stackPop(s);
				conta = stackPop(s) > aux;
				stackPush(s, conta);

				if(mostrePilhaExecucao)
					stackDump(s);

			}
			else if(p->classe == OPER_MENOR){

				aux = stackPop(s);
				conta = stackPop(s) < aux;
				stackPush(s, conta);

				if(mostrePilhaExecucao)
					stackDump(s);
			}

			else if(p->classe == OPER_EXPONENCIACAO){

				aux = stackPop(s);
				conta = pow(stackPop(s), aux);
				stackPush(s, conta);

				if(mostrePilhaExecucao)
					stackDump(s);
			}
			else if(p->classe == OPER_RESTO_DIVISAO){

				aux = stackPop(s);
				conta = fmod(stackPop(s), aux);
				stackPush(s, conta);

				if(mostrePilhaExecucao)
					stackDump(s);

			}
			else if(p->classe == OPER_MULTIPLICACAO){

				aux = stackPop(s);
				conta = stackPop(s)*aux;
				stackPush(s, conta);

				if(mostrePilhaExecucao)
					stackDump(s);

			}
			else if(p->classe == OPER_DIVISAO){

				aux = stackPop(s);
				conta = stackPop(s)/aux;
				stackPush(s, conta);

				if(mostrePilhaExecucao)
					stackDump(s);

			}
			else if(p->classe == OPER_ADICAO){

				aux = stackPop(s);
				conta = stackPop(s) + aux;
				stackPush(s, conta);

				if(mostrePilhaExecucao)
					stackDump(s);

			}
			else if(p->classe == OPER_SUBTRACAO){

				aux = stackPop(s);
				conta = stackPop(s) - aux;
				stackPush(s, conta);

				if(mostrePilhaExecucao)
					stackDump(s);

			}
			else if(p->classe == OPER_MENOS_UNARIO){

				conta = stackPop(s)*(-1);
				stackPush(s, conta);
				
				if(mostrePilhaExecucao)
					stackDump(s);

			}
			else if(p->classe == OPER_LOGICO_AND){

				aux = stackPop(s);
				conta = stackPop(s) && aux;
				stackPush(s, conta);

				if(mostrePilhaExecucao)
					stackDump(s);

			}
			else if(p->classe == OPER_LOGICO_OR){

				aux = stackPop(s);
				conta = stackPop(s) || aux;
				stackPush(s, conta);

				if(mostrePilhaExecucao)
					stackDump(s);

			}
			else if(p->classe == OPER_LOGICO_NOT){

				conta = !stackPop(s);
				stackPush(s, conta);
				
				if(mostrePilhaExecucao)
					stackDump(s);
			}
			
		}
		p = p->prox;
	}
		/*pego o que esta no topo da pilha e retorno*/
	   return getStackTop(s); 
}

