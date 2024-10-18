void DisplayScroll(String Texte[], int Namenzahl, bool zusatz, byte Nummer[], byte lcdCursorX, byte lcdCursorY)
                //(Was geschrieben wird, wie viele Zeilen es sind, soll nummerrierung hinzugefügt werden?, Nummerrierungsarray,
                // wo soll der Cursor auf dem lcd screen sein X-Koordinate, Y-Koordinate)
{
  JStick(Namenzahl, 0);
  delay(300);
  
  if(JStick_Push == false && zusatz == false)
    {
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print(Texte[CursorY]);
      lcd.setCursor(1,1);

      if(CursorY != Namenzahl -1) lcd.print(Texte[CursorY+1]);
      else lcd.print(Texte[0]);

    }
    
  else if (JStick_Push == false && zusatz == true)
    {
      lcd.clear();
      lcd.setCursor(1,0);
      if (Nummer[CursorY] <= 9 && Nummer[CursorY] >=0) lcd.print((String)Nummer[CursorY]+ " " +Texte[CursorY]); //fügt leerzeichen hinzu wenn zahl einstellig
      else lcd.print(Nummer[CursorY] + Texte[CursorY]);
      lcd.setCursor(1,1);

      if(CursorY != Namenzahl -1) 
      {
        if (Nummer[CursorY+1] <= 9 && Nummer[CursorY+1] >=0) lcd.print((String)Nummer[CursorY+1]+" "+Texte[CursorY+1]); //fügt leerzeichen hinzu wenn zahl einstellig
        else lcd.print((String)Nummer[CursorY+1] + Texte[CursorY+1]);
      }
      else if (Nummer[CursorY+1] <= 9 && Nummer[CursorY+1] >=0) lcd.print((String)Nummer[0]+" "+Texte[0]); //fügt leerzeichen hinzu wenn zahl einstellig
      else lcd.print((String)Nummer[0] + Texte[0]); 
    }
      
  lcd.setCursor(0,0); //damit Blinken wieder auf 0,0 ist.
}
