/*
Testing
*/
long intervalAverage_Gyro; //the difference between 2 strokes
long prevtime_Gyro[10];
long smooth_angular_velocity; //This is supposed to come from the smoother taking the data from the gyro

void setup() {
  for (int i = 0; i < sizeof(prevtime_Gyro); i++){
    prevtime_Gyro[i] = 0;
  }
}

void loop() {
}

long ChangeInAngle(long input) {
  //Update the few previous times so that the 10th previous time will be on index 0 and current time on index 9
  for (int i = 0; i < sizeof(prevtime_Gyro) - 1; i++){
    prevtime_Gyro[i] = prevtime_Gyro[i + 1];
  }
  long current_time_Gyro = millis();
  prevtime_Gyro[sizeof(prevtime_Gyro) - 1] = current_time_Gyro; 
  intervalAverage_Gyro = (prevtime_Gyro[sizeof(prevtime_Gyro) - 1] - prevtime_Gyro[0])/10; 
  long changeInAngle = smooth_angular_velocity*intervalAverage_Gyro*1000*180/3.14; //"average variable has values coming from smoother"
  return changeInAngle;
}
