int basicRoll(float AccX, float AccY, float AccZ);

int basicRoll(float AccX,float AccY,float AccZ) 
{

   // Calculating the Roll angle (rotation around X-axis)
   int angle;
   angle = atan(-1 * AccY / sqrt(pow(AccX, 2) + pow(AccZ, 2))) * 180 / PI;
   /*Serial.print("Roll ");
   Serial.print("Angle: ");
   Serial.print(abs(angle));
   Serial.print("     ");
   Serial.print("deg");*/
   delay(50);
   return angle;
    
}

