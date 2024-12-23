int Display_Com() {

char m='"';
String out="";
int got=0;

  if (displaySerial.available()){
    got=displaySerial.read();
    
    if (got<60 && got>0) {
      
      ID = got;

      out=crs[ID-1];
      delay(50);
      
      displaySerial.print("CRS.txt=");
      displaySerial.print(m);
      displaySerial.print(out);
      displaySerial.print(m);
        displaySerial.write(0X0ff);
        displaySerial.write(0X0ff);
        displaySerial.write(0X0ff);

      displaySerial.print("tm0.en=1");//triggert das programm zum auflisten
        displaySerial.write(0X0ff);
        displaySerial.write(0X0ff);
        displaySerial.write(0X0ff);



    }
  }
}