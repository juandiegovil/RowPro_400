
#include <LiquidCrystal_I2C.h>
#include <Arduino_LSM9DS1.h>
#include <Wire.h> 
LiquidCrystal_I2C lcd(0x27, 20, 4);

//Timing variables
long prev_time_timing;

//Gyro variables
long intervalAverage_Gyro; //the difference between 2 strokes
long prevtime_Gyro[10];

//Smoothing variables
long smooth_angular_velocity = 0;
const int numReadings = 10;
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0; 

//Strokes variables
long interval_strokes, current_time, stroke_rate; //the difference between 2 strokes
long impulse = 1000; //the threshold at which something will be considered a stroke
long strokerate[3];
long prevtime_strokes[3];
long total_strokes = 0;

//Main variables
boolean on_or_off;
long angular_velocity;
long smooth_angular_velocity;
long changeInAngle;
long accelerations;
long smooth_accelarations;
