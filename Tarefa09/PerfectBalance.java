import java.util.Arrays;
import java.util.Comparator;

public class PerfectBalance {
   private static int N = 0;
   private static Cel[] cel = new Cel[2];
   private static BST<Integer, Integer> balanced = new BST<Integer, Integer>();

   public void balance(Cel[] v, int b, int e) {
      if (b == e) {
         balanced.put(v[b].key, v[b].value);
         return;
      }
      else {
         int mid = (b + e)/2;
         balanced.put(v[mid].key, v[mid].value);
         if (mid != b) balance(v, b, mid - 1);
         balance(v, mid + 1, e);
      }
   }

   private static class Cel {
      private Integer key;
      private Integer value;
      public Cel(Integer key, Integer value) {
         this.key = key;
         this.value = value;
      }
   }

   private static class CelComparator implements Comparator<Cel> {
      @Override
      public int compare(Cel cel1, Cel cel2) {
         return cel1.key - cel2.key;
      }
   }

   public static void resize(int max) {
      Cel[] temp = new Cel[max];
      for (int i = 0; i < N; i++)
         temp[i] = new Cel(cel[i].key, cel[i].value);
      cel = temp;
   }

   public static void main(String[] args) {
      BST<Integer, Integer> nonb = new BST<Integer, Integer>();
      int i = 0;
      while (!StdIn.isEmpty()) {
         int aux = StdIn.readInt();
         i++;
         if (N == cel.length) resize(N*2);
         cel[N++] = new Cel(aux, i);
         nonb.put(aux, i);
      }
      resize(N);
      CelComparator ccomp = new CelComparator();
      Arrays.sort(cel, ccomp);
      StdOut.println("Altura nao balanceada: " + nonb.height());
      PerfectBalance obj = new PerfectBalance();
      obj.balance(cel, 0, cel.length -1);
      StdOut.println("Altura balanceada: " + balanced.height());
      StdOut.println("Numero de nos lidos: " + nonb.size());
      StdOut.println("floor(lg(" + nonb.size() + ")) = " 
      + Math.floor(Math.log(nonb.size())/Math.log(2)));
   }
}


