// Nomenklatur:
  // Variablen Englsich
  // Kommentare Deutsch
  // Variablen camelCase: erster Buchstabe immer klein
  // Eigene Funktinen Snake_case: erster Buchstabe immer groß

bool uploadToNextionDisplay = false; // wenn true, dann upload modus für Software zum Nextin display. Serial Monitor muss aus sein!

// libarys und definitionen
  #include <AltSoftSerial.h> // Software Serial port
  #include <stdlib.h>

  // Arduino Port Belegung
  #define LED 3
  #define USONIC_TRIG 12 //Ultraschall trigger
  #define USONIC_ECHO 13 //Ulstraschall Echo
  #define RX2 8 // Serial resive, weißes kabel von Nexiton display, AltSoftSerial standard
  #define TX2 9 //  Serial transmit, weißes kabel von Nexiton display, AltSoftSerial standard
  #define PWM_NOT_USABLE 10 // wird verwendet von Libary AltSoftSerial.h
  #define PUMP 14 // noch nicht real verbunden
  #define SHAKER 15 // noch nicht real verbunden

  // EV3 Befehle, beziehen sich auf Index von Array in Funktion EV3_Com
  // FW -> forward, B -> Back, F-> fast, M -> medium, S -> slow, VR -> valve rear, VF -> valve front, O -> open, C -> close
  #define EV3_STOP 0 // stopp
  #define EV3_FW_F 1 // Vorwärts schnell
  #define EV3_FW_M 2 // Vorwärts mittel
  #define EV3_FW_S 3 // Vorwärts langsam
  #define EV3_B_F 4 // zurück schnell
  #define EV3_B_M 5 // zurück mittel
  #define EV3_B_S 6 // zurück schnell
  #define EV3_VR_O 7 // Ventil hinten öffnen
  #define EV3_VF_O 8 // Ventil vorne öffnen
  #define EV3_VR_C 9 // Ventil hinten schließen
  #define EV3_VF_C 10 // Ventil vorne schließen

// Vaiablen Deklarationen
  int i; //incremental Variable

  int ID=0; //Cocktail ID, gibt an welcher Cocktail angefragt ist, bzw. gerade gemischt wird
  String crs [12]= { //Cocktail Rezepte
    // ((ingredient + amount (in CL(two chracters))) * 6) + ((after which step to mix) * 2) + ((buffer) * 2) = 32 chracters 
    // liste der ingredient ID in Dokumentation
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

  char crsMix[17]; // Cocktailrezept mit tatsächlicher Ventilbelegung vom Nexiton display
  bool isMixing = false; // True wenn ein Cocktail gemixt wird
  char valveNum = 0; // an welchem Ventil gearbeitet wird oder zu welchem gefahren wird
  char volume = 0; // welches Volumen jetzt gepumpt werden soll
  char shake1 = 0; // an welchem Schritt zum 1. mal geshaket werden soll
  char shake2 = 0; // an welchem Schritt zum 2. mal geshaket werden soll
  float flowrate = 0.5; // Fließgeschwindigkeit in Cl pro sek

  float valveDistance[10] = { // Abstand zwischen US-Sensor und EV3 um am richtigen Ventil zu stehen
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

// initialisierungen
  AltSoftSerial displaySerial; // zweiter Serieller Port, RX2 pin 8, TX2 pin 9,

// Main Programm
void setup() {
// Serial ports initialisierung
  Serial.begin(31250);
  displaySerial.begin(31250);

// Pin initialisierung
  pinMode(USONIC_TRIG, OUTPUT);
  digitalWrite(USONIC_TRIG, LOW);
  pinMode(USONIC_ECHO, INPUT); 

  pinMode(PUMP, OUTPUT);
  pinMode(LED, OUTPUT);

  EV3_Com(EV3_STOP);
  
}


void loop() {
  if(uploadToNextionDisplay == false){ //Main programm

  EV3_Com(EV3_STOP);
  Display_Com();

  if(isMixing == true){ // Wenn Cocktail gemixt werden soll. isMixing wird von Display_Com gesetzt.
    //wann shaken?

    for(i=0; i<14; i=i+2){
      valveNum = crsMix[i];
      volume = crsMix[i+1];
      
      //zum Ventil fahren
      Distance_Controll(valveDistance[(valveNum+1)/2]); // gibt den aufgerundeten halbierten wert an valveDistance weiter an distance controll um dorthin zu fahren
      
      //richiges Ventil öffnen
      if(valveNum % 2 != 0){ //bei ungeraden Ventilen
        EV3_Com(EV3_VR_O);
      } else {
        EV3_Com(EV3_VF_O);
      }
      
      //Pumpe anschalten
      digitalWrite(PUMP, HIGH);
      
      //richtige Zeit warten
      for(i=0; i<(volume/flowrate)*1000; i=i+100){ //watet bis i größer als die wartezeit ist.
        Display_Com();
        delay(100);
      }
      
      //Pumpe ausschalten
      digitalWrite(PUMP, LOW);
      
      //Ventil schließen
      if(valveNum % 2 != 0){ //durch änderung im EV3 programm könnte man sich einen befehl spaaren
        EV3_Com(EV3_VR_C);
      } else {
        EV3_Com(EV3_VF_C);
      }

      //Wenn i/2+1=shake1 oder =shake2 dann shaken

        //shaken an

        //betimmte zeit warten
        for(i=0; i<5*1000; i=i+100){ //watet bis i größer als die wartezeit ist. (x in sek * 1000)
          Display_Com();
          delay(100);
        }

        //shaken aus

    }
    
    // Nachricht an Display, dass Cocktail fertig
    isMixing = false;
  }

  } else { // Programm zum Hochladen an das Display
    upload_to_display();
  }
}
