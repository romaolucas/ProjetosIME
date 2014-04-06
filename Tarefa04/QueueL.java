// DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESTE PROGRAMA. 
// // TODAS AS PARTES DO PROGRAMA (EXCETO AS QUE FORAM FORNECIDAS 
// // PELO PROFESSOR OU COPIADAS DO LIVRO OU DA BIBLIOTECA DE 
// // SEDGEWICK E WAYNE) FORAM DESENVOLVIDAS POR MIM.  DECLARO 
// // TAMBÉM QUE SOU RESPONSÁVEL POR TODAS AS CÓPIAS DESTE PROGRAMA
// // E QUE NÃO DISTRIBUI NEM FACILITEI A DISTRIBUIÇÃO DE CÓPIAS. 
// //
// // Nome: Lucas Romao Silva
// // NUSP: 8536214
// // Sigla: LURS
// //
// // Data: 2014-03-09
// // Disciplina: MAC0323
// // Este arquivo faz parte da tarefa T04
// /////////////////////////////////////////////////////////////////
//

/////////////////////////////////////////////////////////////////
//// Use layout padrão. 
//// Deste ponto em diante, não escreva NENHUM comentário.
///////////////////////////////////////////////////////////////////


public class QueueL<Item> {

   private Node first;
   private Node last;
   private int N;

   public class Node {
      Item item;
      Node next;
   }

   public boolean isEmpty() {
      return first == null;
   }

   public void enqueue(Item item) {
      Node oldlast = last;
      last = new Node();
      last.item = item;
      last.next = null;
      if (isEmpty()) first = last;
      else oldlast.next = last;
      N++;
   }

   public Item dequeue() {
      Item item = first.item;
      first = first.next;
      N--;
      if (isEmpty()) last = null;
      return item;
   }

   public int size() {
      return N;
   }
}
