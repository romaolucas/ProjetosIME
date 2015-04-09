import java.math.BigInteger;
import java.util.Random;

public class Palindromos { 
   private static long Q;
   private static int R = 256;
   
   public static long hash(String key) {
      long h = 0;
      for (int j = 0; j < key.length(); j++)
         h = (R * h + key.charAt(j)) % Q;
      return h;
   }

   public static boolean check(String txt, int i) {
      return true;
   }

   private static long longRandomPrime() {
      BigInteger prime = BigInteger.probablePrime(31, new Random());
      return prime.longValue();
    }


   public static void main(String[] args) {
      String txt = "";
      long txtHash = hash(txt);
      String rev = "";
      long revHash;
      int nPalindrome = 0;
      int i = 0;
      Q = longRandomPrime();
      while (!StdIn.isEmpty()) {
         i++;
         char c = StdIn.readChar();
         txt += c;
         rev = c + rev.substring(0);
         revHash = hash(rev);
         txtHash = hash(txt);
         if (revHash == txtHash)
            if (check(txt, i)) {
               StdOut.println("Palindromo encontrado em " + i);
               nPalindrome++;
            }
      }
      StdOut.println("Foram lidos " + nPalindrome + " palindromos");
   }
}
