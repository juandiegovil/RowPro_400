#include <Arduino_LSM6DS3.h>
#include <MadgwickAHRS.h>
#include <Math.h>

float pitchFilteredOld;
Madgwick filter;
const float sensorRate = 104.00;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  if(!IMU.begin())  {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
  filter.begin(sensorRate);
  Serial.println("Setup complete!");
}  

void loop() {
  float xAcc, yAcc, zAcc;
  float xGyro, yGyro, zGyro;
  float roll, pitch, heading;
  if(IMU.accelerationAvailable() && IMU.gyroscopeAvailable()){
    IMU.readAcceleration(xAcc, yAcc, zAcc);
    IMU.readGyroscope(xGyro, yGyro, zGyro); 
    filter.updateIMU(xGyro, yGyro, zGyro, xAcc, yAcc, zAcc);
    pitch = filter.getPitch();
    float pitchFiltered = 0.1 * pitch + 0.9 * pitchFilteredOld; // low pass filter
    Serial.println("pitch: " + String(pitchFiltered));
    pitchFilteredOld = pitchFiltered;
  }
}
