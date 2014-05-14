/*
 *Nome: Lucas Romao Silva
 *nUSP.: 8536214
 * */

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;

public class ep1 {

   private static  int N = 0;
   private static  String[] dec = new String[2];
   private static  String[] hex = new String[2];
   
   /*devolveInstrucao(String comando)
    * recebe um comando do hipo e devolve o valor decimal correspondente*/
   public static int devolveInstrucao(String comando) {
      if (comando.equals("LDA")) return 11;
      else if (comando.equals("STA")) return 12;
      else if (comando.equals("ADD")) return 21;
      else if (comando.equals("SUB")) return 22;
      else if (comando.equals("MUL")) return 23;
      else if (comando.equals("DIV")) return 24;
      else if (comando.equals("REM")) return 25;
      else if (comando.equals("REV")) return 29;
      else if (comando.equals("INN")) return 31;
      else if (comando.equals("PRN")) return 41;
      else if (comando.equals("NOP")) return 50;
      else if (comando.equals("JMP")) return 51;
      else if (comando.equals("JLE")) return 52;
      else if (comando.equals("JDZ")) return 53;
      else if (comando.equals("JGT")) return 54;
      else if (comando.equals("JEQ")) return 55;
      else if (comando.equals("JLT")) return 56;
      else if (comando.equals("JGE")) return 57;
      else if (comando.equals("STP")) return 70;
      return 0;
   }

   public static String converteHexa(String comando, int add) {
      String hexa = "";
      int aux = devolveInstrucao(comando);
      while (aux != 0) {
         int comp = aux % 16;
         switch (comp) {
            case 10:
               hexa += "A";
               break;
            case 11:
               hexa += "B";
               break;
            case 12:
               hexa += "C";
               break;
            case 13:
               hexa += "D";
               break;
            case 14:
               hexa += "E";
               break;
            case 15:
               hexa += "F";
               break;
            default:
               hexa += String.valueOf(comp);
               break;
         }
         aux /= 16;
      }
      String end = "";
      while (add != 0) {
         int comp = add % 16;
         switch (comp) {
            case 10:
               end += "A";
               break;
            case 11:
               end += "B";
               break;
            case 12:
               end += "C";
               break;
            case 13:
               end += "D";
               break;
            case 14:
               end += "E";
               break;
            case 15:
               end += "F";
               break;
            default:
               end += String.valueOf(comp);
               break;
         }
         add /= 16;
      }
      if(hexa.length() < 2) hexa += "0";
      if(end.length() < 1) end += "00";
      else if (end.length() < 2) end += "0";
      StringBuffer buffer = new StringBuffer(hexa);
      hexa = buffer.reverse().toString();
      buffer = new StringBuffer(end);
      end = buffer.reverse().toString();
      return hexa+end;
   }

   public static String converteDecimal(String comando, int add) {
      String decimal = "+";
      decimal += String.valueOf(devolveInstrucao(comando));
      if (add < 10) decimal = decimal + "0" + String.valueOf(add);
      else decimal += String.valueOf(add);
      return decimal;
   }

   /*void resize(int max)
    * recebe um inteiro e redimensiona os vetores com os numeros
    * em decimal e em hexadecimal para o tamanho max
    * */
   public static void resize(int max) {
      String[] temp = new String[max];
      String[] temp2 = new String[max];
      for (int i = 0; i < N; i++)
         temp[i] = dec[i];
      dec = temp;
      for (int i = 0; i < N; i++)
         temp2[i] = hex[i];
      hex = temp2;
   }

   /*Consideracoes sobre o EP:
    *1 - o programa supoe que o arquivo com os minemonicos sera dado por
    * linha de comando
    * 2 - o programa supoe que o minemonico e da forma: XXX NN
    * onde XXX e uma instrucao e NN e o endereco
    * 3 - o programa nao da a opcao de escolher o nome do arquivo final
    * 4 - para retirar ambiguidade, todos os numeros sao impressos
    * com 4 caracteres
    * */
   public static void main(String[] args) {
      BufferedReader br = null;
      try {
         String linha = "";

         br = new BufferedReader(new FileReader(args[0]));
         while ((linha = br.readLine()) != null) {
            String comando = linha.substring(0,3);
            int add = Integer.parseInt(linha.substring(4, linha.length()));
            if (N == dec.length) resize(N*2);
            dec[N] = converteDecimal(comando, add);
            hex[N] = converteHexa(comando, add);
            N++;
         }
         PrintWriter arqdec = new PrintWriter("decimal.txt", "UTF-8");
         for (int i = 0; i < N; i++) arqdec.println(dec[i]);
         arqdec.close();
         PrintWriter arqhex = new PrintWriter("hexa.txt", "UTF-8");
         for (int i = 0; i < N; i++) arqhex.println(hex[i]);
         arqhex.close();
      } catch (IOException e) {
         e.printStackTrace();
      }
   }
}

