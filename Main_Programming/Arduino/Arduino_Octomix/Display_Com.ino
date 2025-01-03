// hier sind vier Funcitons! Display_Com (für die Kommunikaion generell),
// Display_Read (welche nur von Display_Com genutzt wird) zum lesen der vom Display gesendeten Daten
// Reset_Function um bei entsprechenden Display befehl neu zu starten
// Display_Write um auf das Display zu schreiben

void (*Reset_Func)(void) = 0; // Pointer auf Adresse 0 (Reset-Vektor) zum resetten vom Arduino


int Display_Com() {
// kommunikation mit dem Nextion Display

  String out="";
  char got=0;
  int i;
  char mark = '"';
// display Command 100: Cocktail ID wurde gesented erwaret crs
// display Command 101: crs_Mix wurde gesendet, Cocktail soll gemischt werden
// display Command 254: Arduino soll resettet werden
//  ID = 0;
  got = Display_Read();

  if(got>99){
// Cocktail ID empfangen und CRS senden
  //debug Info
    Serial.print("Sinvoll von Display= ");
    Serial.println(got, HEX);

    if (got == 100) { // for receving a Cocktial ID and sending an Cocktail recipe
      
      delay(500);
      do{
        ID = Display_Read();
      }while(ID<=0); //geht raus wenn falsch. Wenn über 0 dann geht weiter weil 1<=0 falsch ist
 
      Serial.print("ID= ");
      Serial.println(ID);

      out=crs[ID-1];

      displaySerial.print("CRS.txt=");
      displaySerial.print(mark);
      displaySerial.print(out);
      displaySerial.print(mark);
        displaySerial.write(0X0ff);
        displaySerial.write(0X0ff);
        displaySerial.write(0X0ff);

//      Display_Write("CRS.txt=", out); // schreibt Variable CRS mit dem Cocktialrezept
      Serial.print("crs= ");
      Serial.println(out);

      displaySerial.print("tm0.en=1");
        displaySerial.write(0X0ff);
        displaySerial.write(0X0ff);
        displaySerial.write(0X0ff);

//      Display_Write("tm0.en=", "1"); // triggert das programm zum auflisten
    }

// crsMix empfangen
    if (got==101) {
      Serial.println("crsMix empfangen! -> mixing now");
      delay(50);
      for(i=0; i<sizeof(crsMix)/sizeof(crsMix[0]); i++){
        crsMix[i] = Display_Read();
      }

      Display_Write("Home.isMixing.val=","1");
      isMixing = true;
    }

// Arduino reset
    if (got==254) {
      Serial.println("Arduino Resart!");
      EV3_Com(EV3_STOP);
      Reset_Func();
    }
  }
}


char Display_Read(){
// liest den Seriellen port vom Display aus
  int index = 0;
  char buffer[8]; //4 weil 1x zeichen und 3x 0xFF (oder 0x00) je 2bytes

  if(displaySerial.available() >= 4){
    Serial.print("Display= ");

    while(index < 4) { // liest immer vier stellen aus dem Buffer und return zum verarbeiten
      buffer[index] = displaySerial.read();
      Serial.print(buffer[index],HEX);
      Serial.print("\t");
      index++;
    }
    Serial.println(";");

/*
    if(buffer[4]==0x0FF){ //Endet ein Command mit FF, dann ist dieser ein Touch bzw. Page Event und nicht relevant
      buffer[0] = 0;
    } else {
      Serial.print("Display= ");
      Serial.println(buffer[0], HEX);
    }
    */
  } else buffer[0]=0;

return buffer[0];
}


void Display_Write(String command, String value){
// function that writes something from the arduino to the display  
// command = the command you want to trigger 
// value = value that you want to transmitt to the command 
// for example: "1" or "0" for on/off or  "23021602089900000000000000000000" for Cool Brezze
  char mark='"';

  //displaySerial.print(mark);
  displaySerial.print(command);
  //displaySerial.print(mark);
  displaySerial.print(mark);
  displaySerial.print(value);
  displaySerial.print(mark);
    displaySerial.write(0X0ff);
    displaySerial.write(0X0ff);
    displaySerial.write(0X0ff);
}