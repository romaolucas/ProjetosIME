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

  posfixa.c
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

/* iterface para o uso da funcao deste módulo */
#include "posfixa.h"

#include "util.h"  /* tipo CelUtil, UtilUtil() */

/*-------------------------------------------------------------
    itensParaPosfixa(iniFilaInf)
    
    Recebe uma lista ligada com cabeca iniFilaInf representando uma 
    fila de itens de uma expressao infixa e retorna uma lista ligada 
    com cabeca contendo a fila que representacao a correspondente 
    expressao em notacao posfixa. 

    Nessa conversao, nenhuma celula nova deve ser criada a nao ser,
    possivelmente, a celula cabeca da notacao posfixa.  As demais 
    celulas devem simplesmente migrar da fila da notacao infixa 
    para a fila da notacao posfixa. 

    As celulas da notacao infixa que nao forem utilizadas na notacao 
    posfixa (abre e fecha parentese) devem ser liberadas (freeUtil).
*/

CelUtil *
infixaParaPosfixa (CelUtil *iniFilaInf)
{

	CelUtil *iniPos;
	CelUtil *iniPilha;
	CelUtil *p, *aux;
	CelUtil *morta;
	CelUtil *topo;

	iniPos = mallocSafe(sizeof (CelUtil));
	iniPos->prox = NULL;

	iniPilha = mallocSafe(sizeof (CelUtil));
	iniPilha->prox = NULL;

	p = iniFilaInf->prox;

	/*no laço abaixo, sao verificadas duas coisas:
		1 - se um float ou um identificador
		2 - se ele e um operador

		caso 1, a celula e inserida na fila
		caso 2, divide-se em outros casos:
		 2.1 - abre ou fecha parenteses
		 2.2 - precedencia da direita p/ esquerda
		 2.3 - precedencia da esquerda p/ direita

		caso 2.1, quando for abre parenteses, este e inserido na pilha de operadores
		quando for fecha parenteses, todos os operadores na pilha sao desempilhados e 
		inseridos na fila ate ser encontrado um abre parenteses, depois, as celulas
		que contem o abre e fecha parenteses sao liberadas.

		caso 2.2, todos os operadores da pilha sao desempilhados e inseridos na fila
		ate ser encontrado um abre parentes ou um operador de precedencia menor ou igual
		a do operador atual, uma vez que se temos 2 ^ 2 ^ 3, deve-se empilhar primeiro
		o ^ mais proximo do 3, uma vez que, se fosse empilhado o mais proximo do 2, o resultado
		seria completamente diferente. Por fim, o operador atual e inserido na pilha.

		caso 2.3, todos os operadores sao desempilhados e inseridos na fila ate ser encontrado um
		abre parenteses ou um operador de precedencia menor que o atual. Por fim, o operador atual
		e inserido na fila.
	*/
	while(p != NULL){
		if(p->classe == FLOAT || p->classe == ID_STR){

			/*insiro o elemento na fila*/
			aux = p;
			p = p->prox;
			insereFila(iniPos, aux);
		}
		else if(p->classe == ABRE_PARENTESES){
				/*empilho os parenteses*/
				aux = p;
				p = p->prox;
				aux->prox = iniPilha->prox;
				iniPilha->prox = aux;
			
		}
		else if(p->classe == OPER_MENOS_UNARIO || p->classe == OPER_LOGICO_NOT || p->classe == OPER_EXPONENCIACAO || p->classe == OPER_ATRIBUICAO){

				topo = iniPilha->prox;
				while(topo != NULL && topo->classe != ABRE_PARENTESES && topo->prec > p->prec){
					
					/*insere o elemento na fila*/
					aux = topo;
					topo = topo->prox;

					insereFila(iniPos, aux);
				}

				iniPilha->prox = topo;

				/*empilho o operador*/
				aux = p;
				p = p->prox;

				aux->prox = iniPilha->prox;
				iniPilha->prox = aux;

		}
		else if(p->classe == FECHA_PARENTESES){
			topo = iniPilha->prox;
			while(topo != NULL && topo->classe != ABRE_PARENTESES){

				aux = topo;
				topo = topo->prox;

				insereFila(iniPos, aux);

			}

			iniPilha->prox = topo;

			/*libero os parenteses*/
			morta = iniPilha->prox;
			iniPilha->prox = iniPilha->prox->prox;

			freeUtil(morta);

			morta = p;
			p = p->prox;
			freeUtil(morta);

		}
		else{
				topo = iniPilha->prox;
				while(topo != NULL && topo->classe != ABRE_PARENTESES && topo->prec >= p->prec){
				
						/*insere o elemento na fila*/
						aux = topo;
						topo = topo->prox;
						
						insereFila(iniPos, aux);	

				}

				iniPilha->prox = topo;
				/*empilho o elemento*/				
				aux = p;
				p = p->prox;

				aux->prox = iniPilha->prox;
				iniPilha->prox = aux;

		}

	}
   /*nessa parte, os elementos que ficaram faltando ser inseridos na fila sao inseridos
	*/

	topo = iniPilha->prox;
	while(topo != NULL){

		aux = topo;
		topo = topo->prox;
		/*enfilando os elementos*/
		insereFila(iniPos, aux);

		}

	/*libera a memoria usada pela fila infixa*/	
	freeUtil(iniFilaInf);	
    
	 
    return iniPos; 

}

/*recebe um ponteiro para o inicio de uma lista ligada com cabeca que representa
a fila na notacao posfixa e uma celula a ser inserida e a insere na fila.
*/
void insereFila(CelUtil *iniFila, CelUtil *nova){

		CelUtil *p;

		if(iniFila->prox == NULL){
			nova->prox = iniFila->prox;
			iniFila->prox = nova;

		}
		else{

			p = iniFila->prox;

			while(p->prox != NULL){
				
				p = p->prox;

			}

			nova->prox = p->prox;
			p->prox = nova;

		}


}
