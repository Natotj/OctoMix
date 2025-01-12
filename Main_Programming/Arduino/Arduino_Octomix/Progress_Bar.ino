// the progress in percent
int progress = 0;
// Initialization of Progress_Bar: 1 == True, 0 == False
int initProgress = 1;

void Progress_Bar(){
  // length of the crsMix array (subtracted by one to remove Null (string terminator)) 
  int lenArray = sizeof(crsMix) / sizeof(crsMix[0]) - 1; 
  // how many steps there are for the mixing of a cocktail
  int mixSteps;

  switch (initProgress){
    // Initialization. This is only being executed once as a setup 
    case 1:
      // check how many steps are going to be made -> later used for progress addition 
      for (int i = 0; i < lenArray; i++){
        if (crsMix[i] != '0'){
          mixSteps++;
        }
      }
      // no more init 
      initProgress--;
      break;

    case 0:
      // 100 divided by mixSteps * how often Progress_Bar() is being called in a step 
      // Outcome -> how much is added each time Progress_Bar() is being called 
      float percentAdd = 100 / (mixSteps * 5); 

      // progress
      progress = progress + ceil(percentAdd);

      // sends the rounded progress to the display
      Display_Write_Number("MIXMIX.progressBar.val=", progress);
      // resets the global values for the next use of the progress bar 
      if (progress >= 100){
        progress = 0;
        initProgress = 1;
      }
      break;
  }
}
