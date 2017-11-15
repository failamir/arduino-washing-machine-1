/* 

ARDUINO WASHING MACHINE 
TASK REQUIREMENTS:

Implement a virtual washing machine with Arduino, relay, switches, led, seven segment display and motors.
- Motor1 simulates the drum of the washing machine. It should rotate whenever the machine is washing, rinsing or centrifuging. Otherwise it should be stopped.
- Motor2 simulates the water pump of the washing machine. It should rotate whenever water is pumped out of the machine. Otherwise it should be stopped.
- Switch1 is turning the machine ON/OFF.
- Switch2 simulates the sensor which is ‘1’ whenever there is enough water in the machine.
- Switch3 simulates the sensor which is ‘1’ whenever all the water is pumped out of the machine.
- Relay is ON when the machine takes water.

The routine of the washing machine goes like this:
1. Washing machine takes water for 3s
2. Washing machine is washing for 9s (The speed of the motor should be moderate)
3. Dirty water is pumped out of the machine for 3s
4. Washing machine takes water for 3s
5. Washing machine is rinsing for 5s
6. Rinsing water is pumped out of the machine for 3s
7. Washing machine is centrifuging for 5s (The speed of the motor should be high)
8. Led is blinking when the washing program is finished.
9. Washing machine can be turned OFF

*/

/* ----- OUTPUT MACROS ----- */

#define A 2
#define B 8
#define C 6
#define D 5
#define E 4
#define F 3
#define G 7
#define RELAY 10
#define YELLOW 12
#define PUMP 9
#define DRUM 11
#define SWITCH2 A0
#define SWITCH3 A1

const int all[7] = {A, B, C, D, E, F, G};

/* ----- END OUTPUT MACROS ----- */

/* ----- SETUP ----- */

void setup() {
  Serial.begin(9600);
  // Display outputs
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  // Other outputs
  pinMode(RELAY, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(PUMP, OUTPUT);
  pinMode(DRUM, OUTPUT);
  pinMode(SWITCH2, OUTPUT);
  pinMode(SWITCH3, OUTPUT);
}

/* ----- END SETUP ----- */

/* ----- DISPLAY ----- */

void TurnOnLED(int led){
  digitalWrite(led, LOW);
}

void TurnOffAllLED(){
  for (int i = 0; i < sizeof(all); i++){
    digitalWrite(all[i], HIGH);
  }
}

void DisplayDigit(int digit, int time) {
  Serial.println(digit);
  switch (digit) {
    case 0:
      TurnOnLED(A);
      TurnOnLED(B);
      TurnOnLED(C);
      TurnOnLED(D);
      TurnOnLED(E);
      TurnOnLED(F);
      break;
    case 1:
      TurnOnLED(B);
      TurnOnLED(C);
      break;
    case 2:
      TurnOnLED(A);
      TurnOnLED(B);
      TurnOnLED(G);
      TurnOnLED(E);
      TurnOnLED(D);
      break;
    case 3:
      TurnOnLED(A);
      TurnOnLED(B);
      TurnOnLED(G);
      TurnOnLED(C);
      TurnOnLED(D);
      break;
    case 4:
      TurnOnLED(F);
      TurnOnLED(G);
      TurnOnLED(B);
      TurnOnLED(C);
      break;
    case 5:
      TurnOnLED(A);
      TurnOnLED(F);
      TurnOnLED(G);
      TurnOnLED(C);
      TurnOnLED(D);
      break;
    case 6:
      TurnOnLED(A);
      TurnOnLED(C);
      TurnOnLED(D);
      TurnOnLED(E);
      TurnOnLED(F);
      TurnOnLED(G);
      break;
    case 7:
      TurnOnLED(A);
      TurnOnLED(B);
      TurnOnLED(C);
      break;
    case 8:
      TurnOnLED(A);
      TurnOnLED(B);
      TurnOnLED(C);
      TurnOnLED(D);
      TurnOnLED(E);
      TurnOnLED(F);
      TurnOnLED(G);
      break;
    case 9:
      TurnOnLED(A);
      TurnOnLED(B);
      TurnOnLED(C);
      TurnOnLED(D);
      TurnOnLED(F);
      TurnOnLED(G);
      break;
    default:
      Serial.println("DisplayDigit needs an int 0-9")
      break;
  }

  delay(time);
  TurnOffAllLED();    // remove digit
}

/* ----- END DISPLAY ----- */

/* ----- WASHING HELPER FUNCTIONS ----- */

void turnOnDrum() {
  Serial.println("turnOnDrum");
  analogWrite(DRUM, 128);
}

void turnOnDrumFast() {
  Serial.println("turnOnDrumFast");
  analogWrite(DRUM, 255);
}

void turnOffDrum() {
  Serial.println("turnOffDrum");
  analogWrite(DRUM, 0);
}

void turnOnPump() {
  Serial.println("turnOnPump");
  analogWrite(PUMP, 255);
}

void turnOffPump() {
  Serial.println("turnOffPump");
  analogWrite(PUMP, 0);
}

void turnOnRelay() {
  Serial.println("turnOnRelay");
  digitalWrite (RELAY, HIGH);
}

void turnOffRelay() {
  Serial.println("turnOffRelay");
  digitalWrite (RELAY, LOW);
}

void setWaterStatus(int isFull) {
  if (isFull) {
    Serial.println("setWaterStatus: full");
    analogWrite(SWITCH2, 255);
    analogWrite(SWITCH3, 0);
  } else {
    Serial.println("setWaterStatus: empty");
    analogWrite(SWITCH2, 0);
    analogWrite(SWITCH3, 255);
  }
}

void turnBothSwitchesOff() {
  analogWrite(SWITCH2, 0);  // green OFF
  analogWrite(SWITCH3, 0);   // red OFF
}

void forXSeconds(int seconds) {
  // Show display for given time
  for (int i = 0; i < seconds; i++) {
    DisplayDigit(i, 1000);
  }
}

void blinkLed() {
  digitalWrite(YELLOW, HIGH);
  delay(500);
  digitalWrite(YELLOW, LOW);
  delay(500);
}

/* ----- END WASHING HELPER FUNCTIONS ----- */

/* ----- WASHING CYCLE FUNCTIONS ----- */

int letWaterIn(int time) {
  Serial.println("letWaterIn");
  turnOnRelay();
  forXSeconds(time);
  turnOffRelay();
  setWaterStatus(1);
}

int wash(int time) {
  Serial.println("wash");
  turnOnDrum();
  forXSeconds(time);
  turnOffDrum();
  setWaterStatus(0);
}

int pumpWaterOut(int time) {
  Serial.println("pumpWaterOut");
  turnOnPump();
  forXSeconds(time);
  turnOffPump();
  setWaterStatus(0);
}

int rinse(int time) {
  Serial.println("rinse");
  turnOnDrum();
  forXSeconds(time);
  turnOffDrum();
}

int centrifuge(int time) {
  Serial.println("centrifuge");
  turnOnDrumFast();
  forXSeconds(time);
  turnOffDrum();
}

int washingSequence() {
  letWaterIn(3);
  wash(9);
  pumpWaterOut(3);
  letWaterIn(3);
  rinse(5);
  pumpWaterOut(3);
  centrifuge(5);
  turnBothSwitchesOff();
  while (1) {
    Serial.println("Done, please collect your laundry!");
    blinkLed();
  }
}

/* ----- END WASHING CYCLE FUNCTIONS ----- */

/* ----- LOOP ----- */

void loop() {
  washingSequence();
}

/* ----- END LOOP ----- */
