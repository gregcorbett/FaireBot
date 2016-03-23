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

void batteryCheck(){
  int batteryLevel = analogRead(0);
  if (batteryLevel < batteryLowLev && batteryLevel > usbLev) {
    changeBattery = true;
    light(2, false);
    light(3, false);
  }
  else {
    changeBattery = false;
  }
  if (batteryLevel <= usbLev) {
    light(1, false);
    light(2, false);
    light(3, false);
  }
  else if (batteryLevel >= batteryLowLev && batteryLevel < batteryMidLev) {
    light(1, true);
    light(2, false);
    light(3, false);
  }
  else if (batteryLevel >= batteryMidLev && batteryLevel < batteryHighLev) {
    light(1, true);
    light(2, true);
    light(3, false);
  }
  else if (batteryLevel >= batteryHighLev) {
    light(1, true);
    light(2, true);
    light(3, true);
  }

  if (changeBattery) {
    if (millis() >= batteryFlashTime) {
      batteryFlashTime += batteryFlashDelay;
      batteryToggle = !batteryToggle;
      light(1, batteryToggle);
    }
  }
}     

void light(int led, boolean state) {
  switch (led) {
  case 1:
    if (state) {
      digitalWrite(lowLED, HIGH);
    }
    else {
      digitalWrite(lowLED, LOW);
    }
    break;
  case 2:
    if (state) {
      digitalWrite(midLED, HIGH);
    }
    else {
      digitalWrite(midLED, LOW);
    }
    break;
  case 3:
    if (state) {
      digitalWrite(highLED, HIGH);
    }
    else {
      digitalWrite(highLED, LOW);
    }
    break;
  case 4:
    if (state) {
      digitalWrite(bckLED, HIGH);
    }
    else {
      digitalWrite(bckLED, LOW);
    }
    break;
  case 5:
    if (state) {
      digitalWrite(lftLED, HIGH);
    }
    else {
      digitalWrite(lftLED, LOW);
    }
    break;
  case 6:
    if (state) {
      digitalWrite(rhtLED, HIGH);
    }
    else {
      digitalWrite(rhtLED, LOW);
    }
    break;
  case 7:
    if (state) {
      digitalWrite(fwdLED, HIGH);
    }
    else {
      digitalWrite(fwdLED, LOW);
    }
    break;
  }
}

