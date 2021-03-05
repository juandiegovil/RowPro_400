
//#include <LiquidCrystal_I2C.h>
#include <Arduino_LSM9DS1.h>
//#include <Wire.h> 
//LiquidCrystal_I2C lcd(0x27, 20, 4);
float stroke_rate (float input);

//Timing variables
float prev_time_timing;

//Gyro variables
//float intervalAverage_Gyro; //the difference between 2 strokes
//float prevtime_Gyro[10];

/*
//Smoothing variables
long smooth_angular_velocity = 0;
const int numReadings = 10;
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0; 
*/

//Strokes variables
float interval_strokes, current_time, SR; //the difference between 2 strokes
float impulse = 2; //the threshold at which something will be considered a stroke
float strokerate[3];

float prevtime_strokes[3];

float total_strokes = 0;

/*
//Main variables
boolean on_or_off;
long angular_velocity;
long smooth_angular_velocity;
long changeInAngle;
long accelerations;
long smooth_accelarations;
*/

void setup() {
  
  Serial.begin(57600);
  while (!Serial);
  Serial.println("Started");

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
  prevtime_strokes[0] = 100;
  prevtime_strokes[1] = 200;
  prevtime_strokes[2] = 300;
  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Acceleration in G's");
  Serial.println("X\tY\tZ");
}
void loop() {

float x, y, z;


if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);
    Serial.print(x);
    Serial.print('\t');
    Serial.print(y);
    Serial.print('\t');
    Serial.println(z);

    stroke_rate(x);
    
    
  } 

}

float stroke_rate (float input) {
  //input is the value from accelerometer
  //calculation one stroke
  if (input >= impulse){
    Serial.print("Stroke Rate: ");
    Serial.println ();
    Serial.print ("current_time   ");
    Serial.println(current_time);
    Serial.print("interval_strokes:   ");
    Serial.println(interval_strokes);
   
    Serial.print("strokerate array:   ");
    Serial.println(strokerate[0]);
    Serial.println(strokerate[1]);
    Serial.println(strokerate[2]);
    Serial.print ("prevtime_strokes array:   ");
    Serial.println(prevtime_strokes[0]);
    Serial.println(prevtime_strokes[1]);
    Serial.println(prevtime_strokes[2]);
    Serial.print("total_strokes:   ");
    Serial.println(total_strokes);
    Serial.println("check1");
    Serial.println(input);
    for (int i = 0; i < 2; i++){
     
      prevtime_strokes[i] = prevtime_strokes[i + 1];
      delay(9);
      Serial.println("check2");
    }
    Serial.println("check3");
    current_time = millis();
    Serial.println("check4");
    prevtime_strokes[2] = current_time; 
    Serial.println("check5");
    interval_strokes = prevtime_strokes[2] - prevtime_strokes[1]; 
    Serial.println("check6");
    //interval=current_time-prev_time;
    
    SR = 60/(interval_strokes/1000);
    Serial.println("check7");
    Serial.print("Stroke Rate: ");
    Serial.println ();
    Serial.print ("current_time   ");
    Serial.println(current_time);
    Serial.print("interval_strokes:   ");
    Serial.println(interval_strokes);
    Serial.print("SR:  ");
    Serial.println(SR);
    Serial.print("strokerate array:   ");
    Serial.println(strokerate[0]);
    Serial.println(strokerate[1]);
    Serial.println(strokerate[2]);
    Serial.print ("prevtime_strokes array:   ");
    Serial.println(prevtime_strokes[0]);
    Serial.println(prevtime_strokes[1]);
    Serial.println(prevtime_strokes[2]);
    Serial.print("total_strokes:   ");
    Serial.println(total_strokes);
    return SR;
   
  } 
   Serial.println("check8");
  return total_strokes;
}

//Function to collect the 3 most recent stroke rates average them

float average_stroke_rate(float input){
  //long strokerate[2];
  //long prevtime[2];
  //long total=0;
  //int i=0;
  float temp,time_temp;
  int i = 0;
  //for (int i = 0; i <= 3; i++){
  while (i < 3){
    //time_temp=millis();
    if (input >= impulse){
      temp = stroke_rate(input);
      strokerate[i] = temp;
      i++;
    }
    //if(temp != 0){
      //strokerate[i] = temp;
      //prevtime[i] = time_temp;
    //}
  }
  
  total_strokes = (strokerate[0] + strokerate[1] + strokerate[2])/3;
  return total_strokes;
}
