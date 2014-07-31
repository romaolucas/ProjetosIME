public class TrieST<Value> {
   private static final int R = 256;

   private Node root;      
   private int N;      

   private static class Node {
      private Object val;
      private Node[] next = new Node[R];
   }

   public TrieST() {
   }

   public Value get(String key) {
      Node x = get(root, key, 0);
      if (x == null) return null;
      return (Value) x.val;
   }

   public boolean contains(String key) {
      return get(key) != null;
   }

   private Node get(Node x, String key, int d) {
      if (x == null) return null;
      if (d == key.length()) return x;
      char c = key.charAt(d);
      return get(x.next[c], key, d+1);
   }

   public void put(String key, Value val) {
      root = put(root, key, val, 0);
   }

   private Node put(Node x, String key, Value val, int d) {
      if (x == null) x = new Node();
      if (d == key.length()) {
         if (x.val == null) N++;
            x.val = val;
         return x;
      }
      char c = key.charAt(d);
      x.next[c] = put(x.next[c], key, val, d+1);
      return x;
   }

   public Iterable<String> keys() {
      return keysWithPrefix("");
   }

   public Iterable<String> keysWithPrefix(String prefix) {
      Queue<String> results = new Queue<String>();
      Node x = get(root, prefix, 0);
      collect(x, new StringBuilder(prefix), results);
      return results;
   }

   private void collect(Node x, StringBuilder prefix, Queue<String> results) {
      if (x == null) return;
      if (x.val != null) results.enqueue(prefix.toString());
      for (char c = 0; c < R; c++) {
         prefix.append(c);
         collect(x.next[c], prefix, results);
         prefix.deleteCharAt(prefix.length() - 1);
      }
   }

   public String min() {
      int i = 0;
      String min = "";
      for (String key : keys())
         if (i == 0) {
            min = key;
            break;
         }
      return min;
   }

   public static void main(String[] args) {
      TrieST<Integer> st = new TrieST<Integer>();
      for (int i = 0; !StdIn.isEmpty(); i++) {
         String key = StdIn.readString();
         st.put(key, i);
      }
         StdOut.println(st.min());
     }

}
