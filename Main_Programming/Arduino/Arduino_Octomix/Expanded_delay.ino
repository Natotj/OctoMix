// function that takes in your desired delay & keeps otherthings (like the Display_Com()) upright
void Expanded_delay(int userDelay){

  for (int i = 0; i < userDelay; i += 100){
    Display_Com();
    delay(100);
  }
  // rest of the user delay
  delay(userDelay % 100);
}
