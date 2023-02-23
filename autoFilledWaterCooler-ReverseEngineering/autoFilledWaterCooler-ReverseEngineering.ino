void setup() {
  /*/************ INPUT DECLARATIONS ************/ /*
    1. FLOAT: wather tank level (ADC)
      - Empty = 1.4V
      - Mid = 0V
      - Full 0.8V
    2. FLOAT-P: water overfilling detection
      - Normal = 5V
      - Overfilled = 0V
    3. CN2: lower room door state
      - Opened = 
      - Closed = 
    4. SW-H&C: Heater and Cooler On/Off switches (ADC)
      - None = 5V
      - Heat = 
      - Cool = 
      - Heat & Cool = 
    5. TR-H: current heat temperature (ADC)
      - Normal = 
      - Heat = 
    6. TR-C: current cooling temperature (ADC)
      - Normal = 
      - Cool = 
  /************************************************/
  int heatSensor = A0; // FLOAT
  int coolSensor = A1; // TR-C
  int floatSensor = A2; // TR-H
  int switches = A3; // SW-H&C

  int overSensor = A4; // FLOAT-P
  int door = A5; // CN2

  /*/************ OUTPUT DECLARATIONS ************/ /*
    1. CN-LED (L1, L2, L3, L4): led indicators outputs
      - Filling = 
      - Heating = 0V
      - Cooling = 0.8V
    2. PUMP: water pump On/Off
      - On = 
      - Off = 
    3. HEAT: water heater On/Off
      - On = 
      - Off = 
    4. COOL: water cooler On/Off
      - On = 
      - Off =
  /*************************************************/
  int ledA = 2; // L1
  int ledB = 3; // L2
  int ledC = 4; // L3
  int ledD = 5; // L4
  int pump = 6; // PUMP
  int heater = 8; // HEAT
  int cooler = 9; // COOL

}

void loop() {
  // put your main code here, to run repeatedly:

}
