/*--------------------------------------------------------------------
 FaireBot control firmware rev. 110714
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL BE
 LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 --------------------------------------------------------------------*/


#include <Servo.h>
#include <EEPROM.h>

int forwardLoopVal = 30;  //change for servo forward/backward tuning
int turningLoopVal = 11;  //change for servo turn tuning
int delayReplay = 1000;   //change for dleay between replaying commands

int lowLED = 13;
int midLED = 12;
int highLED = 11;
int bckLED = 10;
int rhtLED = 9;
int fwdLED = 8;
int lftLED = 7;

int fwd = 3;
int bck = 5;
int lft = 6;
int rht = 2;
int ent = 4;

int usbLev = 512;
int batteryLowLev = 717;
int batteryMidLev = 800;
int batteryHighLev = 875;
boolean changeBattery = false;
boolean batteryToggle = false;
int batteryFlashDelay = 100;
unsigned long batteryFlashTime;

Servo leftServo; //180
Servo rightServo;

int memory[100];
int memoryPtr = 0;

void setup() {
  pinMode(lowLED, OUTPUT);
  pinMode(midLED, OUTPUT);
  pinMode(highLED, OUTPUT);
  pinMode(fwdLED, OUTPUT);
  pinMode(bckLED, OUTPUT);
  pinMode(lftLED, OUTPUT);
  pinMode(rhtLED, OUTPUT);

  pinMode(fwd, INPUT);
  pinMode(bck, INPUT);
  pinMode(lft, INPUT);
  pinMode(rht, INPUT);
  pinMode(ent, INPUT);

  leftServo.attach(A1);
  rightServo.attach(A2);

  leftServo.write(90);
  delay(15);
  rightServo.write(90);
  delay(15);

  Serial.begin(9600);
  startup();
}

void loop() {
  if (changeBattery) {
    if (millis() >= batteryFlashTime) {
      batteryFlashTime += batteryFlashDelay;
      batteryToggle = !batteryToggle;
      light(1, batteryToggle);
    }
  }
  batteryCheck();
  buttonCheck();

  //default sit idle
  leftServo.write(90);
  delay(15);
  rightServo.write(90);
  delay(15);
}

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

void addToMemory(int dir){
  memory[memoryPtr] = dir;
  memoryPtr++; 
}

void buttonCheck(){

  if (digitalRead(fwd) == 1) {
    if (memoryPtr >= 100) {
      error();
    }
    else {
      addToMemory(fwd);
      while(digitalRead(fwd) == 1) {
        light(7, true);
      }
      light(7, false);
    }
  }
  else if(digitalRead(bck) == 1) {
    if (memoryPtr >= 100) {
      error();
    }
    else {
      addToMemory(bck);
      while(digitalRead(bck) == 1) {
        light(4, true);
      }
      light(4, false);
    }
  }
  else if(digitalRead(lft) == 1) {
    if (memoryPtr >= 100) {
      error();
    }
    else {
      addToMemory(lft);
      while(digitalRead(lft) == 1) {
        light(5, true);
      }
      light(5, false);
    }
  }
  else if(digitalRead(rht) == 1) {
    if (memoryPtr >= 100) {
      error();
    }
    else {
      addToMemory(rht);
      while(digitalRead(rht) == 1) {
        light(6, true);
      }
      light(6, false);
    }
  }
  else if(digitalRead(ent) == 1) {
    int timePressed = 0;
    while(digitalRead(ent) == 1) {
      delay(1);
      timePressed = timePressed + 1;
      if (timePressed > 3000){
        memory[100];
        memoryPtr = 0;
        startup();
        return; 
      }

    }
    wait();
    run();
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

void run() {
  int command;
  for (int i = 0; i < memoryPtr; i++) {
    command = memory[i];
    if (command == fwd) {
      forward();
    }
    else if (command == bck) {
      reverse();
    }
    else if (command == lft) {
      left();
    }
    else if (command == rht) {
      right();
    }
  }
}

void error() {
  for (int i = 0; i < 4; i++){
    light(4, true);
    light(5, true);
    light(6, true);
    light(7, true);
    delay(50);
    light(4, false);
    light(5, false);
    light(6, false);
    light(7, false);
    delay(50);
  }
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

