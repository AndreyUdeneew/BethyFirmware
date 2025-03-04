uint8_t Button1 = 29;
uint8_t Button2 = 28;
uint8_t Button3 = 27;
uint8_t Button4 = 26;
uint8_t Button5 = 15;
uint8_t Button6 = 14;
uint8_t Button7 = 13;
uint8_t Button8 = 12;
uint8_t Button9 = 11;
uint8_t ENBW = 8;
uint8_t FLTBW = 9;
uint8_t ENColor = 10;
uint8_t FLTColor = 7;

uint8_t LastButton = 0;
const char* ButtonMessage[] = { "b1", "b2", "b3", "b4", "b5", "b6", "b7", "b8", "b9", "b10", "b11" };
uint16_t RESET_DELAY = 1000;

long previousMillis = 0;  // храним время последнего переключения светодиода
unsigned long resettingInterval = 0;
bool BW_is_reseted = false;
bool color_is_reseted = false;

// long interval = 1000;

void setup() {
  pinMode(ENBW, OUTPUT);
  pinMode(ENColor, OUTPUT);
  digitalWrite(ENBW, HIGH);
  digitalWrite(ENColor, HIGH);

  attachInterrupt(digitalPinToInterrupt(Button1), InterruptReactButton1, FALLING);
  attachInterrupt(digitalPinToInterrupt(Button2), InterruptReactButton2, FALLING);
  attachInterrupt(digitalPinToInterrupt(Button3), InterruptReactButton3, FALLING);
  attachInterrupt(digitalPinToInterrupt(Button4), InterruptReactButton4, FALLING);
  attachInterrupt(digitalPinToInterrupt(Button5), InterruptReactButton5, FALLING);
  attachInterrupt(digitalPinToInterrupt(Button6), InterruptReactButton6, FALLING);
  attachInterrupt(digitalPinToInterrupt(Button7), InterruptReactButton7, FALLING);
  attachInterrupt(digitalPinToInterrupt(Button8), InterruptReactButton8, FALLING);
  attachInterrupt(digitalPinToInterrupt(Button9), InterruptReactButton9, FALLING);
  attachInterrupt(digitalPinToInterrupt(FLTBW), InterruptReactFLTBW, FALLING);
  attachInterrupt(digitalPinToInterrupt(FLTColor), InterruptReactFLTColor, FALLING);

  pinMode(Button1, INPUT_PULLUP);
  pinMode(Button2, INPUT_PULLUP);
  pinMode(Button3, INPUT_PULLUP);
  pinMode(Button4, INPUT_PULLUP);
  pinMode(Button5, INPUT_PULLUP);
  pinMode(Button6, INPUT_PULLUP);
  pinMode(Button7, INPUT_PULLUP);
  pinMode(Button8, INPUT_PULLUP);
  pinMode(Button9, INPUT_PULLUP);
  pinMode(FLTBW, INPUT_PULLUP);
  pinMode(FLTColor, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();

  if (Serial.available()) {

    String input = Serial.readStringUntil('\r');
    if (input == "hello") {
      Serial.println("iambetty");
    }
    if (input == "colorreset") {
      Serial.println("doing color reset");
      digitalWrite(ENColor, LOW);
      resettingInterval = millis();
      input = "";
    }
    if (input == "bwreset") {
      Serial.println("doing BW reset");
      digitalWrite(ENBW, LOW);
      resettingInterval = millis();
      input = "";
    }
  }
  if (LastButton > 0) {
    Serial.println(ButtonMessage[LastButton - 1]);
    delay(100);
  }
  if ((currentMillis - resettingInterval) > RESET_DELAY) {
    digitalWrite(ENColor, HIGH);
    digitalWrite(ENBW, HIGH);
  }

  LastButton = 0;
}

void InterruptReactButton1() {
  LastButton = 1;
}
void InterruptReactButton2() {
  LastButton = 2;
}
void InterruptReactButton3() {
  LastButton = 3;
}
void InterruptReactButton4() {
  LastButton = 4;
}
void InterruptReactButton5() {
  LastButton = 5;
}
void InterruptReactButton6() {
  LastButton = 6;
}
void InterruptReactButton7() {
  LastButton = 7;
}
void InterruptReactButton8() {
  LastButton = 8;
}
void InterruptReactButton9() {
  LastButton = 9;
}
void InterruptReactFLTBW() {
  digitalWrite(ENBW, LOW);
  LastButton = 10;
}
void InterruptReactFLTColor() {
  digitalWrite(ENColor, LOW);
  LastButton = 11;
}
