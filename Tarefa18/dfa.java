public class dfa {
   
   public static int[][] buildDfa(String pat, int R) {
      int[][] dfa = new int[R][pat.length()];
      int M = pat.length();

      for (int i = 0; i < M; i++) {
         for (int k = 0; k < R; k++) {
            String aux = pat.substring(0, i) + (char)k;
            String subpat = pat.substring(0, i + 1);
            String c1 = subpat;
            String c2 = aux;
            int len = subpat.length();
            int x = len;
            for (int j = 0; j < len && !c1.equals(c2); j++) {
               x--;
               c1 = subpat.substring(0, x);
               c2 = aux.substring(j + 1);
            }
            dfa[k][i] = x;
        }
      }
      return dfa;
   }

   public static void main(String[] args) {
      String pat;
      int dfa[][];
      StdOut.println("Padrao, por favor: ");
      pat = StdIn.readString();
      dfa = buildDfa(pat, 256);
      StdOut.println((int)pat.charAt(pat.length() - 1));
      for (int k = 0; k < pat.length(); k++) {
         for (int j = 0; j < pat.length(); j++)
            System.out.print(" " + dfa[pat.charAt(k)][j] + " ");
         System.out.print("\n");
      }
   }
}
