#include <SoftwareSerial.h>

#define LED 3
#define USONIC_TRIG 12
#define USONIC_ECHO 13
#define RX2 5
#define TX2 4

#define EV3_STOPP 0
#define EV3_VOR_S 1
#define EV3_VOR_M 2 
#define EV3_VOR_L 3
#define EV3_ZUR_S 4
#define EV3_ZUR_M 5
#define EV3_ZUR_L 6
#define EV3_VR_O 7
#define EV3_VF_O 8
#define EV3_VR_C 9
#define EV3_VF_C 10

// Befehle: 0 - STOPP
//          1 - Vorwärts schnell
//          2 - Vorwärts mittel
//          3 - Vorwärts langsam
//          4 - Rückwärts schnell
//          5 - Rückwärts mitttel
//          6 - Rückwärts langsam
//          7 - Ventil rear open
//          8 - Ventil front open
//          9 - Ventil rear close
//         10 - Ventil front close

int i;

SoftwareSerial displaySerial(RX2, TX2);

void setup() {
  Serial.begin(9600);
  displaySerial.begin(9600);


  pinMode(LED, OUTPUT);

  pinMode(USONIC_TRIG, OUTPUT);
  digitalWrite(USONIC_TRIG, LOW);
  pinMode(USONIC_ECHO, INPUT); 
  
}

void loop() {

//Ultrasonic Sensor function
//Serial.println(EV3_Distance());
//EV3_Com(EV3_STOPP);
Display_Com();
Distance_Controll(20);
Serial.println("Angekommen bei Stopp 1 :)");
delay(1000);

Distance_Controll(70);
Serial.println("Angekommen bei Stopp 2 :)");
delay(1000);


}
