/* stack.c: IMPLEMENTACAO DA PILHA */

#include <stdlib.h>
#include <stdio.h>
#include "util.h"
/*
 * PILHA: uma implementacao com lista encadeada com cabeca
 */
/*Essa interface e uma modificacao das feitas em sala de aula
  Aluno: Lucas Romao Silva nusp.: 8536214
*/
struct stack { /* aqui esta especificado o que e' */
    CelUtil  *topo;   /* uma pilha: um apontador para stacknode */
};
typedef struct stack *Stack;

Stack
stackInit(int n)
{ 
    Stack s = (Stack) mallocSafe(sizeof *s);
	 CelUtil *p = mallocSafe(sizeof (CelUtil));
	 p->prox = NULL;
	 s->topo = p;
	 return s;
}

int 
stackEmpty(Stack s)
{ 
    return s->topo->prox == NULL; 
}

void 
stackPush(Stack s, float conteudo)
{ 
    CelUtil* p = mallocSafe(sizeof *p);
	 p->classe = FLOAT;
    p->vFloat = conteudo;
    p->prox = s->topo->prox;
    s->topo->prox = p;
}

float 
stackPop(Stack s)
{ 
    CelUtil* p = s->topo->prox;
    float conteudo;

    if (p == NULL) /* stackempty() */
    {
	fprintf(stderr,"Putz, voce nao sabe o que esta fazendo!\n");
	exit(-1);
    }
    /* tudo bem, a pilha nao esta vazia... */
    conteudo = p->vFloat;
    s->topo->prox = p->prox;
    free(p);
    return conteudo;  
}

CelUtil*
stackTop(Stack s)
{
    if (s->topo == NULL) /* stackempty() */
    {
	fprintf(stderr,"Putz, voce nao sabe o que esta fazendo!\n");
	exit(-1);
    }

    /* tudo bem, a pilha nao esta vazia... */
    return  s->topo->prox;
}

void 
stackFree(Stack s)
{
    while (s->topo->prox != NULL) 
    {
		CelUtil* p = s->topo->prox;
		s->topo->prox = p->prox;
		free(p);
    }
    free(s->topo);
    free(s);
}

/*A funcao abaixo guarda o conteudo do topo da pilha, caso ele nao seja NULL, numa CelUtil
  Em seguida, a pilha toda e liberada e essa CelUtil que contem todo o conteudo do topo da pilha e retornada
  Note que eu nao faço simplesmente p apontar para o topo, o que e feito e colocar todo o conteudo do topo em p

*/

CelUtil* getStackTop(Stack s){

	CelUtil *p = NULL;
	if(s->topo->prox){
		p = mallocSafe(sizeof (CelUtil));
		p->vFloat = s->topo->prox->vFloat;
		p->prox = NULL;
		
	}
	stackFree(s);
	return p;

}

/*imprime a pilha de execucao*/
void
stackDump(Stack s)
{
    CelUtil *p = s->topo;
	 fprintf(stdout, "==========================\n\n");
	 fprintf(stdout, "  Pilha de Execucao\n");
	 fprintf(stdout, "  Valor  - Classe\n\n");
	 fprintf(stdout, "---------------------------\n");
	 fprintf(stdout, "\n");
    mostreListaUtil(p, VALOR);

}


