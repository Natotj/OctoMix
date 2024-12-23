void Distance_Controll(float soll) {
  // PID-Parameter
  float Kp = 1.0;
  float Ki = 0.1;
  float Kd = 0;

  //Variablen für den Regler
  float ist;
  float error = -2000;
  float out = 0;
  float last_ist = 0; //vorheriger Messwert
  float delta_erlaubt = 0.5; //Erlaubte Abweichung der Positionierung in cm

  float dt = 0.001; //Zeitintervall in sek

  float proportional = 0;
  float integral = 0; 
  float differential = 0;

  bool erster_Durchlauf = true;

  while(abs(error) > delta_erlaubt){
    
    ist = EV3_Distance();
    error = soll - ist;

    if(erster_Durchlauf) { //Bei erstem Durchgang des Reglers 
      last_ist = ist;
      erster_Durchlauf = false;
    }

    proportional = Kp * error;
    integral += error * dt;
    integral = constrain(integral, -15, 15);
    differential = (ist - last_ist) / dt;

    out = proportional + (Ki * integral) - (Kd * differential);

    Serial.println(out);
    
    //übersetzen in EV3 Befehle
      if(out < 0){
        out = abs(out);
        if(out > 20){ // schnellstes Fahren
          EV3_Com(EV3_VOR_S);
        }else if(out > 10){ // mittleres Fahren
          EV3_Com(EV3_VOR_M);
        }else { // langsames Fahren
          EV3_Com(EV3_VOR_L);
        }
      }else{
        if(out > 20){ // schnellstes Fahren
          EV3_Com(EV3_ZUR_S);
        }else if(out > 10){ // mittleres Fahren
          EV3_Com(EV3_ZUR_M);
        }else { // langsames Fahren
          EV3_Com(EV3_ZUR_L);
        }
      }

    last_ist = ist;
/*
    Serial.print("soll: ");
    Serial.print(soll);
    Serial.print("  Ist: ");
    Serial.print(ist);
    Serial.print("  Output: ");*/
    
    
    delay(dt * 1000);
  }
  EV3_Com(EV3_STOPP);
}