#include <AltSoftSerial.h>

#define LED 3
#define NOTUSABLEPWM 10
#define RX2 8 //weiß
#define TX2 9 //gelb

//Second Serial Port
AltSoftSerial nexSerial;

void setup() {
// Serial ports initialisierung
  Serial.begin(31250);
  nexSerial.begin(31250);  
}
void loop() {

  while(true){
    while(Serial.available()) {
        nexSerial.write(Serial.read());
    }
    while(nexSerial.available()) {
        Serial.write(nexSerial.read());
    }
  }

/*
    nexSerial.print("baud=19200");
    nexSerial.write(0X0ff);
    nexSerial.write(0X0ff);
    nexSerial.write(0X0ff);
*/ 
}
