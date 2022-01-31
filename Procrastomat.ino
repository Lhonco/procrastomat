#include <Arduino.h>
#include <U8g2lib.h>
#include <Servo.h>

const int displayFrontPins[] = {13, 12, 11, 10, 9};
const int servoFrontPins[] = {8, 7};
const int switchFrontPins[] = {6, 5};
const int photoTopPinsFront[] = {A0, A1, A2, A3};
const int photoTopPinsBack[] = {A4, A5, A6, A7};
const int servoBackPins[] = {4, 3};
const int potBackPins[] = {A8, A9};
const int segmentRightPins[] = {41, 43, 45, 47, 49, 51, 53};
const int morseRightPin = 52;

int score = 0;
bool start = true;
int lastTask = 0;
int newTask = 0;

U8G2_SSD1327_EA_W128128_F_4W_SW_SPI u8g2(U8G2_R0, displayFrontPins[0], displayFrontPins[1], displayFrontPins[2], displayFrontPins[3], displayFrontPins[4]);

Servo servoBackLeft;
Servo servoBackRight;

Servo servoFrontLeft;
Servo servoFrontRight;

void setup() {
    initialiseServos();
    setPinModes();
    u8g2.begin();
    u8g2.setFont(u8g2_font_ncenB08_tr);
    Serial.begin(9600);
    startSequence();
}

void loop() {
//    while (lastTask == newTask) {
//        newTask = random(0, 5);
//    }
//    lastTask = newTask;
//    selectTask(newTask);
    front();
    right();
    left();
    top();
    back();
//    if (analogRead(photoTopPinsBack[1]) > 10) {
//        newTask = random(0, 4);
//        while (lastTask == newTask) {
//            newTask = random(0, 4);
//        }
//        lastTask = newTask;
//        selectTask(newTask);
//    } else {
//        u8g2.clearBuffer();
//        u8g2.drawStr(0, 52, "Demo Mode");
//        u8g2.sendBuffer();
//        delay(500);
//        front();
//        top();
//    }
}

void setPinModes() {
    // Front
    
    for (int i = 0; i < 2; i++) {
        pinMode(servoFrontPins[i], OUTPUT);
    }

    for (int i = 0; i < 2; i++) {
        pinMode(switchFrontPins[i], INPUT);
    }

    // Right
    pinMode(morseRightPin, INPUT);
    for (int i = 0; i < 7; i++) {
        pinMode(segmentRightPins[i], OUTPUT);
    }

    // Left
    pinMode(morseRightPin, INPUT);
    for (int i = 0; i < 7; i++) {
        pinMode(segmentRightPins[i], OUTPUT);
    }
}

void initialiseServos() {
    servoBackRight.attach(servoBackPins[0]);
    servoBackLeft.attach(servoBackPins[1]);
//    servoBackRight.write(180);
//    servoBackLeft.write(180);

    servoFrontLeft.attach(servoFrontPins[0]);
    servoFrontRight.attach(servoFrontPins[1]);
    servoFrontLeft.write(40);
    servoFrontRight.write(40);
}

void displayStats() {
//    u8g2.setFont(u8g2_font_ncenR08_tr);
    u8g2.drawStr(0, 84, "Time Wasted");
    u8g2.drawStr(0, 96, "                                  ");
    u8g2.setCursor(0, 96);
    u8g2.print(round(millis() / (60000.0)));
    u8g2.drawStr(13, 96, "m");
    u8g2.setCursor(26, 96);
    u8g2.print((millis() / 1000) % 60);
    u8g2.drawStr(38, 96, "s");

    u8g2.drawStr(88, 84, "Score");
    u8g2.setCursor(88, 96);
    u8g2.print(score);
    u8g2.sendBuffer();
}

void startSequence() {
    u8g2.clearBuffer();
    u8g2.drawStr(48, 52, "Hello");
    u8g2.sendBuffer();
    delay(3000);
    u8g2.clearBuffer();
    u8g2.drawStr(0, 52, "     I'm here to waste");
    u8g2.drawStr(0, 64, "          your time");
    u8g2.sendBuffer();
    delay(3000);
}

