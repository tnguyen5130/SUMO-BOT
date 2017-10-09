#define DEBUG true
#define SERIAL 9600
#define INITIAL_DELAY 1000

//COLOR
#define S0_L 0         // left sensor
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
#define TRIG_PIN 8
#define ECHO_PIN 9
#define TIME_OUT 5000
/// USE 5V, GND

//MONITOR
#define IN1 A0
#define IN2 A1
#define IN3 A2
#define IN4 A3

#define MAX_SPEED 150 //from 0 - 255
#define MIN_SPEED 0
/// USE 5V GND

/// Variable
//color

int frequency = 0;

void colorSetup();
void colorTest();
void getColorLeft();
void getColorRight();

//Sonic

//Monitor

///Sources
//Color
void colorSetup()
{
    if (DEBUG)
        Serial.begin(SERIAL);
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

void colorSens(int S0, int S1, int S2, int S3, int sensorOut, char* name)
{
    // Setting red filtered photodiodes to be read
    if (DEBUG)
        Serial.println(name);
    digitalWrite(S2,LOW);
    digitalWrite(S3,LOW);
    // Reading the output frequency
    frequency = pulseIn(sensorOut, LOW);
    // Printing the value on the serial monitor
    if (DEBUG)
    {
        Serial.print("\tR = ");//printing name
        Serial.print(frequency);//printing RED color frequency
        Serial.print("  ");
    }

    delay(100);
    // Setting Green filtered photodiodes to be read
    digitalWrite(S2,HIGH);
    digitalWrite(S3,HIGH);
    // Reading the output frequency
    frequency = pulseIn(sensorOut, LOW);
    // Printing the value on the serial monitor
    if (DEBUG)
    {
        Serial.print("\tG = ");//printing name
        Serial.print(frequency);//printing RED color frequency
        Serial.print("  ");
    }

    delay(100);
    // Setting Blue filtered photodiodes to be read
    digitalWrite(S2,LOW);
    digitalWrite(S3,HIGH);
    // Reading the output frequency
    frequency = pulseIn(sensorOut, LOW);
    // Printing the value on the serial monitor
    if (DEBUG)
    {
       Serial.print("\tB = ");//printing name
        Serial.print(frequency);//printing RED color frequency
        Serial.println("");
    }

    delay(100);
}


void colorTest()
{
    colorSens(S0_L, S1_L, S2_L, S3_L, sensorOut_L, "LEFT");
    colorSens(S0_R, S1_R, S2_R, S3_R, sensorOut_R, "RIGHT");
    if (DEBUG)
        Serial.println("");
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
    if (DEBUG)
        Serial.begin(SERIAL);

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
}

void sonicTest()
{
    long distance = GetDistance();

    if (distance <= 0)
    {
        Serial.println("Echo time out !!");
    }
    else
    {
        Serial.print("Distance to nearest obstacle (cm): ");
        Serial.println(distance);
    }
    delay(1000);
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


/// Main program
void setup()
{
    
    colorSetup();
    sonicSetup();
    monitorSetup();
    delay(INITIAL_DELAY);
}

void loop()
{
    //Color test
    // colorTest();
    
    //Monitor Test
    
    L_Forw(MAX_SPEED);
    R_Forw(MAX_SPEED);
    delay(5000);
    L_Back(MAX_SPEED);
    R_Back(MAX_SPEED);
    delay(5000);
    
}

