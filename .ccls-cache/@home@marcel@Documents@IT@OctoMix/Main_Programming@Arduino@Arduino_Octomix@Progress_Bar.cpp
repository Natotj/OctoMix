// the progress in percent
float progress = 0.0;
// Initialization of Progress_Bar 
bool initProgress = true;

void Progress_Bar(){
  // length of the crsMix array (subtracted by one to remove Null (string terminator)) 
  int lenArray = sizeof(crsMix) / sizeof(crsMix[0]) - 1; 

  switch (initProgress){
    // Initialization. This is only being executed as a setup for each progress bar 
    case 1:
      // check how many steps are going to be made -> later used for percentAdd 
      for (int i = 0; i < lenArray; i++){
        if (crsMix[i] != '0'){
          mixSteps++;
        }
      }
      // from 1 (true) to 0 (false) => no more Initialization 
      initProgress = false;
      break;

    case 0:
      // 100.0 (to get a float and not a rounded down int) divided by mixSteps * how often Progress_Bar() is being called in a step 
      // Outcome -> how much is added each time Progress_Bar() is being called 
      float percentAdd = 100.0 / (mixSteps * 5); 

      // progress addition 
      progress = progress + percentAdd;

      // sends the rounded progress to the display
      Display_Write_Number("MIXMIX.progressBar.val=", floor(progress));

      // resets the values for the next use of the progress bar 
      if (progress >= 99){
        progress = 0;
        initProgress = true;
        mixSteps = 0;
      }
      break;
  }
}
