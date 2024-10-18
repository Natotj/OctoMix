void EinstellungenVentilbelegung() //ScreenEbene = 2
{
  ResetVariablen();
  
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print((String)Zutatenkoordinate[CursorY]+" "+ Zutatennamen[CursorY]);
  lcd.setCursor(1,1);
  lcd.print((String)Zutatenkoordinate[CursorY+1]+" "+ Zutatennamen[CursorY+1]);
  lcd.setCursor(0,0);

  while(ScreenEbene != 9)
   {  
     
     while(JStick_Push == false)
      {
        DisplayScroll(Zutatennamen, Zutatenanzahl, true, Zutatenkoordinate, 0, 0);
      }
    
    JStick_Push = false; //Zurücksetzen
  
  
     if (CursorY != 0) //also nicht auf return
      {
        int SaveCursorY = CursorY; //sichert die Auswahl
        CursorY = Zutatenkoordinate[SaveCursorY];
        lcd.setCursor(1,0);
        
          while(JStick_Push == false)
          {
            JStick(Ventilzahl, 1);
        
            delay(300);
            
            lcd.setCursor(1,0);
            
            if (CursorY <= 9 && CursorY >= 0) lcd.print((String)CursorY+ " " +Zutatennamen[SaveCursorY]); //fügt leerzeichen hinzu wenn zahl einstellig
            else lcd.print((String)CursorY + Zutatennamen[SaveCursorY]);
        
            lcd.setCursor(1,0); //damit der Cursor wieder da is wo er soll und nicht am Ende der Zeile
          }
        JStick_Push = false;
        Zutatenkoordinate[SaveCursorY] = CursorY;
        CursorY = SaveCursorY;
        lcd.setCursor(0,0);
      }
    else
      {
        ScreenEbene = 9;
      }
      
   /* lcd.clear();
    lcd.setCursor(1,0);
    if (CursorY <= 9 && CursorY >= 0) lcd.print((String)Zutatenkoordinate[CursorY]+" "+ Zutatennamen[CursorY]); //fügt leerzeichen hinzu wenn zahl einstellig
    else lcd.print((String)Zutatenkoordinate[CursorY]+ Zutatennamen[CursorY]);
    lcd.setCursor(1,1);
        if (CursorY <= 9 && CursorY >= 0) lcd.print((String)Zutatenkoordinate[CursorY++]+" "+ Zutatennamen[CursorY++]); //fügt leerzeichen hinzu wenn zahl einstellig
    else lcd.print((String)Zutatenkoordinate[CursorY++]+ Zutatennamen[CursorY++]);
    lcd.setCursor(0,0);*/
    

     }
}
