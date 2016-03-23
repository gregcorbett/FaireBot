void startup() {
  for (int i = 1; i < 8; i++) {
    if (i == 5) {
      light(i, true);
      i++;
      light(i, true);
    }
    else {
      light(i, true);
    }
    delay(100);
  }
  for (int i = 1; i < 8; i++) {
    if (i == 5) {
      light(i, false);
      i++;
      light(i, false);
    }
    else {
      light(i, false);
    }
    delay(100);
  }
}
