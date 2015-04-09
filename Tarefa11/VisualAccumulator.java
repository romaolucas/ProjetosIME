// Este arquivo: VisualAccumulator.java
// ------------------------------------
// Esta classe implementa a ADT VisualAccumulator: um 
// acumulador "visual" de valores double que faz um 
// desenho animado da media corrente desses valores.
// Veja p.94 de "Algorithms 4th ed" de Sedgewick e Wayne.
// 
// Bibliotecas usadas:
//   algs4/stdlib.jar  StdDraw, StdOut
//   java              String
//
// Data: 2013-10-27

public class VisualAccumulator {

   private double total;
   private int N;

   // Cria um acumulador visual e define uma tela com
   // eixo x preparado para representar o intervalo [0,X] e
   // eixo y preparado para representar o intervalo [0,Y].
   public VisualAccumulator(int X, double Y) {
      StdDraw.setXscale(0, X);
      StdDraw.setYscale(0, Y);
      StdDraw.setPenRadius(.008);
   }

   // Adiciona um novo valor ao acumulador e desenha dois
   // pontos na tela. Este sera' o N-esimo valor adicionado.
   // Os pontos sao desenhados da seguinte maneira:
   // um ponto cinza com coordenadas (N, valor) e 
   // um ponto vermelho com coordenadas (N, m), 
   // sendo m a media de todos os valores adicionados 
   // ate o momento.
   public void addDataValue(double val) {
      N++;
      total += val;
      StdDraw.setPenColor(StdDraw.DARK_GRAY);
      StdDraw.point(N, val);
      StdDraw.setPenColor(StdDraw.RED);
      StdDraw.point(N, mean());
   }

   // Media de todos os valores acumulados ate este momento.
   public double mean() { 
      return total/N; 
   }

   // Devolve uma string que representa o acumulador.
   // A string da a media dos valores e o numero de pontos
   public String toString() { 
      return "Media (" + N + " valores): " 
             + String.format("%7.5f", mean()); 
   }
}