int Display_Com() {

int ID=0;
int got=0;
char m='"';
String out="";

String crs [7]= {
  // ((ingredient + amount (in CL(two chracters))) * 6) + ((after which step to mix) * 2) + ((buffer) * 2) = 32 chracters 
  "23021602089900000000000000000000",
  "11022202160212100799000000000400",
  "02040503030406990000000000000300",
  "18021602030906990000000000000300",
  "15042102140403990000000000000300",
  "15042102140427050399000000000400",
  "16021002099900000000000000000000"
};


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