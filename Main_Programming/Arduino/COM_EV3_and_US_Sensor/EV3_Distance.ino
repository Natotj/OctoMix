float EV3_Distance(){
  const int numMeasurements = 150; //Anzahl an Messungen für den US-Sensor
  float duration[numMeasurements];
  float sum, mean, distance;
  int validCount;

  sum = 0;
  for(i=0; i<numMeasurements; i++) { //Für einen Mittelwert von 100 Werten
    digitalWrite(USONIC_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(USONIC_TRIG, LOW);

    duration[i] = pulseIn(USONIC_ECHO, HIGH); 
    sum += duration[i];
  }

  mean = sum / numMeasurements;
  sum = 0;
  validCount = 0;
  for (int i = 0; i < numMeasurements; i++) {
    if (abs(duration[i] - mean) <= 0.05 * mean) { // Werte innerhalb 50% Abweichung
      sum += duration[i];
      validCount++;
      }
  }

  mean = sum / validCount;
  distance = (mean * 0.0343) / 2; // Distanz berechnen
return distance;
}