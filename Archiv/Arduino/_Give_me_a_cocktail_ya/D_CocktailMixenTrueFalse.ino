void CocktailMixenTrueFalse()
{
  if(JStick_Push==true /* && Cocktail_mixen !=0*/)
    {
      if(CursorY!=0)//überprüfung ob Einstellungen ausgewählt sind
      {
        lcd.clear();
        lcd.setCursor(1,0);
        lcd.print(Namen[CursorY]);
        lcd.setCursor(0,1);
        lcd.print("Mixen?   YES  NO");
        lcd.setCursor(13,1); 
        lcd.blink();
        
        CursorX = 1; //damit Cursor erst auf NO
        JStick_Push = false;
        
        while(JStick_Push == false)
          {
            JStick(Cocktailanzahl, 0);
        
              if(CursorX % 2 == 0)
              {
                lcd.setCursor(8,1); //Cocktail mixen YES
                lcd.blink();
                delay(300);
              }
              
              else
              {
                lcd.setCursor(13,1); //Cocktail mixen NO
                lcd.blink();
                delay(300);
              }
          }
          
        if(CursorX % 2 == 0) 
          {
            Cocktail_mixen = 1; //Mixvorgang starten
            ScreenEbene = 3;
            JStick_Push = false;
          }
        
        else ScreenEbene = 9 ; //Mixvorgang NICHT starten
          
      }
        else ScreenEbene = 2; //Einstellungen 
    }
}
