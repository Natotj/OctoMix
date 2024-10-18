#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

char m='"';
String out="";
String data_from_Display="";
int ID=0;

String crs [7]=
{
  "23021602089900000000000000000000",
  "11022202160212100799000000000400",
  "02040503030406990000000000000300",
  "18021602030906990000000000000300",
  "15042102140403990000000000000300",
  "15042102140427050399000000000400",
  "16021002099900000000000000000000"
};

union
{
  char charval[4];
  long longval;
} value;


void setup() 
  {
    Serial.begin(9600);
  }

void loop() 
{
  while (Serial.available() > 0) {
    
    ID = Serial.parseInt();

    if (Serial.read() == '\n'){
      out="";
    //ID=2;
    ID--;
    out=ID;
    //out=crs[ID];
    //out=out+m;

    Serial.print("CRS.txt=");
    Serial.print(m);
    Serial.print(out);
    Serial.print(m);
      Serial.write(0X0ff);
      Serial.write(0X0ff);
      Serial.write(0X0ff);

    delay(500);

    Serial.print("tm0.en=1");//triggert das programm zum auflisten
      Serial.write(0X0ff);
      Serial.write(0X0ff);
      Serial.write(0X0ff);

    ID=0;
    }
  }
/*  if (Serial.available()) {
    int c = Serial.read();
    if (Serial.read() == '\n') {
      Serial.print("The button with the number ");
      Serial.print(c);
      Serial.println(" was pressed!");
    }
  } */
//empfangen
/*  if(Serial.available()>0 && ID==0)
  {
    delay(500);
    //ID = Serial.read();
    data_from_Display="";
    value.longval=0;
    
    while(Serial.available()>0)
    {
      data_from_Display += char(Serial.read());
    }

    value.charval[0] = char(data_from_Display[0]);
    value.charval[1] = char(data_from_Display[1]);
    value.charval[2] = char(data_from_Display[2]);
    value.charval[3] = char(data_from_Display[3]);
    
    //value.longval=data_from_Display.toInt();
    ID=value.longval;
    value.longval=0;
  } 

delay(500);//Damit Display auf der nächsten Seite ist.

//senden
 if(Serial.available()==0 && ID>0)
  {
    out="";
    //ID=2;
    ID--;
    out=ID;
    //out=crs[ID];
    //out=out+m;

    Serial.print("CRS.txt=");
    Serial.print(m);
    Serial.print(out);
    Serial.print(m);
      Serial.write(0X0ff);
      Serial.write(0X0ff);
      Serial.write(0X0ff);

    delay(500);

    Serial.print("tm0.en=1");//triggert das programm zum auflisten
      Serial.write(0X0ff);
      Serial.write(0X0ff);
      Serial.write(0X0ff);

    ID=0;
  }*/
}
