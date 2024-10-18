void setup()
// Initialisierung
{
  Serial.begin(9600);
  
  pinMode(DIODE, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(JSTICK_SW), Push, FALLING);
  
  lcd.begin(16, 2);
  lcd.clear();
  
  lcd.setCursor(1,0);
  lcd.print(Namen[0]);
  
  lcd.setCursor(1,1);
  lcd.print(Namen[1]);
  
  lcd.setCursor(0,0);
  lcd.blink();

  analogWrite(DIODE, 20);
  
}


void loop()
// Hauptprogrammschleife
{ 
  if(ScreenEbene == 0)
    {
      DisplayScroll(Namen, Cocktailanzahl, false, 0, 0, 0); //ScreenEbene 0
      CocktailMixenTrueFalse(); //ruft auch Einstellungen (ScreenEbene 1) auf, ganz unten
    }
  
  if(ScreenEbene == 2) EinstellungenVentilbelegung();
  if(ScreenEbene == 3) GiveMeACocktailYa();
  if(ScreenEbene == 9)//zurücksetzen
   {
    ResetVariablen();
    ScreenEbene = 0;
   }
}








//
