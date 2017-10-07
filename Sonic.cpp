#include "Sonic.h"
#include "Sumobot.h"

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

