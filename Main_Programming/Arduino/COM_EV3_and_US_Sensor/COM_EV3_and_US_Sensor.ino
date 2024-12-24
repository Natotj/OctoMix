bool upload_to_Nextion_Display = false; //go into upload mode for the Nextion display if set to true (Serial Monitor has to be off)

#include <AltSoftSerial.h>
#include <stdlib.h>

#define LED 3
#define USONIC_TRIG 12
#define USONIC_ECHO 13
#define RX2 8 // white
#define TX2 9 // yellow
#define PWM_NOT_USABLE 10 // due to AltSoftSerial.h

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

int i; //incremental Variable

int ID=0; //Cocktail ID
String crs [12]= { //Cocktail Rezepte
  // ((ingredient + amount (in CL(two chracters))) * 6) + ((after which step to mix) * 2) + ((buffer) * 2) = 32 chracters 
  "23021602089900000000000000000000", //Cool Brezze
  "11022202160212100799000000000400", //Cherry Bomb
  "02040503030406990000000000000300", //Golden Ginger
  "18021602030906990000000000000300", //St. Kitts
  "15042102140403990000000000000300", //Virgin Pina Colada
  "15042102140427050399000000000400", //Pina Colada
  "16021002099900000000000000000000", //Mexican on Ice
  "24030304069900000000000000000100", //Mexicore
  "24040799000000000000000000000000", //Tequila Tonic
  "25060699000000000000000000000000", //Whisky Ginger
  "25080999000000000000000000000000", //Jack Cola
  "28070799000000000000000000000000", //Gin Tonic
};
char crsMix[17];
bool mixing = false;
char valveNum = 0;
char volume = 0;
char shake1 = 0;
char shake2 = 0;

float valveDistance[10] = {
  4.0,
  12.7,
  21.3,
  30.0,
  38.7,
  47.3,
  56.0,
  64.7,
  73.3,
  82.0,
};


//Second Serial Port
AltSoftSerial displaySerial; // RX2 pin 8, TX2 pin 9

void setup() {
// Serial ports initialisierung
  Serial.begin(31250);
  displaySerial.begin(31250);

// LED initialisierung
  pinMode(LED, OUTPUT);

// Ultraschall Senosr initialisierung
  pinMode(USONIC_TRIG, OUTPUT);
  digitalWrite(USONIC_TRIG, LOW);
  pinMode(USONIC_ECHO, INPUT); 
  
}


void loop() {
  if(upload_to_Nextion_Display == false){ //Main programm

  EV3_Com(EV3_STOPP);
  Display_Com();

  if(mixing == true){
    //wann shaken?

    for(i=0; i<14; i=i+2){
      valveNum = crsMix[i];
      volume = crsMix[i+1];

      //zum Ventil fahren

      //richiges Ventil öffnen

      //Pumpe anschalten

      //richtige Zeit warten

      //Pumpe ausschalten

      //Ventil schließen

      //Wenn i/2+1=shake1 oder =shake2 dann shaken

        //shaken an

        //while bestimmte anzahl durchläufe
          //display com
          //delay

        //shaken aus

    }
    // Nachricht an Display, dass Cocktail fertig
  }



  }else{ // Programm zum Hochladen an das Display
    upload_to_display();
  }
}
