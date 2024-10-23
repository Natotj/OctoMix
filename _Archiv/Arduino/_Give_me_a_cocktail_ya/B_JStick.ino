void JStick(byte Namenszahl, byte mode) //(höchstzahl, 0=scrollen 1=nur wert ausgeben einschließlich höchstzahl und 0)
{
  if(ScreenEbene != 9  &&  firstRun != true)
  {
  int VRY;
  int VRX;
  int merkerY = CursorY;
  int merkerX = CursorX;
  
  do
  {
    VRY = analogRead(JSTICK_VRY);
    VRX = analogRead(JSTICK_VRX);
    
      if(mode != 1) //nur beim modus zählen geht er ins else und dreht inkrementieren zu dekrementieren und anderstherrum
      {
        if(VRX < 205) CursorY--;
        else if(VRX > 818) CursorY++;
                
        if(VRY < 205) CursorX--;
        else if(VRY > 818) CursorX++;
      }

      else
      {
        if(VRX < 205) CursorY++;
        else if(VRX > 818) CursorY--;
      }
      
  }while(CursorY == merkerY  &&  CursorX == merkerX  &&  JStick_Push == false);

    if(mode != 1)
    {
      if(CursorY == Namenszahl) CursorY = 0;
      else if(CursorY == -1) CursorY = (Namenszahl)-1;
    }
    else
    {
      if(CursorY == Namenszahl +1) CursorY = 0;
      else if(CursorY == -1) CursorY = (Namenszahl);
    }
  }  
  else firstRun = false;
}
