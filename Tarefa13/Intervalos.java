public class Intervalos<Key extends Comparable<Key>> {

   private ST<Key, Key> st;

   public Intervalos() {
      st = new ST<Key, Key>();
   }

   public void add(Key k1, Key k2) {
      st.put(k1, k2);      
   }

   public void belongs(Key k) {
      for (Key key : st) {
         int aux1 = k.compareTo(key);
         int aux2 = k.compareTo(st.get(key));
         if (aux1 >= 0 && aux2 <= 0) {
            StdOut.println("Pertence ao intervalo: " + key + " - " + st.get(key));
            return;
         }
      }
      StdOut.println("Nao pertence a nenhum intervalo!");
   }

   public static void main(String[] args) {
      In in = new In(args[0]);
      Intervalos<String> interval = new Intervalos<String>();
      while (in.hasNextLine()) {
         String[] s = in.readLine().split("-");
         interval.add(s[0], s[1]);
      }
      while (!StdIn.isEmpty()) {
         String k = StdIn.readString();
         interval.belongs(k);
      }
   }

}
