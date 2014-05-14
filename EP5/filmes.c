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
   NUSP: 8536214  

   IMDB: filmes.c


   Referências: Com exceção das rotinas fornecidas no esqueleto e em sala
   de aula, caso você tenha utilizado alguma refência, liste-as abaixo
   para que o seu programa não seja considerada plágio.
   Exemplo:
   - função mallocc retirada de: http://www.ime.usp.br/~pf/algoritmos/aulas/aloca.html

   \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
   */


   /*----------------------------------------------------------*/
   /* filmes.h e a interface para as funcoes neste modulo      */
#include "filmes.h" 

   /*----------------------------------------------------------*/
#include <stdlib.h>  /* NULL, free() */
#include <stdio.h>   /* printf(), scanf() */ 
#include <string.h>  /* strlen(), strncpy(), strcmp() */

#include "utils.h"     /* Bool, mallocSafe() */
#include "iofilmes.h"



   /*----------------------------------------------------------------------
   crieFilme(dist, votos, nota, nome, ano)

   Recebe informacoes dobre um filme 

   - dist  : distribuicao de notas
   - votos : numero de votos
   - nota  : nota do filme 
   - ano   : ano de producao do filme

   e cria uma celula do tipo Filme para armazenar essa informacao. 
   A funcao retorna o endereco da celula criada.
   */

Filme *
crieFilme (char dist[], int votos, float nota, char *nome, int ano)
{
   Filme *flm;
   int    len = strlen(nome) + 1; /* +1 para o '\0' */

   flm = mallocSafe(sizeof *flm);

   strncpy(flm->dist, dist, TAM_DIST+1); /* +1 para o '\0' */

   flm->votos = votos;
   flm->nota  = nota;

   flm->nome = mallocSafe(len*sizeof(char));
   strncpy(flm->nome, nome, len);

   flm->ano  = ano;

   flm->prox = flm->ant = NULL; /* paranoia */

   return flm;

   }



   /*----------------------------------------------------------------------
   crieListaFilmes()

   Cria uma estrutura que representa lista de filmes vazia.
   A funcao retorna o endereco dessa estrutura.

   Um lista de filmes e representada por uma lista encadeada 
   com cabeca duplamente ligada. 
   */

ListaFilmes *
crieListaFilmes()
{
   ListaFilmes *lst;

   lst =  mallocSafe(sizeof *lst);

   lst->nFilmes = 0;   
   lst->cab = mallocSafe(sizeof *lst->cab);

   lst->cab->ant  = lst->cab->prox = lst->cab;

   return lst;
}


   /*----------------------------------------------------------------------
   libereListaFilmes(lst)

   Recebe um ponteiro lst para uma estrutura que representa uma lista 
   de filmes e libera toda a memoria alocada para a lista.

   Esta funcao utiliza a funcao libereFilme().

   Obs. do romao: aqui eu libero todos os filmes da lista, porem nao a libero caso o usuario queira reutiliza-la
   No caso onde e necessario libera-la por completo, eu dou free em lst->cab e lst no proprio main.c
   */

void
libereListaFilmes(ListaFilmes *lst)
{
   Filme *p, *morta;
   p = lst->cab->prox;
   while(p != lst->cab){
      morta = p;
      p = p->prox;
      libereFilme(morta);
   }
   lst->cab->prox = lst->cab;
   lst->cab->ant = lst->cab;
}


/*----------------------------------------------------------------------
libereFilme(flm)

Recebe um ponteiro flm para uma estrutura que representa um 
filme e libera a area alocada.

*/

void 
libereFilme(Filme *flm)
{
   flm->ant = flm->prox = NULL;
   free(flm->nome);
   free(flm);
}

/*----------------------------------------------------------------------
insiraFilme(lst, flm)

Recebe um ponteito lst para uma estrutura que representa
uma lista de filmes e um ponteiro para uma estrutura
que representa uma filme.

A funcao insere o filme na lista.

Nota do Romao: Escolhi inserir o elemento no inicio da lista
*/

