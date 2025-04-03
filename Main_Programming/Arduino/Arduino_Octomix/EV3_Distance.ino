float EV3_Distance(){
  const int numMeasurements = 60; // Anzahl an Messungen für den US-Sensor
  float duration[numMeasurements]; // Laufzeit der Schallwelle der jeweilligen Messung
  float sum, mean, distance; // Umrechnung Laufzeit in Abstand
  int validCount; // Anzahl an Messungen im Rahmen der Tolleranz
  int i;
  float airSpeed;

do {
    Display_Com(); //Dass immer auf das Display zugegriffen werden kann
    
    sum = 0;
    for(i=0; i<numMeasurements; i++) { //Misst so oft wie numMeasurements vorgibt
      digitalWrite(USONIC_TRIG, LOW);
      delayMicroseconds(20);
      digitalWrite(USONIC_TRIG, HIGH);
      delayMicroseconds(10);
      digitalWrite(USONIC_TRIG, LOW);

      duration[i] = pulseIn(USONIC_ECHO, HIGH); 
      sum += duration[i];
    }
    mean = sum / numMeasurements;

// Erstellung eines Durchschnittes ohne werten mit großer Abweichung vom Ursprünglichen durchschnittes   
    sum = 0;
    validCount = 0;
    for (int i = 0; i < numMeasurements; i++) { 
      if (abs(duration[i] - mean) <= 0.1 * mean) { // Werte innerhalb 5% Abweichung
        sum += duration[i];
        validCount++;
      }
    }

    mean = sum / validCount;
    airSpeed = sqrt(1.4*286*(273.15 + temp))/10000; //siehe https://www.grc.nasa.gov/www/k-12/VirtualAero/BottleRocket/airplane/sound.html
    distance = (mean * airSpeed) / 2; // Distanz berechnen

} while(distance != distance); //Wenn distance NaN ist dann ist die abfrage true

Serial.println(distance);
return distance;
}