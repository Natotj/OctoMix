// hier sind drei Funcitons! Display_Com (für die Kommunikaion generell),
// Display_Read (welche nur von Display_Com genutzt wird) zum lesen der vom Display gesendeten Daten
// Reset_Function um bei entsprechenden Display befehl neu zu starten

void (*Reset_Func)(void) = 0; // Pointer auf Adresse 0 (Reset-Vektor) zum resetten vom Arduino

int Display_Com() {
// kommunikation mit dem Nextion Display

  String out="";
  int got=0;
  int i;
  char mark = '"';
// display Command 100: Cocktail ID wurde gesented erwaret crs
// display Command 101: crs_Mix wurde gesendet, Cocktail soll gemischt werden
// display Command 254: Arduino soll resettet werden

  got = Display_Read();

  if(got>99){
// Cocktail ID empfangen und CRS senden
    if (got == 100) { // for receving a Cocktial ID and sending an Cocktail recipe
      
      do{
        ID = Display_Read();
      }while(ID<=0); //geht raus wenn falsch. Wenn über 0 dann geht weiter weil 1<=0 falsch ist
 
      Serial.print("ID: ");
      Serial.println(ID);

      out=crs[ID-1];
      
      Display_Write("CRS.txt=", out); // schreibt Variable CRS mit dem Cocktialrezept
      Display_Write("tm0.en=", "1"); // triggert das programm zum auflisten
    }

// crsMix empfangen
    if (got==101) {
      Serial.println("crsMix empfangen! -> mixing now");
      delay(50);
      for(i=0; i<sizeof(crsMix); i++){
        crsMix[i] = Display_Read();
      }

      Display_Write("Home.isMixing.val=","1");
      isMixing = true;
    }

// Arduino reset
    if (got==254) {
      //Arduino resetten
      EV3_Com(EV3_STOP);
      Reset_Func();
    }
  }
}


char Display_Read(){
// liest den Seriellen port vom Display aus
  int index = 0;
  char buffer[4]; //8 weil 1x zeichen und 3x 0xFF (oder 0x00) je 2bytes

  if(displaySerial.available()){
    while(index < sizeof(buffer)) { // liest immer die werten vier stellen aus dem Buffer und return zum verarbeiten
      buffer[index] = displaySerial.read();
      index++;
    }
  }
return buffer[0];
}
