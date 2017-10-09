#include "ColorSens.h"
#include "UltraSonic.h"
#include "Monitor.h"
#include "Sumobot.h"

void setup()
{
    digitalWrite(13,LOW); //no init test
    colorSetup();
    sonicSetup();
    monitorSetup();
    delay(INITIAL_DELAY);
}

void loop()
{
  L_Forw(MAX_SPEED);
  R_Forw(MAX_SPEED);
}