void selectTask(int task) {
    switch (task) {
        case 0:
            front();
            break;
        case 1:
            top();
            break;
        case 2:
            back();
            break;
        case 3:
            right();
            break;
        case 4:
            left();
            break;
      }
}

void front() {
    u8g2.clearBuffer();
    u8g2.drawStr(0, 24, "Switch a switch");
    u8g2.drawStr(0, 36, "to continue");
    u8g2.sendBuffer();

    while (true) {
        displayStats();

        if (digitalRead(switchFrontPins[0]) == HIGH) {
          servoFrontLeft.write(40);
          delay(500);
          servoFrontLeft.write(180);
          delay(500);
          servoFrontLeft.write(40);
          u8g2.drawStr(0, 24, "                               ");
          u8g2.drawStr(0, 36, "                               ");
          u8g2.sendBuffer();
          u8g2.drawStr(0, 52, "Ah not this one");
          u8g2.sendBuffer();
          while (true) {
          if (digitalRead(switchFrontPins[1]) == HIGH) {
          servoFrontRight.write(40);
          delay(500);
          servoFrontRight.write(180);
          delay(500);
          servoFrontRight.write(40);
          break;
          }
        } 
        score++;
        break;
        }

        if (digitalRead(switchFrontPins[1]) == HIGH) {
          servoFrontRight.write(40);
          delay(500);
          servoFrontRight.write(180);
          delay(500);
          servoFrontRight.write(40);
          u8g2.drawStr(0, 24, "                             ");
          u8g2.drawStr(0, 36, "                             ");
          u8g2.sendBuffer();
          u8g2.sendBuffer();
          u8g2.drawStr(0, 52, "Ah not this one");
          u8g2.sendBuffer();
          while (true) {
          if (digitalRead(switchFrontPins[0]) == HIGH) {
          servoFrontLeft.write(40);
          delay(500);
          servoFrontLeft.write(180);
          delay(500);
          servoFrontLeft.write(40);
          break;
          }
        } 
        score++;
        break;
        }
    }
}

void top() {
    u8g2.clearBuffer();
    u8g2.drawStr(0, 12, "Take a box from the");
    u8g2.drawStr(0, 24, "storage place at the");
    u8g2.drawStr(0, 36, "top of the box and ");
    u8g2.drawStr(0, 48, "place it into the top");
    u8g2.drawStr(0, 60, "left corner of the square");
    u8g2.sendBuffer();
                
    while (true) {
        displayStats();


        if (analogRead(photoTopPinsBack[1]) < 10) {
            score++;
            break;
        }
    }
}

void back() {
    int task = random(0, 3);
    int progress = 3;

    switch(task) {
        case 0:
            u8g2.clearBuffer();
            u8g2.drawStr(0, 12, "Point the arm to");
            u8g2.drawStr(0, 24, "the right");
            u8g2.sendBuffer();
            break;
        case 1:
            u8g2.clearBuffer();
            u8g2.drawStr(0, 12, "Point the arm to");
            u8g2.drawStr(0, 24, "the left");
            u8g2.sendBuffer();
            break;
        case 2:
            u8g2.clearBuffer();
            u8g2.drawStr(0, 12, "Point the arm to");
            u8g2.drawStr(0, 24, "the bottom");
            u8g2.sendBuffer();
            break;
                
    }
    while (true) {
        displayStats();

        servoBackLeft.write(round(analogRead(potBackPins[0]) * (180.0 / 1023)));
        servoBackRight.write(round(analogRead(potBackPins[1]) * (180.0 / 1023)));

        if (analogRead(potBackPins[0]) < 100 && analogRead(potBackPins[1]) < 100) {
            progress = 0;
        } else if (analogRead(potBackPins[0]) < 100 && analogRead(potBackPins[1]) > 900) {
            progress = 2;
        } else if (analogRead(potBackPins[0]) > 900 && analogRead(potBackPins[1]) > 1000) {
            progress = 1;
        }

        if (progress == task) {
            score++;
            break;
        }
    }
}

