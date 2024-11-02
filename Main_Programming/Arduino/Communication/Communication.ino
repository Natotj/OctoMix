int ID=0;
int got=0;
char m='"';
String out="";

String crs [7]= {
  "23021602089900000000000000000000",
  "11022202160212100799000000000400",
  "02040503030406990000000000000300",
  "18021602030906990000000000000300",
  "15042102140403990000000000000300",
  "15042102140427050399000000000400",
  "16021002099900000000000000000000"
};



void setup(){
  Serial.begin(9600);
}

void loop(){ // run over and over
  if (Serial.available()){
    got=Serial.read();
    
    if (got<60 && got>0) {
      
      ID = got;

      out=crs[ID-1];
      delay(50);
      
      Serial.print("CRS.txt=");
      Serial.print(m);
      Serial.print(out);
      Serial.print(m);
        Serial.write(0X0ff);
        Serial.write(0X0ff);
        Serial.write(0X0ff);

      Serial.print("tm0.en=1");//triggert das programm zum auflisten
        Serial.write(0X0ff);
        Serial.write(0X0ff);
        Serial.write(0X0ff);
    }
  }

}