void 
insiraFilme(ListaFilmes *lst, Filme *flm)
{
   if(lst->nFilmes == 0){
      /*na condicao de nao ter nenhum filme na lista, e necessario mexer no anterior da lista*/
      /*alem disso, nesse caso os ponteiros do filme apontam para a cabeca*/
      lst->cab->prox = flm;
      flm->ant = lst->cab;
      flm->prox = lst->cab;
      lst->cab->ant = flm;
      lst->nFilmes++;
   }
   else{
      if(!contemFilme(lst, flm)){
            /*nesse caso, o anterior aponta para a cabeca e o proximo para o primeiro elemento*/
         Filme *p = lst->cab->prox;
         flm->ant = lst->cab;
         flm->prox = p;
         p->ant = flm;
         lst->cab->prox = flm;
         lst->nFilmes++;   
      }
   }
}


/*---------------------------------------------------------------------
contemFilme(lst, flm)

Recebe um ponteito lst para uma estrutura que representa
uma lista de filmes e um ponteiro para uma estrutura
que representa uma filme.

A funcao retorna  TRUE se o filme esta na lista e 
FALSE em caso contrario. 

Consideramos que dois filmes f e g sao iguais se

- f->nome  e' igual a g->nome )
- f->nota  e' igual a g->nota
- f->ano   e' igual a g->ano 

Para comparar dois nomes voce pode usar alguma funcao da 
bibliteca do c  como strcmp, strncmp (string,h) 
ou a funcao strCmp (utils.h).

*/

Bool 
contemFilme(ListaFilmes *lst, Filme *flm)
{

   Filme *p = lst->cab->prox;
   while(p != lst->cab){
      if(!strCmp(p->nome, flm->nome) && p->nota == flm->nota && p->ano == flm->ano)
         return TRUE;
      p = p->prox;
   }
   /*se chegar aqui, nao encontrou o filme*/
   return FALSE;
}


/*----------------------------------------------------------------------
removaFilme(lst, flm)

Remove da lista e filmes lst o filme dado por flm.

Pre-condicao: a funcao supoe que o filme flm esta 
  na lista lst.
*/

void 
removaFilme(ListaFilmes *lst, Filme *flm)
{

   Filme *p;
   p = lst->cab->prox;
   while(p != flm)
      p = p->prox;
   p->ant->prox = p->prox;
   p->prox->ant = p->ant;
   lst->nFilmes--;
   libereFilme(p);   

}


/*----------------------------------------------------------------------
mergeSortFilmes(lst, criterio)

Ordena uma lista de filmes utilizando o algoritmo mergeSort 
recursivo adaptado para listas encadeadas duplamente ligadas.

Se criterio == NOTA, entao a lista deve ser ordenada
em ordem decrescente de nota.

Se criterio == NOME, entao a lista deve ser ordenada
em ordem crescente de nome (ordem alfabetica).

------------------------------------------------------------------
A ordenacao deve ser feita 'in-place', ou seja   
o conteudo das celulas nao deve ser copiado,  
apenas os ponteiros devem ser alterados.

A funcao so deve utilizar espaco extra O(1).
Hmmm, ok, sem levar em consideracao o espaco O(lg n)
utilizado pela pilha da recursao).
Em outras palavras, a funcao pode conter apenas declaracoes
de umas poucas variaveis (um vetor v[0..n] conta como 
n variaveis).

------------------------------------------------------------------
Para ordenar por nome, veja a funcao strCmp em utils.[h|c].
*/

void 
mergeSortFilmes(ListaFilmes *lst, Criterio criterio)
{
/*pelo numero de filmes, quebrar a lista em 2 outras com +/- n/2 elementos
 * chamar a mergesort pra cada uma delas, a base da recursao sera nFilmes = 1
 * depois de chamar pra esquerda e pra direita, ir p/ intercala*/
   ListaFilmes *lst1;
   Filme *aux1;
   int i, limite;
   if(lst->nFilmes > 1){
      lst1 = mallocSafe(sizeof(ListaFilmes));
      lst1->cab = mallocSafe(sizeof(Filme));
      lst1->cab->prox = lst1->cab->ant = lst->cab->prox;
      aux1 = lst->cab->prox;
      lst->cab->prox = lst->cab->prox->prox;
      lst->cab->prox->ant = lst->cab;
      aux1->ant = aux1->prox = lst1->cab;
      /*insere os elementos na nova lista*/
      for(i = 1; i < lst->nFilmes/2; i++){
         Filme *p, *q;
         p = lst->cab->prox;
         lst->cab->prox = lst->cab->prox->prox;
         lst->cab->prox->ant = lst->cab;
         q = lst1->cab->ant;
         q->prox = p;
         p->prox = lst1->cab;
         p->ant = q;
         lst1->cab->ant = p;
      }
      if(lst->nFilmes % 2) limite = lst->nFilmes/2 + 1;
         else limite = lst->nFilmes/2;
      /*o numero de filmes e ajustado na intercala*/
      lst1->nFilmes = lst->nFilmes/2;
      lst->nFilmes = limite;
      mergeSortFilmes(lst1, criterio);
      mergeSortFilmes(lst, criterio);
      intercala(lst, lst1, criterio);
      free(lst1->cab);
      free(lst1);
    }
}


