#define DEBUG true
#define SERIAL 9600
#define INITIAL_DELAY 1000

//COLOR
#define S0_L 0          // left sensor
#define S1_L 1
#define S2_L 2
#define S3_L 3

#define S0_R 13         // right sensor
#define S1_R 5
#define S2_R 4
#define S3_R 7

#define sensorOut_L A5
#define sensorOut_R A4
/// USE 5V, 3.5V, GND

//SONIC
#define TRIG_PIN 12
#define ECHO_PIN 13
#define TIME_OUT 3000
/// USE 5V, GND

//MONITOR
#define IN1 5
#define IN2 6
#define IN3 9
#define IN4 10

#define MAX_SPEED 140 //from 0 - 255
#define MIN_SPEED 0
const int L_MAX_SPEED = MAX_SPEED;
const int R_MAX_SPEED = MAX_SPEED * 0.605;

//Color
void colorSetup()
{
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
}

int colorSens(int S0, int S1, int S2, int S3, int sensorOut)
{
    int frequency = 0;
    int sum = 0;
    delayMicroseconds(100);
    digitalWrite(S2,LOW);
    digitalWrite(S3,LOW);

    frequency = pulseIn(sensorOut, LOW);
    sum+=frequency;
 
    //delay(100);
    delayMicroseconds(100);    
    digitalWrite(S2,HIGH);
    digitalWrite(S3,HIGH);
   
    frequency = pulseIn(sensorOut, LOW);
    sum+=frequency;
    
    //delay(100);
    delayMicroseconds(100);    
    digitalWrite(S2,LOW);
    digitalWrite(S3,HIGH);
    
    frequency = pulseIn(sensorOut, LOW);
    sum+=frequency;
    
    //delay(100);
    return sum/3;
}

int getColor_L()
{
  return colorSens(S0_L, S1_L, S2_L, S3_L, sensorOut_L);
}
int getColor_R()
{
  return colorSens(S0_R, S1_R, S2_R, S3_R, sensorOut_R);
}

//Sonic
float GetDistance()
{
    long duration, distanceCm;

    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH, TIME_OUT);

    // convert to distance
    distanceCm = duration / 29.1 / 2;

    return distanceCm;
}

void sonicSetup()
{
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
}

//Monitor
void monitorSetup()
{
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
}
/// Left = IN1 IN2
/// Right = IN3 IN4

/// Stop module
void L_Stop()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
}

void R_Stop()
{
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}
/// Forward module
void L_Forw(int speed)
{
    speed = constrain(speed, MIN_SPEED, MAX_SPEED);
    digitalWrite(IN1, HIGH);
    analogWrite(IN2, 255 - speed);
}

void R_Forw(int speed)
{
    speed = constrain(speed, MIN_SPEED, MAX_SPEED);
    digitalWrite(IN3, HIGH);
    analogWrite(IN4, 255 - speed);
}
/// Backward module
void L_Back(int speed)
{
    speed = constrain(speed, MIN_SPEED, MAX_SPEED);
    digitalWrite(IN1, LOW);
    analogWrite(IN2, speed);
}

void R_Back(int speed)
{
    speed = constrain(speed, MIN_SPEED, MAX_SPEED);
    digitalWrite(IN3, LOW);
    analogWrite(IN4, speed);
}

/// Battle function
void spin()
{    
    L_Back(L_MAX_SPEED * 0.6);
    R_Forw(R_MAX_SPEED * 0.6);
    delay(700);
}
void attack()
{    
    L_Forw(L_MAX_SPEED);
    R_Forw(R_MAX_SPEED); 
    delay(30);   
}
void safeMode()
{
    L_Back(L_MAX_SPEED*0.8);
    R_Back(R_MAX_SPEED*0.8);
    delay(700);
}

/// Main program
void setup()
{
    Serial.begin(SERIAL);
    colorSetup();
    sonicSetup();
    monitorSetup();
    delay(INITIAL_DELAY);
    
}

void loop()
{
    //Color test
    //colorTest();
    //Sonic test
    //Monitor Test
    int colorL = getColor_L();
    int colorR = getColor_R();
    int distance = GetDistance();
    

    if (colorL > 400 && colorR > 400)
    {
      if (distance <= 40 && distance > 2)
      {
        attack();
      }
      else
      {
        spin();
      }
    }
    else
    {
      safeMode();
    }

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.print("\t ColorL: ");
    Serial.print(colorL);
    Serial.print("\t ColorR: ");
    Serial.println(colorR);    
    
}

