

void setup()
{
  lcd.begin();
  if (!IMU.begin())
  {
    Serial.println("Failed to initialize IMU!");
    exit(1);
  }
}

void loop()
{
  float x, y, z, delta = 0.05;

  if (IMU.accelerationAvailable())
  {
    IMU.readAcceleration(x, y, z);
    Serial.println(y);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Angle of Boat Lean");
    lcd.setCursor(0,1);
    lcd.print(abs(y*90));
    lcd.setCursor(8,1);
    lcd.print("Degrees");
    
    if(y <= delta && y >= -delta)
      Serial.println("flat");
      
        
    else if(y > delta && y < 1 - delta)
    {
      Serial.println("tilted to the left");
      lcd.setCursor(0,2);
      lcd.print("Leaning to Port");
    }
    else if(y >= 1 - delta)
      Serial.println("left");
      
    else if(y < -delta && y > delta - 1)
    {
      Serial.println("tilted to the right");
      lcd.setCursor(0,2);
      lcd.print("Leaning to Starboard");
    } 
    else
      Serial.println("right");
  }

  delay(150);
}
