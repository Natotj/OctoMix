/////////////////////////////////////////////////////////////
//               Initialisierung
/////////////////////////////////////////////////////////////

// Nomenklatur:
  // Variablen Englsich
  // Kommentare Deutsch
  // Variablen camelCase: erster Buchstabe immer klein
  // Eigene Funktinen Snake_case: erster Buchstabe immer groß

bool uploadToNextionDisplay = false; // wenn true, dann upload modus für Software zum Nextin display. Serial Monitor muss aus sein!
bool testRun = false; //nur für Testzwecke

// libarys und definitionen
  #include <AltSoftSerial.h> // Software Serial port
  #include <stdlib.h>
  #include <math.h>
  #include <DHT11.h>

  // Arduino Port Belegung
  #define LED 11
  #define USONIC_TRIG 2 //Ultraschall trigger
  #define USONIC_ECHO 3 //Ulstraschall Echo
  #define TEMPERATURE 4 //DHT11 Temperatur und Feuchtigkeitssensor
  #define RX2 8 // Serial resive, weißes kabel von Nexiton display, AltSoftSerial standard
  #define TX2 9 //  Serial transmit, gelbes kabel von Nexiton display, AltSoftSerial standard
  #define PWM_NOT_USABLE 10 // wird verwendet von Libary AltSoftSerial.h
  #define PUMP 5
  #define SHAKER 6

  // EV3 Befehle, beziehen sich auf Index von Array in Funktion EV3_Com
  // FW -> forward, B -> Back, F-> fast, M -> medium, S -> slow, VR -> valve rear, VF -> valve front, O -> open, C -> close
  #define EV3_STOP 0 // stopp
  #define EV3_FW_F 1 // Vorwärts schnell
  #define EV3_FW_M 2 // Vorwärts mittel
  #define EV3_FW_S 3 // Vorwärts langsam
  #define EV3_B_F 4 // zurück schnell
  #define EV3_B_M 5 // zurück mittel
  #define EV3_B_S 6 // zurück schnell
  #define EV3_VR 7 // Ventil hinten öffnen / schließen
  #define EV3_VF 8 // Ventil vorne öffnen / schließen

// globale Vaiablen Deklarationen

//   Cocktail Rezept Variablen
  int ID=0; //Cocktail ID, gibt an welcher Cocktail angefragt ist, bzw. gerade gemischt wird
  String crs [12]= { //Cocktail Rezepte
    // ((ingredient + amount (in CL(two chracters))) * 6) + ((after which step to mix) * 2) + ((buffer) * 2) = 32 chracters 
    // liste der ingredients ID in Dokumentation
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
  char valveNum = 0; // an welchem Ventil gearbeitet wird oder zu welchem gefahren wird
  char volume = 0; // welches Volumen jetzt gepumpt werden soll
  char shake1 = 0; // an welchem Schritt zum 1. mal geshaket werden soll
  char shake2 = 0; // an welchem Schritt zum 2. mal geshaket werden soll

//   Programm Variablen für Mixen
  bool isMixing = false; // True wenn ein Cocktail gemixt wird
  int mixSteps; // how many steps there are for the mixing of a cocktail

//   Variablen der Realen Welt für das Mixen
  float flowrate = 1; // Fließgeschwindigkeit in Cl pro sek
  float valveDistance[10] = { // Abstand zwischen US-Sensor und EV3 um am richtigen Ventil zu stehen
    0.5, //1
    2.800, //2
    22.392, //3
    31.046, //4
    40.167, //5
    52.000, //6
    77.5, //7
    68.104, //8
    75, //9
    83.996, // noch nicht vorhanden!
  };

  int temp = 20; //Temperatur, wird jede minute geupdatet von dht11.readTemperature() in Main
  unsigned long previousMillis = 0; //für die Abfrage des Temp Sensors alle x sekunden
  unsigned long currentMillis = millis(); //für die Abfrage des Temp Sensors alle x sekunden

  int valveDelayOpen = 10; //Zeit die der EV3 zum öffnen eines Ventils benötigt in sekunden
  int valveDelayClose = 10; //Zeit die der EV3 zum schließen eines Ventils benötigt in sekunden


// initialisierungen
  AltSoftSerial displaySerial; // zweiter Serieller Port, RX2 pin 8, TX2 pin 9,
  
  DHT11 dht11(TEMPERATURE); //DHT11 class

void setup() {
//   Serial ports initialisierung
  Serial.begin(31250);
  displaySerial.begin(31250);

//   Pin initialisierung
  pinMode(USONIC_TRIG, OUTPUT);
  digitalWrite(USONIC_TRIG, LOW);
  pinMode(USONIC_ECHO, INPUT); 
  pinMode(TEMPERATURE, INPUT);
  //dht11.setDelay(500); //DHT11 Temperatur Abtastrate in ms, messung jede minute
  do{
    temp = dht11.readTemperature(); //für die richtige Temperatur zu beginn
  } while(temp>60);

  pinMode(PUMP, OUTPUT);
  digitalWrite(PUMP, LOW);
  pinMode(SHAKER, OUTPUT);
  digitalWrite(SHAKER, LOW);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  EV3_Com(EV3_STOP);
  printLine("Arduino Start");
  Display_Write_Number("Home.isMixing.val=", 0);
}