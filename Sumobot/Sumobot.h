#ifndef SUMO_H_INCLUDED
#define SUMO_H_INCLUDED

//SUMO
#define DEBUG true
#define SERIAL 9600
#define INITIAL_DELAY 2000

//COLOR
#define S0_L 0         // left sensor
#define S1_L 1
#define S2_L 2
#define S3_L 3

#define S0_R 13         // right sensor
#define S1_R 5
#define S2_R 6
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
#define IN1 10
#define IN2 11
#define IN3 12
#define IN4 4

#define MAX_SPEED 150 //from 0 - 255
#define MIN_SPEED 0
/// USE 5V GND

#endif // SUMO_H_INCLUDED
