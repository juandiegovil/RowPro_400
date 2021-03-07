/*
   Arduino and MPU6050 Accelerometer and Gyroscope Sensor Tutorial
   by Dejan, https://howtomechatronics.com
*/
#include <Arduino_LSM9DS1.h>

int basicRoll(float AccX, float AccY, float AccZ, float GyroX, float GyroY, float GyroZ);
/*void calculate_IMU_error();
//float AccX,float AccY,float AccZ,float GyroX,float GyroY,float GyroZ
float AccX, AccY, AccZ, GyroX, GyroY, GyroZ;
float accAngleX, accAngleY, gyroAngleX, gyroAngleY, gyroAngleZ;
float roll, pitch, yaw;
float AccErrorX = 0;
float AccErrorY = 0; 
float GyroErrorX = 0; 
float GyroErrorY=0; 
float GyroErrorZ =0;
float elapsedTime, currentTime, previousTime;
int c = 0;
int angle;

void setup() {
  Serial.begin(19200);
  while (!Serial);
  Serial.println("Started");

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
  Serial.print(IMU.accelerationSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Acceleration in G's");
  Serial.println("X\tY\tZ");
  //calculate_IMU_error();
  delay(20);
} */

 /* Wire.begin();                      // Initialize comunication
  Wire.beginTransmission(MPU);       // Start communication with MPU6050 // MPU=0x68
  Wire.write(0x6B);                  // Talk to the register 6B
  Wire.write(0x00);                  // Make reset - place a 0 into the 6B register
  Wire.endTransmission(true);        //end the transmission*/
  /*
  // Configure Accelerometer Sensitivity - Full Scale Range (default +/- 2g)
  Wire.beginTransmission(MPU);
  Wire.write(0x1C);                  //Talk to the ACCEL_CONFIG register (1C hex)
  Wire.write(0x10);                  //Set the register bits as 00010000 (+/- 8g full scale range)
  Wire.endTransmission(true);
  // Configure Gyro Sensitivity - Full Scale Range (default +/- 250deg/s)
  Wire.beginTransmission(MPU);
  Wire.write(0x1B);                   // Talk to the GYRO_CONFIG register (1B hex)
  Wire.write(0x10);                   // Set the register bits as 00010000 (1000deg/s full scale)
  Wire.endTransmission(true);
  delay(20);
  */
  // Call this function if you need to get the IMU error values for your module

//void loop() {
int basicRoll(float AccX,float AccY,float AccZ,float GyroX,float GyroY,float GyroZ) {

   /*
   if ((IMU.accelerationAvailable())&& (IMU.gyroscopeAvailable()))
   {
    IMU.readAcceleration(AccX, AccY, AccZ);
    AccX = AccX /16384.0;
    AccX = AccY /16384.0;
    AccX = AccZ /16384.0;
    
    
    IMU.readGyroscope(GyroX, GyroY, GyroZ);
    GyroX = GyroX / 8.75;
    GyroY = GyroY / 8.75;
    GyroZ = GyroZ / 8.75;

    if ( axis == 0) {
     // Calculating the Pitch angle (rotation around Y-axis)
     angle = atan(-1 * AcX / sqrt(pow(AcY, 2) + pow(AcZ, 2))) * 180 / PI;
     lcd.setCursor(0, 0);
     lcd.print("Pitch");
    }
      else if (axis == 1) {*/
    
   // Calculating the Roll angle (rotation around X-axis)
   int angle;
   angle = atan(-1 * AccY / sqrt(pow(AccX, 2) + pow(AccZ, 2))) * 180 / PI;
   Serial.print("Roll ");
   Serial.print("Angle: ");
   Serial.print(abs(angle));
   Serial.print("     ");
   Serial.print("deg");
   delay(50);
   return angle;
    
    /*Serial.print(" Acc and Gyro Values");
    Serial.print(AccX);
    Serial.print('\t');
    Serial.print(AccY);
    Serial.print('\t');
    Serial.println(AccZ);
  
    Serial.print(GyroX);
    Serial.print('\t');
    Serial.print(GyroY);
    Serial.print('\t');
    Serial.println(GyroZ);
 // } 

// === Read acceleromter data === //
  Wire.beginTransmission(MPU);
  Wire.write(0x3B); // Start with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
  //For a range of +-2g, we need to divide the raw values by 16384, according to the datasheet
  AccX = (Wire.read() << 8 | Wire.read()) / 16384.0; // X-axis value
  AccY = (Wire.read() << 8 | Wire.read()) / 16384.0; // Y-axis value
  AccZ = (Wire.read() << 8 | Wire.read()) / 16384.0; // Z-axis value
  // Calculating Roll and Pitch from the accelerometer data
   
  accAngleX = (atan(AccY / sqrt(pow(AccX, 2) + pow(AccZ, 2))) * 180 / PI) - 0.58; // AccErrorX ~(0.58) See the calculate_IMU_error()custom function for more details
  accAngleY = (atan(-1 * AccX / sqrt(pow(AccY, 2) + pow(AccZ, 2))) * 180 / PI) + 1.58; // AccErrorY ~(-1.58)

  // === Read gyroscope data === //
  previousTime = currentTime;        // Previous time is stored before the actual time read
  currentTime = millis();            // Current time actual time read
  elapsedTime = (currentTime - previousTime) / 1000; // Divide by 1000 to get seconds
  Wire.beginTransmission(MPU);
  Wire.write(0x43); // Gyro data first register address 0x43
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true); // Read 4 registers total, each axis value is stored in 2 registers
  GyroX = (Wire.read() << 8 | Wire.read()) / 131.0; // For a 250deg/s range we have to divide first the raw value by 131.0, according to the datasheet
  GyroY = (Wire.read() << 8 | Wire.read()) / 131.0;
  GyroZ = (Wire.read() << 8 | Wire.read()) / 131.0;
  // Correct the outputs with the calculated error values
  GyroX = GyroX + 0.56; // GyroErrorX ~(-0.56)
  GyroY = GyroY - 2; // GyroErrorY ~(2)
  GyroZ = GyroZ + 0.79; // GyroErrorZ ~ (-0.8)

  // Currently the raw values are in degrees per seconds, deg/s, so we need to multiply by sendonds (s) to get the angle in degrees
  gyroAngleX = gyroAngleX + GyroX * elapsedTime; // deg/s * s = deg
  gyroAngleY = gyroAngleY + GyroY * elapsedTime;
  yaw =  yaw + GyroZ * elapsedTime;
//Serial.print(" GyroAngleX: ");
//Serial.println(GyroAngleX: );



  // Complementary filter - combine acceleromter and gyro angle values
  roll = 0.96 * gyroAngleX + 0.04 * accAngleX;
  pitch = 0.96 * gyroAngleY + 0.04 * accAngleY;
  
  // Print the values on the serial monitor
  Serial.println("Roll/Pitch/Yaw");
  Serial.print(roll);
  Serial.print("/");
  Serial.print(pitch);
  Serial.print("/");
  Serial.println(yaw);
  delay(100); */
}

