public class FreqCounter {

   public static void main(String[] args) {
      int minlen = Integer.parseInt(args[0]);
      int cont, total;
      QueueL<String> q = new QueueL<String>();
      String ultima = "";
      SequentialSearchST<String, Integer> st;
      st  = new SequentialSearchST<String, Integer>();
      QueueL<Integer> puts = new QueueL<Integer>();
      cont = total = 0;
      while (!StdIn.isEmpty()) {
         Integer aux;
         String word = StdIn.readString();
         if (word.length() < minlen) continue;
         aux = st.get(word);
         if (aux == null) {
            aux = 1;
            ultima = word;
            cont++;
         }
         else aux++;
         puts.enqueue(st.put(word, aux));
         total++;
      }
      String max = ultima;
      StdOut.println("Ultima palavra lida: " + ultima);
      StdOut.println("Numero de palavras lidas antes da ultima: " + (cont - 1));
      for (String palavra : st)
         if (st.get(palavra) > st.get(max))
            max = palavra;
      for (String palavra : st)
         if (st.get(palavra) == st.get(max))
            q.enqueue(palavra);
      while (!q.isEmpty()) {
         String palavra = q.dequeue();
         StdOut.println(palavra);
      }
      VisualAccumulator acc = new VisualAccumulator(total, cont);
      while (!puts.isEmpty()) acc.addDataValue(puts.dequeue());
      StdOut.println(acc); 
   }
}
