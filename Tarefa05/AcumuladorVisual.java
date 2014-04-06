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
// // Este arquivo faz parte da tarefa T05
// /////////////////////////////////////////////////////////////////
//

/////////////////////////////////////////////////////////////////
//// Use layout padrão. 
//// Deste ponto em diante, não escreva NENHUM comentário.
///////////////////////////////////////////////////////////////////


public class AcumuladorVisual {

   public static void main(String[] args) {
      int maior = 0;
      QueueL<Integer> q = new QueueL<Integer>();
      while (!StdIn.isEmpty()) {
         int aux = StdIn.readInt();
         if (aux > maior) maior = aux;
         q.enqueue(aux);
      }
      VisualAccumulator acc = new VisualAccumulator(q.size(), maior);
      while (!q.isEmpty()) acc.addDataValue(q.dequeue());
      StdOut.println(acc);
   }

}
