#define INPUT1 12
#define INPUT2 13
#define INPUTDIST 0
#define LED1 7
#define LED2 8
#define OUTPUTDISTANCE 6

void setup() {
  pinMode(INPUT1, INPUT);
  pinMode(INPUT2, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite()
}


void loop() {
  bool in1 = digitalRead(INPUT1);
  bool in2 = digitalRead(INPUT2);
  digitalWrite(LED1, in1);
  digitalWrite(LED2, in2);
}
