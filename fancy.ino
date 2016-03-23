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

void wait() {
  int countDownDelay = 500;
  light(7, false);
  light(6, false);
  light(4, false);
  light(5, false);
  delay(countDownDelay);
  light(7, true);
  light(6, false);
  light(4, false);
  light(5, false);
  delay(countDownDelay);
  light(7, true);
  light(6, true);
  light(4, false);
  light(5, false);
  delay(countDownDelay);
  light(7, true);
  light(6, true);
  light(4, true);
  light(5, false);
  delay(countDownDelay);
  light(7, true);
  light(6, true);
  light(4, true);
  light(5, true);
  delay(countDownDelay);
  light(7, false);
  light(6, false);
  light(4, false);
  light(5, false);
}