void right() {
//    int numberShown = random(1, 10);
    int numberShown = 2;
    int buttonPressed = 0;
    segmentDisplayNumber(numberShown);
    u8g2.clearBuffer();

    while (true) {
        displayStats();

        
        if (digitalRead(morseRightPin) == HIGH) {
            buttonPressed++;
        }

        u8g2.drawStr(0, 12, "Click the button on");
        u8g2.drawStr(0, 24, "the right side for as");
        u8g2.drawStr(0, 36, "many times shown");
        u8g2.drawStr(0, 48, "Pressed so far:");
        u8g2.setCursor(88, 48);
        u8g2.print("        ");
        u8g2.print(buttonPressed);
        u8g2.sendBuffer();

        if (buttonPressed == numberShown) {
            score++;
            segmentOff();
            break;
        }
    }
}

void left() {
    u8g2.clearBuffer();
    u8g2.drawStr(0, 12, "Press the button");
    u8g2.drawStr(0, 24, "on the left side");
    u8g2.drawStr(0, 36, "of the box so the");
    u8g2.drawStr(0, 48, "LED turns off");
    u8g2.sendBuffer();

    digitalWrite(29, HIGH);
    while (true) {
        displayStats();

        if (digitalRead(46) == HIGH) {
            score++;
            digitalWrite(29, LOW);
            break;
        }
    }
}

void segmentDisplayNumber(int selectedNumber) {
    switch (selectedNumber) {
        case 0:
            digitalWrite(segmentRightPins[0], LOW);
            digitalWrite(segmentRightPins[1], HIGH);
            digitalWrite(segmentRightPins[2], HIGH);
            digitalWrite(segmentRightPins[3], HIGH);
            digitalWrite(segmentRightPins[4], HIGH);
            digitalWrite(segmentRightPins[5], HIGH);
            digitalWrite(segmentRightPins[6], HIGH);
            break;
        case 1:
            digitalWrite(segmentRightPins[0], LOW);
            digitalWrite(segmentRightPins[1], LOW);
            digitalWrite(segmentRightPins[2], LOW);
            digitalWrite(segmentRightPins[3], LOW);
            digitalWrite(segmentRightPins[4], HIGH);
            digitalWrite(segmentRightPins[5], LOW);
            digitalWrite(segmentRightPins[6], HIGH);
            break;
        case 2:
            digitalWrite(segmentRightPins[0], HIGH);
            digitalWrite(segmentRightPins[1], LOW);
            digitalWrite(segmentRightPins[2], HIGH);
            digitalWrite(segmentRightPins[3], HIGH);
            digitalWrite(segmentRightPins[4], LOW);
            digitalWrite(segmentRightPins[5], HIGH);
            digitalWrite(segmentRightPins[6], HIGH);
            break;
        case 3:
            digitalWrite(segmentRightPins[0], HIGH);
            digitalWrite(segmentRightPins[1], LOW);
            digitalWrite(segmentRightPins[2], LOW);
            digitalWrite(segmentRightPins[3], HIGH);
            digitalWrite(segmentRightPins[4], HIGH);
            digitalWrite(segmentRightPins[5], HIGH);
            digitalWrite(segmentRightPins[6], HIGH);
            break;
        case 4:
            digitalWrite(segmentRightPins[0], HIGH);
            digitalWrite(segmentRightPins[1], HIGH);
            digitalWrite(segmentRightPins[2], LOW);
            digitalWrite(segmentRightPins[3], LOW);
            digitalWrite(segmentRightPins[4], HIGH);
            digitalWrite(segmentRightPins[5], LOW);
            digitalWrite(segmentRightPins[6], HIGH);
            break;
        case 5:
            digitalWrite(segmentRightPins[0], HIGH);
            digitalWrite(segmentRightPins[1], HIGH);
            digitalWrite(segmentRightPins[2], LOW);
            digitalWrite(segmentRightPins[3], HIGH);
            digitalWrite(segmentRightPins[4], HIGH);
            digitalWrite(segmentRightPins[5], HIGH);
            digitalWrite(segmentRightPins[6], LOW);
            break;
        case 6:
            digitalWrite(segmentRightPins[0], HIGH);
            digitalWrite(segmentRightPins[1], HIGH);
            digitalWrite(segmentRightPins[2], HIGH);
            digitalWrite(segmentRightPins[3], HIGH);
            digitalWrite(segmentRightPins[4], HIGH);
            digitalWrite(segmentRightPins[5], HIGH);
            digitalWrite(segmentRightPins[6], LOW);
            break;
        case 7:
            digitalWrite(segmentRightPins[0], LOW);
            digitalWrite(segmentRightPins[1], LOW);
            digitalWrite(segmentRightPins[2], LOW);
            digitalWrite(segmentRightPins[3], LOW);
            digitalWrite(segmentRightPins[4], HIGH);
            digitalWrite(segmentRightPins[5], HIGH);
            digitalWrite(segmentRightPins[6], HIGH);
            break;
        case 8:
            digitalWrite(segmentRightPins[0], HIGH);
            digitalWrite(segmentRightPins[1], HIGH);
            digitalWrite(segmentRightPins[2], HIGH);
            digitalWrite(segmentRightPins[3], HIGH);
            digitalWrite(segmentRightPins[4], HIGH);
            digitalWrite(segmentRightPins[5], HIGH);
            digitalWrite(segmentRightPins[6], HIGH);
            break;
        case 9:
            digitalWrite(segmentRightPins[0], HIGH);
            digitalWrite(segmentRightPins[1], HIGH);
            digitalWrite(segmentRightPins[2], LOW);
            digitalWrite(segmentRightPins[3], LOW);
            digitalWrite(segmentRightPins[4], HIGH);
            digitalWrite(segmentRightPins[5], HIGH);
            digitalWrite(segmentRightPins[6], HIGH);
            break;
            
    }
}

