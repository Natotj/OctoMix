#define LCD_RS 4
#define LCD_E 7
#define LCD_D4 8
#define LCD_D5 9
#define LCD_D6 10
#define LCD_D7 11
#define JSTICK_VRX 3
#define JSTICK_VRY 4
#define JSTICK_SW 2
#define LED 6
#define USONIC_TRIG 1
#define USONIC_ECHO 0

int a[11]={0, 2, 7, 11, 15, 21, 35, 60, 95, 140, 255};
// EV3 Werte: 3-5, 8-10, 12-14, 15-17, 18-20, 23-25, 28-31, 33-35, 38-40, 44-46
// Befehle: 0 - STOPP
//          1 - Vorwärts schnell
//          2 - Vorwärts mittel
//          3 - Vorwärts langsam
//          4 - Rückwärts schnell
//          5 - Rückwärts mitttel
//          6 - Rückwärts langsam
//          7 - Ventil rear open
//          8 - Ventil front open
//          9 - Ventil rear close
//         10 - Ventil front close
//int a[10]={3, 10, 22, 40, 64, 93, 127, 165, 207, 255}; alte werte
int w=0;
String save="";
String save2="";
int test=0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*
  Serial.println("vor"); //vor
  analogWrite(DIODE_ROT, 7);
  delay(1000);

  Serial.println("0"); 
  analogWrite(DIODE_ROT, 0);
  delay(500);

  Serial.println("Ventil 1");
  analogWrite(DIODE_ROT, 80);
  delay(1000);

  Serial.println("0");
  analogWrite(DIODE_ROT, 0);
  delay(500);


  Serial.println("zurück"); //zurück
  analogWrite(DIODE_ROT, 25);
  delay(1000);
  
  Serial.println("Ventil 2");
  analogWrite(DIODE_ROT, 200);
  delay(1000);

    Serial.println("0");
  analogWrite(DIODE_ROT, 0);
  delay(500);
*/
//analogWrite(LED, a[7]);
delay(500);
  for(int i=0; i<=10; i++)
  {
    //i=random(0,10);
    analogWrite(LED, a[i]);
    delay(5000);
    analogWrite(LED, 0);
    Serial.print(i);
    Serial.println();
    delay(50);
  } 
/*  if(Serial.available()>0)
  {
    while(Serial.available()>0)
    {
      w=Serial.read();
      w=w-48;
      save+=w;
      delay(30);
    }
    w=save.toInt();
    save="";
    analogWrite(LED, w);
    Serial.print("LED auf Wert:");
    Serial.println(w);
  }
*/

}
