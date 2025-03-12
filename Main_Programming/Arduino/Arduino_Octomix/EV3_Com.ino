  int EV3_COM[9]={0, 2, 5, 10, 20, 40, 80, 160, 255};
void EV3_Com(int command) {
  
//old values  int EV3_COM[11]={0, 2, 5, 10, 18, 40, 70, 110, 160, 212, 255};
  int EV3_COM[9]={0, 2, 5, 10, 20, 40, 80, 160, 255};
  /* Only for Testing the values
  delay(4000);
  int i;
  for(i=0; i < 11; i++) {
    analogWrite(LED, EV3_COM[i]);
    Serial.println(i);
    delay(4000);
  }
  */
  if(command>=0 && command <=10){
    analogWrite(LED, EV3_COM[command]);
      //printLine("EV3_Com_Command = ");
      //Serial.print(command);
  } else {
    analogWrite(LED, 0);
  }
}