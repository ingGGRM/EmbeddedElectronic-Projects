/********** INPUT DECLARATIONS **********/
int heatSensor = A0;  // TR-H
int coolSensor = A1;  // TR-C
int floatSensor = A2; // FLOAT
int switches = A3;    // SW-H&C

int overSensor = A4; // FLOAT-P
int door = A5;       // CN2

// variables to store input readings
int heatAdc;
int coolAdc;
int floatAdc;
int switchesAdc;

/********** OUTPUT DECLARATIONS **********/
int ledA = 2; // L1
int ledB = 3; // L2
int ledC = 4; // L3
int ledD = 5; // L4
// int pump = 6;    // PUMP
// int heater = 7;  // HEAT
// int cooler = 8 ;  // COOL

int pump = 11;   // PUMP
int heater = 12; // HEAT
int cooler = 13; // COOL

/********** OUTPUT DECLARATIONS **********/
boolean canHeat = true; //
boolean canCool = true; //
boolean canFill = true; //
boolean swHeat = false;
boolean swCool = false;

/********** MAIN SETUP FUNCTION **********/
void setup()
{
  pinMode(heatSensor, INPUT);  // ANALOG
  pinMode(coolSensor, INPUT);  // ANALOG
  pinMode(floatSensor, INPUT); // ANALOG
  pinMode(switches, INPUT);    // ANALOG
  pinMode(overSensor, INPUT);  // DIGITAL
  pinMode(door, INPUT);        // DIGITAL

  pinMode(ledA, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(ledC, OUTPUT);
  pinMode(ledD, OUTPUT);

  pinMode(pump, OUTPUT);
  pinMode(heater, OUTPUT);
  pinMode(cooler, OUTPUT);

  // set initial outputs state
  digitalWrite(ledA, HIGH); // sets the powerOn led to On state
  digitalWrite(ledB, LOW);  // sets the powerOn led to On state
  digitalWrite(ledC, LOW);
  digitalWrite(ledD, HIGH);

  digitalWrite(pump, LOW);
  digitalWrite(heater, LOW);
  digitalWrite(cooler, LOW);

  /********** SET TIMER INTERRUPT TO NEAR 1 SECOND DELAY **********/
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 15000;
  TCCR1B |= (1 << CS12);
  TIMSK1 |= (1 << TOIE1);
  interrupts();

  /********** SET SERIAL MONITOR CONFIG **********/
  Serial.begin(9600);

  /********** SET ADC TO DEFAULT VREF **********/
  analogReference(DEFAULT);
}

/********** MAIN LOOP FUNCTION **********/
void loop()
{
  if (canCool && swCool && !canFill)
    digitalWrite(cooler, HIGH); // Start Cooler
  else
    digitalWrite(cooler, LOW); // Stop Cooler

  if (canHeat && swHeat && !canFill)
  {
    digitalWrite(heater, HIGH); // Start Heater
    digitalWrite(ledC, HIGH);
  }
  else
  {
    digitalWrite(heater, LOW); // Stop Heater
    digitalWrite(ledC, LOW);
  }

  if (canFill && !digitalRead(door) && digitalRead(overSensor))
  {
    digitalWrite(pump, HIGH); // Start Pump
  }
  else
  {
    digitalWrite(pump, LOW); // Stop Pump
  }
}

/********** TIMER OVERFLOW INTERRUPT ISR **********/
ISR(TIMER1_OVF_vect)
{
  TCNT1 = 15000; // reset timer for next loops

  // take ADC readings from sensors
  heatAdc = analogRead(heatSensor);
  coolAdc = analogRead(coolSensor);
  floatAdc = analogRead(floatSensor);
  switchesAdc = analogRead(switches);

  // set heatSensor readings that can make start/stop heater
  if (heatAdc > 800)
    canHeat = false;
  else if (heatAdc < 700 && heatAdc > 150)
    canHeat = true;

  // set coolSensor readings that can make start/stop cooler
  if (coolAdc < 100)
    canCool = false;
  else if (coolAdc > 150 && coolAdc < 300)
    canCool = true;

  // set switches readings to see user desire to heat or cool
  if (switchesAdc < 310 && switchesAdc > 210) // user wants to heat
  {
    swHeat = true;
    swCool = false;
  }
  else if (switchesAdc < 200 && switchesAdc > 150) // user wants to cool
  {
    swHeat = false;
    swCool = true;
  }
  else if (switchesAdc < 140 && switchesAdc > 100) // user wants to heat and cool
  {
    swHeat = true;
    swCool = true;
  }
  else // user doesn't want to heat or cool
  {
    swHeat = false;
    swCool = false;
  }

  // set floatSensor readings to know the tank level
  if (floatAdc > 250 && floatAdc < 300)
    canFill = true;
  else
    canFill = false;

  verbose(); // calls a function to print the sensors readings to the serial console
}

/********** SERIAL CONSOLE DATA SHOW **********/
int verbose()
{
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
  Serial.print(digitalRead(overSensor));
  Serial.println(" overFilled");
  Serial.println();
  Serial.print(digitalRead(door));
  Serial.println(" door");
  Serial.println();

  if (canFill)
  {
    Serial.println("Can Fill");
    Serial.println();
  }
  else
  {
    Serial.println("Can't Fill");
    Serial.println();
  }

  if (canCool)
  {
    Serial.println("Can Cool");
    Serial.println();
  }
  else
  {
    Serial.println("Can't Cool");
    Serial.println();
  }

  if (canHeat)
  {
    Serial.println("Can Heat");
    Serial.println();
  }
  else
  {
    Serial.println("Can't Heat");
    Serial.println();
  }
}
