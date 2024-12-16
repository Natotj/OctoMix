#define LED 3
#define USONIC_TRIG 12
#define USONIC_ECHO 13

int a[11]={0, 2, 5, 10, 18, 40, 70, 110, 160, 200, 255};
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

void setup() {
  Serial.begin(9600);

  pinMode(LED, OUTPUT);

  pinMode(USONIC_TRIG, OUTPUT);
  digitalWrite(USONIC_TRIG, LOW);
  pinMode(USONIC_ECHO, INPUT); 
}

void loop() {

float duration, distance;
digitalWrite(USONIC_TRIG, HIGH);
delayMicroseconds(10);
digitalWrite(USONIC_TRIG, LOW);
duration = pulseIn(USONIC_ECHO, HIGH);
distance = (duration*0.0343)/2;
Serial.print("Distance: ");
Serial.println(distance);
delay(100000);
/*
delay(4000);
int i;
for(i=0; i < 11; i++) {
  
  analogWrite(LED, a[i]);
  Serial.println(i);
  delay(4000);
}
*/

/*
delay(4000);

  analogWrite(LED, a[7]);
  Serial.println("vorwäts");
  delay(8000);
  analogWrite(LED, 0);
  Serial.println("stop");
  delay(4000);
  analogWrite(LED, a[9]);
  Serial.println("rückwärts");
  delay(8000);
  analogWrite(LED, 0);
  Serial.println("stop");

  delay(4000);

  analogWrite(LED, a[8]);
  Serial.println("vorwäts");
  delay(8000);
  analogWrite(LED, 0);
  Serial.println("stop");
  delay(4000);
  analogWrite(LED, a[10]);
  Serial.println("rückwärts");
  delay(8000);
  analogWrite(LED, 0);
  Serial.println("stop");

*/
}