void segmentOff() {
    digitalWrite(segmentRightPins[0], LOW);
    digitalWrite(segmentRightPins[1], LOW);
    digitalWrite(segmentRightPins[2], LOW);
    digitalWrite(segmentRightPins[3], LOW);
    digitalWrite(segmentRightPins[4], LOW);
    digitalWrite(segmentRightPins[5], LOW);
    digitalWrite(segmentRightPins[6], LOW);
}




















































void testOverSerial() {
    boolean newInput;
    char input;
    
    if (Serial.available() > 0) {
    input = Serial.read();
    newInput = true;
    if (newInput == true && input == 'p') {
      for (int i = 0; i < 4; i++) {
        Serial.print("A");
        Serial.print(i);
        Serial.print(": ");
        Serial.print(analogRead(photoTopPinsFront[i]));
        Serial.print("  ");
      }
      Serial.println();
      for (int i = 0; i < 4; i++) {
        Serial.print("A");
        Serial.print(i + 4);
        Serial.print(": ");
        Serial.print(analogRead(photoTopPinsBack[i]));
        Serial.print("  ");
      }
      Serial.println();
      newInput = false;
    }

    else if (newInput == true && input == 'w') {
      while (true) {
        input = Serial.read();
        newInput = true;
        Serial.print("Left Pot: ");
        Serial.print(analogRead(potBackPins[0]));
        Serial.print("  Left Servo:");
        Serial.print(analogRead(potBackPins[0]) * (180.0 / 1023));
        Serial.print("  Right: ");
        Serial.println(analogRead(potBackPins[1]));
        servoBackLeft.write(round(analogRead(potBackPins[0]) * (180.0 / 1023)));
        servoBackRight.write(round(analogRead(potBackPins[1]) * (180.0 / 1023)));
        if (newInput == true && input == 'q') {
          break;
        }
      }
      newInput = false;

    }

    else if (newInput == true && input == 's') {
      for (int i = 41; i < 54; i += 2) {
        Serial.println("Here");
        digitalWrite(i, HIGH);
        delay(600);
      }

      for (int i = 41; i < 54; i += 2) {
        digitalWrite(i, LOW);
        delay(600);
      }
      newInput = false;
    }

    else if (newInput == true && input == 'm') {
      while (true) {
        input = Serial.read();
        newInput = true;

        if (digitalRead(morseRightPin) == HIGH) {
          Serial.println("High");
        } else {
          Serial.println("Low");
        }
        if (newInput == true && input == 'q') {
          break;
        }
      }
      newInput = false;
    }

    else if (newInput == true && input == 'l') {
      while (true) {
        input = Serial.read();
        newInput = true;

        for (int i = 36; i < 51; i += 2) {
          if (digitalRead(i) == HIGH) {
            Serial.print(i);
            Serial.print(": High  ");
          } else {
            Serial.print(i);
            Serial.print(": Low  ");
          }
        }
        Serial.println();
        delay(200);
        if (newInput == true && input == 'q') {
          for (int i = 25; i < 42; i += 2) {
            digitalWrite(i,HIGH);
            delay(600);
          }
          for (int i = 25; i < 42; i += 2) {
            digitalWrite(i,LOW);
            delay(600);
          }
          break;
        }
      }
      newInput = false;
    }

    else if (newInput == true && input == 'u') {
      while (true) {
        input = Serial.read();
        newInput = true;

        if (digitalRead(switchFrontPins[0]) == HIGH) {
          servoFrontLeft.write(40);
          delay(500);
          servoFrontLeft.write(180);
          delay(500);
          servoFrontLeft.write(40);
          Serial.println("High");
        }
        else {
          Serial.println("Low");
        }

        if (digitalRead(switchFrontPins[1]) == HIGH) {
          servoFrontRight.write(40);
          delay(500);
          servoFrontRight.write(180);
          delay(500);
          servoFrontRight.write(40);
          Serial.println("High");
        }
        else {
          Serial.println("Low");
        }

        delay(100);
        if (newInput == true && input == 'q') {
          break;
        }
      }
      newInput = false;
    }
  }
}

