/**/void setup() {    }long stroke_rate(long input,prev_time) {    //input is the value from accelerometer//long prev_time=millis(); //the intial time on which all times will be takenlong interval,current_time,stroke_rate; //the difference between 2 strokeslong impulse=1000; //the threshold at which something will be considered a stroke //calculation one strokeif (input >= impulse){  current_time=millis();  interval=current_time-prev_time;  stroke_rate=60/(interval*1000);  return stroke_rate;}return 0;}//Function to collect the 3 most recent stroke rates average themlong average_stroke_rate(long acc){  long strokerate[2];  long prevtime[2];  long total=0;  int i=0;  long temp,time_temp;    while (i<=3){    time_temp=millis();    temp=stroke_rate(acc,time_temp);    if(temp!=0){    strokerate[i]=temp;    prevtime[i]=time_temp;    }    i++;  }    total=(strokerate[0]+strokerate[1]+strokerate[2])/3;  return total;}