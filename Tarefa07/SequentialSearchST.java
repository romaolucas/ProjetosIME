import java.util.Iterator;
import java.util.NoSuchElementException;

public class SequentialSearchST<Key, Value> implements Iterable<Key>  {

   private Node first;
   private Key chave;
   private VisualAccumulator acc;

   private class Node { 
      private Key key;
      private Value val;
      private Node next;
      public Node(Key key, Value val, Node next) {
         this.key = key;
         this.val = val;
         this.next = next;
      }
   }

   public Value get(Key key) { 
      for (Node x = first; x != null; x = x.next)
         if (key.equals(x.key))
            return x.val;      
      return null;            
   }

   public int put(Key key, Value val) {
      int i = 0;
      for (Node x = first; x != null; x = x.next, i++)
         if (key.equals(x.key)) { 
            x.val = val;
            return i; 
         }
      first = new Node(key, val, first);
      return i;
   }

    public Iterator<Key> iterator()  {
        return new ListIterator(first);  
    }

    private class ListIterator implements Iterator<Key> {
        private Node current;

        public ListIterator (Node first) {
            current = first;
        }

        public boolean hasNext()  { return current != null;                     }
        public void remove()      { throw new UnsupportedOperationException();  }

        public Key next() {
            if (!hasNext()) throw new NoSuchElementException();
            chave = current.key;
            current = current.next; 
            return chave;
        }
    }
}

