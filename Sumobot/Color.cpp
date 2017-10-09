// COLOR SENSOR/////////////////
#include "Color.h"
#include "Sumobot.h"

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
        Serial.print(name + " \t");
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
