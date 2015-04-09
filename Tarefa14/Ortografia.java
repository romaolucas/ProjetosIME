/*Uso: java Ortografia <dicionario> <ST> < <Arquivo a verificar>
 * ou java Ortografia <dicionario> <ST>
 * <ST> pode ser: rb - para arvore rubro-negra
 *                sc - para separate chaining hash table
 *                lp - para linear probing hash table
 * ex.: java Ortografia list.txt rb < tinyTale.txt
 *
 * Observado: Usando o dicionario words.utf-8.txt e o livro
 * tale-PF.txt, obteve-se os seguintes resultados:
 * Desempenho da arvore rubro-negra: 1.902
 * Desempenho da tabela de hash com separate chaining: 1.93
 * Desempenho da tabela de hash com linear probing: 1.566 
 *
 * Provavelmente por conta do fato da separate chaining hash table usar
 * listas ligadas, seu desempenho acaba sendo um pouco inferior ao da
 * arvore rubro-negra, pois esta faz buscas de maneira muito rapida.
 * Ja a tabela de linear probing, possui um metodo muito mais eficiente
 * de insercao e busca, portanto, seu desempenho tende a ser melhor do que
 * as demais
 * */
public class Ortografia {  
   public static void main(String[] args) {
      String st = "";
      RedBlackBST<String, Integer> rbst;
      rbst = new RedBlackBST<String, Integer>();
      SeparateChainingHashST<String, Integer> sht;
      sht = new SeparateChainingHashST<String, Integer>();
      LinearProbingHashST<String, Integer> lpht;
      lpht = new LinearProbingHashST<String, Integer>();
      String op = args[1];
      if (op.equals("rb")) 
         st = "arvore rubro-negra";
      else if (op.equals("sc")) 
         st = "separate chaining hash table";
      else if (op.equals("lp")) 
         st = "linear probing hash table";
      In in = new In(args[0]);
      Stopwatch sw1 = new Stopwatch();
      int i = 0;
      while (!in.isEmpty()) {
         String word = in.readString();
         if (op.equals("rb")) rbst.put(word, i + 1);
         else if (op.equals("sc")) sht.put(word, i + 1);
         else lpht.put(word, i + 1);
      }
      while (!StdIn.isEmpty()) {
         String word = StdIn.readString();
         if (op.equals("rb")) { 
            if (!rbst.contains(word))
               StdOut.println(word);
         }
         else if (op.equals("sc")) {
            if (!sht.contains(word))
               StdOut.println(word);
         }
         else { 
            if (!lpht.contains(word))
               StdOut.println(word);
         }
      }
      StdOut.println("Desempenho da busca numa st implementada em uma "
            + st + " e: " + sw1.elapsedTime());
   }
}
