//////////////////////////////////////////////////////////////
//          Main Program wich needs to be run
/////////////////////////////////////////////////////////////
// lokale Variablen
int i = 0;

void loop() {

//// Standby
  Display_Com();
  EV3_Com(EV3_STOP);

// Programm zu Testzwecken für den Main Ablauf
  if(testRun == true){
   crsMix[0] = 0xF;  //15
    crsMix[1] = 0x4;  //04
    crsMix[2] = 0x15; //21
    crsMix[3] = 0x2; //02
    crsMix[4] = 0xE; //14
    crsMix[5] = 0x04; //04
    crsMix[6] = 0x1B; //27
    crsMix[7] = 0x5; //05
    crsMix[8] = 0x3; //03
    crsMix[9] = 0x14; //20
    crsMix[10] = 0x0; //0
    crsMix[11] = 0x0; //0
    crsMix[12] = 0x0; //0
    crsMix[13] = 0x0; //0
    crsMix[14] = 0x0; //0
    crsMix[15] = 0x0; //0
    crsMix[16] = 0x4; //4
    crsMix[17] = 0x0; //0
    isMixing = true;
  }

//// Ablauf Cocktail Mixen

  if(isMixing == true){ // Wenn Cocktail gemixt werden soll. isMixing wird von Display_Com gesetzt.
    //wann shaken?
    shake1 = crsMix[15];
    shake2 = crsMix[16];

    Progress_Bar();

    for(i=0; i<16; i+=2){
      printLine("New V");

      valveNum = crsMix[i];
      volume = crsMix[i+1];

      if (valveNum != 0){
        //zum Ventil fahren
        if(testRun == false) Distance_Controll(valveDistance[(valveNum+1)/2]); // gibt den aufgerundeten halbierten wert an valveDistance weiter an distance controll um dorthin zu fahren
        else Expanded_delay(5*1000);

        printLine("am Vent");
        Progress_Bar();  

        valveMove(valveNum); //Ventil öffnen
        Progress_Bar();
      
        //Pumpe
        digitalWrite(PUMP, HIGH); // Pumpe anschalten
        Expanded_delay(volume/flowrate * 1000); // richtige Zeit warten
        digitalWrite(PUMP, LOW); //Pumpe ausschalten
        Progress_Bar();
       
        valveMove(valveNum); //Ventil schließen
        Progress_Bar();

        //Shanken Wenn i/2+1=shake1 oder =shake2 dann shaken
        if((i/2+1)==shake1 || (i/2+1)==shake2) {
          digitalWrite(SHAKER, HIGH); // shaken an
          Progress_Bar(); 
          Expanded_delay(10*1000); // watet bis i größer als die wartezeit ist. (x in sek * 1000)
          digitalWrite(SHAKER, LOW); // shaken aus
        }
      }
    }
    // Nachricht an Display, dass Cocktail fertig
    Display_Write_Number("Home.isMixing.val=", 0);
    isMixing = false;
  }

  if(uploadToNextionDisplay == true) upload_to_display(); //Upload a Program to the Nextion display

  //Programm zum Testen von LED Werten der Übertragung
    /*while(true){
        delay(4000);
      int i;
      for(i=0; i < 9; i++) {
        analogWrite(LED, EV3_COM[i]);
        Serial.println(i);
        delay(4000);
      }
    }*/
}