/*----------------------------------------------------------------------
quickSortFilmes(lst, criterio) [opcional]

Ordena uma lista de filmes utilizando o algoritmo quickSort 
adaptado para listas encadeadas duplamente ligadas.

Se criterio == NOTA, entao a lista deve ser ordenada
em ordem decrescente de nota.

Se criterio == NOME, entao a lista deve ser ordenada
em ordem crescente de nome (ordem alfabetica).

------------------------------------------------------------------
A ordenacao deve ser feita 'in-place', ou seja   
o conteudo das celulas nao deve ser copiado,  
apenas os ponteiros devem ser alterados.

A funcao so deve utilizar espaco extra O(1).
Hmmm, ok, sem levar em consideracao o espaco O(lg n)
utilizado pela pilha da recursao).
Em outras palavras, a funcao pode conter apenas declaracoes
de umas poucas variaveis (um vetor v[0..n] conta como 
n variaveis).

------------------------------------------------------------------
Para ordenar por nome, veja a funcao strCmp em utils.[h|c].

Observacao importante do romao: algo nela faz a minha lista ficar errada
*/
/*a partir do separa, obtenho duas listas, uma delas indo de lst->cab->prox ate j->ant
 * e outra que vai de j->prox ate lst->cab->ant, o pivo j, so e reinserido depois de chamar a funcao para
 * as duas novas listas
 * */
void 
quickSortFilmes(ListaFilmes *lst, Criterio criterio)
{
   ListaFilmes *lst1;
   Filme *j, *p;
   int i = 1;
   if(lst->nFilmes > 1){
      lst1 = mallocSafe(sizeof(ListaFilmes));
      lst1->cab = mallocSafe(sizeof(Filme));
      j = separa(lst, criterio);
      lst1->cab->prox = lst1->cab->ant = lst->cab->prox;
      p = lst->cab->prox;
      lst->cab->prox = lst->cab->prox->prox;
      lst->cab->prox->ant = lst->cab;
      p->ant = p->prox = lst1->cab;
      /*a segunda condicao e um caso particular onde o j e o primeiro elemento da minha lista
       * na verdade, nem sei se esse caso ocorre, mas preferi inclui-lo*/
      while(lst->cab->prox != j && lst1->cab->prox != j){
         Filme *aux1, *aux2;
         aux1 = lst->cab->prox;
         aux2 = lst1->cab->ant;
         lst->cab->prox = lst->cab->prox->prox;
         lst->cab->prox->ant = lst->cab;
         aux1->prox = lst1->cab;
         aux1->ant = aux2;
         aux2->prox = aux1;
         lst1->cab->ant = aux1;
         i++;
      }
      /*deixo o j isolado*/
      if(lst1->cab->prox != j){
         lst->cab->prox = lst->cab->prox->prox;
         lst->cab->prox->ant = lst->cab;
      }
      lst1->nFilmes = i;
      lst->nFilmes = lst->nFilmes - i;
      quickSortFilmes(lst1, criterio);
      quickSortFilmes(lst, criterio);
      /*readiciono o j*/
      if(lst1->cab->prox != j){
           Filme *aux = lst1->cab->ant;
           aux->prox = j;
           j->ant = aux;
           j->prox = lst1->cab;
           lst1->cab->ant = j;
           lst1->nFilmes++;
      }
      lst1->cab->ant->prox = lst->cab->prox;
      lst->cab->prox->ant = lst1->cab->ant;
      lst1->cab->prox->ant = lst->cab;
      lst->cab->prox = lst1->cab->prox;
      lst->nFilmes = lst->nFilmes + lst1->nFilmes;
      free(lst1->cab);
      free(lst1);
   }
}

