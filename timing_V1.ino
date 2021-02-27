long prev_time;
//This function is to be used in a for loop
//call this function before an if statement 
//will return 1 or 0 and use that to make timing
boolean timing(int interval){
  //prev_time global variable
  long current_time=millis(); //gets the time atm
  long difference; //to be used as difference in current and prev time
  difference=current_time-prev_time; //finds the difference in the times
   if(difference>=interval){ //if the difference is larger than the interval will return 1
    prev_time=current_time; //update global variable of prev_time for nxt count
    return true;
   }
    
  return false;
  
}

