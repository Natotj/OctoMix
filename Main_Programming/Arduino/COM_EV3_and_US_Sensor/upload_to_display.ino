void upload_to_display() { 
  while(true){
    while(Serial.available()) {
        displaySerial.write(Serial.read());
    }

    while(displaySerial.available()) {
        Serial.write(displaySerial.read());
    }
  }
}