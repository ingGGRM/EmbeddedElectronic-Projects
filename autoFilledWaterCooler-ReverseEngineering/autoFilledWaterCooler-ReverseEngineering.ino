/********** INPUT DECLARATIONS **********/
int heatSensor = A0;   // FLOAT
int coolSensor = A1;   // TR-C
int floatSensor = A2;  // TR-H
int switches = A3;     // SW-H&C

int overSensor = A4;  // FLOAT-P
int door = A5;        // CN2

int heatAdc;
int coolAdc;
int floatAdc;
int switchesAdc;
int overAdc;
int doorAdc;

/********** OUTPUT DECLARATIONS **********/
int ledA = 2;    // L1
int ledB = 3;    // L2
int ledC = 4;    // L3
int ledD = 5;    // L4
int pump = 6;    // PUMP
int heater = 7;  // HEAT
int cooler = 8;  // COOL

/********** OUTPUT DECLARATIONS **********/
boolean canHeat = true;  //
boolean canCool = true;  //
boolean canFill = true;  //

/********** MAIN SETUP FUNCTION **********/
void setup() {
  pinMode(heatSensor, INPUT);   // ANALOG
  pinMode(coolSensor, INPUT);   // ANALOG
  pinMode(floatSensor, INPUT);  // ANALOG
  pinMode(switches, INPUT);     // ANALOG
  pinMode(overSensor, INPUT);   // DIGITAL
  pinMode(door, INPUT);         // DIGITAL

  pinMode(ledA, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(ledC, OUTPUT);
  pinMode(ledD, OUTPUT);
  pinMode(pump, OUTPUT);
  pinMode(heater, OUTPUT);
  pinMode(cooler, OUTPUT);

  // set initial outputs state
  digitalWrite(ledA, HIGH);
  digitalWrite(ledB, LOW);
  digitalWrite(ledC, LOW);
  digitalWrite(ledD, LOW); /***************** Bug1: Starts Pump *****************/
  digitalWrite(pump, LOW); /***************** Bug2: Starts Cooler *****************/
  digitalWrite(heater, HIGH);
  digitalWrite(cooler, HIGH);

  /********** SET 2HZ TIMER INTERRUPT **********/
  noInterrupts();  // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  // Set timer1_counter to the correct value for our interrupt interval
  TCNT1 = 15000;           // 34286 // preload timer 65536-16MHz/256/2Hz
  TCCR1B |= (1 << CS12);   // 256 prescaler
  TIMSK1 |= (1 << TOIE1);  // enable timer overflow interrupt
  interrupts();            // enable all interrupts

  /********** SET SERIAL MONITOR CONFIG **********/
  Serial.begin(9600);

  analogReference(DEFAULT);
}

/********** MAIN LOOP FUNCTION **********/
void loop() {
  if (canCool) {
    digitalWrite(pump, HIGH);  // Start Cooler
  } else {
    digitalWrite(pump, LOW);  // Stop Cooler
  }

  if (canFill) {
    digitalWrite(ledD, HIGH);  // Start Pump
  } else {
    digitalWrite(ledD, LOW);  // Stop Pump
  }
}

/********** TIMER OVERFLOW INTERRUPT ISR **********/
ISR(TIMER1_OVF_vect) {
  TCNT1 = 15000;  // reset timer for next loops

  heatAdc = analogRead(heatSensor);
  coolAdc = analogRead(coolSensor);
  floatAdc = analogRead(floatSensor);
  switchesAdc = analogRead(switches);
  overAdc = analogRead(overSensor);
  doorAdc = analogRead(door);

  if (coolAdc < 180 && coolAdc > 170)
    canCool = false;
  else if (coolAdc > 200 && coolAdc < 290)
    canCool = true;

  if ((floatAdc > 265 && floatAdc < 275) || digitalRead(overSensor) == LOW)
    canFill = false;
  else if ((floatAdc > 285 && floatAdc < 295) || digitalRead(overSensor) == HIGH)
    canFill = true;

  verbose();
}

int verbose() {
  Serial.print(heatAdc);
  Serial.println(" heat");
  Serial.println();
  Serial.print(coolAdc);
  Serial.println(" cool");
  Serial.println();
  Serial.print(floatAdc);
  Serial.println(" float");
  Serial.println();
  Serial.print(switchesAdc);
  Serial.println(" switches");
  Serial.println();
  Serial.print(overAdc);
  Serial.println(" overFilled");
  Serial.println();
  Serial.print(doorAdc);
  Serial.println(" door");
  Serial.println();

  if (canFill) {
    Serial.println("Can Fill");
    Serial.println();
  } else {
    Serial.println("Can't Fill");
    Serial.println();
  }

  if (canCool) {
    Serial.println("Can Cool");
    Serial.println();
  } else {
    Serial.println("Can't Cool");
    Serial.println();
  }
}
