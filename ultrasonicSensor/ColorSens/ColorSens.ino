// COLOR SENSOR/////////////////
#define S0_L 0         // left motor
#define S1_L 1
#define S2_L 2 
#define S3_L 3

#define S0_R 4         // right motor
#define S1_R 5
#define S2_R 6 
#define S3_R 7

#define sensorOut_L A5
#define sensorOut_R A4
int frequency = 0;

void setup() {
  pinMode(S0_L, OUTPUT);
  pinMode(S1_L, OUTPUT);
  pinMode(S2_L, OUTPUT);
  pinMode(S3_L, OUTPUT);
  pinMode(sensorOut_L, INPUT);

  pinMode(S0_R, OUTPUT);
  pinMode(S1_R, OUTPUT);
  pinMode(S2_R, OUTPUT);
  pinMode(S3_R, OUTPUT);
  pinMode(sensorOut_R, INPUT);
  
  // Setting frequency-scaling to 20%
  digitalWrite(S0_L,HIGH);
  digitalWrite(S1_L,LOW);

  digitalWrite(S0_R,HIGH);
  digitalWrite(S1_R,LOW);
  
  Serial.begin(9600);
}

void colorSens(int S0, int S1, int S2, int S3, int sensorOut, char* name)
{
  // Setting red filtered photodiodes to be read
  Serial.print(name);
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(100);
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(100);
  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.println("  ");
  delay(100);
}


void loop() {
  colorSens(S0_L, S1_L, S2_L, S3_L, sensorOut_L, "LEFT");
  colorSens(S0_R, S1_R, S2_R, S3_R, sensorOut_R, "RIGHT");
  Serial.println("");  
}
