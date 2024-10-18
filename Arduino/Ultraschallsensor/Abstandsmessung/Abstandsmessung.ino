int trigger=12; //Trigger-Pin des Ultraschallsensors an Pin7 des Arduino-Boards 
int echo=13; // Echo-Pim des Ultraschallsensors an Pin6 des Arduino-Boards 
int VCC=11;
double dauer=0; // Das Wort dauer ist jetzt eine Variable, unter der die Zeit gespeichert wird, die eine Schallwelle bis zur Reflektion und zurück benötigt. Startwert ist hier 0.
double entfernung=0; // Das Wort „entfernung“ ist jetzt die variable, unter der die berechnete Entfernung gespeichert wird. Info: Anstelle von „int“ steht hier vor den beiden Variablen „long“. Das hat den Vorteil, dass eine größere Zahl gespeichert werden kann. Nachteil: Die Variable benötigt mehr Platz im Speicher.

void setup()
{
Serial.begin (9600); //Serielle kommunikation starten, damit man sich später die Werte am serial monitor ansehen kann.
pinMode(VCC, OUTPUT);
pinMode(trigger, OUTPUT); // Trigger-Pin ist ein Ausgang
pinMode(echo, INPUT); // Echo-Pin ist ein Eingang
digitalWrite(VCC, HIGH);
digitalWrite(trigger, LOW); //Hier nimmt man die Spannung für kurze Zeit vom Trigger-Pin, damit man später beim senden des Trigger-Signals ein rauschfreies Signal hat.
}

void loop() 
{

dauer=0;
for(int n=0; n<=10; n++) 
  {
  delay(10);
  digitalWrite(trigger, HIGH); //Jetzt sendet man eine Ultraschallwelle los.
  delay(10); //Dieser „Ton“ erklingt für 10 Millisekunden.
  digitalWrite(trigger, LOW);//Dann wird der „Ton“ abgeschaltet.
  dauer = dauer + pulseIn(echo, HIGH); //Mit dem Befehl „pulseIn“ zählt der Mikrokontroller die Zeit in Mikrosekunden, bis der Schall zum Ultraschallsensor zurückkehrt.
  }
dauer = dauer/10; //für den Durchschnitt und durch 2
entfernung =(dauer/2) * 0.03432;;

//if (entfernung >= 500 || entfernung <= 0) //Wenn die gemessene Entfernung über 500cm oder unter 0cm liegt,…
//  {
//  Serial.println("Kein Messwert"); //dann soll der serial monitor ausgeben „Kein Messwert“, weil Messwerte in diesen Bereichen falsch oder ungenau sind.
//  }
//else //  Ansonsten…
//  {
  Serial.print(entfernung); //…soll der Wert der Entfernung an den serial monitor hier ausgegeben werden.
  Serial.println(" cm"); // Hinter dem Wert der Entfernung soll auch am Serial Monitor die Einheit "cm" angegeben werden.
//  }
//delay(100)); //Das delay von einer Sekunde sorgt in ca. jeder neuen Sekunde für einen neuen Messwert.
}