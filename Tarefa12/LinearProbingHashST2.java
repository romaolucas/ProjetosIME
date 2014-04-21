public class LinearProbingHashST2<Key, Value> {

   private int N = 0;       
   private int M = 997;
   private int k;
   private Key[] keys;  
   private Value[] vals;
   private Key[] aux;

   public LinearProbingHashST2() {
      keys = (Key[])   new Object[M];
      vals = (Value[]) new Object[M];
      aux = (Key[]) new Object[M];
   }

   public LinearProbingHashST2(int cap) {
      M = cap;
      keys = (Key[])   new Object[M];
      vals = (Value[]) new Object[M];
      aux = (Key[]) new Object[M];
   }

   private int hash(Key key) {
      return (key.hashCode() & 0x7fffffff) % M;
   }

   public void put(Key key, Value val) {
      int i;
      for (i = hash(key); keys[i] != null; i = (i + 1) % M) 
         if (keys[i].equals(key)) { 
            vals[i] = val; 
            return; 
         }
      keys[i] = key;
      vals[i] = val;
      aux[N] = key;
      N++;
   }

   public Value get(Key key) {
      for (int i = hash(key); keys[i] != null; i = (i + 1) % M){ 
         k++;
         if (keys[i].equals(key))
            return vals[i];
      }
      return null;
   }

   public double averageSearchHit() {
      int total = 0;
      for (int i = 0; aux[i] != null; i++) {
            k = 0;
            get(aux[i]);
            total += k;
      }
      return (double) total/N;
    }

   public double propositionMHit() {
      double alpha = (double) N/M;
      return (1 + 1/(1 - alpha))/2;
   }

   public double propositionMMiss() {
      double alpha = (double) N/M;
      return (1 + 1/Math.pow((1 - alpha), 2))/2;
   }

   public double averageSearchMiss() {
      int k = 0;
      for (int i = 0; i < M - 1; i++) {
         if (keys[i] != null) {
            int j = i;
            while (keys[j + 1] != null)
               j = (j + 1) % M;
            if (j  > i) i = j;
            else i = M;
            k++;
         }
      }
      return (double) k/N;
   }
}
