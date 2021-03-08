
float strokeRate (float acceleration, float impulse, float prevtimeStrokes[], int strokeCount);

float strokeRate (float acceleration, float impulse, float prevtimeStrokes[], int strokeCount) 
{ 
  //input is the value from accelerometer
  //calculation one stroke
  float intervalStrokes;
  
  if (acceleration >= impulse)
  {
    //current_time = millis();
  
    strokeCount++;
 
    
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
  
  } 
  return (60/(intervalStrokes/1000));
}
