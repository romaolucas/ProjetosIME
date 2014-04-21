public class CustoSondagemLinear {

   public static void main(String[] args) {
      Queue<Double> q1 = new Queue<Double>();
      Queue<Double> q2 = new Queue<Double>();
      Queue<Double> q3 = new Queue<Double>();
      Queue<Double> q4 = new Queue<Double>();
      LinearProbingHashST2<Integer, Integer> hst;
      int N = Integer.parseInt(args[0]);
      int M = 997;
      double y1 = 0;
      double y2 = 0;
      if (args.length == 1) {
         hst = new LinearProbingHashST2<Integer, Integer>();
      }
      else {
         M = Integer.parseInt(args[1]);
         hst = new LinearProbingHashST2<Integer, Integer>(M);
      }
      for (int i = 0; i < N; i++) {
         hst.put(StdRandom.uniform(M*M), i);
         q1.enqueue(hst.averageSearchHit());
         q2.enqueue(hst.propositionMHit());
         double aux = Math.max(hst.averageSearchHit(), hst.propositionMHit());
         if (aux > y1) y1 = aux;
         q3.enqueue(hst.averageSearchMiss());
         q4.enqueue(hst.propositionMMiss());
         aux = Math.max(hst.averageSearchMiss(), hst.propositionMMiss());
         if (aux > y2) y2 = aux;
      }
      VisualAccumulator acc1 = new VisualAccumulator("Buscas bem-sucedidas", N, y1);
      VisualAccumulator acc2 = new VisualAccumulator("Buscas mal-sucedidas", N, y2);
      for (int i = 0; i < N; i++) {
         acc1.addDataValue(q1.dequeue(), q2.dequeue());
         acc2.addDataValue(q3.dequeue(), q4.dequeue());
      }
      StdOut.println(acc1);
      StdOut.println(acc2);
   }

}
