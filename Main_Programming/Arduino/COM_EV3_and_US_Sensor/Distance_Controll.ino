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
    Display_Com();
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

    last_ist = ist; 
    
    delay(dt * 1000);
  }
  EV3_Com(EV3_STOP);
}