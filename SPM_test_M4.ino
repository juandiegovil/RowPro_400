//#include <LiquidCrystal_I2C.h>
#include <Arduino_LSM9DS1.h>
//#include <Wire.h> 
//LiquidCrystal_I2C lcd(0x27, 20, 4);
float stroke_rate (float input);

//Timing variables
//float prev_time_timing;

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


//Strokes variables
float interval_strokes, current_time, StrokeRate; //the difference between 2 strokes
float impulse = 1.0; //the threshold at which something will be considered a stroke
float prevtime_strokes[3];
int stroke_count = 0;

//Main variables
boolean on_or_off;
long angular_velocity;
long smooth_angular_velocity;
long changeInAngle;
long accelerations;
long smooth_accelarations;


void setup() 
{
  lcd.begin();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ROW PRO 2.0");
  lcd.setCursor(0, 1);
  lcd.print("Stroke per Min:");// 15 
  lcd.setCursor(0,2);
  lcd.print("Stroke Count:"); // 13
  lcd.setCursor(0,3);
  lcd.print("Session Time:"); //13
  Serial.begin(57600);
  while (!Serial);
  Serial.println("Started");
  stroke_count = 0;
  if (!IMU.begin()) 
  {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
  prevtime_strokes[0] = 6000;
  prevtime_strokes[1] = 3000;
  prevtime_strokes[2] = 0;
  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Acceleration in G's");
  Serial.println("X\tY\tZ");
}

void loop() 
{
  float x, y, z;
  lcd.setCursor(15, 3);
  lcd.print(millis()/1000);
    
  if (IMU.accelerationAvailable()) 
  {
    IMU.readAcceleration(x, y, z);
    Serial.print(x);
    Serial.print('\t');
    Serial.print(y);
    Serial.print('\t');
    Serial.println(z);
    stroke_rate(x);
    delay(50);
  } 

}*/

float strokeRate(float acceleration, float impulse, float prevtimeStrokes, int strokeCount) 
{ 
  //input is the value from accelerometer
  //calculation one stroke
  float intervalStrokes;
  
  if (acceleration >= impulse)
  {
    //current_time = millis();
    
    strokeCount++;
    /*Serial.print("Stroke Count:  ");
    Serial.println(strokeCount);
    lcd.setCursor(15, 2);
    lcd.print(strokeCount);
    Serial.print ("currentTime   ");*/
    //Serial.println(current_time);
    //Serial.println("check1");
    
    for (int i = 1; i >=0; i--)
    {
      prevtimeStrokes[i+1] = prevtimeStrokes[i];
      //Serial.println("in for loop");
    }
    //Serial.println("out of for loop");
    prevtimeStrokes[0] = millis();
    //prevtime_strokes[0] = current_time; //load current time into array [0]
    /*Serial.print ("prevtimeStrokes array:   ");
    Serial.println(prevtimeStrokes[0]);
    Serial.println(prevtimeStrokes[1]);
    Serial.println(prevtimeStrokes[2]);*/
    intervalStrokes = (prevtimeStrokes[0] - prevtimeStrokes[2])/2; // total time between strokes 1-3 divided by 2
    /*Serial.print("time between stroke in ms:  ");
    Serial.println(intervalStrokes);
    //strokeRate = 60/(interval_strokes/1000); 
    lcd.setCursor(16, 1);
    lcd.print(strokeRate);
    Serial.print("Stroke Rate:  "); */
    //Serial.println(strokeRate);
  } 
  return (60/(intervalStrokes/1000));
}
