void MixWarteScreen()
{
  if(Cocktail_mixen == 1)
  {
    Save_CursorY = CursorY;
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(1,0);
    lcd.print(Namen[Save_CursorY]);
    lcd.setCursor(0,1);
   /* lcd.print("."); //macht Wartepunkte

    byte Position = 1;
    
    while(Cocktail_mixen == 1)
    {
      lcd.setCursor(Position,1);
      lcd.print(".");
      delay(400);

      if(Position <= 16) Position++;
      else
      {
        lcd.clear();
        lcd.setCursor(1,0);
        lcd.print(Namen[CursorY]);
        Position = 0;
        delay (100);
      }
    }*/
  for(byte i=0; i<=10; i=i+2)
    {
      Serial.println(Zutatenkoordinate[(Rezept [Save_CursorY -1][i])]);
      Fahren( Zutatenkoordinate[(Rezept [Save_CursorY -1][i])]);
      
      digitalWrite(PUMPE, HIGH);
      
      Serial.println(Zutatenkoordinate[(Rezept [Save_CursorY -1][i+1])]);
      delay(Zutatenkoordinate[(Rezept [Save_CursorY -1][i+1])] * t_pro_ml);

      digitalWrite(PUMPE, LOW);
      analogWrite(DIODE, 0);
    }
  }
}

void Fahren(int Ventil_soll)
  {
    Ventil_soll = ((Ventil_soll +1) /2) *25;
    Serial.println(Ventil_soll);
    
    if (analogRead(ABNEHMER) < 20) Wert_Abnehmer = Save_Wert_Abnehmer;
    if ((Wert_Abnehmer >= (Ventil_soll -5)) && (Wert_Abnehmer <= (Ventil_soll +5)))  ; //schon an Position?
    else
    {
      while(true)
      {
        int VRY;
        int VRX;
        int merkerY = CursorY;
        int CY = CursorY;
        
        do
        {
          VRY = analogRead(JSTICK_VRY);
          VRX = analogRead(JSTICK_VRX);
          
          if(VRX < 205) CY = CY +5;
          else if(VRX > 818) CY = CY -5;
            
        } while(CY == merkerY  &&  JStick_Push == false);

        if(CY == 255 +1) CY = 0;
        else if(CY == -1) CY = 255;
      
        lcd.clear();
        Wert_Abnehmer = CY;
        Serial.println(Wert_Abnehmer);
        if (Wert_Abnehmer < 20) lcd.print("rk"); //analogWrite(DIODE, 25); //fahre Vorwärts, weil nichts sieht
        else if ((Wert_Abnehmer >= (Ventil_soll -5)) && (Wert_Abnehmer <= (Ventil_soll +5))) break; //fahre nichts
        else if (Wert_Abnehmer > (Ventil_soll +5) ) lcd.print("V"); //analogWrite(DIODE, 7); //fahre Vorwärts, weil bei 5 V
        else if (Wert_Abnehmer < (Ventil_soll -5) ) lcd.print("R"); // analogWrite(DIODE, 25); //fahre rückwärts, weil bei 0,5
        //Wert_Abnehmer = analogRead(ABNEHMER);
        delay(300);
      }
      lcd.println("angekommen");
      delay(5000);
      Save_Wert_Abnehmer = Wert_Abnehmer;
      if(Ventil_soll%2  == 0) analogWrite(DIODE, 80);
      else analogWrite(DIODE, 200);
      delay(1000);
    }
  }
