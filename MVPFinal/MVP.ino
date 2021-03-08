
#include <Arduino_LSM9DS1.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd (0x27, 20, 4);
float strokeRate (float acceleration, float impulse, float prevtimeStrokes[], int strokeCount);

void readAccAndGyro();
void printOutput();
void displayOutput();


//Strokes variables
float stroke_Rate, smoothStrokeRate; //the difference between 2 strokes
float impulse = 1.0; //the threshold at which something will be considered a stroke
float prevtimeStrokes[3];
int strokeCount = 0;

//Level variables
int rollAngle;


//Main variables

float AccX, AccY, AccZ;

void setup() 
  {
    Serial.begin(19200);
    while (!Serial);
     Serial.println("Started");
  
     

    if (!IMU.begin()) 
    {
        Serial.println("Failed to initialize IMU!");
        while (1);
    }
    delay(20);
    
    prevtimeStrokes[0] = 6000;
    prevtimeStrokes[1] = 3000;
    prevtimeStrokes[2] = 0;
    
    //lcd.begin();
    //lcd.clear();
    /*lcd.setCursor(0, 0);
    lcd.print("ROW PRO 2.0");
    lcd.setCursor(0, 1);
    lcd.print("Stroke Rate:");
    lcd.setCursor(0, 2);
    lcd.print("Stroke Count:");
    lcd.setCursor(0, 3);
    lcd.print("Roll Angle:");
    */
}

void loop() 
{
   
    readAccAndGyro();
    
    rollAngle = basicRoll(AccX, AccY, AccY);
   
    stroke_Rate = strokeRate(AccX, impulse, prevtimeStrokes, strokeCount);
    
    printOutput();
    
    displayOutput();
    //on_or_off = timing(delay_input);
}

void readAccAndGyro()
{
  
    if (IMU.accelerationAvailable())
    {
        IMU.readAcceleration(AccX, AccY, AccZ);
        
    }
}

void printOutput() {
    Serial.print("Roll Angle: ");
    Serial.print(abs(rollAngle));
    Serial.print("  deg");
    Serial.println('\t');

    Serial.print("Stroke Count:  ");
    Serial.println(strokeCount);
    Serial.print('\t');
    Serial.print ("prevtimeStrokes array:   ");
    Serial.print(prevtimeStrokes[0]);
    Serial.print ("  ");
    Serial.print(prevtimeStrokes[1]);
    Serial.print ("  ");
    Serial.print(prevtimeStrokes[2]);
    //Serial.print('\t');
    //Serial.print("Time between stroke in ms:  ");
    //Serial.print(intervalStrokes);
    Serial.print('\t');
    Serial.print("Stroke Rate:  ");
    Serial.print(stroke_Rate);
}

void displayOutput() {
    lcd.setCursor(16, 1);
    lcd.print(stroke_Rate);
    
    lcd.setCursor(15, 2);
    lcd.print(strokeCount);
    
    lcd.setCursor(15, 3);
    lcd.print(rollAngle);
}
