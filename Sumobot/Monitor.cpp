#include "Monitor.h"
#include "Sumobot.h"

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

///
void monitorRun()
{

}

