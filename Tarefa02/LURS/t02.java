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
// // Data: 2014-02-24
// // Disciplina: MAC0323
// // Este arquivo faz parte da tarefa T02
// /////////////////////////////////////////////////////////////////
//

/////////////////////////////////////////////////////////////////
//// Use layout padrão. 
//// Deste ponto em diante, não escreva NENHUM comentário.
///////////////////////////////////////////////////////////////////

import java.util.Arrays;

public class t02 {

   private t02() { }

   public static int rank( int key, int[] a) {
      int lo = 0;
      int hi = a.length - 1;
      while (lo <= hi) {
         int mid = lo + (hi - lo) / 2;
         if      (key < a[mid]) hi = mid - 1;
         else if (key > a[mid]) lo = mid + 1;
         else return mid;
      }
      return -1;
   }

   public static void main( String[] args) {
      In in = new In( args[0]);
      int[] whitelist = in.readAllInts();
      int count = 0;
      Arrays.sort( whitelist);
      while (!StdIn.isEmpty()) {
         int key = StdIn.readInt();
         if (rank( key, whitelist) == -1){
            count++;
         }
      }
      StdOut.println( "Numeros do primeiro arquivo: " + whitelist.length);
      StdOut.println( "Quantidade de numeros que nao estao no primeiro: " + count);
   }
}
