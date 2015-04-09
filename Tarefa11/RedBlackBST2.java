import java.util.NoSuchElementException;

public class RedBlackBST2<Key extends Comparable<Key>, Value> {

   private static final boolean RED   = true;
   private static final boolean BLACK = false;

   private Node root;

   private int nRubro;

   private class Node {
      private Key key;          
      private Value val;         
      private Node left, right;  
      private boolean color;     
      private int N;        

      public Node(Key key, Value val, boolean color, int N) {
         this.key = key;
         this.val = val;
         this.color = color;
         this.N = N;
      }
   }

   private boolean isRed(Node x) {
        if (x == null) return false;
        return (x.color == RED);
   }

   private int size(Node x) {
        if (x == null) return 0;
        return x.N;
   } 


   public int size() {
       return size(root);
   }

   
   public Value get(Key key) {
      return get(root, key);
   }

   private Value get(Node x, Key key) {
      while (x != null) {
         int cmp = key.compareTo(x.key);
         if      (cmp < 0) x = x.left;
         else if (cmp > 0) x = x.right;
         else              return x.val;
      }
      return null;
    }

   public void put(Key key, Value val) {
        root = put(root, key, val);
        root.color = BLACK;
   }

   
   private Node put(Node h, Key key, Value val) { 
      if (h == null) return new Node(key, val, RED, 1);
      int cmp = key.compareTo(h.key);
      if      (cmp < 0) h.left  = put(h.left,  key, val); 
      else if (cmp > 0) h.right = put(h.right, key, val); 
      else              h.val   = val;
      if (isRed(h.right) && !isRed(h.left))      h = rotateLeft(h);
      if (isRed(h.left)  &&  isRed(h.left.left)) h = rotateRight(h);
      if (isRed(h.left)  &&  isRed(h.right))     flipColors(h);
      h.N = size(h.left) + size(h.right) + 1;
      return h;
   }


   private Node rotateRight(Node h) {
      Node x = h.left;
      h.left = x.right;
      x.right = h;
      x.color = x.right.color;
      x.right.color = RED;
      x.N = h.N;
      h.N = size(h.left) + size(h.right) + 1;
      return x;
   }

   private Node rotateLeft(Node h) {
      Node x = h.right;
      h.right = x.left;
      x.left = h;
      x.color = x.left.color;
      x.left.color = RED;
      x.N = h.N;
      h.N = size(h.left) + size(h.right) + 1;
      return x;
   }

   
   private void flipColors(Node h) {
      h.color = RED;
      h.left.color = BLACK;
      h.right.color = BLACK;
   }

   public int contaRubro() {
      nRubro = 0;
      return contaRubro(root);
   }

   private int contaRubro(Node x) {
      if (x == null) return 0;
      contaRubro(x.left);
      contaRubro(x.right);
      if (isRed(x)) nRubro++;
      return nRubro;
   }

   public int height() {
      return height(root);
   }

   public int height(Node x) {
      if (x == null) return -1;
      return 1 + Math.max(height(x.left), height(x.right));
   }

    public static void main(String[] args) { 
        RedBlackBST2<String, Integer> st = new RedBlackBST2<String, Integer>();
        for (int i = 0; !StdIn.isEmpty(); i++) {
            String key = StdIn.readString();
            st.put(key, i);
        }
        StdOut.println("Numero de nos rubros: " + st.contaRubro());
    }
}
