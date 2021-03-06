/*

*/
#include "timing_V1.ino";
#include "stroke_per_min.ino";
#include "changeInAngle.ino";
#include "Smoothing_copy.ino";
#include "accelerometer-test.ino";

//Timing variables
float prev_time_timing;

//Gyro variables
float intervalAverage_Gyro; //the difference between 2 strokes
float prevtime_Gyro[10];

//Smoothing variables
float smooth_angular_velocity = 0;
const int numReadings = 10;
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0; 

//Strokes variables
float interval_strokes, current_time, stroke_rate; //the difference between 2 strokes
float impulse = 1000; //the threshold at which something will be considered a stroke
float strokerate[3];
float prevtime_strokes[3];
float total_strokes = 0;

//Main variables
boolean on_or_off;
float angular_velocity;
float smooth_angular_velocity;
float changeInAngle;
float accelerations;
float smooth_accelarations;

void setup() {
    //timing
    //accelorometer data
    //gyro data
    //Smoother
    //stroke per min
    //change in angle
}

void loop() {
    on_or_off = timing(delay_input);
    angular_velocity = run_gyrometer();
    smooth_angular_velocity = smoother(angular_velocity);
    changeInAngle = ChangeInAngle(smooth_angular_velocity);
    accelarations = run_accelerometer();
    smooth_accelarations = smoother(accelarations);
    stroke_rate = strokeRate(smooth_accelarations);
}
