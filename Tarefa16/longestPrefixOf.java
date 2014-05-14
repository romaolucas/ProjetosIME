/*Invariante:
 * Para x != null, s.substring(0, d) esta representada
 * na arvore
 * Para x = null, s.substring(0, d-1) esta representada na arvore
 * */
public String longestPrefixOf(String s) {
   Node x = root;
   int k = -1;
   int d = 0;
   while (x != null && d != s.length()) {
      if (x.val != null) k = d;
      char c = s.charAt(d);
      x = x.next[c];
      d++;
   }
   if (k != 0) return s.substring(0, k);
   return null;
}
