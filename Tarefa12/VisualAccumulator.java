public class VisualAccumulator {

   private double total;
   private int N;
   private Draw obj;
   private String title;

   public VisualAccumulator(String title, int X, double Y) {
      obj = new Draw(title);
      this.title = title;
      obj.setXscale(0, X);
      obj.setYscale(0, Y);
      obj.setPenRadius(.008);
   }

   public void addDataValue(double avg, double prop) {
      N++;
      obj.setPenColor(Draw.DARK_GRAY);
      obj.point(N, avg);
      obj.setPenColor(Draw.RED);
      obj.point(N, prop);
   }

   
   public String toString() { 
      return "Valores duma " + title; 
   }
}