/*
void calculate_IMU_error() {
  //float accAngleX, accAngleY, gyroAngleX, gyroAngleY, gyroAngleZ;
  //float roll, pitch, yaw;
  //float AccErrorX, AccErrorY, GyroErrorX, GyroErrorY, GyroErrorZ;
  
   //if ((IMU.accelerationAvailable())&& (IMU.gyroscopeAvailable()))
   //{
    IMU.readAcceleration(AccX, AccY, AccZ);
    AccX = AccX /16384.0;
    AccX = AccY /16384.0;
    AccX = AccZ /16384.0;
    

    
    IMU.readGyroscope(GyroX, GyroY, GyroZ);
    GyroX = GyroX / 8.75;
    GyroY = GyroY / 8.75;
    GyroZ = GyroZ / 8.75;

   
    Serial.print(" Calibrate Acc and Gyro Values");
    Serial.print(AccX);
    Serial.print('\t');
    Serial.print(AccY);
    Serial.print('\t');
    Serial.println(AccZ);
  
    Serial.print(GyroX);
    Serial.print('\t');
    Serial.print(GyroY);
    Serial.print('\t');
    Serial.println(GyroZ);
 // } 
  

  
  // We can call this funtion in the setup section to calculate the accelerometer and gyro data error. From here we will get the error values used in the above equations printed on the Serial Monitor.
  // Note that we should place the IMU flat in order to get the proper values, so that we then can the correct values
  // Read accelerometer values 200 times
  while (c < 200) {
    Wire.beginTransmission(MPU);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 6, true);
    AccX = (Wire.read() << 8 | Wire.read()) / 16384.0 ;
    AccY = (Wire.read() << 8 | Wire.read()) / 16384.0 ;
    AccZ = (Wire.read() << 8 | Wire.read()) / 16384.0 ;
    // Sum all readings
    AccErrorX = AccErrorX + ((atan((AccY) / sqrt(pow((AccX), 2) + pow((AccZ), 2))) * 180 / PI));
    AccErrorY = AccErrorY + ((atan(-1 * (AccX) / sqrt(pow((AccY), 2) + pow((AccZ), 2))) * 180 / PI));
    c++;
  }
  //Divide the sum by 200 to get the error value
  AccErrorX = AccErrorX / 200;
  AccErrorY = AccErrorY / 200;
  c = 0;
  // Read gyro values 200 times
  while (c < 200) {
    Wire.beginTransmission(MPU);
    Wire.write(0x43);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 6, true);
    GyroX = Wire.read() << 8 | Wire.read();
    GyroY = Wire.read() << 8 | Wire.read();
    GyroZ = Wire.read() << 8 | Wire.read();
    // Sum all readings
    GyroErrorX = GyroErrorX + (GyroX / 131.0);
    GyroErrorY = GyroErrorY + (GyroY / 131.0);
    GyroErrorZ = GyroErrorZ + (GyroZ / 131.0);
    c++;
  }
  //Divide the sum by 200 to get the error value
  GyroErrorX = GyroErrorX / 200;
  GyroErrorY = GyroErrorY / 200;
  GyroErrorZ = GyroErrorZ / 200;
  // Print the error values on the Serial Monitor
  Serial.print("AccErrorX: ");
  Serial.println(AccErrorX);
  Serial.print("AccErrorY: ");
  Serial.println(AccErrorY);
  Serial.print("GyroErrorX: ");
  Serial.println(GyroErrorX);
  Serial.print("GyroErrorY: ");
  Serial.println(GyroErrorY);
  Serial.print("GyroErrorZ: ");
  Serial.println(GyroErrorZ);
}*/
