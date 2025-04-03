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

void temperatureRead(){
int tempTest;

  currentMillis = millis();
  if (currentMillis - previousMillis >= 240000) {  
        previousMillis = currentMillis;  // Zeitstempel aktualisieren
        tempTest = dht11.readTemperature(); //um immer die richtige Temperatur zu haben
        if (tempTest < 60) temp = tempTest;
    }
}

void valveMove(int position) {
    if(position % 2 != 0){ //durch änderung im EV3 programm könnte man sich einen befehl spaaren
    EV3_Com(EV3_VR);
    printLine("EV3_VR");
  } else {
    EV3_Com(EV3_VF);
    printLine("EV3_VF");
  }
  Expanded_delay(15*1000);
  EV3_Com(EV3_STOP);
}