void videoSetup() {
   if (digitalRead(switchFrontPins[0]) == HIGH) {
    delay(3000);
    u8g2.clearBuffer();
    u8g2.drawStr(0, 30, "");
    u8g2.sendBuffer();
    delay(1000);
    
    servoFrontLeft.write(40);
    delay(500);
    servoFrontLeft.write(180);
    delay(500);
    servoFrontLeft.write(40);
  }

  if (digitalRead(switchFrontPins[1]) == HIGH) {
        for (int i = 25; i < 42; i += 2) {
            digitalWrite(i,HIGH);
            delay(600);
          }
          for (int i = 25; i < 42; i += 2) {
            digitalWrite(i,LOW);
            delay(600);
          }
  }
  if (digitalRead(switchFrontPins[0]) == HIGH) {
    delay(500);
    u8g2.clearBuffer();
    u8g2.drawStr(0, 30, "Ah not this one");
    u8g2.sendBuffer();
    delay(1000);
    
    servoFrontLeft.write(40);
    delay(500);
    servoFrontLeft.write(180);
    delay(500);
    servoFrontLeft.write(40);

    while (true) {
      if (digitalRead(switchFrontPins[1]) == HIGH) {
        delay(500);
        u8g2.clearBuffer();
        u8g2.drawStr(0, 30, "Oh maybe the first one");
        u8g2.drawStr(0, 40, "was better after all");
        u8g2.sendBuffer();
        delay(1000);
        
        servoFrontRight.write(40);
        delay(500);
        servoFrontRight.write(180);
        delay(500);
        servoFrontRight.write(40);

        while (true) {
          if (digitalRead(switchFrontPins[0]) == HIGH) {
            delay(500);
            u8g2.clearBuffer();
            u8g2.drawStr(0, 30, "Ok see that letter on");
            u8g2.drawStr(0, 40, "the side?");
            u8g2.sendBuffer();
          }
        }
      }
    }
  }
}
