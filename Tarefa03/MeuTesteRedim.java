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
// // Este arquivo faz parte da tarefa T03
// /////////////////////////////////////////////////////////////////
//

/////////////////////////////////////////////////////////////////
//// Use layout padrão. 
//// Deste ponto em diante, não escreva NENHUM comentário.
///////////////////////////////////////////////////////////////////

import java.util.Arrays;

public class MeuTesteRedim {
  
   private static int N = 0;
   private static String[] texto = new String[2];

   public MeuTesteRedim() {}

   public static void resize(int max) {
      String[] temp = new String[max];
      for (int i = 0; i < N; i++)
         temp[i] = texto[i];
      texto = temp;
   }

   public static void main(String args[]) {
      while (!StdIn.isEmpty()) {
         String aux = StdIn.readLine();
         if (aux.length() > 0) {
            if (N == texto.length) resize(N * 2);
            texto[N++] = aux;
         }
      }
      StdOut.println("Leitura completa!");
      resize(N);
      Arrays.sort(texto);
      StdOut.println("Ordenacao concluida!");
      for (int i = 0; i < N; i++)
         StdOut.println(texto[i]);
   }
}
