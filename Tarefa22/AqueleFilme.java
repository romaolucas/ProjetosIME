public class AqueleFilme {
   
   public static char converte(char c) {
      boolean q1 = c >= 'a' && c <= 'z';
      boolean q2 = c >= '0' && c <= '9';
      if (c == ' ' || q1 || q2) return c;
      else {
         if (c >= 'A' && c <= 'Z') return (char) (c - 'A' + 'a');
         else
            switch (c) {
               case 'ã': case 'á': case 'à': case 'â': case 'ä': case 'å':
                  return 'a';
               case 'À': case 'Á': case 'Ã': case 'Â': case 'Ä': case 'Å':
                  return 'a';
               case 'ê': case 'è': case 'é': case 'ë':
                  return 'e';
               case 'Ê': case 'É': case 'È': case 'Ë':
                  return 'e';
               case 'Í': case 'Ì': case 'Î': case 'Ï':
                  return 'i';
               case 'ì': case 'í': case 'î': case 'ï':
                  return 'i';
               case 'Ñ': case 'ñ':
                  return 'n';
               case 'Ò': case 'Ó': case 'Ö': case 'Ô': case 'Õ':
                  return 'o';
               case 'ò': case 'ó': case 'ö': case 'ô': case 'õ':
                  return 'o';
               case 'Ù': case 'Ú': case 'Ü': case 'Û':
                  return 'u';
               case 'ù': case 'ú': case 'ü': case 'û': 
                  return 'u';
               case 'ý': case 'ÿ': case 'Ý': case 'Ÿ':
                  return 'y';
               default:
                  return '?';
            }
      }
   }

   public static String converte(String s) {
      String news = "";
      for (int i = 0; i < s.length(); i++)
         news += converte(s.charAt(i));
      return news;
   }

   public static String convertePonto(String s) {
      String news = "";
      for (int i = 0; i < s.length(); i++) {
         if (s.charAt(i) != '.') news += converte(s.charAt(i));
         else news += s.charAt(i);
      }
      return news;
   }

   public static void main(String[] args) {
      In in = new In("movies.txt");
      TrieSET set = new TrieSET();
      String alvo = args[0];
      int i = 0;
      while (in.hasNextLine()) {
         String key = "";
         String lixo;
         char c = in.readChar();
         while (c != '(') {
            key += c;
            c = in.readChar();
         }
         key = key.substring(0, key.length() - 1);
         set.add(converte(key));
         lixo = in.readLine();
         i++;
      }
      StdOut.println("Lidas " + i + " linhas");
      StdOut.println("Filmes com " + alvo + " como prefixo: ");
      for (String s : set.keysWithPrefix(converte(alvo)))
         StdOut.println(s);
      StdOut.print("\n");
      StdOut.println("Mais longo prefixo de " + alvo
           +  " que seja título de um filme: ");
      String aux = set.longestPrefixOf(converte(alvo));
      if (aux != null) StdOut.println(aux);
      StdOut.print("\n");
      StdOut.println("Titulos dos filmes que casam com " + alvo + " quando ."
            + " e interpretado como curinga: ");
      for (String s : set.keysThatMatch(convertePonto(alvo)))
         StdOut.println(s);
   }
}
