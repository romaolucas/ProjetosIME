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

public class UltimasLinhas {
   
   public static void main(String[] args) {
      int k = Integer.parseInt(args[0]);
      QueueL<String> q = new QueueL<String>();
      while (!StdIn.isEmpty()) {
         if (k != 0 && q.size() == k) q.dequeue();
         q.enqueue(StdIn.readLine());
      }
      if (k == 0) StdOut.println("K = 0!");
      for (int i = 0; !q.isEmpty() && i < k; i++)
         StdOut.println(q.dequeue());
   }

}
