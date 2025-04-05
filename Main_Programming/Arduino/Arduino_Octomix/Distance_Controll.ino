void Distance_Controll(float setPoint) {
  //Funktion um den EV3 über das gewünschte Ventil zu fahren. setPoint gibt den gewünschten Abstand zwischen US-Sensor und EV3 an. deltaErlaubt steuert die zulässige abweichung.
// PID-Parameter
  float Kp = 0.43*1.5;
  float Ki = 0.14*1.5;
  float Kd = 0.43*1.5;

//Variablen für den Regler
  float is; // ist wert vom US-Sensor
  float error = -2000; // Fehler
  float out = 0; // Regler ausgabe
  float lastIs = 0; //vorheriger Messwert
  float deltaErlaubt = 0.25; //Erlaubte Abweichung der Positionierung in cm
  float dt = 0.184; //mittelwert wenn EV3 in der Mitte steht
  int onSpot = 0; //Zähler damit der Regler nicht abbricht sobald zufällig eine passende Messung kommt
  
  bool ersterDurchlauf = true;

// Anteile vom Regler
  float proportional = 0;
  float integral = 0; 
  float differential = 0;


  //while(abs(error) > deltaErlaubt){
  while(onSpot < 10){ //erst wenn Regler noch 10 mal am richtigen platz geregelt hat geht es weiter
    Display_Com(); //um die kommunikation mit dem Display aufrecht zu erhalten
    is = EV3_Distance();
    error = setPoint - is;
    //Serial.println(error);
    if(abs(error) < deltaErlaubt) onSpot++; //wird immer hoch gesetzt wenn possition stimmt, verhindert zufällige gute Messungen

    if(ersterDurchlauf) { //Bei erstem Durchgang des Reglers 
      lastIs = is;
      ersterDurchlauf = false;
    }

    proportional = Kp * error;
    integral += error * dt;
    integral = constrain(integral, -15, 15);
    differential = (is - lastIs) / dt;

    out = proportional + (Ki * integral) - (Kd * differential);
    
    //übersetzen in EV3 Befehle
      if(out < 0){ 
        out = abs(out);
        if(out > 15){ // schnellstes Fahren
          EV3_Com(EV3_FW_F);
        }else if(out > 5){ // mittleres Fahren
          EV3_Com(EV3_FW_M);
        }else { // langsames Fahren
          EV3_Com(EV3_FW_S);
        }
      }else{
        if(out > 15){ // schnellstes Fahren
          EV3_Com(EV3_B_F);
        }else if(out > 5){ // mittleres Fahren
          EV3_Com(EV3_B_M);
        }else { // langsames Fahren
          EV3_Com(EV3_B_S);
        }
      }

    lastIs = is; 
  }
  EV3_Com(EV3_STOP);
  onSpot = 0;
}