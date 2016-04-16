void forward() {
  light(7, true);
  for (int i = 0; i < forwardLoopVal; i++) {
    leftServo.write(180);
    rightServo.write(0);
    delay(30);
  }
  light(7, false);
  sitIdle();
  delay(delayReplay);
}

void reverse() {
  light(4, true);
  for (int i = 0; i < forwardLoopVal; i++) {
    leftServo.write(0);
    rightServo.write(180);
    delay(30);
  }
  light(4, false);
  sitIdle();
  delay(delayReplay);
}

void left() {
  light(5, true);
  for (int i = 0; i < turningLoopVal; i++) {
    leftServo.write(0);
    rightServo.write(0);
    delay(30);
  }
  light(5, false);
  sitIdle();
  delay(delayReplay);
}

void right() {
  light(6, true);
  for (int i = 0; i < turningLoopVal; i++) {
    leftServo.write(180);
    rightServo.write(180);
    delay(30);
  }
  light(6, false);
  sitIdle();
  delay(delayReplay);
}

void sitIdle() {
  //default sit idle
  leftServo.write(90);
  rightServo.write(90);
  delay(30);
}
