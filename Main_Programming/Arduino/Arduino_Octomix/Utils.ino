// Utils.ino consists of little functions that you use frequently make the code more readable and short

// better performing and more lightweight replacement for Serial.println() 
void printLine(String pString){
 Serial.write(pString.c_str()); 
 Serial.write("\n"); 
}

// simpler way to end a display Command. And saving some Serial prints
void displayComandEnd(){
  for(int j=0;j<3;j++){
    displaySerial.write(0X0ff);
  }
}

