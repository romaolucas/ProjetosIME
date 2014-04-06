import java.util.Random;

public class ContaRubros {
   public static void main(String[] args) {
      Queue<Double> pctRed = new Queue<Double>();
      int choice = Integer.parseInt(args[0]);
      int N = 0;
      double y = 0;
      switch (choice) {
         case 1:
            N = 10000;
            break;
         case 2:
            N = 100000;
            break;
         case 3:
            N = 1000000;
            break;
         default:
            N = 100;
            break;
      }
      for (int k = 0; k < 100; k++) {
         int tamanho;
         double   vermelho;
         Random aux = new Random();
         RedBlackBST2<Integer, Integer> st = new RedBlackBST2<Integer, Integer>();
         for (int i = 0; i < N; i++) 
            st.put(aux.nextInt(), i);
         vermelho = (double) st.contaRubro()/st.size();
         if (vermelho > y) y = vermelho;
         pctRed.enqueue(vermelho);
      }
      VisualAccumulator acc = new VisualAccumulator(100, y);
      while (!pctRed.isEmpty())
         acc.addDataValue(pctRed.dequeue());
      StdOut.println(acc);
   }
}
