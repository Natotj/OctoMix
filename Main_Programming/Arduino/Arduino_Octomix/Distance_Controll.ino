void Distance_Controll(float setPoint) {
  //Funktion um den EV3 über das gewünschte Ventil zu fahren. setPoint gibt den gewünschten Abstand zwischen US-Sensor und EV3 an. deltaErlaubt steuert die zulässige abweichung.
// PID-Parameter
  float Kp = 1.0;
  float Ki = 0.1;
  float Kd = 0;

//Variablen für den Regler
  float is; // ist wert vom US-Sensor
  float error = -2000; // Fehler
  float out = 0; // Regler ausgabe
  float lastIs = 0; //vorheriger Messwert
  float deltaErlaubt = 0.2; //Erlaubte Abweichung der Positionierung in cm
  float dt = 0.0005; //Zeitintervall in sek
  
  bool ersterDurchlauf = true;

// Anteile vom Regler
  float proportional = 0;
  float integral = 0; 
  float differential = 0;


  while(abs(error) > deltaErlaubt){
    Display_Com();
    is = EV3_Distance();
    error = setPoint - is;

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
        if(out > 20){ // schnellstes Fahren
          EV3_Com(EV3_FW_F);
        }else if(out > 10){ // mittleres Fahren
          EV3_Com(EV3_FW_M);
        }else { // langsames Fahren
          EV3_Com(EV3_FW_S);
        }
      }else{
        if(out > 20){ // schnellstes Fahren
          EV3_Com(EV3_B_F);
        }else if(out > 10){ // mittleres Fahren
          EV3_Com(EV3_B_M);
        }else { // langsames Fahren
          EV3_Com(EV3_B_S);
        }
      }

    lastIs = is; 
    
    delay(dt * 1000);
  }
  EV3_Com(EV3_STOP);
}