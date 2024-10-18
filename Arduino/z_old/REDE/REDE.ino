char m='"';
String out="";
String data_from_Display="";
String saveT="";
long ID=0;
int where=-1;

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
//empfangen
  if(Serial.available()>0)
  {
    data_from_Display="";
    value.longval=0;
    delay(30);

    while(Serial.available()>0)
    {
      data_from_Display += char(Serial.read());
    }

    saveT=data_from_Display;
    where=saveT.lastIndexOf("val");//Arduino muss jetzt erst schauen, ob im data_from_Display auch der Code val vorkommt. Wenn ja, dann ist dahinter in 4 chars die ID
    data_from_Display=data_from_Display.substring(where+3, where+7);

Serial.println(where);
Serial.println(data_from_Display.length());
Serial.println(data_from_Display);   
Serial.println(".");
    
    if(where>=0)
    {
Serial.println("if(where>=0");
      value.charval[0] = char(data_from_Display[0]);
      value.charval[1] = char(data_from_Display[1]);
      value.charval[2] = char(data_from_Display[2]);
      value.charval[3] = char(data_from_Display[3]);
        
      ID=value.longval;
      value.longval=0;
    
Serial.println(ID);

    }
  } 

//delay(30);//Damit Display auf der nächsten Seite ist.

//senden
  if(Serial.available()==0 && ID>0)
  {
    out=crs[ID];
    ID--;
    Serial.write(0X0ff);
    Serial.write(0X0ff);
    Serial.write(0X0ff);

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

    ID=0;
  }
}