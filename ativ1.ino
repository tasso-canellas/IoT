#define LED1 18
#define LED2 21
#define LEDbat 25
#define stateDistance 19

long duration;
float distanceCm;
#define SOUND_SPEED 0.034

#define CHARGING 'c'
#define IDLE     'i'
#define CLEANING 'l'
#define DOCKING  'd'

char state = IDLE;
bool led1State = LOW;
bool led2State = LOW;
unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;
unsigned long previousMillis = 0;
unsigned long currMilli;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LEDbat, OUTPUT);
  Serial.begin(115200);
  idle();
}

void idle() {
  state = IDLE;
  digitalWrite(LED1, LOW);
  led1State = LOW;
  digitalWrite(LED2, LOW);
  digitalWrite(LEDbat, HIGH);
  led2State= LOW;
  previousMillis = currMilli;
  previousMillis1 = currMilli;
  previousMillis2 = currMilli;
}

void charging() {
  state = CHARGING;
  digitalWrite(LED1, HIGH);
  led1State = HIGH;
  digitalWrite(LED2, HIGH);
  led2State = HIGH;
  previousMillis = currMilli;
  previousMillis1 = currMilli;
  previousMillis2 = currMilli;
}

void cleaning() {
  state = CLEANING;
  digitalWrite(LED1, HIGH);
  led1State = HIGH;
  digitalWrite(LED2, LOW);
  led2State = LOW;
  previousMillis = currMilli;
  previousMillis1 = currMilli;
  previousMillis2 = currMilli;
}

void docking() {
  state = DOCKING;
  digitalWrite(LED1, LOW);
  led1State = LOW;
  led2State = HIGH;
  digitalWrite(LED2, HIGH);
  digitalWrite(LEDbat, LOW);
  previousMillis = currMilli;
  previousMillis1 = currMilli;
  previousMillis2 = currMilli;
}

void loop() {
  currMilli = millis();

  if (Serial.available()) {
    char temp = Serial.read();

    if (temp == 'a') {
      switch (state) {
        case IDLE:
          cleaning();
          break;
        case CHARGING:
          cleaning();
          break;
      }
    }

    else if (temp == 'b' && state == CLEANING) {
      docking();
    }
  }

  if (currMilli - previousMillis > 2000) {
    if (state == CLEANING) {
      docking();
    }
    else if (state == DOCKING) {
      charging();
    }
    else if (state == CHARGING){
      idle();
    }
  }

  else{
    if (currMilli - previousMillis1 > 100 && (state == CLEANING || state == CHARGING)) {
      led1State = !led1State;
      digitalWrite(LED1, led1State);
      digitalWrite(LED2, led2State);
      previousMillis1 = currMilli;
    }

    if (currMilli - previousMillis2 > 50 && (state == DOCKING || state == CHARGING)) {
      led2State = !led2State;
      digitalWrite(LED2, led2State);
      digitalWrite(LED1, led1State);
      previousMillis2 = currMilli;
    }
  }

  float analog = 0.1275*(currMilli-previousMillis);
  analog = constrain(analog, 0, 255);

  switch(state){
    case CLEANING:
      dacWrite(LEDbat, 255 - analog);
      break;
    
    case CHARGING:
      dacWrite(LEDbat, analog);
      break;
  }
}
