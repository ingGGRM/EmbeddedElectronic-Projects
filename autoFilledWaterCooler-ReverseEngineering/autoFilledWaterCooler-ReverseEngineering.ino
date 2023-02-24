void setup()
{
	/************ INPUT DECLARATIONS ************/
	int heatSensor = A0;  // FLOAT
	int coolSensor = A1;  // TR-C
	int floatSensor = A2; // TR-H
	int switches = A3;	  // SW-H&C

	int overSensor = A4; // FLOAT-P
	int door = A5;		 // CN2

	pinMode(heatSensor, INPUT);	 // ANALOG
	pinMode(coolSensor, INPUT);	 // ANALOG
	pinMode(floatSensor, INPUT); // ANALOG
	pinMode(switches, INPUT);	 // ANALOG
	pinMode(overSensor, INPUT);	 // DIGITAL
	pinMode(door, INPUT);		 // DIGITAL
	/********************************************/

	/************ OUTPUT DECLARATIONS ***********/
	int ledA = 2;	// L1
	int ledB = 3;	// L2
	int ledC = 4;	// L3
	int ledD = 5;	// L4
	int pump = 6;	// PUMP
	int heater = 8; // HEAT
	int cooler = 9; // COOL

	pinMode(ledA, OUTPUT);
	pinMode(ledB, OUTPUT);
	pinMode(ledC, OUTPUT);
	pinMode(ledD, OUTPUT);
	pinMode(pump, OUTPUT);
	pinMode(heater, OUTPUT);
	pinMode(cooler, OUTPUT);

	// set initial outputs state
	digitalWrite(ledA, LOW);
	digitalWrite(ledB, LOW);
	digitalWrite(ledC, LOW);
	digitalWrite(ledD, LOW);
	digitalWrite(pump, LOW);
	digitalWrite(heater, LOW);
	digitalWrite(cooler, LOW);
	/********************************************/
}

void loop()
{
	// put your main code here, to run repeatedly:
}
