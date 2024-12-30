int progress = 0;
int initProgress = 1;

void Progress_Bar(){
  // Initialization: 1 == True, 0 == False
  int lenArray = sizeof(crsMix) / sizeof(crsMix[0]); 
  int mixSteps;

  switch (initProgress){
    // Initialization. This is only being executed once as a setup for the rest 
    case 1:
      // check how many steps are going to be made -> later used for progress addition 
      for (int i = 0; i < lenArray; i++){
        if (crsMix[i] != 0){
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
      progress = progress + percentAdd;
      // convert to string for the Display_Write function & rounded for nextion
      String progressString = String(ceil(progress));

      Display_Write("MIXMIX.progressBar.val=", progressString);
      if (progress >= 100){
        progress = 0;
        initProgress = 1;
      }
      break;
  }
}
