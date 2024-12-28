void upload_to_display() { 
// Schleift die Serielle Kommunikation direkt durch zwischen USB und Display
  while(true){
    while(Serial.available()) {
        displaySerial.write(Serial.read());
    }

    while(displaySerial.available()) {
        Serial.write(displaySerial.read());
    }
  }
}