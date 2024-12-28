// function that writes something from the arduino to the display  
// command = the command you want to trigger 
// value = value that you want to transmitt to the command 
// for example: "1" or "0" for on/off or  "23021602089900000000000000000000" for Cool Brezze

void Display_Write(String command, String value){
  char mark='"';

  displaySerial.print(mark);
  displaySerial.print(command);
  displaySerial.print(mark);
  displaySerial.print(mark);
  displaySerial.print(value);
  displaySerial.print(mark);
    displaySerial.write(0X0ff);
    displaySerial.write(0X0ff);
    displaySerial.write(0X0ff);
}
