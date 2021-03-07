/*

*/
#include "SPM_test_M4.ino";
#include "BasicRoll.ino";

void readAccAndGyro();
void printOutput();
void displayOutput();

//Smoothing variables
/*const int numReadings = 10;
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;*/ 

//Strokes variables
float strokeRate, smoothStrokeRate; //the difference between 2 strokes
float impulse = 1.0; //the threshold at which something will be considered a stroke
float prevtimeStrokes[3];
int strokeCount = 0;

//Level variables
int rollAngle;
int smoothRollAngle;

//Main variables
//boolean on_or_off;
float AccX, AccY, AccZ, GyroX, GyroY, GyroZ;

void setup() {
    Serial.begin(19200);
    while (!Serial);
     Serial.println("Started");

    if (!IMU.begin()) {
        Serial.println("Failed to initialize IMU!");
        while (1);
    }
    delay(20);
    
    prevtime_strokes[0] = 6000;
    prevtime_strokes[1] = 3000;
    prevtime_strokes[2] = 0;
    
    lcd.begin();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ROW PRO 2.0");
    lcd.setCursor(0, 1);
    lcd.print("Stroke Rate:");
    lcd.setCursor(0, 2);
    lcd.print("Stroke Count:");
    lcd.setCursor(0, 3);
    lcd.print("Roll Angle:");
}

void loop() {
    readAccAndGyro();
    
    rollAngle = basicRoll(AccX/16384.0, AccY/16384.0, AccZ/16384.0, GyroX/8.75, GyroY/8.75, GyroZ/8.75);
    //rollAngle = basicRoll(AccX, AccY, AccY, GyroX, GyroY, GyroZ);
    //smoothRollAngle = smoother(rollAngle);
    
    strokeRate = strokeRate(AccX, impulse, prevtimeStrokes, strokeCount);
    //smoothStrokeRate = smoother(strokeRate);
    printOutput();
    displayOutput();
    //on_or_off = timing(delay_input);
}

void readAccAndGyro() {
    if ((IMU.accelerationAvailable())&& (IMU.gyroscopeAvailable())){
        IMU.readAcceleration(AccX, AccY, AccZ);
        /*AccX = AccX /16384.0;
        AccX = AccY /16384.0;
        AccX = AccZ /16384.0;*/
        IMU.readGyroscope(GyroX, GyroY, GyroZ);
        /*GyroX = GyroX / 8.75;
        GyroY = GyroY / 8.75;
        GyroZ = GyroZ / 8.75;*/
    }
}

void printOutput() {
    Serial.print("Roll Angle: ");
    Serial.print(abs(angle));
    Serial.print("  deg");
    Serial.print('\t\t');

    Serial.print("Stroke Count:  ");
    Serial.println(strokeCount);
    Serial.print('\t');
    Serial.print ("prevtimeStrokes array:   ");
    Serial.print(prevtimeStrokes[0]);
    Serial.print ("  ");
    Serial.print(prevtimeStrokes[1]);
    Serial.print ("  ");
    Serial.print(prevtimeStrokes[2]);
    Serial.print('\t');
    Serial.print("Time between stroke in ms:  ");
    Serial.print(intervalStrokes);
    Serial.print('\t');
    Serial.print("Stroke Rate:  ");
    Serial.print(strokeRate);
}

void displayOutput() {
    lcd.setCursor(16, 1);
    lcd.print(strokeRate);
    
    lcd.setCursor(15, 2);
    lcd.print(strokeCount);
    
    lcd.setCursor(15, 3);
    lcd.print(rollAngle);
}
