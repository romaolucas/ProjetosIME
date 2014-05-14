public Value get(String key) {
   Node x = root;
   for (int d = 0; d < key.length(); d++) {
      if (x == null) return null;
      char c = key.charAt(d);
      x = x.next[c];
   }
   return x.val;
}