/*intercala( lst1, lst2, criterio)
recebe duas lista que estarao ordenadas em ordem decrescente de nota,
caso criterio seja nota ou crescente de nome caso o criterio seja o nome
e junta essas duas listas em uma so de modo que essa lista resultante esteja
ordenada de maneira crescente (caso criterio seja nome) ou decrescente (caso criterio seja nota)
esta funcao foi adaptada da funcao intercala escrita em:
http://www.ime.usp.br/~pf/algoritmos/aulas/mrgsrt.html
 * */
void intercala(ListaFilmes *lst1, ListaFilmes *lst2, Criterio criterio){
   Filme *p, *q, *aux;
   p = lst1->cab->prox;
   q = lst2->cab->prox;
   while(p != lst1->cab && q != lst2->cab){
      if(criterio == NOTA){
         if(p->nota > q->nota)
            p = p->prox;
         else{
            aux = q;
            q = q->prox;
            aux->ant = p->ant;
            p->ant->prox = aux;
            aux->prox = p;
            p->ant = aux;
         }
      }
      else{
         if(strCmp(p->nome, q->nome) < 0)
            p = p->prox;
         else{
            aux = q;
            q = q->prox;
            aux->ant = p->ant;
            p->ant->prox = aux;
            aux->prox = p;
            p->ant = aux;
         }
      }

   }
   while(p != lst1->cab) 
      p = p->prox;
   while(q != lst2->cab){
      aux = q;
      q = q->prox;
      aux->ant = p->ant;
      p->ant->prox = aux;
      aux->prox = p;
      p->ant = aux;
   }
   lst1->nFilmes = lst1->nFilmes + lst2->nFilmes;
   
}

/*
 *Filme separa (lst, criterio)
 recebe o ponteiro para uma lista de filmes e o criterio de comparacao e retorna
 um ponteiro para um filme c tal que:
  anteriores->nota >=  c->nota > proximos->nota
   ou anteriores->nome <= c->nome < proximos->nome
 Funcao adaptada da separa encontrada no link: http://www.ime.usp.br/~pf/algoritmos/aulas/quick.html
 * */
Filme *separa(ListaFilmes *lst, Criterio criterio){
   Filme *c, *i, *j, *t, *anterior, *proximo;
   c = lst->cab->prox;
   i = c->prox;
   j = lst->cab->ant;
   while(i->ant != j && i != lst->cab){
      if(criterio == NOTA){
         if(i->nota >= c->nota) i = i->prox;
         else if(c->nota > j->nota) j = j->ant;
         else{
            if(i->prox == j){
               i->prox = j->prox;
               j->prox->ant = i;
               i->ant->prox = j;
               j->ant = i->ant;
               i->ant = j;
               j->prox = i;
            }
            else{
               anterior = i->ant;
               proximo = i->prox;
               i->prox = j->prox;
               i->ant = j->ant;
               j->ant->prox = j->prox->ant = i;
               j->ant = anterior;
               j->prox = proximo;
               anterior->prox = proximo->ant = j;
               t = i;
               i = j;
               j = t;
            }
         }
      }
      else{
         if(strCmp(i->nome, c->nome) < 0) i = i->prox;
         else if(strCmp(c->nome, j->nome) < 0) j = j->ant;
         else{
            if(i->prox == j){
               i->prox = j->prox;
               j->prox->ant = i;
               i->ant->prox = j;
               j->ant = i->ant;
               i->ant = j;
               j->prox = i;
            }
            else{
               anterior = i->ant;
               proximo = i->prox;
               i->prox = j->prox;
               i->ant = j->ant;
               j->ant->prox = j->prox->ant = i;
               j->ant = anterior;
               j->prox = proximo;
               anterior->prox = proximo->ant = j;
               t = i;
               i = j;
               j = t;
            }
         }
      }
   }
   if(c->prox == j){
      c->prox = j->prox;
      j->prox->ant = c;
      c->ant->prox = j;
      c->ant = c;
      j->prox = c;
   }
   else{
      proximo = c->prox;
      c->ant = j->ant;
      c->prox = j->prox;
      j->prox->ant = j->ant->prox = c;
      j->ant = lst->cab;
      j->prox = proximo;
      lst->cab->prox = j;
   }
   return c;
}
