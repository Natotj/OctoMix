void EV3_Com(int command) {
  
  int EV3_COM[11]={0, 2, 5, 10, 18, 40, 70, 110, 160, 200, 255};
  
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
      printLine("EV3_Com_Command = ");
      Serial.print(command);
  } else {
    analogWrite(LED, 0);
  }
}