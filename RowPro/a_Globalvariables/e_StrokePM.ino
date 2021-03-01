
void setup() {
    
}

//input is the value from accelerometer
//long prev_time=millis(); //the intial time on which all times will be taken
long interval_strokes, current_time, stroke_rate; //the difference between 2 strokes
long impulse = 1000; //the threshold at which something will be considered a stroke
long strokerate[3];
long prevtime_strokes[3];
long total_strokes = 0;

long stroke_rate (long input) {
  //input is the value from accelerometer
  //calculation one stroke
  if (input >= impulse){
    for (int i = 0; i < sizeof(prevtime_strokes) - 1; i++){
      prevtime_strokes[i] = prevtime_strokes[i + 1];
    }
    current_time = millis();
    prevtime_strokes[sizeof(prevtime_strokes) - 1] = current_time; 
    interval = prevtime_strokes[sizeof(prevtime_strokes) - 1]-prevtime_strokes[sizeof(prevtime_strokes) - 2]; 
    //interval=current_time-prev_time;
    stroke_rate = 60/(interval_strokes*1000);
    return stroke_rate;
  } 
  return total_strokes;
}


//Function to collect the 3 most recent stroke rates average them

long average_stroke_rate(long input){
  //long strokerate[2];
  //long prevtime[2];
  //long total=0;
  //int i=0;
  long temp,time_temp;
  int i = 0;
  //for (int i = 0; i <= 3; i++){
  while (i <= 3){
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
  return total;
}
