// MOTOR///////////////////////
#define IN1 A0
#define IN2 A1
#define IN3 A2
#define IN4 A3
#define MAX_SPEED 150 
#define MIN_SPEED 0
// COLOR SENSOR/////////////////
#define S0_r 1         // right motor
#define S1_r 2
#define S2_r 3 
#define S3_r 4
#define S0_l 5         // left motor
#define S1_l 6
#define S2_l 7 
#define S3_l 8
#define sensorOut A4
////////////////////////////////
///UltrasonicSensor/////////////
#define TRIG1 9              //FRONT//
#define ECHO1 10
#define TRIG2 11             //BACK//
#define ECHO2 12
//OPPONENT//////////////
#define OPPONENT 40

int STOP=0,FD=1,BD=-1;
int R1,G1,B1,C1,R2,G2,B2,C2;

void motor1Act(int act,int spd);
void motor2Act(int act,int spd);
void forward(int speed);
void backward(int speed);
void rotate(int speed);
void findEnemy();
void colorRead();
bool checkBorder();
int getDistance1();
int getDistance2();
bool findEnemy();
///////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  //Motor setup
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  
  //Ultrasonic Setup
  pinMode(TRIG1,OUTPUT);
  pinMode(ECHO1,INPUT);
  pinMode(TRIG2,OUTPUT);
  pinMode(ECHO2,INPUT);
}

void loop() {
  colorRead();
  while(checkBorder()==false)
  {
    colorRead();
    while(findEnemy()==true)
    {
      forward(MAX_SPEED);
    }
  }
  backward(50);
  delay(50);
}
/////////////////////////////////////////////////////////////////////////////////
void colorRead()
{
  digitalWrite(S2_r,HIGH);
  digitalWrite(S3_r,LOW);
  C1= pulseIn(sensorOut,LOW);

  Serial.print("C1 ");
  Serial.print(C1);
  Serial.print("\t");
  delay(50);

  digitalWrite(S2_r,LOW);
  digitalWrite(S3_r,HIGH);
  B1= pulseIn(sensorOut,LOW);

  Serial.print("B1 ");
  Serial.print(B1);
  Serial.print("\t");
  delay(50);

  digitalWrite(S2_r,LOW);
  digitalWrite(S3_r,LOW);
  R1= pulseIn(sensorOut,LOW);

  Serial.print("R1 ");
  Serial.print(R1);
  Serial.print("\t");
  delay(50);

  digitalWrite(S2_r,HIGH);
  digitalWrite(S3_r,HIGH);
  G1= pulseIn(sensorOut,LOW);

  Serial.print("G1 ");
  Serial.print(G1);
  Serial.print("\n");
  delay(50);

/////////
  digitalWrite(S2_l,HIGH);
  digitalWrite(S3_l,LOW);
  C2= pulseIn(sensorOut,LOW);

  Serial.print("C2 ");
  Serial.print(C2);
  Serial.print("\t");
  delay(50);

  digitalWrite(S2_l,LOW);
  digitalWrite(S3_l,HIGH);
  B2= pulseIn(sensorOut,LOW);

  Serial.print("B2 ");
  Serial.print(B2);
  Serial.print("\t");
  delay(50);

  digitalWrite(S2_l,LOW);
  digitalWrite(S3_l,LOW);
  R2= pulseIn(sensorOut,LOW);

  Serial.print("R2 ");
  Serial.print(R2);
  Serial.print("\t");
  delay(50);

  digitalWrite(S2_l,HIGH);
  digitalWrite(S3_l,HIGH);
  G2= pulseIn(sensorOut,LOW);

  Serial.print("G2 ");
  Serial.print(G2);
  Serial.print("\n");
  delay(50);
}

bool checkBorder()
{
  if(C1<0 || C2<0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void motor1Act(int act,int spd)
{
  spd = constrain(spd, MIN_SPEED, MAX_SPEED);
  
  switch(act)
  {
    case 0: //STOP
      digitalWrite(IN1,LOW);
      digitalWrite(IN2,LOW);
      break;
    case 1: //FORWARD
      digitalWrite(IN1,HIGH);
      analogWrite(IN2,255-spd);
      break;
    case -1: //BACKWARD
      digitalWrite(IN1,LOW);
      analogWrite(IN2,spd);
      break;
  }
}

void motor2Act(int act,int spd)
{
  spd = constrain(spd, MIN_SPEED, MAX_SPEED);
  
  switch(act)
  {
    case 0: //STOP
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,LOW);
      break;
    case 1: //FORWARD
      digitalWrite(IN3,HIGH);
      analogWrite(IN4,255-spd);
      break;
    case -1: //BACKWARD
      digitalWrite(IN3,LOW);
      analogWrite(IN4,spd);
      break;
  }
}

void forward(int speed)
{
  motor1Act(FD,speed);
  motor2Act(FD,speed);
}

void backward(int speed)
{
  motor1Act(BD,speed);
  motor2Act(BD,speed);
}

void stop()
{
  motor1Act(STOP,0)
  motor2Act(STOP,0)
}
void rotate(int speed)
{
  motor1Act(FD,speed);
  motor2Act(BD,speed);
}

bool findEnemy()
{
  stop();
  while(dis>OPPONENT)
  {
    int dis=getDistance1();
    rotate(50);
  }
  return true;
}
int getDistance1()
{
  float Time,dis;
  digitalWrite(TRIG1,LOW);
  delayMicroseconds(10);
  digitalWrite(TRIG1,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG1,LOW);

  Time=pulseIn(ECHO1,HIGH,5000);     //delay 5s
  dis = Time/29.1/2;
  //dis=Time/2/29.412;       //Convert to cm

  return dis;
}
int getDistance2()
{
  float Time,dis;
  digitalWrite(TRIG2,LOW);
  delayMicroseconds(10);
  digitalWrite(TRIG2,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG2,LOW);

  Time=pulseIn(ECHO2,HIGH,5000);     //delay 5s
  dis = Time/29.1/2;
  //dis=Time/2/29.412;       //Convert to cm

  return dis;
}
