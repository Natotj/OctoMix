// Utils.ino consists of little functions that you use frequently make the code more readable and short

// better performing and more lightweight replacement for Serial.println() 
void printLine(String pString){
 Serial.write(pString.c_str()); 
 Serial.write("\n"); 
}
